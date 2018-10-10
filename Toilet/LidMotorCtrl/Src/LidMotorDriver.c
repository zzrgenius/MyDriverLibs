/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : LidMotorDriver.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月20日
  最近修改   :
  功能描述   : 翻盖电机驱动,可用于智能马桶翻圈翻盖。盖住时位置为0,直立为最大
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月20日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "LidMotorDriver.h"
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
#define LID_MOTOR_LOCK_TM 5//X10ms电机堵转检测时间
#define LID_MOTOR_LOCK_CNT 2 //连续检测到堵转次数,则定义堵转
#define LID_MOTOR_CHANGE_DIR_TM 10//x10ms换向禁止检测堵转时间
 
/*****************************************************************************
 函 数 名: f_LidMotorRangeCheck
 功能描述  : 盖板区域检测
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_LidMotorRangeCheck(LID_MOTOR_DRIVER *pDriver)
{
	//获取位置值
	pDriver->pHardware->GetLidMotorPos(pDriver);
	
	if (pDriver->data.curAngle > pDriver->pHardware->maxPos)
	{
		pDriver->data.curAngle = pDriver->pHardware->maxPos;
	}
	else if (pDriver->data.curAngle < pDriver->pHardware->minPos)
	{
		pDriver->data.curAngle = pDriver->pHardware->minPos;
	}


    //区域判断
    if (pDriver->pHardware->bIncrease)//采样上翻变大
    {
		if (pDriver->data.curAngle <= pDriver->pHardware->setRangeLow)
		{
			pDriver->data.posRange = LID_IN_RANGE_LOW;
		}
		else if (pDriver->data.curAngle >= pDriver->pHardware->setRangeHigh)
		{
			pDriver->data.posRange = LID_IN_RANGE_HIGH;
		}
		else 
		{
			pDriver->data.posRange = LID_IN_RANGE_MID;
		}
    }
    else 
    {
		if (pDriver->data.curAngle >= pDriver->pHardware->setRangeLow)
		{
			pDriver->data.posRange = LID_IN_RANGE_LOW;
		}
		else if (pDriver->data.curAngle <= pDriver->pHardware->setRangeHigh)
		{
			pDriver->data.posRange = LID_IN_RANGE_HIGH;
		}
		else 
		{
			pDriver->data.posRange = LID_IN_RANGE_MID;
		}
    }
}

/*****************************************************************************
 函 数 名: f_LidMotorLockDeal
 功能描述  : 堵转处理
 输入参数:
 返 回 值: 
 注     意: 10ms调用
 
 修改历史:
  1.日    期   : 2018年4月20日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_LidMotorLockDeal(LID_MOTOR_DRIVER *pDriver)
{
	uint offset;
	uchar ret;
	uchar lock = false;

	//堵转检测
	f_AddU8Data(&(pDriver->data.lockTm));
    if (pDriver->data.bEnLockCheck)
    {
		/*
			对于正转,实际位置应该增大,如果此时位置变小或变大小于误差值，则认为已堵转，对于反转则相反。
			
		*/
		if (pDriver->data.lockTm >= LID_MOTOR_LOCK_TM)//堵转检测间隔时间
		{
    		pDriver->data.lockTm = 0;
    		if (MOTOR_DIR_FWD == pDriver->data.curDir)//当前正转
    		{
    			ret = f_CalcU16Offset(pDriver->data.curAngle, pDriver->data.lastAngle, &offset);
    		}
    		else//反转
    		{
				ret = f_CalcU16Offset(pDriver->data.lastAngle, pDriver->data.curAngle, &offset);
    		}
    		pDriver->data.lastAngle = pDriver->data.curAngle;
    		
			if (pDriver->pHardware->bIncrease == ret)
			{
				//变化过小，认为堵转
				if (offset < pDriver->pHardware->lockOffset)
				{
					f_AddU8Data(&(pDriver->data.lockCnt));
				}
				else
				{
					pDriver->data.lockCnt = 0;
				}
			}
			else//反向转动,认为堵转
			{
				f_AddU8Data(&(pDriver->data.lockCnt));
			}

			if (pDriver->data.lockCnt >= LID_MOTOR_LOCK_CNT)
			{
				pDriver->data.curDir = MOTOR_DIR_STOP;

				if (pDriver->data.bReset) //复位时堵转认为已经复位到位
				{
				    pDriver->data.bReset = false;
                    if (pDriver->pHardware->bIncrease)
                    {
                        pDriver->data.curAngle = pDriver->pHardware->minPos;
                    }
                    else
                    {
                        pDriver->data.curAngle = pDriver->pHardware->maxPos;
                    }
				}
			}
		}
    }
    else
    {
		pDriver->data.lockTm = 0;
		pDriver->data.lastAngle = pDriver->data.curAngle;
    }
}

/*****************************************************************************
 函 数 名: f_LidMotorHandleCheck
 功能描述  : 手动翻盖检测
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月15日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
LID_MOTOR_DIR f_LidMotorHandleCheck(LID_MOTOR_DRIVER *pDriver, uint lastPos)
{
	uint offset;
	uchar ret;
	
	ret = f_CalcU16Offset(pDriver->data.curAngle, lastPos, &offset);
    if (MOTOR_DIR_STOP == pDriver->data.curDir)
    {
		if (offset >= pDriver->pHardware->handleOffset)
		{
			if (pDriver->pHardware->bIncrease == ret)//手动上翻
			{
				return MOTOR_DIR_FWD; //正转
			}
			else//手动下翻
			{
				return MOTOR_DIR_REV; //反转
			}
		}	
    }
    return MOTOR_DIR_STOP;
}

/*****************************************************************************
 函 数 名: f_LidMotorBreak
 功能描述  : 刹车处理
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_LidMotorBreak(LID_MOTOR_DRIVER *pDriver)
{
    //运行到刹车流程：运行到刹车 上臂先关,延时10us以上再开启下臂
		
    //上臂关闭
    pDriver->pHardware->MotorFwdEn(STATE_OFF); //正转使能关闭
    pDriver->pHardware->MotorRevEn(STATE_OFF); //反转使能关闭

    //延时(需要实际测试)
    if (pDriver->data.bRunning)
    {
        f_Delay(50);
        pDriver->data.bRunning = false;
    }
    
    //下臂打开接地
    f_IoPwmDriverSetPercent(&(pDriver->data.pwmFwdOut), 100);
    f_IoPwmDriverSetPercent(&(pDriver->data.pwmRevOut), 100); 
}

/*****************************************************************************
 函 数 名: f_LidMotorDeal
 功能描述  : 翻盖电机控制
 输入参数:
 返 回 值: 
 注     意: 10ms调用
 
 修改历史:
  1.日    期   : 2018年4月20日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_LidMotorCtrl(LID_MOTOR_DRIVER *pDriver)
{
	schar percent;
	
	//换向过去抖时间或非停止状态才允许堵转检测
	if (MOTOR_DIR_STOP == pDriver->data.curDir)
	{
		pDriver->data.bEnLockCheck = false;
		pDriver->data.changeDirTm = 0;
	}
	else
	{
		if (pDriver->data.lastDir == pDriver->data.curDir)
		{
			f_AddU8Data(&(pDriver->data.changeDirTm));

			if (pDriver->data.changeDirTm >= LID_MOTOR_CHANGE_DIR_TM)
			{
				pDriver->data.bEnLockCheck = true;
			}
		}
		else
		{
			pDriver->data.bEnLockCheck = false;
			pDriver->data.changeDirTm = 0;
		}
	}

	f_LidMotorRangeCheck(pDriver); //AD采集及区域判断
	f_LidMotorLockDeal(pDriver); //堵转检测

	//获取设置速度档位
	if (pDriver->pHardware->bIncrease)//采样上翻变大
	{
		pDriver->data.posIndex = SPEED_DEV_CNT*(pDriver->data.curAngle - pDriver->pHardware->minPos)/(pDriver->pHardware->maxPos - pDriver->pHardware->minPos);
	}
	else
	{
		pDriver->data.posIndex = SPEED_DEV_CNT*(pDriver->pHardware->maxPos - pDriver->data.curAngle)/(pDriver->pHardware->maxPos - pDriver->pHardware->minPos);
	}
	
	if (pDriver->data.posIndex >= SPEED_DEV_CNT)
	{
		pDriver->data.posIndex = SPEED_DEV_CNT - 1;
	}
	
	if (MOTOR_DIR_FWD == pDriver->data.curDir) //正转调速
	{
		percent = pDriver->data.speedFwd[pDriver->data.posIndex]; //获取当前理论速度
		if (0 != percent)//速度调整 , 0为了的为专门刹车用,不调整
		{
		    //刹车到运行流程：先关下臂, 延时10us以上，打开上臂运行
		    pDriver->pHardware->MotorRevEn(STATE_ON); //反转使能开启(用于调节过程中刹车)
		    f_IoPwmDriverSetPercent(&(pDriver->data.pwmRevOut), 0); //反转输出关闭(下臂关闭)
		    
		    //延时(需要实际测试)
            if (false == pDriver->data.bRunning)
            {
                f_Delay(50);
                pDriver->data.bRunning = true;
            }
            
		    pDriver->pHardware->MotorFwdEn(STATE_ON); //正向使能打开(上臂打开)
		    
			percent	+= pDriver->data.fwdOffset; //根据调整后的偏差决定最终速度
			if (percent > 100)
			{
				percent = 100;
			}
			else if (percent < 0)
			{
				percent = 0;
			}
			f_IoPwmDriverSetPercent(&(pDriver->data.pwmFwdOut), (uchar)percent); //正转速度调节
		}
		else //准备刹车(2个引脚全接地，下2个臂打开)
		{
            f_LidMotorBreak(pDriver);
		}
	}
	else if (MOTOR_DIR_REV == pDriver->data.curDir) //反转调速
	{
		percent = pDriver->data.speedRev[pDriver->data.posIndex]; //获取当前理论速度
		if (0 != percent)//速度调整 , 0为了的为专门刹车用,不调整
		{
		    //刹车到运行流程：先关下臂, 延时10us以上，打开上臂运行
		    pDriver->pHardware->MotorFwdEn(STATE_ON); //正转使能开启(用于调节过程中刹车)
		    f_IoPwmDriverSetPercent(&(pDriver->data.pwmFwdOut), 0); //正转输出关闭(下臂关闭)
		    
		    //延时(需要实际测试)
            if (false == pDriver->data.bRunning)
            {
                f_Delay(50);
                pDriver->data.bRunning = true;
            }
            
		    pDriver->pHardware->MotorRevEn(STATE_ON); //正向使能打开(上臂打开)
		    
			percent	+= pDriver->data.fwdOffset; //根据调整后的偏差决定最终速度
			if (percent > 100)
			{
				percent = 100;
			}
			else if (percent < 0)
			{
				percent = 0;
			}
			f_IoPwmDriverSetPercent(&(pDriver->data.pwmRevOut), (uchar)percent); //反转速度调节
		}
		else //准备刹车(2个引脚全接地，下2个臂打开)
		{
            f_LidMotorBreak(pDriver);
		}
	}
	else//停止
	{
		pDriver->pHardware->MotorFwdEn(STATE_OFF);
		pDriver->pHardware->MotorRevEn(STATE_OFF);
		f_IoPwmDriverSetPercent(&(pDriver->data.pwmFwdOut), 0);
		f_IoPwmDriverSetPercent(&(pDriver->data.pwmRevOut), 0);
		pDriver->data.bRunning = false;
	}
	
	pDriver->data.lastDir = pDriver->data.curDir;
}

/*****************************************************************************
 函 数 名: f_LidMotorSetState
 功能描述  : 设置电机运行状态
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月15日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_LidMotorSetState(LID_MOTOR_DRIVER *pDriver, LID_MOTOR_DIR dir)
{
    if (pDriver->data.curDir != dir)//有换向操作
    {
        pDriver->data.bRunning = false; //每次切换是需要桥臂切换延时
    }
    
    pDriver->data.curDir = dir;

    if (MOTOR_DIR_STOP == dir)//当前要求停止,则复位结束
    {
        pDriver->data.bReset = false;
    }
    
    return true;
}

/*****************************************************************************
 函 数 名: f_LidMotorIsOverMid
 功能描述  : 是否超过中间区域
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月15日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_LidMotorIsOverMid(LID_MOTOR_DRIVER *pDriver)
{
    uint mid = (pDriver->pHardware->maxPos + pDriver->pHardware->minPos)/2;

    if (pDriver->pHardware->bIncrease)//采样上翻变大
    {
		if (pDriver->data.curAngle > mid)
		{
			return true;
		}
    }
    else
    {
		if (pDriver->data.curAngle < mid)
		{
			return true;
		}
    }
    return false;
}

/*****************************************************************************
 函 数 名: f_LidMotorReset
 功能描述  : 盖板复位
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年6月13日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_LidMotorReset(LID_MOTOR_DRIVER *pDriver)
{
    //设置当前位置为开盖最大位置
    if (pDriver->pHardware->bIncrease)
    {
        pDriver->data.curAngle = pDriver->pHardware->maxPos;
    }
    else
    {
        pDriver->data.curAngle = pDriver->pHardware->minPos;
    }

    //启动复位
    pDriver->data.bReset = true;
}

/*****************************************************************************
 函 数 名: f_LidMotorChangePos
 功能描述  : 用于霍尔信号的捕获
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 放外部中断，脉冲信号,下降沿触发
 
 修改历史      :
  1.日    期   : 2018年6月13日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_LidMotorChangePos(LID_MOTOR_DRIVER *pDriver, uchar dir)
{
    if (dir) //正向
    {
        f_AddU16Data(&(pDriver->data.curAngle));
    }
    else //反向
    {
        f_DecU16Data(&(pDriver->data.curAngle));
    }
}


/*****************************************************************************
 函 数 名: f_LidMotorDriverInit
 功能描述  : 翻盖电机驱动初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月15日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_LidMotorDriverInit(LID_MOTOR_DRIVER *pDriver, 
								  LID_MOTOR_HARDWARE *pHardware,
								  SetOut fwdOut,
								  SetOut revOut, 
								  uint period)
{
    f_Memset(pDriver, 0, sizeof(LID_MOTOR_DRIVER));
    pDriver->pHardware = pHardware;
    f_IoPwmDriverInit(&(pDriver->data.pwmFwdOut), fwdOut, period);
    f_IoPwmDriverInit(&(pDriver->data.pwmRevOut), revOut, period); 
}

