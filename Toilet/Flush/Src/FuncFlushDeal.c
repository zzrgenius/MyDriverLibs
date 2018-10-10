/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : FuncFlushDeal.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月9日
  最近修改   :
  功能描述   : 冲水处理流程
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月9日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "HeadInclude.h"

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
FUNC_FLUSH AT_NEAR funcFlush;

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
#define VALUE_DELAY_TO_BREAK_TM 2//阀开关后，归位刹车状态时间,单位10ms

#define ROUND_FLUSH_TM 10//仅润壁冲水时间,单位100ms

#define FLUSH_BATTERY_LOW_AD 410//电池电量低,约6V
#define FLUSH_BATTERY_LOW_OFFSET 40//电池电池回差

#define FLUSH_BOTH_TM 10//冲洗重叠时间(用于最后排污和回水之间的时间重叠),单位100ms

//====底层硬件控制====
//润壁阀控制
void f_FuncFlushRoundValve(FLUSH_VALVE_STATE state)
{
	if (FLUSH_VALVE_ON == state)
	{
		ROUND_VALVE_A(true);
		ROUND_VALVE_B(false);
	}
	else if (FLUSH_VALVE_OFF == state)
	{
		ROUND_VALVE_A(false);
		ROUND_VALVE_B(true);
	}
	else if (FLUSH_VALVE_BRAKE == state)
	{
		ROUND_VALVE_A(true);
		ROUND_VALVE_B(true);
	}
}

//底部阀控制
void f_FuncFlushBottomValve(FLUSH_VALVE_STATE state)
{
	if (FLUSH_VALVE_ON == state)
	{
		BOTTOM_VALVE_A(true);
		BOTTOM_VALVE_B(false);
	}
	else if (FLUSH_VALVE_OFF == state)
	{
		BOTTOM_VALVE_A(false);
		BOTTOM_VALVE_B(true);
	}
	else if (FLUSH_VALVE_BRAKE == state)
	{
		BOTTOM_VALVE_A(true);
		BOTTOM_VALVE_B(true);
	}
}

/*****************************************************************************
 函 数 名: f_FuncFlushValveCtrl
 功能描述  : 冲水阀控制
 输入参数:
 返 回 值: 
 注     意: 10ms时基
 
 修改历史:
  1.日    期   : 2018年5月10日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncFlushValveCtrl(void)
{
	//润壁阀
	f_AddU8Data(&funcFlush.roundValve.dealyToBreakTm);
    if (funcFlush.roundValve.bState != funcFlush.roundValve.bLastState)
    {
		funcFlush.roundValve.dealyToBreakTm = 0;
		if (funcFlush.roundValve.bState)
		{
			funcFlush.roundValve.setValve = FLUSH_VALVE_ON;//开
			funcFlush.roundValve.lastSetValve= FLUSH_VALVE_ON;//开
		}
		else
		{
			funcFlush.roundValve.setValve = FLUSH_VALVE_OFF;//关
			funcFlush.roundValve.lastSetValve = FLUSH_VALVE_OFF;//关
		}
    }
    funcFlush.roundValve.bLastState = funcFlush.roundValve.bState;
    if (funcFlush.roundValve.dealyToBreakTm >= VALUE_DELAY_TO_BREAK_TM)
    {
		funcFlush.roundValve.setValve = FLUSH_VALVE_BRAKE;//刹车
    }
    f_FuncFlushRoundValve(funcFlush.roundValve.setValve);

    //底部阀
	f_AddU8Data(&funcFlush.bottomValve.dealyToBreakTm);
    if (funcFlush.bottomValve.bState != funcFlush.bottomValve.bLastState)
    {
		funcFlush.bottomValve.dealyToBreakTm = 0;
		if (funcFlush.bottomValve.bState)
		{
			funcFlush.bottomValve.setValve = FLUSH_VALVE_ON;//开
			funcFlush.bottomValve.lastSetValve = FLUSH_VALVE_ON;//开
		}
		else
		{
			funcFlush.bottomValve.setValve = FLUSH_VALVE_OFF;//关
			funcFlush.bottomValve.lastSetValve = FLUSH_VALVE_OFF;//关
		}
    }
    funcFlush.bottomValve.bLastState = funcFlush.bottomValve.bState;
    if (funcFlush.bottomValve.dealyToBreakTm >= VALUE_DELAY_TO_BREAK_TM)
    {
		funcFlush.bottomValve.setValve = FLUSH_VALVE_BRAKE;//刹车
    }
    f_FuncFlushBottomValve(funcFlush.bottomValve.setValve);
}


/*****************************************************************************
 函 数 名: f_FuncFlushDeal
 功能描述: 冲水处理
 输入参数: 
 返 回 值: 
 注     意: 10ms调用
 
 修改历史:
  1.日    期   : 2018年5月9日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncFlushDeal(void)
{
    uint minTm;
    
	//无电电量低时，冲水立即结束
	if (funcFlush.bPowerOff && funcFlush.bLowPower)
	{
		funcFlush.curStep = FLUSH_SREQ_STOP;
	}
	
	f_AddU16Data(&funcFlush.flushTm);
    switch (funcFlush.curStep)
    {
		case FLUSH_SREQ_STOP:
			funcFlush.roundValve.bState = false;//润壁阀关闭
			funcFlush.bottomValve.bState = false;//底部阀关闭

			if (FLUSH_VALVE_OFF == funcFlush.roundValve.lastSetValve 
			&& FLUSH_VALVE_BRAKE == funcFlush.roundValve.setValve
			&& FLUSH_VALVE_OFF == funcFlush.bottomValve.lastSetValve 
			&& FLUSH_VALVE_BRAKE == funcFlush.bottomValve.setValve)//阀已切回刹车(从关切到刹车)
			{
				//关闭电源
				MAIN_POWER_LOCK(false);
				VALE_POWER_LOCK(false);
			}
			break;
			
		case FLUSH_SREQ_START:
			funcFlush.flushTm = 0;
			funcFlush.curStep = FLUSH_SREQ_ROUND_1;

			//打开电源
			MAIN_POWER_LOCK(true);
			VALE_POWER_LOCK(true);
			break;
			
		case FLUSH_SREQ_ROUND_1:
			if (funcFlush.flushTm >= funcFlush.setRound_1_Tm)
			{
				funcFlush.flushTm = 0;
				funcFlush.curStep = FLUSH_SREQ_BOTTOM;
			}
			else
			{
				funcFlush.roundValve.bState = true;
				funcFlush.bottomValve.bState = false;
			}
			break;

		case FLUSH_SREQ_BOTTOM:
			if (funcFlush.flushTm >= funcFlush.setBottomTm)
			{
				funcFlush.flushTm = 0;
				funcFlush.curStep = FLUSH_SREQ_ROUND_2;

                if (0 != funcFlush.setBottomTm)
                {
                    minTm = funcFlush.setBottomTm < FLUSH_BOTH_TM?funcFlush.setBottomTm:FLUSH_BOTH_TM;  
                    //下一个流程减去重叠时间
    				if (funcFlush.setRound_2_Tm <= minTm)
    				{
                        funcFlush.setRound_2_Tm = 0;
    				}
    				else
    				{
                        funcFlush.setRound_2_Tm -= minTm; 
    				}
				}
			}
			else
			{
				funcFlush.bottomValve.bState = true;
				funcFlush.roundValve.bState = false;

				if (funcFlush.setBottomTm - funcFlush.flushTm <= FLUSH_BOTH_TM) //重叠时间
				{
				    if (funcFlush.setBottomTm - funcFlush.flushTm <= funcFlush.setRound_2_Tm)
				    {
                        funcFlush.roundValve.bState = true;
                    }
				}
			}
			break;

		case FLUSH_SREQ_ROUND_2:
			if (funcFlush.flushTm >= funcFlush.setRound_2_Tm)
			{
				funcFlush.flushTm = 0; 
				funcFlush.curStep = FLUSH_SREQ_STOP;
			}
			else
			{
				funcFlush.roundValve.bState = true;
				funcFlush.bottomValve.bState = false;
			}
			break;
			
		default:
			funcFlush.curStep = FLUSH_SREQ_STOP;
			break;
	
    }
}

/*****************************************************************************
 函 数 名: f_FuncSetFlushMode
 功能描述  : 设置冲水模式，对应产生冲水时间
 输入参数: cmd 冲水命令
 返 回 值: true启动冲水;false:启动失败
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月10日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_FuncSetFlushMode(FUNC_FLUSH_CMD cmd)
{
	//无电电量低时，无法启动冲水
	if (funcFlush.bPowerOff && funcFlush.bLowPower)
	{
		return false;
	}

	//正常命令处理
    if (FLUSH_CMD_NULL == cmd)//停止
    {
		if (funcFlush.curStep != FLUSH_SREQ_STOP)
		{
			funcFlush.curStep = FLUSH_SREQ_STOP;
			return true;
		}
    }
    else if (FLUSH_CMD_ROUND == cmd)//落座后润壁冲水
    {
		if (funcFlush.curStep == FLUSH_SREQ_STOP)//当前无冲水
		{
			funcFlush.curStep = FLUSH_SREQ_START;
			funcFlush.setRound_1_Tm = 0;
			funcFlush.setBottomTm = 0;
			funcFlush.setRound_2_Tm = ROUND_FLUSH_TM;
			return true;
		}
    }
    else if (FLUSH_CMD_NORMAL == cmd)//离座后润壁+底部+润壁冲水
    {
		if (funcFlush.curStep == FLUSH_SREQ_STOP)//当前无冲水
		{
			funcFlush.curStep = FLUSH_SREQ_START;
			funcFlush.setRound_1_Tm = funcFlush.saveFlushtm[FLUSH_ADJUST_WASH];
			funcFlush.setBottomTm = funcFlush.saveFlushtm[FLUSH_ADJUST_CLEAN];
            funcFlush.setRound_2_Tm = funcFlush.saveFlushtm[FLUSH_ADJUST_BACK];
			return true;
		}
    }
    return false;
}

/*****************************************************************************
 函 数 名: f_FuncSetFlushTm
 功能描述  : 通过设置时间段来控制冲水(与f_FuncSetFlushMode想过相似)
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 固定时间调用，不受调整影响
 
 修改历史      :
  1.日    期   : 2018年6月18日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_FuncSetFlushTm(uint tm_wash, uint tm_clean, uint tm_back)
{
    //无电电量低时，无法启动冲水
	if (funcFlush.bPowerOff && funcFlush.bLowPower)
	{
		return false;
	}

	if (funcFlush.curStep == FLUSH_SREQ_STOP)//当前无冲水
	{
		funcFlush.curStep = FLUSH_SREQ_START;
		funcFlush.setRound_1_Tm = tm_wash;
		funcFlush.setBottomTm = tm_clean;
		funcFlush.setRound_2_Tm = tm_back;
		return true;
	}
	return false;
}

/*****************************************************************************
 函 数 名: f_FuncFlushPowerCheck
 功能描述  : 冲水电源检测,正常掉电或者无电冲水低电量时，结束冲水
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月10日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncFlushPowerCheck(void)
{
    if (POWER_CUT_CHECK)
    {
    	if (false == funcFlush.bPowerOff)
    	{
			f_Delay(10); //去抖
			if (POWER_CUT_CHECK)
			{
				funcFlush.bPowerOff = true;	
			}
		}
    }
    else 
    {
		funcFlush.bPowerOff = false;	
    }
}

/*****************************************************************************
 函 数 名: f_FuncFlushBatteryCheck
 功能描述  : 冲水电池电测
 输入参数:
 返 回 值: 
 注     意: 100ms调用
 
 修改历史:
  1.日    期   : 2018年5月10日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncFlushBatteryCheck(void)
{
	funcFlush.batteryAD = f_MCU_GetAD(BATTERY_LOW_CHECK_CHANNEL);

    //判断
    if (funcFlush.batteryAD <= FLUSH_BATTERY_LOW_AD)
    {
		f_AddU8Data(&funcFlush.batteryOffCnt);
		funcFlush.batteryOnCnt = 0;

		if (funcFlush.batteryOffCnt >= 4)
		{
			funcFlush.bLowPower = true;
		}
    }
    else if (funcFlush.batteryAD >= FLUSH_BATTERY_LOW_AD + FLUSH_BATTERY_LOW_OFFSET)
    {
		f_AddU8Data(&funcFlush.batteryOnCnt);
		funcFlush.batteryOffCnt = 0;

		if (funcFlush.batteryOnCnt >= 4)
		{
			funcFlush.bLowPower = false;
		}
    }
}

/*****************************************************************************
 函 数 名: f_FuncFlushInit
 功能描述  : 冲水功能初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月10日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncFlushInit(void)
{
    f_Memset(&funcFlush, 0, sizeof(FUNC_FLUSH));

	//====2个阀上电后，关闭一次====
	//打开电源
	MAIN_POWER_LOCK(true);
	VALE_POWER_LOCK(true);
	funcFlush.roundValve.bLastState = true;
	funcFlush.bottomValve.bLastState = true;
	funcFlush.roundValve.setValve = FLUSH_VALVE_OFF;
	funcFlush.bottomValve.setValve = FLUSH_VALVE_OFF;
}

