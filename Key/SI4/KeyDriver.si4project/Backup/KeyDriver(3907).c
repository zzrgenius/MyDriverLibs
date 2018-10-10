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

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
 #include "KeyDriver.h"

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

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/

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
	
	if (NULL == pKeyDriver->pHardDriver || NULL == pKeyDriver->dealCallback)
	{
		return;	
	}

	//���������ȡ
	pKeyDriver->pHardDriver->GetKeys(pKeyDriver);

	switch (pKeyDriver->dealStep)
	{
		case KEY_DEAL_IDLE://��������״̬
			pKeyDriver->data.pressTm = 0;
			pKeyDriver->data.name = KEY_DRIVER_NO_KEY;

			//�а�������
			if (KEY_DRIVER_NO_KEY != pKeyDriver->data.newName)
			{
				pKeyDriver->dealStep = KEY_DEAL_PRESS;
				pKeyDriver->data.state |= KEY_PRESSED;//����������Ϣ
			}
			pKeyDriver->data.name = pKeyDriver->data.newName;
			
			break;

		case KEY_DEAL_PRESS://��������״̬
			pKeyDriver->flag.bit.bHasKey = true;
			
			if (pKeyDriver->data.pressTm < 0xffff)//������ͨ�ú�������
			{
				pKeyDriver->data.pressTm ++;
			}
		
			if (pKeyDriver->flag.bit.bDealDone)//��ǰ�����İ�����Ϣ�Ѵ���,ֱ�ӵȴ��ͷ�
			{
				pKeyDriver->dealStep = KEY_DEAL_WATE_RELEASE;
			}

			//�Զ���״̬����
			for (i = 0; ; i++)
			{
				if (SetTimeInf(i) == 0xff)
				{
					break;
				}

				//����״ֻ̬����һ��
				if (pKeyDriver->data.pressTm == GetTime(i))
				{
					pKeyDriver->data.state |= SetTimeInf(i);
					break;
				}
			}
			break;

		case KEY_DEAL_WATE_RELEASE://�����ȴ��ͷ�״̬
			//�ȴ�ȫ�������ͷ�,�ͷ�ʱ�����ͷ�״̬,�����Ѵ��������ͷ���Ϣ
			if (KEY_DRIVER_NO_KEY == pKeyDriver->data.newName)
			{
				pKeyDriver->dealStep = KEY_DEAL_IDLE;

				if (!pKeyDriver->flag.bit.bDealDone)
				{
					pKeyDriver->data.state |= KEY_RELEASE;
				}
			}
			break;

		default:
			pKeyDriver->data.name = KEY_DRIVER_NO_KEY;
			pKeyDriver->data.newName = KEY_DRIVER_NO_KEY;
			pKeyDriver->dealStep = KEY_DEAL_IDLE;
			break;
	}

	//����������
	pKeyDriver->dealCallback(pKeyDriver);

	//������������
	pKeyDriver->data.state = KEY_STATE_IDLE;
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
							KEY_HARDWARE_DRIVER const *pKeyDriverHardware, 
							KeyDriverCallback const pKeyDealFunc)
{
	//f_MemSet(pKeyDriver, 0, sizeof(KEY_DRIVER));
	pKeyDriver->pHardDriver = pKeyDriverHardware;
	pKeyDriver->dealCallback = pKeyDealFunc;
}

