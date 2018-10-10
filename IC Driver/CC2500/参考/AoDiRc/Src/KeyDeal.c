/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : KeyDeal.c
  �� �� ��   : V1.0
  ��    ��   : zhufeng
  ��������   : 2018��4��27��
  ����޸�   :
  ��������   : ���������ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����   : �����ļ�

******************************************************************************/
#define VAR_KEY_DEAL_GLOBALS
#include "Include.h"
/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/

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
 �� �� ��: f_pKeyDeal
 ��������  : ��������
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pKeyDeal(void)
{
	switch(KeyScanInf.KeyPressName)
	{
		case KEY_SIGNAL_PRESS_1:// s20
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x15;	//-����
				if(SysInf.ValveGear > 0)	//ˮѹ����
				{
					SysInf.ValveGear --;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_2:// s15
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x11;	//��Ȧ
			}
			break;
		}
		case KEY_SIGNAL_PRESS_3:// s16
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x14;	//+����
				if(SysInf.ValveGear < 3)
				{
					SysInf.ValveGear ++;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_4:// s17
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x13;	//����
				if(SysInf.NozzleGear < 7)
				{
					SysInf.NozzleGear ++;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_5:// s18
		{
			if(KeyScanInf.nKeyResultInf & PRESSED_RE)//�̰�����
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x16;	//ֹͣ
			}
			else if(KeyScanInf.nKeyResultInf & PRESSED_2S)//����
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x17;	//���ػ�
			}
			break;
		}
		case KEY_SIGNAL_PRESS_6:// s19
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x12;	//ǰ��
				if(SysInf.NozzleGear > 0)
				{
					SysInf.NozzleGear --;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_7:// s10
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x0d;	//ҹ��
			}
			break;
		}
		case KEY_SIGNAL_PRESS_8:// s11
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x02;	//��ϴ
			}
			break;
		}
		case KEY_SIGNAL_PRESS_9:// s12
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x03;	//��ϴ
			}
			break;
		}
		case KEY_SIGNAL_PRESS_10:// s13
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x05;	//���
			}
			break;
		}
		case KEY_SIGNAL_PRESS_11:// s14
		{
			if(KeyScanInf.nKeyResultInf & PRESSED_RE)//�̰�����
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x10;	//����
			}
			else if(KeyScanInf.nKeyResultInf & PRESSED_2S)//����
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x19;	//������ֵ����
			}
			break;
		}
		case KEY_SIGNAL_PRESS_12:// s5
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x06;	//ˮ��
				SysInf.TempOpt = WATER_TEMP;	//ѡ��ˮ��
				if(SysInf.WaterTempGear < 3)
				{
					SysInf.WaterTempGear ++;
				}
				else
				{
					SysInf.WaterTempGear = 0;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_13:// s6
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x08;	//����
				SysInf.TempOpt = DRY_TEMP;//ѡ�����
				if(SysInf.DryTempGear < 3)
				{
					SysInf.DryTempGear ++;
				}
				else
				{
					SysInf.DryTempGear = 0;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_14:// s7
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//�̰�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x07;	//����
				SysInf.TempOpt = SEAT_TEMP;//ѡ������
				if(SysInf.SeatTempGear < 3)
				{
					SysInf.SeatTempGear ++;
				}
				else
				{
					SysInf.SeatTempGear = 0;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_15:// s8
		{
			if(KeyScanInf.nKeyResultInf & PRESSED_RE)//�ͷ�
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x09;//���Ȱ�Ħ
			}
			else if(KeyScanInf.nKeyResultInf & PRESSED_2S)
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x0a;//ǿ����Ħ
			}
			break;
		}
		case KEY_SIGNAL_PRESS_16:// s9
		{
			if(KeyScanInf.nKeyResultInf & PRESSED_RE)//�̰�����
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x0e;	//��ˮ
			}
			else if(KeyScanInf.nKeyResultInf & PRESSED_2S)
			{
				KeyScanInf.bKeyUsedFlag = true;
				//SendInf.SendStart = true;
				SysInf.RfSendFlag = true;
				SysInf.KeyNum = 0x18;//��ˮʱ�����
			}
			break;
		}
		default:
		{
			KeyScanInf.nKeyResultInf = NO_KEY;
			break;
		}
	}
	KeyScanInf.nKeyResultInf = NO_KEY;	
}
