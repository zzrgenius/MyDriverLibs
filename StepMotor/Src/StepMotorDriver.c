/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : StepMotorDriver.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月18日
  最近修改   :
  功能描述   : 步进电机控制驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "StepMotorDriver.h"
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
 函 数 名: void f_StepmotorRun(STEPMOTER_DRIVER *pDriver)
 功能描述  : 步进电机运行处理
 输入参数: pDriver 驱动指针
 返 回 值: 
 注     意: 100us调用
 
 修改历史:
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_StepmotorRun(STEPMOTER_DRIVER *pDriver)
{
    #define STEP_START_STEP 16 //启动步数(大扭矩迁入)
	sint needRunStep;
	
	if (pDriver->data.curPosStep == pDriver->data.targetPosStep)
	{
		pDriver->data.stepOptCnt = 0;
		pDriver->data.startStep = 0;
		pDriver->data.runDir = STEPMOTOR_DIR_STOP;
		pDriver->data.flag.bits.bRunning = false;
		pDriver->pHardware->StepmotorOut(pDriver, 0); //关闭输出
	}
	else//请求的位置发生变化
	{
		f_AddU16Data(&(pDriver->data.stepOptCnt)); //换相计数
		
		if ( (pDriver->data.startStep <= STEP_START_STEP && pDriver->data.stepOptCnt > pDriver->pHardware->startOptTm)
		|| (pDriver->data.startStep > STEP_START_STEP && pDriver->data.stepOptCnt > pDriver->pHardware->stepOPtTm))
		{
			pDriver->data.stepOptCnt = 0;
			needRunStep = pDriver->data.targetPosStep - pDriver->data.curPosStep;
			f_AddU8Data(&(pDriver->data.startStep)); //启动步数
			
			if (needRunStep < 0)
			{
				//需要反转
				pDriver->data.runDir = STEPMOTOR_DIR_REV;
				pDriver->data.curPosStep --;
				
				if (pDriver->data.curPhase > 0)
				{
					pDriver->data.curPhase--;
				}
				else
				{
					pDriver->data.curPhase = (pDriver->pHardware->phaseCnt - 1);
				}
			}
			else
			{
				//需要正转
				pDriver->data.runDir = STEPMOTOR_DIR_FWD;
				pDriver->data.curPosStep ++;

				if (pDriver->data.curPhase < (pDriver->pHardware->phaseCnt - 1))
				{
					pDriver->data.curPhase ++;
				}
				else
				{
					pDriver->data.curPhase = 0;
				}
			}

			//底层输出
			pDriver->data.flag.bits.bRunning = true;
			pDriver->pHardware->StepmotorOut(pDriver, pDriver->pHardware->pTab_Step[pDriver->data.curPhase]);
		}
	} 
}

/*****************************************************************************
 函 数 名: void f_StepmotorSetTarget(STEPMOTER_DRIVER *pDriver, sint pos, uchar bForce)
 功能描述  : 设置步进电机设置绝对位置
 输入参数: pDriver 驱动指针
 		   pos 基于0点位置
 		   bForce 是否强制切换
 返 回 值: 
 注     意: 需要时调用
 
 修改历史:
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_StepmotorSetTarget(STEPMOTER_DRIVER *pDriver, sint pos, uchar bForce)
{
	//强制切换/非强制时只有电机不运行的时候能设置新的目标位置，否则无效
	if (bForce || (!bForce && !pDriver->data.flag.bits.bRunning))
	{
    	pDriver->data.targetPosStep = pos;
    }
}

/*****************************************************************************
 函 数 名: f_StepmotorStop
 功能描述  : 电机停止
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年6月21日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_StepmotorStop(STEPMOTER_DRIVER *pDriver)
{
    pDriver->data.targetPosStep = pDriver->data.curPosStep;
}

/*****************************************************************************
 函 数 名: f_StepmotorIsRun
 功能描述  : 电机是否正在运行
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年6月24日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_StepmotorIsRun(STEPMOTER_DRIVER *pDriver)
{
    return pDriver->data.flag.bits.bRunning;
}

/*****************************************************************************
 函 数 名: void f_StepmotorIsAtPos(STEPMOTER_DRIVER *pDriver, sint pos)
 功能描述  : 是否在当前位置
 输入参数: pDriver 驱动指针
 		   pos 基于0点位置
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_StepmotorIsAtPos(STEPMOTER_DRIVER *pDriver, sint pos)
{
    return (pDriver->data.curPosStep == pos)?true:false;
}

/*****************************************************************************
 函 数 名: f_StepmotorReset
 功能描述  : 步进电机复位
 输入参数:
 返 回 值: 
 注     意: 需要时调用
 
 修改历史:
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_StepmotorReset(STEPMOTER_DRIVER *pDriver)
{
    pDriver->data.flag.bits.bInReset = true;
    pDriver->data.resetStep = STEPMOTER_RESET_MAX;
}

/*****************************************************************************
 函 数 名: f_StepmotorOffsetCurPos
 功能描述  : 重新设置当前位置(以当前位置偏移)
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年8月31日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_StepmotorOffsetCurPos(STEPMOTER_DRIVER *pDriver, sint offset)
{
    pDriver->data.targetPosStep += offset;
    if (pDriver->data.targetPosStep > pDriver->pHardware->pTab_Reset[STEPMOTER_RESET_MAX])
    {
        pDriver->data.targetPosStep = pDriver->pHardware->pTab_Reset[STEPMOTER_RESET_MAX];
    }
    else if (pDriver->data.targetPosStep < pDriver->pHardware->pTab_Reset[STEPMOTER_RESET_MIN])
    {
        pDriver->data.targetPosStep = pDriver->pHardware->pTab_Reset[STEPMOTER_RESET_MIN];
    }

    pDriver->data.curPosStep =  pDriver->data.targetPosStep;
}

/*****************************************************************************
 函 数 名: f_StepmotorResetIsOver
 功能描述  : 判断是否复位完成
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_StepmotorResetIsOver(STEPMOTER_DRIVER *pDriver)
{
    return pDriver->data.flag.bits.bInReset == false?true:false;
}

/*****************************************************************************
 函 数 名: f_StepmotorStopReset
 功能描述  : 停止复位
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_StepmotorStopReset(STEPMOTER_DRIVER *pDriver)
{
    pDriver->data.flag.bits.bInReset = false;
}


/*****************************************************************************
 函 数 名: f_StepmotorResetDeal
 功能描述  : 步进电机复位流程处理
 输入参数:
 返 回 值: 
 注     意: 100ms调用
 
 修改历史:
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_StepmotorResetDeal(STEPMOTER_DRIVER *pDriver)
{
    if (pDriver->data.flag.bits.bInReset)
    {
		if(!f_StepmotorIsAtPos(pDriver, pDriver->pHardware->pTab_Reset[pDriver->data.resetStep]))
		{
			//未到达当前位置，强制继续运行到目标位置
			f_StepmotorSetTarget(pDriver, pDriver->pHardware->pTab_Reset[pDriver->data.resetStep], true);
		}
		else
		{
			if (pDriver->data.resetStep < STEPMOTER_RESET_ORG)
			{
				//按步骤先到到最大->最小->原点
				pDriver->data.resetStep++;
			}
			else
			{
				//复位完成
				pDriver->data.flag.bits.bInReset = false;
			}
		}
	}
}

/*****************************************************************************
 函 数 名: void f_StepmotorDriverInit(STEPMOTER_DRIVER *pDriver, STEPMOTOR_HARDWARE_DRIVER *pHardware)
 功能描述  : 步进电机驱动初始化
 输入参数:
 返 回 值: 
 注     意: 首次初始化时调用
 
 修改历史:
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_StepmotorDriverInit(STEPMOTER_DRIVER *pDriver, const STEPMOTOR_HARDWARE_DRIVER *pHardware)
{
	f_Memset(pDriver, 0, sizeof(STEPMOTER_DRIVER));
	pDriver->pHardware = pHardware;
}

