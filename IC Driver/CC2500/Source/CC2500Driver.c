/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : CC2500Driver.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月31日
  最近修改   :
  功能描述   : CC2500驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "CC2500Driver.h"
#include "CC2500Register.h"
#include "SubFunction.h"
#include "CC2500Protocol.h"
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
uchar f_CC2500_InitByChannel(uchar channel);

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/
CC250_DRIVER cc2500;


/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
//CC2500_GDO0 CC2500的一些状态返回线

/*****************************************************************************
 函 数 名: f_CC2500_WaitIDLE
 功能描述  : 等待CC2500空闲
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年6月1日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_CC2500_WaitIDLE(uint tryCnt)
{
    while (tryCnt > 0)
    {
        if (false == CC2500_SDI)
        {
            break;
        }
        tryCnt--;
        f_Delay(10);
    }

    if (0 == tryCnt)//超时结束
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*****************************************************************************
 函 数 名: f_CC2500_WriteReg
 功能描述  : 写CC2500寄存器
 输入参数  : addr 寄存器地址
           setValue 设置寄存器值
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_WriteReg(uchar addr, uchar setValue)
{
    f_SPIEnChip(cc2500.spi, STATE_ON);
    f_CC2500_WaitIDLE(1000);
    f_SPIWriteData(cc2500.spi, addr&0x7F, 8);
    f_SPIWriteData(cc2500.spi, setValue, 8);

    f_SPIEnChip(cc2500.spi, STATE_OFF);
}

/*****************************************************************************
 函 数 名: f_CC2500_WriteBurst
 功能描述  : CC2500连续写多个数据
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_WriteBurst(uchar addr, uchar *pData, uchar len)
{
    uchar i;
    
    f_SPIEnChip(cc2500.spi, STATE_ON);
    f_CC2500_WaitIDLE(1000);
    f_SPIWriteData(cc2500.spi, addr|TI_CCxxx0_WRITE_BURST, 8);
    for (i = 0; i < len; i++)
    {
        f_SPIWriteData(cc2500.spi, pData[i], 8);
    }
    f_SPIEnChip(cc2500.spi, STATE_OFF);
}

/*****************************************************************************
 函 数 名: f_CC2500_ReadReg
 功能描述  : 读CC2500寄存器
 输入参数  : addr 寄存器地址
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_CC2500_ReadReg(uchar addr)
{
    uchar getValue;
    
    f_SPIEnChip(cc2500.spi, STATE_ON);
    f_CC2500_WaitIDLE(1000);
    f_SPIWriteData(cc2500.spi, addr|TI_CCxxx0_READ_SINGLE, 8);
    getValue = (uchar)f_SPIReadData(cc2500.spi, 8);
    f_SPIEnChip(cc2500.spi, STATE_OFF);
    return getValue;
}

/*****************************************************************************
 函 数 名: f_CC2500_ReadBurst
 功能描述  : CC2500连续读取
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_ReadBurst(uchar addr, uchar *pData, uchar len)
{
    uchar i;
    
    f_SPIEnChip(cc2500.spi, STATE_ON);
    f_CC2500_WaitIDLE(1000);
    f_SPIWriteData(cc2500.spi, addr|TI_CCxxx0_READ_BURST, 8);
    for (i = 0; i < len; i++)
    {
        pData[i] = (uchar)f_SPIReadData(cc2500.spi, 8);
    }
    f_SPIEnChip(cc2500.spi, STATE_OFF);
}

/*****************************************************************************
 函 数 名: f_CC2500_WriteStrobe
 功能描述  : CCC2500写状态寄存器
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_WriteStrobe(uchar strobe)
{
    f_SPIEnChip(cc2500.spi, STATE_ON);
    f_CC2500_WaitIDLE(1000);
    f_SPIWriteData(cc2500.spi, strobe, 8);
    f_SPIEnChip(cc2500.spi, STATE_OFF);
}

/*****************************************************************************
 函 数 名: f_CC2500_ReadStrobe
 功能描述  : 读CC2500状态寄存器
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_CC2500_ReadStrobe(uchar addr)
{
    uchar getValue;
    f_CC2500_ReadBurst(addr, &getValue, 1);
    return getValue;
}

/*****************************************************************************
 函 数 名: f_CC2500_ResetAllReg
 功能描述  : CC2500重新设置所有寄存器
 输入参数  : channel 射频通道号
 输出参数  :
 返 回 值: 成功:true;失败:false
 注     意: 速度250K,FIFO长度256
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_CC2500_ResetAllReg(uchar channel)
{
    uchar i;

    for (i = 0; i < CC2500_REG_SIZE; i ++)
    {
        f_CC2500_WriteReg(tab_CC2500Register[i].addr, tab_CC2500Register[i].setValue);
    }
    f_CC2500_WriteReg(TI_CCxxx0_CHANNR, channel);// Channel number.
    if (0x3B != f_CC2500_ReadReg(TI_CCxxx0_MDMCFG3))
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*****************************************************************************
 函 数 名: f_CC2500_IntoSleep
 功能描述  : CC2500进入休眠模式
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_IntoSleep(void)
{
    f_CC2500_WriteStrobe(TI_CCxxx0_SIDLE);
	f_CC2500_WriteStrobe(TI_CCxxx0_SPWD);
	cc2500.bRfSleep = true;
}

/*****************************************************************************
 函 数 名: f_CC2500_AutoSleep
 功能描述  : 自动进入休眠，进行节能
 输入参数  : void  
 输出参数  :
 返 回 值: 
 注     意: 100ms调用
 
 修改历史      :
  1.日    期   : 2018年9月19日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_AutoSleep(void)
{
    if (false == cc2500.bRfSleep
	&& 0 == cc2500.needSendCnt
	&& true == cc2500.bResetOK) //发送完成(已成功初始化)
	{
        cc2500.autoSleepTm++;
        if (cc2500.autoSleepTm >= 20) //2s自动进入模块休眠
        {
            cc2500.autoSleepTm = 0;
            f_CC2500_IntoSleep();    
        }
	}
	else
	{
        cc2500.autoSleepTm = 0;
	}
    
}

/*****************************************************************************
 函 数 名: f_CC2500_SetRevMode
 功能描述  : 设置CC2500为接收模式
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_SetRevMode(void)
{
    if (false == cc2500.bResetOK)
    {
        return;
    }
    
    f_CC2500_WriteStrobe(TI_CCxxx0_SIDLE);
	f_CC2500_WriteStrobe(TI_CCxxx0_SFRX); //清空FIFO
	f_CC2500_WriteStrobe(TI_CCxxx0_SRX); //选择接受模式
}

/*****************************************************************************
 函 数 名: f_CC2500_SendData
 功能描述  : CC2500发送数据
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_SendData(uchar *pData, uchar len)
{
    uint waitCnt;
    
    f_CC2500_WriteStrobe(TI_CCxxx0_SIDLE);
	f_CC2500_WriteStrobe(TI_CCxxx0_SFTX);
	f_CC2500_WriteBurst(TI_CCxxx0_TXFIFO, pData, len);
	f_CC2500_WriteStrobe(TI_CCxxx0_STX);

    //等待发送启动-需要330us 最多等1ms
	waitCnt = 800;
	while(waitCnt--)
	{
		if(CC2500_SDI)
		{
		    break; 
		}
	}

    //等待发送结束-250Kbps 64Bytes*8=512Bits 约2ms发射完成，这里最多等3ms
	f_CC2500_WaitIDLE(2400);
	
	//发送完成后自动进入IDLE状态
}

/*****************************************************************************
 函 数 名: f_CC2500_RevData
 功能描述  : CC2500接收数据
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_CC2500_RevData(uchar *pData, uchar *len)
{
    #define CC2500_APPEND_LEN 2
    uchar status[CC2500_APPEND_LEN];
    uchar getLen;
    uchar nTemp;

    *len = 0;
	nTemp = f_CC2500_ReadStrobe(TI_CCxxx0_RXBYTES);
	if (nTemp & TI_CCxxx0_NUM_RXBYTES)
	{
		getLen = f_CC2500_ReadReg(TI_CCxxx0_RXFIFO);//读包长度(不包含多发的多余字节)
		
		if (getLen < CC2500_REV_LEN)
		{
			f_CC2500_ReadBurst(TI_CCxxx0_RXFIFO, pData, getLen); //读取数据,将多余字节也读出
			f_CC2500_ReadBurst(TI_CCxxx0_RXFIFO, status, CC2500_APPEND_LEN);//read 2 appended status bytes (status[0]=RSSI,status[1]=LQI)
			f_CC2500_WriteStrobe(TI_CCxxx0_SFRX);
			if (status[TI_CCxxx0_LQI_RX] & TI_CCxxx0_CRC_OK)
			{
			    *len = getLen;
			    cc2500.bRfSleep = false; //收到数据会主动被唤醒
				return true;
			}
		} 
	}
	f_CC2500_SetRevMode();
	return false;
}

/*****************************************************************************
 函 数 名: f_CC2500_ChangeChannel
 功能描述  : 更改通道
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 根据接收调频周期测试(需要实测)或发送需要时调用
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_ChangeChannel(void)
{
    if (false == cc2500.bResetOK)
    {
        return;
    }
    
    if (cc2500.curChannelIndex < CC2500_MAX_CHANNEL)
    {
        cc2500.curChannelIndex++;
    }
    else
    {
        cc2500.curChannelIndex = 0;
    }
    f_CC2500_WriteStrobe(TI_CCxxx0_SIDLE);
	f_CC2500_WriteReg(TI_CCxxx0_CHANNR, cc2500.channels[cc2500.curChannelIndex]);// Channel number.
	f_CC2500_WriteStrobe(TI_CCxxx0_SCAL);//检验
	f_Delay(200);
}

/*****************************************************************************
 函 数 名: f_CC2500_StartSend
 功能描述  : CC2500启动发送
 输入参数  : void  
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年6月1日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_StartSend(void)
{
    cc2500.needSendCnt++;
}

/*****************************************************************************
 函 数 名: f_CC2500_SendDeal
 功能描述  : CC2500发送处理
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 主循环调用
 
 修改历史      :
  1.日    期   : 2018年6月1日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_SendDeal(void)
{
	#define CC2500_SEND_REPET_CNT	3//数据重复发送次数
	
	static uchar sendTimes = 0; //发送次数
	static uchar len = 0;

    if (false == cc2500.bResetOK) //初始化失败或者未完成初始化
    {
        cc2500.needSendCnt = 0;
        return;
    }

	if (cc2500.needSendCnt > 0)
	{	
		//获取缓存(只获取一次)
		if (0 == sendTimes)
		{
			len = f_CC2500_GetSendBuffer(&cc2500.sendBuffer[1], sizeof(cc2500.sendBuffer) - 1);
			len ++;//多发第一个字节,表示长度
			cc2500.sendBuffer[0] = len; //第一个字节表示长度
			if (cc2500.bRfSleep) //正在休眠先唤醒
            {
                cc2500.bRfSleep = false;
			    f_CC2500_InitByChannel(cc2500.channels[cc2500.curChannelIndex]);//重新初始化下寄存器(发送结束，模块会进休眠)
			}
		}

		f_CC2500_SendData(cc2500.sendBuffer, len + 1); //需要多发一个字节，否则CRC校验会有问题
		f_CC2500_ChangeChannel();
		
		sendTimes++;
		if (sendTimes >= (CC2500_SEND_REPET_CNT*CC2500_MAX_CHANNEL))
		{
			//发送结束
			sendTimes = 0;
			cc2500.needSendCnt--;	
		}
	}
}

/*****************************************************************************
 函 数 名: f_CC2500ReciveDeal
 功能描述  : CC2500接收处理
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 主循环调用
 
 修改历史      :
  1.日    期   : 2018年6月1日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_ReciveDeal(void)
{
    uchar len;
    uchar ioState;
    if (false == cc2500.bResetOK) //初始化失败或者未完成初始化
    {
        return;
    }

    ioState = CC2500_GD0;
    if (false == ioState 
    && cc2500.bLastGD0 != ioState) //下降沿
    {
	    if (cc2500.needSendCnt > 0)//正在有数据发送
	    {
	        //结束发送数据，转接收模式
	        cc2500.needSendCnt = 0; 
            f_CC2500_SetRevMode();
	    }
		if(true == f_CC2500_RevData(cc2500.revBuffer, &len))
		{
		    f_CC2500_RevProtocolDeal(cc2500.revBuffer, len);
		}
    }
    cc2500.bLastGD0 = ioState;
}

/*****************************************************************************
 函 数 名: f_CC2500_Reset
 功能描述  : CC2500复位(上电)
 输入参数  :
 输出参数  :
 返 回 值: 成功:true;失败false
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_CC2500_Reset(void)
{
    CC2500_CLK(STATE_ON);
	CC2500_SDO(STATE_OFF);	
	f_SPIEnChip(cc2500.spi, STATE_ON);
	f_Delay(20);
	f_SPIEnChip(cc2500.spi, STATE_OFF);
	f_Delay(20000);
	f_SPIEnChip(cc2500.spi, STATE_ON);
	if (false == f_CC2500_WaitIDLE(1000))
	{
        f_SPIEnChip(cc2500.spi, STATE_OFF);
		return false;
	}
	
	f_SPIWriteData(cc2500.spi, TI_CCxxx0_SRES, 8);
	f_Delay(20000);
	if (false == f_CC2500_WaitIDLE(1000))
	{
        f_SPIEnChip(cc2500.spi, STATE_OFF);
		return false;
	}
	f_SPIEnChip(cc2500.spi, STATE_OFF);
	return true;
}

/*****************************************************************************
 函 数 名: f_CC2500_InitByChannel
 功能描述  : 通过通道初始化
 输入参数  :
 输出参数  :
 返 回 值: 成功:true;失败false
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_CC2500_InitByChannel(uchar channel)
{
    f_SPIEnChip(cc2500.spi, STATE_OFF);
    CC2500_CLK(STATE_OFF);
	CC2500_SDO(STATE_OFF);	
	
	if(false == f_CC2500_Reset())
	{
	    return false;
	}
	
	if(false == f_CC2500_ResetAllReg(channel))
	{
	    return false;
	}

	f_CC2500_WriteStrobe(TI_CCxxx0_SIDLE);
	f_CC2500_WriteStrobe(TI_CCxxx0_SCAL);//检验
	cc2500.bRfSleep = false;
	return true;    
}


/*****************************************************************************
 函 数 名: f_CC2500_Init
 功能描述  : CC2500初始化
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_CC2500_Init(SPI_DRIVER *spi)
{
    uchar tryCnt = 50;
    
    f_Memset(&cc2500, 0, sizeof(CC250_DRIVER));
    cc2500.spi = spi;
    cc2500.channels[0] = 6;
    cc2500.channels[1] = 66;
    cc2500.channels[2] = 126;
    cc2500.channels[3] = 186;
    
    do
    {
        if (true == f_CC2500_InitByChannel(cc2500.channels[cc2500.curChannelIndex])) //初始化成功
        {
            cc2500.bResetOK = true;
            break;
        }
//        f_Delay(20000);
        f_MCU_FeedDog();//喂狗
    }while(tryCnt --);
}
