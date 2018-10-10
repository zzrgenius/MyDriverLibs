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
 #define KEY_DRIVER_NO_KEY 0

/*****************************************************************************
 �� �� ��: void f_KeyDriverTimer(   KeyDriver const *pKeyDriver)
 ��������: 
 �������: ��������ָ��
 �� �� ֵ: 
 ע     ��: ϵͳ10msʱ������
 
 �޸���ʷ:
  1.��    ��   : 2018��4��11��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_KeyDriverDeal(   KeyDriver const *pKeyDriver)
{
	uchar i;
	//���������ȡ
	if (NULL == pKeyDriver->pHardDriver)
	{
		return;	
	}
	pKeyDriver->pHardDriver(pKeyDriver);

	switch (pKeyDriver->keyDealStep)
	{
		case KEY_DEAL_IDLE://��������״̬
			pKeyDriver->keyData.keyPressTm = 0;
			pKeyDriver->keyData.keyName = KEY_DRIVER_NO_KEY;

			//�а�������
			if (KEY_DRIVER_NO_KEY != pKeyDriver->keyData.newKeyName)
			{
				pKeyDriver->keyDealStep = KEY_DEAL_PRESS;
				pKeyDriver->keyData.keyState |= KEY_PRESSED;//����������Ϣ
			}
			pKeyDriver->keyData.keyName = pKeyDriver->keyData.newKeyName;
			
			break;

		case KEY_DEAL_PRESS://��������״̬
			pKeyDriver->keyFlag.bit.bHasKey = true;
			
			if (pKeyDriver->keyData.keyPressTm < 0xffff)//������ͨ�ú�������
			{
				pKeyDriver->keyData.keyPressTm ++;
			}
		
			if (pKeyDriver->keyFlag.bit.bKeyDeal)//��ǰ�����İ�����Ϣ�Ѵ���,ֱ�ӵȴ��ͷ�
			{
				pKeyDriver->keyDealStep = KEY_DEAL_WATE_RELEASE;
			}

			//�Զ���״̬����
			for (i = 0; ; i++)
			{
				if (SetTimeInf(i) == 0xff)
				{
					break;
				}

				//����״ֻ̬����һ��
				if (pKeyDriver->keyData.keyPressTm == GetTime(i))
				{
					pKeyDriver->keyData.keyState |= SetTimeInf(i);
					break;
				}
			}

			break;

		case KEY_DEAL_WATE_RELEASE://�����ȴ��ͷ�״̬
			//�ȴ�ȫ�������ͷ�,�ͷ�ʱ�����ͷ�״̬,�����Ѵ��������ͷ���Ϣ
			if (KEY_DRIVER_NO_KEY == pKeyDriver->keyData.newKeyName)
			{
				pKeyDriver->keyDealStep = KEY_DEAL_IDLE;

				if (!pKeyDriver->keyFlag.bit.bKeyDeal)
				{
					pKeyDriver->keyData.keyState |= KEY_RELEASE;
				}
			}
			break;

		default:
			pKeyDriver->keyData.keyName = KEY_DRIVER_NO_KEY;
			pKeyDriver->keyData.newKeyName = KEY_DRIVER_NO_KEY;
			pKeyDriver->keyDealStep = KEY_DEAL_IDLE;
			break;
	}

	//����������

	//������������
	pKeyDriver->keyData.keyState = KEY_IDLE;
}


/*****************************************************************************
 �� �� ��: f_test
 ��������: 
 �������: ��
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��11��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
UINT32_T  f_test( # )
{
    #
}

