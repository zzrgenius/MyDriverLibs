/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : IRControl.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月24日
  最近修改   :
  功能描述   : 红外发送接收处理
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月24日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "IRControl.h"
#include "IRConfig.h"
#include "IO_Define.h"
#include "SubFunction.h"

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
IR_CONTROL_DRIVER irControlDriver;


/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

/*****************************************************************************
 函 数 名: f_IR_ReadLevel
 功能描述  : 读取电平时间
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月10日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IR_ReadLevel(void)
{
    uchar ioState = IO_IR_IN;

    //定时读取(下降沿)
//       irControlDriver.bLastRevLevelState != ioState
//    && false == ioState
    
    if (irControlDriver.revPeriodTmBuf >= IR_MAX_PERIOD_TM)//周期超长(中断判断下降沿)
    {
		irControlDriver.bRevOneBitOVer = true;
		irControlDriver.revLowTm = irControlDriver.revLowTmBuf;
		irControlDriver.revPeriodTm = irControlDriver.revPeriodTmBuf;
		irControlDriver.revLowTmBuf = 0;
		irControlDriver.revPeriodTmBuf = 0;
    }

	//累积周期和低电平时间
	f_AddU16Data(&irControlDriver.revPeriodTmBuf); //周期
    if (ioState == false)
    {
		f_AddU16Data(&irControlDriver.revLowTmBuf);
    }
    
    irControlDriver.bLastRevLevelState = ioState;
}

/*****************************************************************************
 函 数 名: f_IR_ReadBit
 功能描述  : 从红外度一个周期电平
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月24日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
IR_READ_BIT_INFO f_IR_ReadBit(uint lowTm, uint periodTm)
{
	//数据判断 低电平+周期
	if (f_CalcU16Err(lowTm, IR_HEAD_LOW_TM) <= IR_READ_LOW_RANGE)//头码低电平判断
	{
		if (f_CalcU16Err(periodTm, IR_HEAD_PERIOD_TM) <= IR_READ_PERIOD_RANGE)
		{
			return IR_READ_HEAD; //头码
		}
	}
	else if (f_CalcU16Err(lowTm, IR_DATA_0_LOW_TM) <= IR_READ_LOW_RANGE)//数据类型
	{
		if (f_CalcU16Err(periodTm, IR_DATA_0_PERIOD_TM) <= IR_READ_PERIOD_RANGE)
		{
			return IR_READ_BIT_0; //数据位0
		}
		else if (f_CalcU16Err(periodTm, IR_DATA_1_PERIOD_TM) <= IR_READ_PERIOD_RANGE)
		{
			return IR_READ_BIT_1; //数据位1
		}
	}
	else if (f_CalcU16Err(lowTm, IR_END_LOW_TM) <= IR_READ_LOW_RANGE)//尾码低电平判断
	{
		if (f_CalcU16Err(periodTm, IR_MAX_PERIOD_TM) <= IR_READ_PERIOD_RANGE) //尾码只有低电平,靠最大周期结束
		{
			return IR_READ_END; //尾码
		}
	}

	return IR_READ_NULL;
}

/*****************************************************************************
 函 数 名: f_IR_ReadByte
 功能描述  : 从红外读取一个字节数据
 输入参数:
 返 回 值: true:完成字节读取;false正在读取
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月24日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_IR_ReadByte(uchar *pBuf, IR_READ_BIT_INFO revBit)
{
    if(IR_READ_BIT_0 == revBit || IR_READ_BIT_1 == revBit)
    {
    	irControlDriver.revBitPos ++;
    	(*pBuf) <<= 1;
		if (IR_READ_BIT_1 == revBit)
		{
			*pBuf |= 0x01;
		}
		
		if (irControlDriver.revBitPos >= 8)
		{
			irControlDriver.revBitPos = 0;
			return true;
		}
    }
    else
    {
		irControlDriver.revBitPos = 0;
    }
    return false;
}

/*****************************************************************************
 函 数 名: f_IR_SendOneBit
 功能描述  : 红外发送一个位
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IR_SendOneBit(uchar data)
{
	if (data)//发送1
	{
		irControlDriver.setLowTm = IR_DATA_1_LOW_TM;
		irControlDriver.setPeriodTm = IR_DATA_1_PERIOD_TM;
	}
	else//发送0
	{
		irControlDriver.setLowTm = IR_DATA_0_LOW_TM;
		irControlDriver.setPeriodTm = IR_DATA_0_PERIOD_TM;
	}
	irControlDriver.sendTm = 0;
	irControlDriver.bSendOneBitOver = false;
}

/*****************************************************************************
 函 数 名: f_IR_SendByte
 功能描述  : 发送一字节数据
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IR_SendByte(uchar data)
{
    if (false == irControlDriver.bSendOneByteOver)
    {
		if (irControlDriver.bSendOneBitOver)//当前位发送完成
		{
			if (irControlDriver.sendBitPos >= 8)//当前字节发送完成
			{
				irControlDriver.sendBitPos = 0;
				irControlDriver.bSendOneByteOver = true;
			}
			else 
			{
				f_IR_SendOneBit((data << irControlDriver.sendBitPos) & 0x80);//高位发送
				irControlDriver.sendBitPos ++;
			}
		}
    }
}

/*****************************************************************************
 函 数 名: f_IR_SendLevel
 功能描述  : 发送电平数据
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IR_SendLevel(void)
{
	if (false == irControlDriver.bSendOneBitOver)
	{
		f_AddU16Data(&(irControlDriver.sendTm));
	    if (irControlDriver.sendTm >= irControlDriver.setPeriodTm)
	    {
	    	//一个发送周期结束
	    	IO_IR_OUT(true);
			irControlDriver.bSendOneBitOver = true;
	    }
	    else
	    {
		    if (irControlDriver.sendTm <= irControlDriver.setLowTm)
		    {
				IO_IR_OUT(false);		
		    }
		    else
		    {
				IO_IR_OUT(true);
		    }
	    }
    }
}


/*****************************************************************************
 函 数 名: f_IR_ControlDeal
 功能描述: 红外接收处理
 输入参数:
 返 回 值: 
 注     意: 100us调用
 
 修改历史:
  1.日    期   : 2018年4月24日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IR_ControlDeal(void)
{
	IR_READ_BIT_INFO getBitInfo;

	f_IR_ReadLevel(); //读取电平
	if (irControlDriver.bRevOneBitOVer && irControlDriver.bNeedDeal == false)//接收处理完成后才继续接
	{
		irControlDriver.bRevOneBitOVer = false;
		getBitInfo = f_IR_ReadBit(irControlDriver.revLowTm, irControlDriver.revPeriodTm);

		//头码强制重新读取数据
		if (IR_READ_HEAD == getBitInfo)
		{
			irControlDriver.revStep = IR_STEP_HEAD;
		}
		
		//接收处理
		switch(irControlDriver.revStep)
		{
			case IR_STEP_HEAD:
				if (IR_READ_HEAD == getBitInfo)
				{
					irControlDriver.revStep = IR_STEP_DATA;
					irControlDriver.revByteCnt = 0;
					irControlDriver.revBitPos = 0;
					f_Memset(irControlDriver.revBuf, 0, sizeof(irControlDriver.revBuf));
				}
				break;

			case IR_STEP_DATA:
				if(f_IR_ReadByte(&irControlDriver.revBuf[irControlDriver.revByteCnt], getBitInfo))
				{
					if (irControlDriver.revByteCnt < IR_REV_BUF_NUM)
					{
						irControlDriver.revByteCnt++;
					}
					else
					{
						irControlDriver.revStep = IR_STEP_HEAD;
					}
				}

				if (IR_READ_NULL == getBitInfo)
				{
					irControlDriver.revNULLCnt++; //一般空闲的时候会接收错误,错误累积后表示接收结束
				}
				else
				{
					irControlDriver.revNULLCnt = 0;
				}

				//接收错误或者收到尾码表示一帧结束
				if (irControlDriver.revNULLCnt >= 2 || IR_READ_END == getBitInfo)
				{
					irControlDriver.bNeedDeal = true;
					irControlDriver.revStep = IR_STEP_HEAD;
					irControlDriver.revNULLCnt = 0;
				}
				break;

			default:
				irControlDriver.revStep = IR_STEP_HEAD;
				break;
		}
	}

	//发送处理
	switch(irControlDriver.sendStep)
	{
		case IR_STEP_IDLE:
			irControlDriver.sendBitPos = 0;
			irControlDriver.sendByteCnt = 0;
			irControlDriver.bSendOneByteOver = false;
			irControlDriver.bSendOneBitOver = true;
			irControlDriver.bSendSpecialCode = false;
			irControlDriver.sendTm = 0;
			break;
			
		case IR_STEP_HEAD:
			if (!irControlDriver.bSendSpecialCode)
			{
				irControlDriver.bSendSpecialCode = true;
				irControlDriver.bSendOneBitOver = false;
				irControlDriver.setLowTm = IR_HEAD_LOW_TM;
				irControlDriver.setPeriodTm = IR_HEAD_PERIOD_TM;
				irControlDriver.sendTm = 0;
			}
			if (irControlDriver.bSendOneBitOver)
			{
				irControlDriver.sendStep = IR_STEP_DATA;
			}
			break;

		case IR_STEP_DATA:
			f_IR_SendByte(irControlDriver.sendBuf[irControlDriver.sendByteCnt]);

			if (irControlDriver.bSendOneByteOver)//当前字节发送完成
			{
				irControlDriver.bSendOneByteOver = false;
				irControlDriver.sendByteCnt ++;
				if (irControlDriver.sendByteCnt >= irControlDriver.needSendByte)
				{
					irControlDriver.bSendSpecialCode = false;
					irControlDriver.sendStep = IR_STEP_END;
				}
			}
			break;

		case IR_STEP_END://发送尾码
			if (!irControlDriver.bSendSpecialCode)
			{
				irControlDriver.bSendSpecialCode = true;
				irControlDriver.bSendOneBitOver = false;
				irControlDriver.setLowTm = IR_END_LOW_TM;
				irControlDriver.setPeriodTm = IR_END_PERIOD_TM;
				irControlDriver.sendTm = 0;
			}
			if (irControlDriver.bSendOneBitOver)
			{
				irControlDriver.sendStep = IR_STEP_IDLE;
			}
			break;
			
	}
	f_IR_SendLevel();
}
/*****************************************************************************
 函 数 名: f_IR_StartSend
 功能描述  : 启动发送
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IR_StartSend(uchar *pBuf, uchar len)
{
    if (IR_STEP_IDLE == irControlDriver.sendStep)
    {

		//获取缓存
		f_MemCpy(irControlDriver.sendBuf, pBuf, len);
		irControlDriver.needSendByte = len;
		
		//开始发送
		irControlDriver.sendStep = IR_STEP_HEAD;
    }
}

/*****************************************************************************
 函 数 名: f_IRControlInit
 功能描述  : 红外收发初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月29日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IRControlInit(void)
{
    IO_IR_OUT(true);
    f_Memset(&irControlDriver, 0, sizeof(IR_CONTROL_DRIVER));
    irControlDriver.sendStep = IR_STEP_IDLE;
    irControlDriver.revStep = IR_STEP_HEAD;
    irControlDriver.bLastRevLevelState = true; //默认上次收到高电平
}

