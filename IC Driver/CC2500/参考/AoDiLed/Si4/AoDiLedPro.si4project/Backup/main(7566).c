 /* =========================================================
* 文 件 名: Main.c
* 版    权: 
* 功能描述: 主函数
* 版本信息: V1.0 
========================================================= */
#define VAR_MAIN_GLOBALS
#include "Include.h"
/*=========================================================
* 功能说明:主函数
* 创建时间:2017-06-02 朱峰
* 版本信息:V1.0
=========================================================*/
void main(void)
{
	f_Delay(3000);
	_DI();
	f_pCpuInit();
	f_pLedInit();
	f_pUart1Init(UART1_BAUT_RATE);
	Cc2500Inf.RF_Channel[0] = 6;
	Cc2500Inf.RF_Channel[1] = 66;
	Cc2500Inf.RF_Channel[2] = 126;
	Cc2500Inf.RF_Channel[3] = 186;
//	PL1167_Init();
	f_pInitDataEeprom();
	//f_Cc2500Init();
	_EI();
	while (1)
	{
		f_pCpuFeedDog();
		f_DealRXD();//RF接收处理201705
//		f_RfRecDeal();
		f_pUart1SendDeal(&machineInf);
		f_pUart1ReceDeal(&machineInf);
		if(t1msFlag)
		{
			t1msFlag = 0;
			if(tTime.t10msTask == 0)
			{
				f_pUart1TimeCnt();
			}
			tTime.t10msTask++;
			if(tTime.t10msTask>9)
			{
				tTime.t10msTask = 0;
			}
		}
		if(t10msFlag)
		{
			t10msFlag = 0;
			if(tTime.t100msTask == 0)
			{
				f_pLedDeal(&machineInf);
				f_pLedDriveDeal();//LED底层驱动
			}
			else if(tTime.t100msTask == 1)
			{
				f_pWriteOneDataEeprom();	//EEPROM写入数据
			}
			tTime.t100msTask++;
			if(tTime.t100msTask>9)
			{
				tTime.t100msTask = 0;
			}
		}
		if(t55msFlag)
		{
			//f_FreqDeal();
			Cc2500Inf.RF_Channel_Index++;
			if(Cc2500Inf.RF_Channel_Index > 3)
			{
				Cc2500Inf.RF_Channel_Index = 0;
			}
 			SetCC2500_ChannelNumber(Cc2500Inf.RF_Channel[Cc2500Inf.RF_Channel_Index]);
 			f_RxCC2500();
			t55msFlag = 0;
		}
		if(t1sFlag)
		{
			t1sFlag = 0; 
			tTime.time1sCnt++; 
			if(tTime.time1sCnt > 0)
			{
				tTime.time1sCnt = 0;
			}
//			AddCharData(&Cc2500Inf.nCC2500Time1);
//			AddIntData(&Cc2500Inf.nCC2500Time2);
			if(LedInf.DryDisCnt > 0)
			{
				LedInf.DryDisCnt --;
			}
			
//			if(temp ==0)
//			{
//				temp = 1;
//				LedWaterBIcon = true;
//			}
//			else
//			{
//				temp = 0;
//				LedWaterBIcon = false;
//			}
		}   
	}
}