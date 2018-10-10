/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : KeyDeal.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��12��
  ����޸�   :
  ��������   : ��������Ӧ�ô������ݲ�ͬ��Ŀ�����Ӧ����״̬
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "HeadInclude.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                       *
 *----------------------------------------------*/
extern const KEY_HARDWARE_DRIVER keyHardware;

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                         *
 *----------------------------------------------*/
KEY_DRIVER keyDriver;

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
 �� �� ��: f_KeyDeal
 ��������  : ����������
 �������: ��
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��12��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_KeyDeal(KEY_DRIVER *pKeyDriver)
{
	switch(f_GetKeyName())
	{
		case KEY_SIGLE_HIP://�β�
			if (f_IsKeyState(KEY_RELEASE))
			{
				//���ú����ͷ���Ϣ����
				f_SetKeyDealDone();

				functionInfo.keyCode = 0x50;
			}
			else if (f_IsKeyState(KEY_PRESS_3S))
			{
				//���ú����ͷ���Ϣ����
				f_SetKeyDealDone();

				if (STATE_ON == funcSit.sitSwitch.state)//����Ϊǿ��
				{
					functionInfo.keyCode = 0x51;
				}
				else //����Ϊ����Խ�(��������)
				{
					functionInfo.keyCode = 0x90;//�Զ��尴����
				}
			}
			break;
			
		case KEY_SIGLE_FEMAL:
			if (f_IsKeyState(KEY_RELEASE))
			{
				//���ú����ͷ���Ϣ����
				f_SetKeyDealDone();

				functionInfo.keyCode = 0x52;
			}
			else if (f_IsKeyState(KEY_PRESS_3S))
			{
				//���ú����ͷ���Ϣ����
				f_SetKeyDealDone();

				functionInfo.keyCode = 0x53;
			}
			break;

		case KEY_SIGLE_STOP:
			if (f_IsKeyState(KEY_RELEASE))
			{
				//���ú����ͷ���Ϣ����
				f_SetKeyDealDone();

				if (SYS_STATE_STANDBY == systemInfo.sysState)
				{
					functionInfo.keyCode = 0x60; //����
				}
 				else 
				{
					functionInfo.keyCode = 0x76; //ֹͣ
				}
			}
			else if (f_IsKeyState(KEY_PRESS_3S))
			{
				if (SYS_STATE_RUN == systemInfo.sysState)
				{
					//���ú����ͷ���Ϣ����
					f_SetKeyDealDone();
					functionInfo.keyCode = 0x61; //�ػ�
				}
			}
			break;
			
		case KEY_COMM_SIT://ģ������
			if (f_IsKeyState(KEY_PRESSED))
			{
				//���ú����ͷ���Ϣ����
				f_SetKeyDealDone();
				
				functionInfo.keyCode = 0x91; //������
			}
			else if (f_IsKeyState(KEY_PRESS_3S))
			{
				if (SYS_STATE_RUN == systemInfo.sysState)
				{
					//���ú����ͷ���Ϣ����
					f_SetKeyDealDone();
					
					functionInfo.keyCode = 0x91; //������
					funcSit.bFourceSit = true; //ģ��������
				}
			}
			break;

		case KEY_COMM_INTO_AGEING://�ϻ�
			if (f_IsKeyState(KEY_PRESS_3S))
			{
				if (SYS_STATE_RUN == systemInfo.sysState 
				&& funcSit.bFourceSit) //������ģ������
				{
					//���ú����ͷ���Ϣ����
					f_SetKeyDealDone();
					
					functionInfo.keyCode = 0x92; //�ϻ�����
				}
			}
			break;

		default:
			break;
	} 
}

/*****************************************************************************
 �� �� ��: f_KeyDealInit
 ��������  : ���������ܴ����ʼ��
 �������: ��
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��12��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_KeyDealInit(void)
{
    f_KeyDriverInit(&keyDriver, &keyHardware, f_KeyDeal);
}


