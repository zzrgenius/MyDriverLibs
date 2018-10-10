#define VAR_RF_GLOBALS
#include "Include.h"

byte_def tComState;
#define bReceiveOverFlag			tComState.m_bit.b0	//接收完成标志
#define bReceiveFinishFlag			tComState.m_bit.b1	//接收成功标志
#define bSendFlag					tComState.m_bit.b2	//发送标志
#define bWaitReceiveFlag			tComState.m_bit.b3

uchar sendNum;
/*=========================================================
* 功能描述: 累加和
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar f_AddTotalNum(uchar *nBuff,uchar nEndNo)
{
	uchar i,nTotalSum;
	nTotalSum = 0;
	for(i = 0; i < nEndNo; i ++)
	{
		nTotalSum += nBuff[i];
	}
	return nTotalSum;
}

/*=========================================================
* 功能描述: 数组赋值
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_MemSetData(uchar *nBuff,uchar nSetData,uchar nEndNo)
{
	uchar i;
	for(i = 0; i < nEndNo; i ++)
	{
		nBuff[i] = nSetData;
	}
}

/*=========================================================
* 功能描述: 开始发送数据 每隔50ms（即一定时间）调用一次
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_StartDataSend(void)
{	
	if(bSendFlag == true)																						//发送数据
	{      
		LED = 0;
	  	f_SendPacket(&ucCOMBuf[0], ucCOMBuf[0]+1);

	  	SetCC2500_ChannelNumber(Cc2500Inf.RF_Channel[Cc2500Inf.RF_Channel_Index]);
		Cc2500Inf.RF_ChNum++;
		if(Cc2500Inf.RF_ChNum > 4)
		{
			Cc2500Inf.RF_ChNum = 0;
			Cc2500Inf.RF_Channel_Index ++;
			if(Cc2500Inf.RF_Channel_Index > 3)
			{ 
				Cc2500Inf.RF_Channel_Index = 0;
				Cc2500Inf.RF_CrcNum ++;
				if(Cc2500Inf.RF_CrcNum > 2)
				{
					Cc2500Inf.RF_CrcNum = 0;
					bSendFlag = false;
   					LED = 1;
				}
			}
		}



	  	
//		Cc2500Inf.RF_Channel_Index ++;
//		if(Cc2500Inf.RF_Channel_Index > 3)
//		{
//			Cc2500Inf.RF_Channel_Index = 0;
//			Cc2500Inf.RF_ChNum++;
//			if(Cc2500Inf.RF_ChNum > 4)
//			{
//				Cc2500Inf.RF_ChNum = 0;
//				bSendFlag = false;
//   				LED = 1;
//			}
//		}
  	}
}

/*=========================================================
* 函 数 名: f_GetSendBuff()
* 功能描述: 获取发送缓冲
* 调用方法: f_GetSendBuff()
* 调用函数: 
* 全局变量: 
========================================================= */
void f_GetSendBuffRF(void)
{
	if(SysInf.RfSendFlag)
	{
		SysInf.RfSendFlag = false;
		bSendFlag = true;						// 使能发送 
		f_MemSetData(ucCOMBuf,0,TXD_TOTAL_BYTES);		
		ucCOMBuf[0] = TXD_TOTAL_BYTES;		// 发送字节数 
		ucCOMBuf[1] = ADDR[0];
		ucCOMBuf[2] = ADDR[1];
		ucCOMBuf[3] = ADDR[2];
		ucCOMBuf[4] = sendNum++;				//指向遥控器板
		ucCOMBuf[5] = 0X03;					//控制命令			
		ucCOMBuf[6] = SysInf.SeatTempGear << 4;
		ucCOMBuf[6] |= SysInf.WaterTempGear;	//高4位座温低4位水温  
		ucCOMBuf[7] = SysInf.DryTempGear;		//低4位风温高4位暂时空余
		ucCOMBuf[8] = SysInf.ValveGear<< 4;
		ucCOMBuf[8] |= SysInf.NozzleGear;
		ucCOMBuf[9] = 0x01;//系统开关机状态
		ucCOMBuf[10] = SysInf.KeyNum;
		ucCOMBuf[TXD_TOTAL_BYTES - 1] = f_AddTotalNum(ucCOMBuf,(TXD_TOTAL_BYTES - 1));
		SysInf.KeyNum = 0x00;
	}
}

