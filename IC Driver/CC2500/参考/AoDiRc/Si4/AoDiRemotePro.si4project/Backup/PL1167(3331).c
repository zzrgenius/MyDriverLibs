#define VAR_PL1167_GLOBALS
#include "Include.h"
uint regval;
uchar sendNum;
const uint FreqTemp[]=
{
	//0x0001,0x0021,0x0041,0x0051,0x0061
	0x0073,0x0003,0x0063,0x0043,0x0033
	//0x0073,0x0073,0x0073,0x0073,0x0073
};

uchar SendBuff[SEND_LEN];
uchar DataBuff[6];
const uchar PrfRegAddrTab[]=
{
	0x00,0x01,0x02,0x04,0x05,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,
	0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,
	0x20,0x21,0x22,0x23,
	0x28,0x29,0x2a,0x2b,
	0x24,0x25,0x26,0x27,
	0x07,0x24,0x27,
};

const uint PrfRegTab[]=
{
	/*0x6fe0,0x5681,0x6617,0x9cc9,0x6637,0x0030,0x6c90,0x1840,0x7ffd,0x0008,0x0000,0x48bd,
	0x00ff,0x8005,0x0067,0x1659,0x19e0,0x1300,0x1800,
	0x5000,0x3fc7,0x2000,0x0340,
	0x4401,0xb800,0xfdc8,0x000f,
	0x7209,0x0000,0x0000,0xb057,
	0x0073,0xeede,0x11f9*/
	0x6fe0,0x5681,0x6617,0x9cc9,0x6637,0x0030,0x6c90,0x4800,0x7ffd,0x0008,0x0000,0x48bd,
	0x00ff,0x8005,0x0067,0x1659,0x19e0,0x1300,0x1800,
	0x5000,0x3fc7,0x2000,0x0340,
	0x4401,0xb800,0xfdc8,0x000f,
	0x7209,0x0000,0x0000,0xb057,
	0x0073,0xeede,0x11f9
};

//**********************************//
/*const uchar PrfRegAddrTab[]=
{
  0x00,0x01,0x02,0x04,0x05,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,
  0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,
  0x20,0x21,0x22,0x23,
  0x28,0x29,0x2a,0x2b,
  0x24,0x25,0x26,0x27,
   0x07,0x24,0x27,0x07
  // 0x34,0x24,0x27,0x07
};

const uint PrfRegTab[]=
{
	0x6fe0,0x5681,0x6617,0x9cc9,0x6637,0x0030,0x6c90,0x1840,0x7ffd,0x0008,0x0000,0x48bd,
	0x00ff,0x8005,0x0067,0x1659,0x19e0,0x1300,0x1800,
	0x5000,0x3fc7,0x2000,0x0340,
	0x4401,0xb800,0xfdc8,0x000f,
	0x0000,0x0000,0x0000,0x7407,
	0x0000,0xeede,0x11f9,0x00f3
	//0x8080,0x7407,0x0000,0x00a0
};*/
const uchar FreqRegAddrTab[]=	//接收
{
  0x07,0x34,0x07
};
const uint FreqRegTab[][3]=
{
	{0x0073,0x8080,0x0083},
	{0x0003,0x8080,0x00e3},
	{0x0063,0x8080,0x00c3},
	{0x0043,0x8080,0x00b3},
	{0x0033,0x8080,0x00f3}
};
uchar RfData[11];
uchar tempData1,tempData2;
uchar buff;
uchar irData[4];
//**********************************//


void SpiWr8(uchar dat)
{
 	uchar i;
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
	uchar i;
	uchar dat = 0;
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

uint PrfRegRd16(uchar addr)
{
	uint dat;
	
	SPICS = 0;
	SpiWr8(addr|PRF_REG_RD);
	dat = SpiRd16();
	SPICS = 1;
	return dat;
}

/*=========================================================
* 功能描述:   射频芯片初始化
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void PL1167_Init(void)
{
	uchar i,j,err;
	uint regval;
	//RFRST = 1;
	//f_NOPDelay(10000);// 10ms
	RFRST = 0;
	SPICS = 1;
	f_NOPDelay(10000);// 10ms
	RFRST = 1;
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
* 功能描述: 发送处理
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_SendBuffer(void)
{
	uchar i,j,err;
	
	if(SendInf.SendStart == true)
	{
		LED = 0;
		SendBuff[0] = SEND_LEN;
		SendBuff[1] = ADDR[0];
		SendBuff[2] = ADDR[1];
		SendBuff[3] = ADDR[2];
		SendBuff[4] = sendNum++;				//指向遥控器板
		SendBuff[5] = 0X03;					//控制命令			
		SendBuff[6] = SysInf.SeatTempGear << 4;
		SendBuff[6] |= SysInf.WaterTempGear;	//高4位座温低4位水温  
		SendBuff[7] = SysInf.DryTempGear;		//低4位风温高4位暂时空余
		SendBuff[8] = SysInf.ValveGear<< 4;
		SendBuff[8] |= SysInf.NozzleGear;
		SendBuff[9] = 0x01;//系统开关机状态
		SendBuff[10] = SysInf.KeyNum;
		SendBuff[11] = f_AddTotalNum(SendBuff,SEND_LEN-1);
		SysInf.KeyNum = 0x00;
		SendInf.SendStart = false;
		SendInf.SendFlag = true;
		
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
				}
			}
			if(err==0)
				break;		
		}
	}
}
/*=========================================================
* 功能描述: 发送处理
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_SendDeal(void)
{
	static uchar i=0;
	static uchar j=0;
	uchar m;
	if(SendInf.SendFlag == true)
	{
		PrfWrReg16(0x07, FreqTemp[j]);
		PrfWrReg16(0x34, 0x8080);
		SPICS = 0;
		SpiWr8(0x32);
		for(m=0;m<SEND_LEN;m++)
		{
			SpiWr8(SendBuff[m]);
		}
		SPICS = 1;
		PrfWrReg16(0x07, FreqTemp[j]|0x0100);
		while(PKT==0)
		{
			
		};
		PrfWrReg16(0x07, FreqTemp[j]);
		//SendInf.SendFlag = false;
		i++;
		if(i>4)
		{
			i=0;
			j++;
			if(j>4)
			{
				j=0;
				SendInf.SendFlag = false;
			}
		}
		LED = 1;
	}
}


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
	if(_pb2==1)
	{
		NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();
		if(_pb2==1)		
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
				RfData[i] = SpiRd8();
			}
			SPICS = 1;
			
			PrfWrReg16(0x34, 0x8080);
			PrfWrReg16(0x07, 0x00f3);
			//数据判断
			if(RfData[0] == 0x55 && RfData[1] == 0xaa && RfData[2] == 0xf0)
			{
				if((tempData1 != RfData[3]) && (tempData2 != RfData[10]) )
				{
					tempData1 = RfData[3];
					tempData2 = RfData[10];
					if(RfData[7] == (RfData[4] + RfData[5] + RfData[6]))
					{	
							if(temp > 0)
							{
								buff ++;
							}
							else
							{
								temp = 1;
							}
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
			}
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
	uchar i;
	
	//if(pFuctionData->rfInf.RfRecFlag == false)
	//{
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
	//}
}
