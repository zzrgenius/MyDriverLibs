/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : PL1167Driver.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月21日
  最近修改   :
  功能描述   : PL1167驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月21日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "SPIDriver.h"
#include "PL1167Driver.h"
#include "SubFunction.h"
#include "Protocol.h"
#include "IO_Define.h"

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
#define PL1167_SEND_LEN 20//发送缓存大小
#define PL1167_REV_LEN 20//接收缓存大小
uchar PL1167SnedBuffer[PL1167_SEND_LEN];
uchar PL1167RevBuffer[PL1167_REV_LEN];

u_u8_def PL1167Flags;
#define bPL1167StartWait PL1167Flags.m_bit.b0//开始发送等待

uchar PL1167SendWaitTm;//启动发送后等待发送超时时间
uchar PL1167NeedSendCnt;//共需要发送的次数

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/
const uint Tab_SendFreq[] = 
{	
	0x0073, 0x0003, 0x0063, 0x0043, 0x0033
};

const uchar Tab_FreqRegAddr[] =
{  
	0x07, 0x34, 0x07
};

const uint Tab_FreqReg[][3]=
{
	{0x0073, 0x8080, 0x0083},
	{0x0003, 0x8080, 0x00e3},
	{0x0063, 0x8080, 0x00c3},
	{0x0043, 0x8080, 0x00b3},
	{0x0033, 0x8080, 0x00f3}
};

const uchar Tab_PL1167RegAddr[]=
{  
	0x00, 0x01, 0x02, 0x04, 0x05, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 
	0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 
	0x20, 0x21, 0x22, 0x23, 
	0x28, 0x29, 0x2a, 0x2b, 
	0x24, 0x25, 0x26, 0x27, 
	0x07, 0x24, 0x27
};

const uint Tab_PL1167Reg[]=
{	
	0x6fe0, 0x5681, 0x6617, 0x9cc9, 0x6637, 0x0030, 0x6c90, 0x1840, 0x7ffd, 0x0008, 0x0000, 0x48bd, 
	0x00ff, 0x8005, 0x0067, 0x1659, 0x19e0, 0x1300, 0x1800, 
	0x5000, 0x3fc7, 0x2000, 0x0340, 
	0x4401, 0xb800, 0xfdc8, 0x000f, 
	0x0000, 0x0000, 0x0000, 0x7407, 
	0x0000, 0xeede, 0x11f9
};

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
#define PL1167_REG_RD	0x80

/*****************************************************************************
 函 数 名: f_PL1167WriteReg
 功能描述  : PL1167写寄存器
 输入参数: reg:寄存器
 		   data:数据
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月22日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PL1167WriteReg(uchar reg, uint data)
{
    SPI_CS(true);
	f_SPIWriteData(reg, 8);
	f_SPIWriteData((uchar)(data>>8), 8);
	f_SPIWriteData((uchar)(data), 8);
	SPI_CS(false);
}

/*****************************************************************************
 函 数 名: f_PL1167ReadReg
 功能描述  : 读取PL1167寄存器数据
 输入参数: reg寄存器地球
 		   len 数据长度
 返 回 值: 寄存器数据
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月22日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uint f_PL1167ReadReg(uchar reg, uchar len)
{
	uint value;
	
    SPI_CS(true);
	f_SPIWriteData(reg|PL1167_REG_RD, 8);
	value = f_SPIReadData(16);
	SPI_CS(false);
	
	return value;
}

/*****************************************************************************
 函 数 名: f_PL1167ReadData
 功能描述  : PL1167读取数据
 输入参数: pBuf缓存指针
 返 回 值: 实际读取长度
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月24日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_PL1167ReadData(uchar *pBuf)
{
	uchar bufLen;
	uchar i;
	
	SPI_CS(true);
	//读取缓存长度
	f_SPIWriteData(0x32|PL1167_REG_RD, 8);
	bufLen = f_SPIReadData(8);
	
	if (bufLen > PL1167_REV_LEN)
	{
		bufLen = PL1167_REV_LEN;
	}
	
	for (i = 0; i < bufLen; i++)
	{
		pBuf[i] = f_SPIReadData(8);
	}
	
	SPI_CS(false); 

	return bufLen;
}

/*****************************************************************************
 函 数 名: f_PL1167_SendData
 功能描述  : PL1167发送数据
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月24日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PL1167SendData(uchar *pData, uchar len)
{
	uchar i;
	
	SPI_CS(true);
    f_SPIWriteData(0x32, 8);
    for (i  = 0; i < len; i++)
    {
		f_SPIWriteData(pData[i], 8);
    }
	SPI_CS(false);    
}

/*****************************************************************************
 函 数 名: f_PL1167InitReg
 功能描述  : PL1167寄存器初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月24日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PL1167InitReg(void)
{
	uchar i;
	uchar j;
	uchar error = false;
	
    for (i = 0; i < 3; i++)
	{
		for (j = 0; j < sizeof(Tab_PL1167RegAddr); j++)
		{
			f_PL1167WriteReg(Tab_PL1167RegAddr[j], Tab_PL1167Reg[j]);
			if (f_PL1167ReadReg(Tab_PL1167RegAddr[j], 16) != Tab_PL1167Reg[j])
			{
				error = true;
				NOP();
			}
		}
		
		if (false == error)
		{
			break;
		}
	}
}

/*****************************************************************************
 函 数 名: void f_PL1167Init(void)
 功能描述  : PL1167初始化
 输入参数: 
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月22日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PL1167Init(void)
{
	PL1167_RST(true);
	SPI_CS(true);
	f_Delay(5000);// 10ms
	PL1167_RST(false);
	f_Delay(5000);// 10ms
	SPI_CS(false);
	f_PL1167InitReg();

	PL1167NeedSendCnt = 0;
	bPL1167StartWait = false;
}

/*****************************************************************************
 函 数 名: f_PL1167ChangeFreq
 功能描述  : PL1167调频(收用)
 输入参数:
 返 回 值: 
 注     意: 根据f_PL1167SendDeal测试发送跳频周期，略大一点
 
 修改历史:
  1.日    期   : 2018年4月22日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PL1167ChangeFreq(void)
{
    static uchar freqCnt = 0;
	uchar i;

	//频率调整,每次调整一个
	for (i = 0; i < sizeof(Tab_FreqRegAddr); i++)
	{
		f_PL1167WriteReg(Tab_FreqRegAddr[i], Tab_FreqReg[freqCnt][i]);
	}
	
	freqCnt++;	
	if(freqCnt >= sizeof(Tab_FreqReg)/sizeof(Tab_FreqReg[0]))
	{
		freqCnt = 0;
	}
}

/*****************************************************************************
 函 数 名: f_PL1167SendDeal
 功能描述  : PL1167发送处理，共有5个频率通道，发送为每个通道一次发送一串数据，循环3次。
 输入参数:
 返 回 值: 
 注     意: 主循环调用（测试调频整体周期48ms）
 
 修改历史:
  1.日    期   : 2018年4月23日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PL1167SendDeal(void)
{
	#define SEND_FREQ_SIZE  (sizeof(Tab_SendFreq)/sizeof(uint))//频率通道切换表大小
	#define SEND_REPET_CNT	3//数据重复发送次数
	
	static uchar sendTimes = 0;
	static uchar len = 0;

	if (PL1167NeedSendCnt > 0)
	{	
		if (!bPL1167StartWait)
		{
			//获取缓存(只获取一次)
			if (0 == sendTimes)
			{
				len = f_GetSendBuffer(&PL1167SnedBuffer[1], sizeof(PL1167SnedBuffer));
				len ++;//多发第一个字节,表示长度
				PL1167SnedBuffer[0] = len;
			}
			
			f_PL1167WriteReg(0x07, Tab_SendFreq[sendTimes%SEND_FREQ_SIZE]);//设置发送通道
			f_PL1167WriteReg(0x34, 0x8080);//清除缓存数据
			f_PL1167SendData(PL1167SnedBuffer, len);//发送缓存
			f_PL1167WriteReg(0x07, Tab_SendFreq[sendTimes%SEND_FREQ_SIZE]|0x0100);//发送使能
		
			bPL1167StartWait = true;
			PL1167SendWaitTm = 0;
		}
		
		if (PL1167_PKT || PL1167SendWaitTm >= 10)//发送完成或等待10ms
		{
			sendTimes++;
			bPL1167StartWait = false;
			if (sendTimes >= (SEND_REPET_CNT*SEND_FREQ_SIZE))
			{
				//发送结束
				f_PL1167WriteReg(0x07, Tab_SendFreq[SEND_FREQ_SIZE - 1]);//发送关闭
				sendTimes = 0;
				PL1167NeedSendCnt --;	
			}
		}
	}
}

/*****************************************************************************
 函 数 名: f_PL1167RevDeal
 功能描述  : PL1167接收处理
 输入参数:
 返 回 值: 
 注     意: 主循环调用
 
 修改历史:
  1.日    期   : 2018年4月24日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PL1167RevDeal(void)
{	
	uchar len;
    if (false == PL1167_PKT)
    {
		//延时判断防干扰
		f_Delay(10);
		if (false == PL1167_PKT)
		{
			len = f_PL1167ReadData(PL1167RevBuffer);
			f_PL1167WriteReg(0x34, 0x8080);
			f_PL1167WriteReg(0x07, 0x00f3);
			f_RevDataDeal(PL1167RevBuffer, len);
		}
    }
}

/*****************************************************************************
 函 数 名: f_PL1167StartSend
 功能描述  : 启动发送
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月3日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PL1167StartSend(void)
{
    PL1167NeedSendCnt++;
}

/*****************************************************************************
 函 数 名: f_PL1167IntoSleep
 功能描述  : 让PL1167进入休眠模式
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月4日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PL1167IntoSleep(void)
{
    f_PL1167WriteReg(0x23, 0x4340);
}
