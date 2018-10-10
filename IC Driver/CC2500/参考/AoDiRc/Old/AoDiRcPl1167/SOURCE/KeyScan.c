#define VAR_KEY_SCAN_GLOBALS
#include "Include.h"

void f_KeayDelay(void)
{
	uchar i;
	for(i = 0; i < 15; i ++)
	{
		NOP();
	}
}

/*=========================================================
* 函 数 名: void f_ChangeKeyInf(unsigned long *KeyInfDeal)
* 功能描述: 获取按键按下信息
* 调用方法: f_ChangeKeyInf(&KeyInfDeal);
* 调用函数: 无
* 全局变量: 
* 输    入: KeyInfDeal 按键信息
* 返    回: 无
* 处理过程:
*  注   意：
* 修改日期	修改人		修改说明
* 2017-08-26		朱峰 			完成基本功能
=========================================================*/
void f_ChangeKeyInf(unsigned long *KeyInfDeal)
{
	(*KeyInfDeal) = NO_KEY;
	
	KEY_COM1 = false;
	KEY_COM2 = true;
	KEY_COM3 = true;
	KEY_COM4 = true;
	f_KeayDelay();
	if(!KEY_SEG1)
	{
		(*KeyInfDeal) |= KEY_SIG_1; // s20
	}
	
	KEY_COM1 = true;
	KEY_COM2 = false;
	KEY_COM3 = true;
	KEY_COM4 = true;
	f_KeayDelay();
	if(!KEY_SEG1)
	{
		(*KeyInfDeal) |= KEY_SIG_2; // s15
	}
	if(!KEY_SEG2)
	{
		(*KeyInfDeal) |= KEY_SIG_3; // s16
	}
	if(!KEY_SEG3)
	{
		(*KeyInfDeal) |= KEY_SIG_4; // s17
	}
	if(!KEY_SEG4)
	{
		(*KeyInfDeal) |= KEY_SIG_5; // s18
	}
	if(!KEY_SEG5)
	{
		(*KeyInfDeal) |= KEY_SIG_6; // s19
	}

	KEY_COM1 = true;
	KEY_COM2 = true;
	KEY_COM3 = false;
	KEY_COM4 = true;
	f_KeayDelay();
	if(!KEY_SEG1)
	{
		(*KeyInfDeal) |= KEY_SIG_7; // s10
	}
	if(!KEY_SEG2)
	{
		(*KeyInfDeal) |= KEY_SIG_8; // s11
	}
	if(!KEY_SEG3)
	{
		(*KeyInfDeal) |= KEY_SIG_9; // s12
	}
	if(!KEY_SEG4)
	{
		(*KeyInfDeal) |= KEY_SIG_10; // s13
	}
	if(!KEY_SEG5)
	{
		(*KeyInfDeal) |= KEY_SIG_11; // s14
	}

	KEY_COM1 = true;
	KEY_COM2 = true;
	KEY_COM3 = true;
	KEY_COM4 = false;
	f_KeayDelay();
	if(!KEY_SEG1)
	{
		(*KeyInfDeal) |= KEY_SIG_12; // s5
	}
	if(!KEY_SEG2)
	{
		(*KeyInfDeal) |= KEY_SIG_13; // s6
	}
	if(!KEY_SEG3)
	{
		(*KeyInfDeal) |= KEY_SIG_14; // s7
	}
	if(!KEY_SEG4)
	{
		(*KeyInfDeal) |= KEY_SIG_15; // s8
	}
	if(!KEY_SEG5)
	{
		(*KeyInfDeal) |= KEY_SIG_16; // s9
	}
	f_KeayDelay();
}

/*=========================================================
* 函 数 名: void f_ChangeKeyInf(unsigned long *KeyInfDeal)
* 功能描述: 获取按键按下信息
* 调用方法: f_ChangeKeyInf(&KeyInfDeal);
* 调用函数: 无
* 全局变量: 
* 输    入: KeyInfDeal 按键信息
* 返    回: 无
* 处理过程:
*  注   意：
* 修改日期	修改人		修改说明
* 2017-08-26		朱峰 			完成基本功能
=========================================================*/
void ReadKey(unsigned char *GetKeyState,unsigned char *ScanStep,unsigned int *KeyDelayTime,KEY_PRESSED_STATE Key_Get)
{	
	switch(*ScanStep)
	{
		case 0: 
		{
			*KeyDelayTime = 0;
			KeyScanInf.nKeyRealDownTm = 0;
			*GetKeyState = NO_KEY;
			(*ScanStep) = 1;
			break;
		}	
		case MAX_STEP://等待结束 
		{
			;
			break;
		}	
		default: 
		{	
			if(*KeyDelayTime >= GetTime((*ScanStep) - 1))
			{
				if(SetTimeInf((*ScanStep) - 1) != 0xff)
				{
					(*GetKeyState) |= SetTimeInf((*ScanStep) - 1);
					KeyScanInf.KeyPressName = Key_Get;
					KeyScanInf.bKeyPressFlag = true; //按键按下标志
					(*ScanStep) ++;
				}
				else
				{
					(*ScanStep) = MAX_STEP;
				}		
			}
			break;
		}
	}
}

/*=========================================================
* 函 数 名: void f_KeyScan(void)
* 功能描述: 按键扫描
* 调用方法: f_KeyScan();
* 调用函数: 无
* 全局变量: 
* 输    入: 无
* 返    回: 无
* 处理过程:
*  注   意：
* 修改日期	修改人		修改说明
* 2017-08-26		朱峰 			完成基本功能
=========================================================*/
void f_KeyScan(void)
{
	#define SIG_FUNCTION 0
	#define COM_FUNCTION 1
	unsigned char 	keyName;
	unsigned char 	U8Tmp;
	unsigned int	U16Tmp;
	static unsigned char nLastScanInf = 0;

	if(KeyScanInf.nKeyDownTm <= 65530)
	{
		KeyScanInf.nKeyDownTm++;
	}
	if(KeyScanInf.nNoKeyTm <= 65530)
	{
		KeyScanInf.nNoKeyTm++;
	}
	f_ChangeKeyInf(&KeyScanInf.nKeyInf);
	if((KeyScanInf.nKeyInf & KEY_ALL) == NO_KEY)//按键释放
	{
		if(KeyScanInf.nNoKeyTm >= KEY_DELAY_TIME)//释放去抖
		{
			//按键信息清除
			KeyScanInf.nKeyResultInf = NO_KEY;

			if(KeyScanInf.bKeyUsedFlag == false
			&& KeyScanInf.bKeyFirstRelse == false)//释放短按判断(前面键结果无使用)
			{
				KeyScanInf.nKeyResultInf |= PRESSED_RE;//短按释放
				KeyScanInf.bKeyFirstRelse = true;
			}
			//按键参数清零
			if(KeyScanInf.nKeyResultInf == NO_KEY)//释放信息已被清除
			{
				KeyScanInf.KeyPressName = KEY_FREE;
				KeyScanInf.nKeyStep = 0;
				KeyScanInf.bKeyPressFlag = false;
				KeyScanInf.bKeyUsedFlag = false;
				nLastScanInf = SIG_FUNCTION;
			}
		}
	}
	else 
	{
		bInSleepFlag = false;
		nKeyWakeTm = 0;	//进休眠时间计数
		
		KeyScanInf.nNoKeyTm = 0;
		KeyScanInf.bKeyFirstRelse = false;
		if(KeyScanInf.bKeyUsedFlag)//已经有按键响应
		{
			KeyScanInf.nKeyStep = MAX_STEP;//直接等待释放
			return;
		}
		
		for(keyName = 0; keyName < KEY_COM_NUMB; keyName ++)//组合按键扫描处理
		{
			if(((KeyScanInf.nKeyInf & KEY_ALL) == nTab_KeyHexDef[keyName])
			&& KeyScanInf.bKeyUsedFlag == false)
			{
				if(KeyScanInf.bKeyUsedFlag == false && nLastScanInf == SIG_FUNCTION)//由单键转组合
				{
					nLastScanInf = COM_FUNCTION;
					KeyScanInf.nKeyStep = 0;
				}
				
				ReadKey(
						&KeyScanInf.nKeyResultInf,
						&KeyScanInf.nKeyStep,
						&KeyScanInf.nKeyDownTm,
						keyName + 1
						);
				return;
			}
		}

		for(keyName  = SIG_BASE; keyName < SIG_BASE + KEY_SIG_NUMB; keyName ++)//单按键扫描处理
		{
			if(((KeyScanInf.nKeyInf & KEY_ALL) == nTab_KeyHexDef[keyName])
			&& KeyScanInf.bKeyUsedFlag == false)
			{
				if(KeyScanInf.bKeyUsedFlag == false && nLastScanInf == COM_FUNCTION)//由组合转单键
				{
					KeyScanInf.bKeyUsedFlag = true;//直接等待释放
					KeyScanInf.nKeyStep = MAX_STEP;//直接等待释放
				}
				nLastScanInf = SIG_FUNCTION;
				
				ReadKey(
						&KeyScanInf.nKeyResultInf,
						&KeyScanInf.nKeyStep,
						&KeyScanInf.nKeyDownTm,
						keyName + 1
						);
				return;
			}
		}

		/*if(KeyScanInf.nKeyInf && (~(KEY_TOTAL_COM)))//所有无效组合
		{
			KeyScanInf.bKeyFirstRelse = true;//无释放消息
		}*/

		//数据清除
		KeyScanInf.nKeyStep = MAX_STEP;//直接等待释放
	}
}
