/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : KeyDriver.c
  �� �� ��   : ����
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��10��
  ����޸�   :
  ��������   : ͨ�ð�����������ģ��,ͳһ����������Ϣ����Ӧ�ò㴦��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��10��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

  2.��    ��   : 2018��4��16��
    ��    ��   : Ǯ�پ�
    �޸�����   : 1�����Ӱ�����ס�޳�����
    		  2������ǿ�ƶ�����������֧��

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
 #include "KeyDriver.h"
 #include "SubFunction.h"
 #include "TimeFlag.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/
//����������
#if (KEY_DRIVER_INDE_KEY_NUM > 0)
	KEY_DRIVER_INDE_KEY keyDriverIndeKey[KEY_DRIVER_INDE_KEY_NUM];
#endif

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/

/*****************************************************************************
 �� �� ��: uchar f_IsSingleKey(ulong KeyName)
 ��������: �жϵ�ǰ�����Ƿ�Ϊ����
 �������:
 �� �� ֵ: 
 ע     ��: Ŀǰǿ��Ϊ32λ����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��14��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_IsSingleKey(ulong KeyName)
{
	uchar i;
	uchar enKeyCnt = 0;
	for (i = 0; i < 32; i++)
	{
	    if ((KeyName>>i) & 0x01)
	    {
			if ( ++enKeyCnt >= 2)
			{
				return false;
			}
	    }
    }

    return true;
}

/*****************************************************************************
 �� �� ��: f_IndependentKeyDeal
 ��������  : ��������������ʹ����������£���Ҫ�ֱ������ͬ����������Ӧ��
 			�����������ͬʱ����״̬ʱ�����ⷢ(���10ms)
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��14��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
#if (KEY_DRIVER_INDE_KEY_NUM > 0)
void f_IndependentKeyDeal(KEY_DRIVER        *pKeyDriver)
{
	uchar i;
	uchar stateIndex;

	//������������
	for (i = 0; i < KEY_DRIVER_INDE_KEY_NUM; i++)
	{
		keyDriverIndeKey[i].newName = pKeyDriver->data.newName & Tab_IndeKeyValue[i];
		f_AddU16Data(&(keyDriverIndeKey[i].pressTm));//����ʱ���ۼ�
	
		switch (keyDriverIndeKey[i].dealStep)
		{
			case KEY_DEAL_IDLE://��������״̬
				keyDriverIndeKey[i].pressTm = 0;

				//�а�������
				if (KEY_DRIVER_NO_KEY != keyDriverIndeKey[i].newName)
				{
					keyDriverIndeKey[i].dealStep = KEY_DEAL_PRESS;
					keyDriverIndeKey[i].state |= KEY_PRESSED;//����������Ϣ
				}
				keyDriverIndeKey[i].name = keyDriverIndeKey[i].newName;
				break;

			case KEY_DEAL_PRESS://��������״̬
				#ifdef KEY_DONE_OVER
					//�����ͷŻ����Ѿ�����
					if (KEY_DRIVER_NO_KEY == keyDriverIndeKey[i].newName || f_GetKeyDealDone(keyDriverIndeKey[i].name))
					{
						keyDriverIndeKey[i].pressTm = 0;
						keyDriverIndeKey[i].dealStep = KEY_DEAL_WATE_RELEASE;
					}
				#else
					//�����ͷ�
					if (KEY_DRIVER_NO_KEY == keyDriverIndeKey[i].newName)
					{
						keyDriverIndeKey[i].pressTm = 0;
						keyDriverIndeKey[i].dealStep = KEY_DEAL_WATE_RELEASE;
					}
					#endif
				break;

			case KEY_DEAL_WATE_RELEASE://�����ȴ��ͷ�״̬
				if (KEY_DRIVER_NO_KEY == keyDriverIndeKey[i].newName)
				{
					keyDriverIndeKey[i].dealStep = KEY_DEAL_IDLE;
					if (!f_GetKeyDealDone(keyDriverIndeKey[i].name))
					{
						keyDriverIndeKey[i].state = 0; //�������״̬
						keyDriverIndeKey[i].state |= KEY_RELEASE;
					}
				}
				break;

			default:
				keyDriverIndeKey[i].name = KEY_DRIVER_NO_KEY;
				keyDriverIndeKey[i].newName = KEY_DRIVER_NO_KEY;
				keyDriverIndeKey[i].dealStep = KEY_DEAL_IDLE;
				break;
		}

		//�Զ���״̬����
		for (stateIndex = 0; (keyDriverIndeKey[i].pressTm > 0) && (f_SetKeyTimeState(stateIndex) != KEY_STATE_RESERVE); stateIndex++)
		{
			//����״ֻ̬����һ��
			if (keyDriverIndeKey[i].pressTm == f_GetKeyStateTime(stateIndex))
			{
				//�ȴ��ͷ�ʱ��ֻ��������״̬
				if (KEY_DEAL_WATE_RELEASE ==keyDriverIndeKey[i].dealStep
				&& KEY_LOCKED != f_SetKeyTimeState(stateIndex))
				{
					break;
				}

				keyDriverIndeKey[i].state |= f_SetKeyTimeState(stateIndex);
				break;
			}
		}

		//��ǰ��������״̬����-��������
		if (KEY_STATE_IDLE != keyDriverIndeKey[i].state)
		{
			//ͨ��ͨ�õ����ݽӿ������ṩ��Ϣ
			pKeyDriver->data.name = keyDriverIndeKey[i].name;
			pKeyDriver->data.state = keyDriverIndeKey[i].state;

			keyDriverIndeKey[i].state = KEY_STATE_IDLE;
		}
	}			
}
#endif
 
/*****************************************************************************
 �� �� ��: void f_KeyDriverTimer(KeyDriver const *pKeyDriver)
 ��������: 
 �������: pKeyDriver����������ָ��
 �� �� ֵ: 
 ע     ��: ϵͳ10msʱ������
 
 �޸���ʷ:
  1.��    ��   : 2018��4��11��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_KeyDriverDeal(KEY_DRIVER       *pKeyDriver)
{
	uchar i;

	//ϵͳ10ms�ж�

	//ָ����Ч���жϣ��ж��Ƿ�ɹ�ע��
	if (NULL == pKeyDriver->pHardDriver || NULL == pKeyDriver->dealCallback)
	{
		return;	
	}

	//���������ȡ
	pKeyDriver->pHardDriver->GetKeys(pKeyDriver);
	
	//�������봦����ֹ������Ӱ��
	pKeyDriver->data.mask |= ~(pKeyDriver->data.getKeys);//һ����Ӧ�İ����ͷ�,��λmask�ָ�
	pKeyDriver->data.newName = pKeyDriver->data.getKeys & pKeyDriver->data.mask;

	f_AddU16Data(&(pKeyDriver->data.pressTm));//����ʱ���ۼ�
	switch (pKeyDriver->dealStep)
	{
		case KEY_DEAL_IDLE://��������״̬
			pKeyDriver->data.pressTm = 0;
			pKeyDriver->data.keyDone = 0;
			pKeyDriver->data.state = KEY_STATE_IDLE;
			pKeyDriver->flag.byte = 0;

			//�а�������
			if (KEY_DRIVER_NO_KEY != pKeyDriver->data.newName)
			{
				pKeyDriver->dealStep = KEY_DEAL_PRESS;
				pKeyDriver->data.state |= KEY_PRESSED;//����������Ϣ
			}
			pKeyDriver->data.name = pKeyDriver->data.newName;
			break;

		case KEY_DEAL_PRESS://��������״̬
			pKeyDriver->flag.bits.bHasKey = true;
			
			//�����仯�����¼�ⰴ��
			if (pKeyDriver->data.name != pKeyDriver->data.newName)
			{
				if (f_IsSingleKey(pKeyDriver->data.name) 
				&& KEY_DRIVER_NO_KEY != pKeyDriver->data.newName)
				{
					//�����仯�����¼��(�µ����)
					pKeyDriver->dealStep = KEY_DEAL_IDLE;
				}
				else
				{
					//��ϼ����ȵȴ��ͷ�/ֱ���ͷ�
					pKeyDriver->dealStep = KEY_DEAL_WATE_RELEASE;
				}
			}

			#ifdef KEY_DONE_OVER
				//�����Ѵ�����ȴ��ͷ�,����������״̬
				if (f_GetKeyDealDone(pKeyDriver->data.name))
				{
					pKeyDriver->dealStep = KEY_DEAL_WATE_RELEASE;
				}
			#endif
			break;

		case KEY_DEAL_WATE_RELEASE://�����ȴ��ͷ�״̬
			//�ȴ�ȫ�������ͷ�,�ͷ�ʱ�����ͷ�״̬,�����Ѵ��������ͷ���Ϣ
			if (KEY_DRIVER_NO_KEY == pKeyDriver->data.newName)
			{
				pKeyDriver->dealStep = KEY_DEAL_IDLE;

				if (!f_GetKeyDealDone(pKeyDriver->data.name))
				{
					pKeyDriver->data.state = 0; //�������״̬
					pKeyDriver->data.state |= KEY_RELEASE;
				}
			}
			else
			{
				//Ϊ�����仯ʱ�����¼���°����Ƿ���ܿ���
				if (pKeyDriver->data.name != pKeyDriver->data.newName)
				{
					pKeyDriver->data.pressTm = 0;
					pKeyDriver->data.name = pKeyDriver->data.newName;
				}
			}
			break;

		default:
			pKeyDriver->data.name = KEY_DRIVER_NO_KEY;
			pKeyDriver->data.newName = KEY_DRIVER_NO_KEY;
			pKeyDriver->dealStep = KEY_DEAL_IDLE;
			break;
	}

	//�Զ���״̬����
	for (i = 0; (pKeyDriver->data.pressTm > 0) && (f_SetKeyTimeState(i) != KEY_STATE_RESERVE); i++)
	{
		//����״ֻ̬����һ��
		if (pKeyDriver->data.pressTm == f_GetKeyStateTime(i))
		{
			//�ȴ��ͷ�ʱ��ֻ��������״̬
			if (KEY_DEAL_WATE_RELEASE == pKeyDriver->dealStep
			&& KEY_LOCKED != f_SetKeyTimeState(i))
			{
				break;
			}
			
			pKeyDriver->data.state |= f_SetKeyTimeState(i);
			break;
		}
	}
	
	//����������ȡ
	#if (KEY_DRIVER_INDE_KEY_NUM > 0)
		f_IndependentKeyDeal(pKeyDriver);
	#endif

	//��������״̬����
	if (f_IsKeyState(KEY_LOCKED))
	{
		//��Ϊ��ס���������Ƴ���⣬�������ָ�ʱ���Զ�������ӽ�����
		f_RemoveKey(pKeyDriver->data.getKeys);
		f_SetKeyDealDone();
	}
	
	//����������
	pKeyDriver->dealCallback(pKeyDriver);

	//������������
	if (f_GetKeyDealDone(pKeyDriver->data.name))
	{
		pKeyDriver->data.state = KEY_STATE_IDLE;
	}
}

/*****************************************************************************
 �� �� ��: void f_KeyDriverInit( KeyDriver const *pKeyDriver,
							KeyHardwareDriver const *pKeyDriverHardware, 
							KeyDriverCallback const pKeyDealFunc)
 ��������: 
 �������: pKeyDriver:��������ָ��; 
 		   pKeyDriverHardware����������Ӳ����ָ��; 
 		   pKeyDealFunc:��������ص�����
 �� �� ֵ: 
 ע     ��: ��ʼ��ע�����һ��
 
 �޸���ʷ:
  1.��    ��   : 2018��4��11��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_KeyDriverInit( KEY_DRIVER *pKeyDriver,
							const KEY_HARDWARE_DRIVER *pKeyDriverHardware, 
							const KeyDriverCallback pKeyDealFunc)
{
	f_Memset(pKeyDriver, 0, sizeof(KEY_DRIVER));
	pKeyDriver->data.mask = KEY_DRIVER_ALL_KEY;
	pKeyDriver->pHardDriver = pKeyDriverHardware;
	pKeyDriver->dealCallback = pKeyDealFunc;
}


