#define VAR_KEY_DEAL_GLOBALS
#include "Include.h"

/*=========================================================
* 功能描述:  按键处理
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_KeyDeal(void)
{
	switch(KeyScanInf.KeyPressName)
	{
		case KEY_SIGNAL_PRESS_1:// s20
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x15;	//-按键
				if(SysInf.ValveGear > 0)	//水压调节
				{
					SysInf.ValveGear --;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_2:// s15
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x11;	//翻圈
			}
			break;
		}
		case KEY_SIGNAL_PRESS_3:// s16
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x14;	//+按键
				if(SysInf.ValveGear < 3)
				{
					SysInf.ValveGear ++;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_4:// s17
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x13;	//后移
				if(SysInf.NozzleGear < 7)
				{
					SysInf.NozzleGear ++;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_5:// s18
		{
			/*if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SysInf.RfSendCnt = 1;
				SysInf.KeyNum = 0x16;	//停止
			}*/
			if(KeyScanInf.nKeyResultInf & PRESSED_RE)//短按松手
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x16;	//停止
			}
			else if(KeyScanInf.nKeyResultInf & PRESSED_2S)//长按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x17;	//开关机
			}
			break;
		}
		case KEY_SIGNAL_PRESS_6:// s19
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x12;	//前移
				if(SysInf.NozzleGear > 0)
				{
					SysInf.NozzleGear --;
				}
			}
			break;
		}
		case KEY_SIGNAL_PRESS_7:// s10
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x0d;	//夜灯
			}
			break;
		}
		case KEY_SIGNAL_PRESS_8:// s11
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x02;	//臀洗
			}
			break;
		}
		case KEY_SIGNAL_PRESS_9:// s12
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x03;	//妇洗
			}
			break;
		}
		case KEY_SIGNAL_PRESS_10:// s13
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x05;	//烘干
			}
			break;
		}
		case KEY_SIGNAL_PRESS_11:// s14
		{
			if(KeyScanInf.nKeyResultInf & PRESSED_RE)//短按松手
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x10;	//翻盖
			}
			else if(KeyScanInf.nKeyResultInf & PRESSED_2S)//长按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x19;	//翻盖力值调整
			}
			break;
		}
		case KEY_SIGNAL_PRESS_12:// s5
		{
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x06;	//水温
				SysInf.TempOpt = WATER_TEMP;	//选择水温
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
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x08;	//风温
				SysInf.TempOpt = DRY_TEMP;//选择风温
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
			if(KeyScanInf.nKeyResultInf & PRESSED)//短按
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x07;	//座温
				SysInf.TempOpt = SEAT_TEMP;//选择座温
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
			if(KeyScanInf.nKeyResultInf & PRESSED_RE)//释放
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x09;//冷热按摩
			}
			else if(KeyScanInf.nKeyResultInf & PRESSED_2S)
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x0a;//强弱按摩
			}
			break;
		}
		case KEY_SIGNAL_PRESS_16:// s9
		{
			if(KeyScanInf.nKeyResultInf & PRESSED_RE)//短按松手
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x0e;	//冲水
			}
			else if(KeyScanInf.nKeyResultInf & PRESSED_2S)
			{
				KeyScanInf.bKeyUsedFlag = true;
				SendInf.SendStart = true;
				SysInf.KeyNum = 0x18;//冲水时间调整
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
