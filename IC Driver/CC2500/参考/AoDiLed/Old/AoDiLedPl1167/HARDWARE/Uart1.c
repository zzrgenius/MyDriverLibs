#define VAR_UART1_GLOBALS
#include "Include.h"

/*=========================================================
* 功能描述:  发送一个字节,将数据发送到硬件缓存
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void Uart1SendByte(uchar nByte)
{
	UART1_DATA_DR = nByte;  
}

/*=========================================================
* 功能描述:  接收一个字节,从硬件缓存读取一个字节
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar Uart1ReceByte(void)
{
	uchar nTemp = 0;
	volatile uchar nError = 0;

	nError = UART1_DATA_SR;//先读一次SR，再读DR可清除故障标志
	nError = 0;
	while(!(UART1_DATA_SR&0x20))//等待数据接收,RXNE
	{
		nError ++;
		if(nError >= 30)
			break;
	}
	nTemp = UART1_DATA_DR;	//读寄存器会清除标志(清除故障)
	return nTemp;
}

/*=========================================================
* 功能描述:  发送缓存添加判断
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar Uart1BufAddJudge(void)
{
	if(Uart1Tx.rUart1UseLine < UART1_MAX_LINE)
	{
		Uart1Tx.rUart1UseLine ++;
		return true;
	}
	else
	{
		return false;
	}
}

/*=========================================================
* 功能描述:  发送中断函数
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
IT_HEADE void UART1_TX_Interrupt(void)
{	
	Uart1Tx.rUart1NoComCnt = 0;
	if(Uart1ComFlag.rUart1EnSendFlag)//有要发送的缓存
	{
		if(Uart1Tx.rUart1ComPos <= Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][0])
		{
			Uart1SendByte(Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][Uart1Tx.rUart1ComPos]);
			Uart1Tx.rUart1ComPos ++;
		}
		else
		{
			if(Uart1Tx.rUart1ComPos < UART1_MAX_BYTE - 1)//需要判断最后一个发送完成
			{
				Uart1Tx.rUart1ComPos ++;	
			}	
		}
	}
	UART1_DATA_SR &= (~0xC0);//TIEN,TICEN
}

/*=========================================================
* 功能描述:  接收中断函数
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
IT_HEADE void UART1_RX_Interrupt(void)
{
	Uart1Rx.rUart1NoComCnt = 0;
	Uart1ComFlag.rUart1EnAddLine = true;
	//单帧队列过长从0开始重新覆盖(会无效)
	if(Uart1Rx.rUart1ComPos >= UART1_MAX_BYTE)
	{
		Uart1Rx.rUart1ComPos = UART1_MAX_BYTE - 1;
	}
	Uart1Rx.Uart1ComBuff[Uart1Rx.rUart1BuffLine][Uart1Rx.rUart1ComPos] = Uart1ReceByte();
	Uart1Rx.rUart1ComPos++;
}

/*=========================================================
* 功能描述:  串口时间处理
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_Uart1TimeCnt(void)
{
	//无接收计时
	AddIntData(&Uart1Rx.rUart1NoComCnt);
	//时间间隔换队列
	if(Uart1ComFlag.rUart1EnAddLine)
	{
		if(Uart1Rx.rUart1NoComCnt >=UART1_RX_GAP_TM)//超过接收的2个字节间隙时间,认为已经换帧
		{
			Uart1ComFlag.rUart1EnAddLine = false;
			if(Uart1Rx.rUart1UseLine < UART1_MAX_LINE)//需解析行累加
			{
				Uart1Rx.rUart1UseLine++;	
				//换行
				if(Uart1Rx.rUart1BuffLine < (UART1_MAX_LINE - 1))
				{
					Uart1Rx.rUart1BuffLine++;	
				}
				else
				{
					Uart1Rx.rUart1BuffLine = 0;
				}
				Uart1Rx.rUart1ComPos = 0;
			}
		}
	}
	//故障判断
	if(Uart1Rx.rUart1NoComCnt >= 200) // 2 s
	{
		Uart1ComFlag.rUart1CommErrFlag = true;	
	}
	else
	{
		Uart1ComFlag.rUart1CommErrFlag = false;	
	}
	//发送记时
	AddIntData(&Uart1Tx.rUart1NoComCnt);
}

/*=========================================================
* 功能描述:  串口函数初始化
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_Uart1_init(uint baudRate)
{
	uint nRate;
	UART1_DATA_CR1 = 0X00;
	UART1_DATA_CR2 = 0X00;
	UART1_DATA_CR3 = 0X00;
	UART1_DATA_SR = 0X00;
	// 必须先写BRR2  
	// 例如对于波特率位115200时，分频系数=16000000/115200=139  
	// 对应的十六进制数为008B，BBR1=08,BBR2=0B
	nRate = SYS_CLOCK/baudRate;
	UART1_DATA_BR2 = (uchar)((nRate&0x000f) +( (nRate>>8)&0xf0));
	UART1_DATA_BR1 = (uchar)(nRate>>4);
	UART1_CR2_REN_TRUE;	//接收中断开启
	UART1_CR2_RIEN_TRUE;	 
	UART1_CR2_TEN_TRUE;	 
	UART1_CR2_TIEN_TRUE;	//发送中断开启 
}

/*=========================================================
* 功能描述:  添加需要发送的数据
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_Uart1GetSendData(BIG_STRUCT *pFuctionData)
{
	static uint i=0;
	if(Uart1BufAddJudge() == false)//无法继续添加
	{
		return;
	}
	NeedSendInf.NeedSendFlag = false;	
	
	TxComBuff.jHead = 0x31;
	TxComBuff.jCheck = f_CheckSum((unsigned char *)&TxComBuff, 0,sizeof(UART1_COM_TX) - 1);
	//TxComBuff.jCheck = f_XorSum((unsigned char *)&TxComBuff, 0,sizeof(UART1_COM_TX) - 2);
	Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1BuffLine][0] = sizeof(UART1_COM_TX);
	f_Memcpy(&Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1BuffLine][1], &TxComBuff, sizeof(UART1_COM_TX));
	TxComBuff.jFunCmd = 0x00;
	//更新队列到下一个
	if(Uart1Tx.rUart1BuffLine< (UART1_MAX_LINE - 1))
	{
		Uart1Tx.rUart1BuffLine ++;
	}
	else
	{
		Uart1Tx.rUart1BuffLine = 0;
	}
}

/*=========================================================
* 功能描述:  发送函数处理
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_Uart1SendDeal(BIG_STRUCT *pFuctionData)
{
	if(NeedSendInf.NeedSendFlag)	//添加	需要发送的数据
	{
		f_Uart1GetSendData(pFuctionData);
	}
	if(Uart1Tx.rUart1UseLine > 0)//有要发送的缓存
	{
		Uart1ComFlag.rUart1EnSendFlag = true;	//允许发送
		if(Uart1Tx.rUart1NoComCnt >= 50)//500ms无发送，阻塞了,重发当前帧
		{
			Uart1ComFlag.rUart1StartSend = true;//启动发送
			Uart1Tx.rUart1ComPos = 0;
		}
		if(Uart1Tx.rUart1ComPos > Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][0])//当前帧发完
		{
			Uart1Tx.rUart1UseLine--;	
			Uart1Tx.rUart1ComPos = 0;
			if(Uart1Tx.rUart1ComLine < (UART1_MAX_LINE - 1))
			{
				Uart1Tx.rUart1ComLine++;	
			}
			else
			{
				Uart1Tx.rUart1ComLine = 0;
			}
			if(Uart1Tx.rUart1UseLine > 0)//当前发完还有需要发送
			{
				Uart1ComFlag.rUart1StartSend = true;//启动发送	
			}
		}
		if(Uart1ComFlag.rUart1StartSend)//启动发送
		{
			Uart1ComFlag.rUart1StartSend = false;	
			Uart1Tx.rUart1ComPos = 2;
			Uart1SendByte(Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][1]);//发送第1个数据
		}
	}
	else
	{
		Uart1ComFlag.rUart1EnSendFlag = false;
		Uart1ComFlag.rUart1StartSend = true;
		Uart1Tx.rUart1NoComCnt = 0;
	}
}

/*=========================================================
* 功能描述:  接收处理
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_Uart1ReceDeal(BIG_STRUCT *pFuctionData)
{
	uchar j;
	uint nCRCbuf = 0;

	if(Uart1Rx.rUart1UseLine > 0)//有需要解析的行
	{
		if(Uart1Rx.Uart1ComBuff[Uart1Rx.rUart1ComLine][0] == 0x31)
		{
			f_Memcpy(&RxComBuff, &Uart1Rx.Uart1ComBuff[Uart1Rx.rUart1ComLine][0], sizeof(UART1_COM_RX));	
			NeedSendInf.NeedSendFlag = 1;
			pFuctionData->bInitInf = RxComBuff.nInitInf;
			pFuctionData->SystemCurState = RxComBuff.nSystemCurState;
			pFuctionData->curFunInf.curFunc = RxComBuff.nCurFunc;
			pFuctionData->WashInf.bTempChange = RxComBuff.nTempChange;
			pFuctionData->seatInf.seatSensorState.bSwitchState = RxComBuff.nSwitchState;
			pFuctionData->systemErrInf.byte = RxComBuff.nSystemErrInf;
			pFuctionData->seatInf.SeatOffTm.hour = RxComBuff.nSeatOffHour;
			pFuctionData->seatInf.SwitchSeatEn = RxComBuff.nSeatEn;
			pFuctionData->curFunInf.posState = RxComBuff.nPosState;
			pFuctionData->curFunInf.levelState = RxComBuff.nLevelState;
			if(pFuctionData->addrInf.addrFlag == 0x00)
			{
				pFuctionData->addrInf.addrFlag = RxComBuff.nAddrFlag;//调整地址码
			}
			pFuctionData->flushTimeState = RxComBuff.nFlushTimeState;
			pFuctionData->heatInf.waterHeat.setWaterLevel = RxComBuff.nSetWaterLevel;
			pFuctionData->heatInf.seatHeat.setSeatLevel = RxComBuff.nSetSeatLevel;
			pFuctionData->heatInf.dryHeat.setDryLevel = RxComBuff.nSetDryLevel;

			if(TxComBuff.jSetSeatLevel == RxComBuff.nSetSeatLevel)
			{
				if(LedInf.delaySeatDis)
				{
					LedInf.delaySeatDis = false;
					LedInf.DryDisCnt = 0;// 延时10S
				}
			}
			if(TxComBuff.jSetDryLevel == RxComBuff.nSetDryLevel)
			{
				if(LedInf.delayDrytDis)
				{
					LedInf.delayDrytDis = false;
					LedInf.DryDisCnt = 11;// 延时10S
				}
			}
		}
		//当前帧解析完成
		Uart1Rx.rUart1UseLine  --;
		if(Uart1Rx.rUart1ComLine < (UART1_MAX_LINE - 1))
		{
			Uart1Rx.rUart1ComLine ++;
		}
		else
		{
			Uart1Rx.rUart1ComLine = 0;
		}
	}
}