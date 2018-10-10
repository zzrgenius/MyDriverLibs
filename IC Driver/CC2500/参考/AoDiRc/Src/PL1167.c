/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : PL1167.c
  版 本 号   : V1.0
  作    者   : zhufeng
  生成日期   : 2018年4月27日
  最近修改   :
  功能描述   : PL1167文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容   : 创建文件

******************************************************************************/
#define VAR_PL1167_GLOBALS
#include "Include.h"
/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
uchar SendBuff[SEND_LEN];
//uchar RfData[11];
//uchar irData[4];

static const uchar PrfRegAddrTab[]=
{
	0x00,0x01,0x02,0x04,0x05,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,
	0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,
	0x20,0x21,0x22,0x23,
	0x28,0x29,0x2a,0x2b,
	0x24,0x25,0x26,0x27,
	0x07,0x24,0x27,
};

static const uint PrfRegTab[]=
{
	0x6fe0,0x5681,0x6617,0x9cc9,0x6637,0x0030,0x6c90,0x4800,0x7ffd,0x0008,0x0000,0x48bd,
	0x00ff,0x8005,0x0067,0x1659,0x19e0,0x1300,0x1800,
	0x5000,0x3fc7,0x2000,0x0340,
	0x4401,0xb800,0xfdc8,0x000f,
	0x7209,0x0000,0x0000,0xb057,
	0x0073,0xeede,0x11f9
};

static const uint FreqTemp[]=
{
	0x0073,0x0003,0x0063,0x0043,0x0033
};

static const uchar FreqRegAddrTab[]=	//接收
{
  0x07,0x34,0x07
};
static const uint FreqRegTab[][3]=
{
	{0x0073,0x8080,0x0083},
	{0x0003,0x8080,0x00e3},
	{0x0063,0x8080,0x00c3},
	{0x0043,0x8080,0x00b3},
	{0x0033,0x8080,0x00f3}
};

/*****************************************************************************
 函 数 名: f_pSpiWr8
 功能描述  : 写8位SPI
 输入参数: uchar dat  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pSpiWr8(uchar dat)
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

/*****************************************************************************
 函 数 名: f_pSpiRd8
 功能描述  : 读8位SPI
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_pSpiRd8(void)
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

/*****************************************************************************
 函 数 名: f_pSpiRd16
 功能描述  : 读16位SPI
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
uint f_pSpiRd16(void)
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

/*****************************************************************************
 函 数 名: f_pPrfWrReg16
 功能描述  : 写16位寄存器
 输入参数: uchar reg    
             uint regval  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pPrfWrReg16(uchar reg, uint regval)
{
	SPICS = 0;
	f_pSpiWr8(reg);
	f_pSpiWr8((uchar)(regval>>8));
	f_pSpiWr8((uchar)(regval&0x00FF));
	SPICS = 1;
}

/*****************************************************************************
 函 数 名: f_pPrfRegRd16
 功能描述  : 读16位寄存器
 输入参数: uchar addr  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
uint f_pPrfRegRd16(uchar addr)
{
	uint dat;
	
	SPICS = 0;
	f_pSpiWr8(addr|PRF_REG_RD);
	dat = f_pSpiRd16();
	SPICS = 1;
	return dat;
}

/*****************************************************************************
 函 数 名: f_pPL1167ReInit
 功能描述  : PL1167重初始化
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月21日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pPL1167ReInit(void)
{
	uchar i,j,err;
	uint regval;
	for(i=0;i<3;i++)
	{
		err = 0;
		for(j=0;j<PRF_INIT_TAB_LEN;j++)
		{
			f_pPrfWrReg16(PrfRegAddrTab[j], PrfRegTab[j]);
			regval = f_pPrfRegRd16(PrfRegAddrTab[j]);
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

/*****************************************************************************
 函 数 名: f_pPL1167Init
 功能描述  : 射频芯片初始化
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pPL1167Init(void)
{
	RFRST = 0;
	SPICS = 1;
	f_NOPDelay(10000);// 10ms
	RFRST = 1;
	f_pPL1167ReInit();
}

/*****************************************************************************
 函 数 名: f_pAddTotalNum
 功能描述  : 累加和
 输入参数: uchar *nBuff  
             uchar nEndNo  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_pAddTotalNum(uchar *nBuff,uchar nEndNo)
{
	uchar i,nTotalSum;
	nTotalSum = 0;
	for(i = 0; i < nEndNo; i ++)
	{
		nTotalSum += nBuff[i];
	}
	return nTotalSum;
}

/*****************************************************************************
 函 数 名: f_pSendBuffer
 功能描述  : 发送处理
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pSendBuffer(void)
{
	static uchar sendNum = 0;
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
		SendBuff[11] = f_pAddTotalNum(SendBuff,SEND_LEN-1);
		SysInf.KeyNum = 0x00;
		SendInf.SendStart = false;
		SendInf.SendFlag = true;
		f_pPL1167ReInit();
	}
}

/*****************************************************************************
 函 数 名: f_pSendDeal
 功能描述  : 发送处理
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pSendDeal(void)
{
	uchar i;
	uint j;
	static uchar m=0;
	static uchar n=0;
	f_pSendBuffer();
	if(SendInf.SendFlag)
	{
		f_pPrfWrReg16(0x07, FreqTemp[n]);
		f_pPrfWrReg16(0x34, 0x8080);
		SPICS = 0;
		f_pSpiWr8(0x32);
		for(i=0;i<SEND_LEN;i++)
		{
			f_pSpiWr8(SendBuff[i]);
		}
		SPICS = 1;
		f_pPrfWrReg16(0x07, FreqTemp[n]|0x0100);
		j = 0;
		while(PKT==0)
		{
			if (j ++ > 1000)	//此处需要添加超时处理 1ms
				break;			
		};
		f_pPrfWrReg16(0x07, FreqTemp[n]);
		m++;
		if(m>4)
		{
			m=0;
			n++;
			if(n>4)
			{
				n=0;
				SendInf.SendFlag = false;
			}
		}
		LED = 1;
	}
}

/*****************************************************************************
 函 数 名: f_pRfRecDeal
 功能描述  : 接收处理
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
//void f_pRfRecDeal(void)
//{
//	uchar i;
//	uchar lenght;
//	static uchar tempData1,tempData2;
//	if(_pb2==1)
//	{
//		NOP();NOP();NOP();NOP();
//		NOP();NOP();NOP();NOP();
//		NOP();NOP();NOP();NOP();
//		NOP();NOP();NOP();NOP();
//		if(_pb2==1)		
//		{
//			SPICS = 0;
//			f_pSpiWr8(0x32|PRF_REG_RD);
//			lenght = f_pSpiRd8();
//			if(lenght > 11)
//			{
//				lenght = 11;
//			}
//			for(i=0;i<lenght;i++)
//			{
//				RfData[i] = f_pSpiRd8();
//			}
//			SPICS = 1;
//			
//			f_pPrfWrReg16(0x34, 0x8080);
//			f_pPrfWrReg16(0x07, 0x00f3);
//			//数据判断
//			if(RfData[0] == 0x55 && RfData[1] == 0xaa && RfData[2] == 0xf0)
//			{
//				if((tempData1 != RfData[3]) && (tempData2 != RfData[10]) )
//				{
//					tempData1 = RfData[3];
//					tempData2 = RfData[10];
//					if(RfData[7] == (RfData[4] + RfData[5] + RfData[6]))
//					{	
//							irData[0] = RfData[4];
//							irData[1] = RfData[5];
//							irData[2] = RfData[6];
//							irData[3] = RfData[7];
//					}
//				}
//			}
//			for(i=0;i<11;i++)
//			{
//				RfData[i] = 0x00;
//			}
//		}
//	}
//}

/*****************************************************************************
 函 数 名: f_pFreqDeal
 功能描述  : 调频处理
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
//void f_pFreqDeal(void)
//{
//	static uchar freqTemp = 0;
//	uchar i;
//	i=0;
//	for(i=0;i<3;i++)
//	{
//		f_pPrfWrReg16(FreqRegAddrTab[i], FreqRegTab[freqTemp][i]);
//	}
//	freqTemp++;	
//	if(freqTemp > 4)
//	{
//		freqTemp =0;
//	}
//}
