#include "Include.h"

byte_def tComState;
#define bReceiveOverFlag			tComState.m_bit.b0	//接收完成标志
#define bReceiveFinishFlag			tComState.m_bit.b1	//接收成功标志
#define bSendFlag					tComState.m_bit.b2	//发送标志
#define bWaitReceiveFlag			tComState.m_bit.b3

uchar ucCOMBuf[64];		//RXD_TOTAL_BYTES		// 接收,发送缓冲 

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
/*void f_MemSetData(uchar *nBuff,uchar nSetData,uchar nEndNo)
{
	uchar i;
	for(i = 0; i < nEndNo; i ++)
	{
		nBuff[i] = nSetData;
	}
}*/

/*=========================================================
* 功能描述: 开始发送数据 每隔50ms（即一定时间）调用一次
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_StartDataSend(void)
{
	uchar j;
	uchar nCC2500State;
	if(!bSendFlag)																						//无发送数据返回
		return;
	j = TXD_TOTAL_BYTES - 1;
	ucCOMBuf[j] = f_AddTotalNum(ucCOMBuf,j);
	if (bSendFlag)																						//发送数据
	{      
	  	//f_SendPacket(&ucCOMBuf[0], ucCOMBuf[0]+1);
  	}
}

/*=========================================================
* 功能描述: 处理通信接收到的信号
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_DealRXD(void)
{
	uchar i,j;
	if (!bReceiveOverFlag)			/* 接收未完成，返回 */
		return;
	bReceiveOverFlag = 0;
	/* 判断校验码 */
	j = RXD_TOTAL_BYTES - 1;
	if(ucCOMBuf[j] != f_AddTotalNum(ucCOMBuf,j))
	{
		f_RxCC2500();
		return;
	}
	if(machineInf.addrInf.addrFlag == 0)
	{
		if( ucCOMBuf[1] == machineInf.AddressRf[0]
		&& ucCOMBuf[2] == machineInf.AddressRf[1]
		&& ucCOMBuf[3] == machineInf.AddressRf[2])
		{
			if(ucCOMBuf[4] != sendNum)	//用于遥控器板接收识别码
			{
				sendNum = ucCOMBuf[4];
				if(ucCOMBuf[5] == 0x03)	//帧类型用于控制命令
				{
					TxComBuff.jSetSeatLevel = ucCOMBuf[6]>>4;
					TxComBuff.jSetWaterLevel = ucCOMBuf[6]&0x0f; 
					TxComBuff.jSetDryLevel = ucCOMBuf[7]&0x0f; 
					TxComBuff.jLevelState = ucCOMBuf[8]>>4;
					TxComBuff.jPosState = ucCOMBuf[8]&0x0f; 
					TxComBuff.jFunCmd = ucCOMBuf[10];
					if(TxComBuff.jFunCmd == 0x08)
					{
						LedInf.delayDrytDis = true;
						//LedInf.DryDisCnt = 3;
						//LedInf.DryDisCnt = 11;// 延时10S
					}
				}
			}
		}		
	}
	else
	{
		machineInf.AddressRf[0] = ucCOMBuf[1];
		machineInf.AddressRf[1] = ucCOMBuf[2];
		machineInf.AddressRf[2] = ucCOMBuf[3];
		machineInf.addrInf.addrFlag = 0;
	}
	f_RxCC2500();
}

/*=========================================================
* 功能描述: 外部中断0中断，下降沿触发
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
IT_HEADE void PBExtInterrupt(void)
{
	if((EXTI_CR1  & 0x08) == 0x08)//下降沿有效
	{
		if(PBI_5==0)
		{
			NOP();NOP();NOP();NOP();
			if(PBI_5==0)
			{
				if (bSendFlag)	
				{
					bSendFlag = 0;	
					f_RxCC2500(); 	
				}
				else
				{
					if(halRfReceivePacket(&ucCOMBuf[1], &ucCOMBuf[0]) == 1)
					{   
						bReceiveOverFlag = 1;  
						Cc2500Inf.nCC2500Time1 = 0;
						Cc2500Inf.nCC2500Time2 = 0;
					}
				}
			}
		}
	}
}

