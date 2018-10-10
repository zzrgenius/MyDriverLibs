/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : IoPwmDriver.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月13日
  最近修改   :
  功能描述   : 用于IO模拟输出PWM
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月13日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "IoPwmDriver.h"
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

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
/*****************************************************************************
 函 数 名: f_IoPwmDriverOut
 功能描述  : IO输出
 输入参数:
 返 回 值: 
 注     意: 根据需求输出,可100us调用
 
 修改历史:
  1.日    期   : 2018年5月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IoPwmDriverOut(IO_PWM_DRIVER *pDriver)
{
    if (pDriver->bFourceHigh && pDriver->setFourceHighTm > 0)//强制高输出,让电机全压启动一段时间
	{
		pDriver->curTm = 0;
		pDriver->IO_OUT(STATE_ON);
		f_AddU16Data(&(pDriver->fourceHighTm));
		if (pDriver->fourceHighTm >= pDriver->setFourceHighTm)
		{
			pDriver->bFourceHigh = false;
		}
	}
	else
	{
		f_AddU16Data(&(pDriver->curTm));
		if (pDriver->curTm <= pDriver->setPeriodTm)
	    {
			if (pDriver->curTm <= pDriver->setHighTm)
			{
				pDriver->IO_OUT(STATE_ON);
			}
			else
			{
				pDriver->IO_OUT(STATE_OFF);
			}
	    }
	    else
	    {
			pDriver->curTm = 0;
	    }
    }
}

/*****************************************************************************
 函 数 名: f_IoPwmDriverSetPercent
 功能描述  : 设置输出前周期百分比
 输入参数:
 返 回 值: 
 注     意: IO数据可进行电平反相
 
 修改历史:
  1.日    期   : 2018年5月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IoPwmDriverSetPercent(IO_PWM_DRIVER *pDriver, uchar percent)
{
	if (0 == percent)
	{
		pDriver->setHighTm = 0;
		pDriver->bFourceHigh = false;
		pDriver->IO_OUT(STATE_OFF); //硬件输出立即有效
	}
	else if (100 == percent)
	{
		pDriver->setHighTm = pDriver->setPeriodTm;
		pDriver->bFourceHigh = false;
		pDriver->IO_OUT(STATE_ON); //硬件输出立即有效
	}
	else
	{
		//由关闭到启动,启动时先全压启动
		if (0 == pDriver->setHighTm)//未设置前处于关闭状态
		{
			pDriver->bFourceHigh = true;
			pDriver->fourceHighTm = 0;
		}
		
		if (percent > 100)
		{
			percent = 100;
		}
		
		pDriver->setHighTm = (uint)((ulong)(pDriver->setPeriodTm)*(ulong)(percent)/100);
	}
}

/*****************************************************************************
 函 数 名: f_IoPwmDriverSetFource
 功能描述: 
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IoPwmDriverSetFource(IO_PWM_DRIVER *pDriver, uint tm)
{
    pDriver->bFourceHigh = true;
    pDriver->setFourceHighTm = tm;
}

/*****************************************************************************
 函 数 名: f_IoPwmDriverInit
 功能描述: 驱动初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IoPwmDriverInit(IO_PWM_DRIVER *pDriver, SetOut io, uint period)
{
	f_Memset(pDriver, 0, sizeof(IO_PWM_DRIVER));
    pDriver->IO_OUT = io;
    pDriver->setPeriodTm = period;
}
