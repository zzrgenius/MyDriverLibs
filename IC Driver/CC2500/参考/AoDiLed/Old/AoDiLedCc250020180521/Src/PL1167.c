#define VAR_PL1167_GLOBALS
#include "Include.h"

uchar ucCOMBuf[64];		//RXD_TOTAL_BYTES		// 接收,发送缓冲 
uchar sendNum;

//uint dataBuff[40];

uchar RfData[11];
uchar RfDataBuff[11];
uchar irData[4];
//uchar buff;
uchar tempData1,tempData2;
FLASH uchar FreqRegAddrTab[]=
{
  0x07,0x34,0x07
};

FLASH uint FreqRegTab[][]=
{
	{0x0073,0x8080,0x0083},
	{0x0003,0x8080,0x00e3},
	{0x0063,0x8080,0x00c3},
	{0x0043,0x8080,0x00b3},
	{0x0033,0x8080,0x00f3}
};

uchar PrfRegAddrTab[]=
{
  0x00,0x01,0x02,0x04,0x05,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,
  0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,
  0x20,0x21,0x22,0x23,
  0x28,0x29,0x2a,0x2b,
  0x24,0x25,0x26,0x27,
   0x07,0x24,0x27,0x07
};

uint PrfRegTab[]=
{
	0x6fe0,0x5681,0x6617,0x9cc9,0x6637,0x0030,0x6c90,0x1840,0x7ffd,0x0008,0x0000,0x48bd,
	0x00ff,0x8005,0x0067,0x1659,0x19e0,0x1300,0x1800,
	0x5000,0x3fc7,0x2000,0x0340,
	0x4401,0xb800,0xfdc8,0x000f,
	0x0000,0x0000,0x0000,0x7407,
	0x0000,0xeede,0x11f9,0x00f3
};

void SpiWr8(uchar dat)
{
 	uchar i;
 	uchar j;
	for(i=0; i<8; i++)  
	{
		SPICLK = 1;
		if((dat&0x80)==0x80)
			SPIMOSI = 1;
		else
			SPIMOSI = 0;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		SPICLK = 0;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		dat <<= 1;
	}
	
}

uchar SpiRd8(void)
{
	uchar i,dat;
	for(i=0; i<8; i++)
	{
		SPICLK = 1;
		dat <<= 1;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		SPICLK = 0;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		if(SPIMISO==0)
			dat &= 0xfe;
		else
			dat |= 0x01;
	}
	return dat;
}

uint SpiRd16(void)
{
	uint dat;
	uchar i;
	
	dat = 0;
	for(i=0; i<16; i++)  
	{
		SPICLK = 1;
		dat <<= 1;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		SPICLK = 0;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		if(SPIMISO==0)
			dat &= 0xfffe;
		else
			dat |= 0x0001;
	}
	return dat;
}


void PrfWrReg16(uchar reg, uint regval)
{
	SPICS = 0;
	SpiWr8(reg);
	SpiWr8((uchar)(regval>>8));
	SpiWr8((uchar)(regval&0x00FF));
	SPICS = 1;
}

/*uint PrfRdReg16(uchar reg)
{
	uint regval;
	SPICS = 0;
	SpiWr8(reg|PRF_REG_RD);
	regval = SpiRd8();
	regval <<= 8;
	regval |= SpiRd8();
	SPICS = 1;
	return regval;
}*/

uint PrfRegRd16(uchar addr)
{
	uint dat;
	
	SPICS = 0;
	SpiWr8(addr|PRF_REG_RD);
	dat = SpiRd16();
	SPICS = 1;
	return dat;
}

//-----------------------------------------------------------------------------
// RF 初始化
//----------------------------------------------------------------------------- 
void PL1167_Init(void)
{
	uchar i,j,err;
	uint regval;
	SPICLK = 0;
	SPIMOSI = 0;
	SPICS = 0;
	RFRST = 0;
	RFRST = 0;
	SPICS = 1;
	f_Delay(10000);// 10ms
	RFRST = 1;
	f_Delay(10000);// 10ms
	for(i=0;i<3;i++)
	{
		err = 0;
		for(j=0;j<PRF_INIT_TAB_LEN;j++)
		{
			PrfWrReg16(PrfRegAddrTab[j], PrfRegTab[j]);
			regval = PrfRegRd16(PrfRegAddrTab[j]);
			if(regval!=PrfRegTab[j])
			{
				err = 1;
				NOP();
			}
		}
		if(err==0)
			break;		
	}
}


/*=========================================================
* 功能描述: 接收中断
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
/*IT_HEADE void PDExtInterrupt(void)
{
	uchar m,n;
	uchar lenght;
	if(PDI_2==0)
	{
		NOP();NOP();NOP();NOP();
		if(PDI_2==0)		
		{
			machineInf.rfInf.RfRecFlag = true;//接收到数据
		}
	}
}*/

/*=========================================================
* 功能描述: 接收处理
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_RfRecDeal(void)
{
	uchar i;
	uchar lenght;
	static uchar temp = 0;
	if(PKT==0)
	{
		NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();
		if(PKT==0)		
		{
			SPICS = 0;
			SpiWr8(0x32|PRF_REG_RD);
			lenght = SpiRd8();
			if(lenght > 11)
			{
				lenght = 11;
			}
			for(i=0;i<lenght;i++)
			{
				//RfData[i] = SpiRd8();
				ucCOMBuf[i] = SpiRd8();
			}
			SPICS = 1;
			
			PrfWrReg16(0x34, 0x8080);
			PrfWrReg16(0x07, 0x00f3);
			
			//数据判断
			if(machineInf.addrInf.addrFlag == 0)
			{
				if( ucCOMBuf[0] == machineInf.AddressRf[0]
				&& ucCOMBuf[1] == machineInf.AddressRf[1]
				&& ucCOMBuf[2] == machineInf.AddressRf[2])
				{
					if(ucCOMBuf[3] != sendNum)	//用于遥控器板接收识别码
					{
						sendNum = ucCOMBuf[3];
						if(ucCOMBuf[4] == 0x03)	//帧类型用于控制命令
						{
							//testPL = 10;
							TxComBuff.jSetSeatLevel = ucCOMBuf[5]>>4;
							//machineInf.heatInf.seatHeat.setSeatLevel  = ucCOMBuf[5]>>4;
							TxComBuff.jSetWaterLevel = ucCOMBuf[5]&0x0f; 
							//machineInf.heatInf.waterHeat.setWaterLevel = ucCOMBuf[5]&0x0f; 
							TxComBuff.jSetDryLevel = ucCOMBuf[6]&0x0f; 
							//machineInf.heatInf.dryHeat.setDryLevel = ucCOMBuf[6]&0x0f; 
							TxComBuff.jLevelState = ucCOMBuf[7]>>4;
							TxComBuff.jPosState = ucCOMBuf[7]&0x0f; 
							TxComBuff.jFunCmd = ucCOMBuf[9];
							if(TxComBuff.jFunCmd == 0x08)
							{
								//LedInf.DryDisCnt = 3;
								//LedInf.DryDisCnt = 11;// 延时10S
								LedInf.delayDrytDis = true;
							}
							if(TxComBuff.jFunCmd == 0x07)
							{
								LedInf.delaySeatDis = true;
								//LedInf.DryDisCnt = 3;
								//LedInf.DryDisCnt = 0;// 延时10S
							}
						}
					}
				}		
			}
			else
			{
				machineInf.AddressRf[0] = ucCOMBuf[0];
				machineInf.AddressRf[1] = ucCOMBuf[1];
				machineInf.AddressRf[2] = ucCOMBuf[2];
				machineInf.addrInf.addrFlag = 0;
			}
			
			/*if(RfData[0] == 0x55 && RfData[1] == 0xaa && RfData[2] == 0xf0)
			{
				if((tempData1 != RfData[3]) && (tempData2 != RfData[10]) )
				{
					tempData1 = RfData[3];
					tempData2 = RfData[10];
					if(RfData[7] == (RfData[4] + RfData[5] + RfData[6]))
					{	
						testPL = 1;
						irData[0] = RfData[4];
						irData[1] = RfData[5];
						irData[2] = RfData[6];
						irData[3] = RfData[7];
					}
				}
			}
			for(i=0;i<11;i++)
			{
				RfData[i] = 0x00;
			}*/
		}
	}
}

/*=========================================================
* 功能描述: 调频处理
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_FreqDeal(void)
{
	static uchar freqTemp = 0;
	uchar i,j,err;
	uint regval;
	i=0;
	for(i=0;i<3;i++)
	{
		err = 0;
		for(j=0;j<PRF_INIT_TAB_LEN;j++)
		{	
			f_pCpuFeedDog();
			PrfWrReg16(PrfRegAddrTab[j], PrfRegTab[j]);
			regval = PrfRegRd16(PrfRegAddrTab[j]);
			if(regval!=PrfRegTab[j])
			{
				err = 1;
				NOP();
			}
		}
		if(err==0)
			break;		
	}
	
	i=0;
	for(i=0;i<3;i++)
	{
		PrfWrReg16(FreqRegAddrTab[i], FreqRegTab[freqTemp][i]);
	}
	freqTemp++;	
	if(freqTemp > 4)
	{
		freqTemp =0;
	}
}

/*=========================================================
* 功能描述: 单总线数据发送
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
/*void f_IrSendDeal(BIG_STRUCT *pFuctionData)
{
	//if((pFuctionData->rfInf.IrSendFlag == true) && (pFuctionData->IrInf.irTimeFlag == true))
	if(pFuctionData->rfInf.IrSendFlag == true)
	{
		//pFuctionData->IrInf.irTimeFlag = false;
		switch(pFuctionData->IrInf.irState)
		{
			case IR_START://开始
			{
				pFuctionData->IrInf.IRrcv_bits = 0;
				pFuctionData->IrInf.irTmCnt = 0;
				IR_SEND(OUT_OFF);
				pFuctionData->IrInf.irState ++;
				break;
			}
			case IR_START_L://引导低
			{
				pFuctionData->IrInf.irTmCnt ++;
				if(pFuctionData->IrInf.irTmCnt > 29)
				{
					pFuctionData->IrInf.irTmCnt = 0;
					IR_SEND(OUT_ON);
					pFuctionData->IrInf.irState ++;
				}
				break;
			}
			case IR_START_H://引导高
			{
				pFuctionData->IrInf.irTmCnt ++;
				if(pFuctionData->IrInf.irTmCnt > 14)
				{
					pFuctionData->IrInf.irTmCnt = 0;
					IR_SEND(OUT_OFF);
					pFuctionData->IrInf.irState ++;
				}
				break;				
			}
			case IR_BIT_L://字节低
			{
				pFuctionData->IrInf.irTmCnt ++;
				if(pFuctionData->IrInf.IRrcv_bits < 8)
				{
					pFuctionData->IrInf.irFlag = (irData[0] >> pFuctionData->IrInf.IRrcv_bits)&0x01;
				}
				else if(pFuctionData->IrInf.IRrcv_bits < 16)
				{
					pFuctionData->IrInf.irFlag = (irData[1] >> (pFuctionData->IrInf.IRrcv_bits-8))&0x01;
				}
				else if(pFuctionData->IrInf.IRrcv_bits < 24)
				{
					pFuctionData->IrInf.irFlag = (irData[2] >> (pFuctionData->IrInf.IRrcv_bits-16))&0x01;
				}
				else
				{
					pFuctionData->IrInf.irFlag = (irData[3] >> (pFuctionData->IrInf.IRrcv_bits-24))&0x01;
				}
				//发送1
				if(pFuctionData->IrInf.irFlag == 0x01)
				{
					if(pFuctionData->IrInf.irTmCnt > 19)
					{
						pFuctionData->IrInf.irTmCnt = 0;
						IR_SEND(OUT_ON);
						pFuctionData->IrInf.irState ++;
					}
				}
				else
				{
					if(pFuctionData->IrInf.irTmCnt > 9)
					{
						pFuctionData->IrInf.irTmCnt = 0;
						IR_SEND(OUT_ON);
						pFuctionData->IrInf.irState ++;
					}
				}
				break;
			}
			case IR_BIT_H://字节高
			{
				pFuctionData->IrInf.irTmCnt ++;
				if(pFuctionData->IrInf.irTmCnt > 4)
				{
					pFuctionData->IrInf.irTmCnt = 0;
					IR_SEND(OUT_OFF);
					pFuctionData->IrInf.IRrcv_bits ++;
					if(pFuctionData->IrInf.IRrcv_bits == 8)
					{
						NOP();
					}
					if(pFuctionData->IrInf.IRrcv_bits == 16)
					{
						NOP();
					}
					if(pFuctionData->IrInf.IRrcv_bits == 24)
					{
						NOP();
					}
					if(pFuctionData->IrInf.IRrcv_bits < 32)
					{
						pFuctionData->IrInf.irState = IR_BIT_L;
					}
					else
					{
						pFuctionData->IrInf.irState ++;
					}
				}
				break;
			}
			case IR_BIT_END://结束
			{
				pFuctionData->IrInf.irTmCnt ++;
				if(pFuctionData->IrInf.irTmCnt > 4)
				{
					pFuctionData->IrInf.irTmCnt = 0;
					IR_SEND(OUT_ON);
					pFuctionData->IrInf.irState = IR_START;
					pFuctionData->rfInf.IrSendFlag = false;
				}
				break;
			}
			default:
			{
				pFuctionData->IrInf.irState = IR_START;
				break;
			}
		}
	}
}*/