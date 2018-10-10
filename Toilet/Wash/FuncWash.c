/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : FuncWash.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月10日
  最近修改   :
  功能描述   : 清洗流程处理
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月10日
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
FUNC_WASH AT_NEAR funcWashHip;//臀部清洗
FUNC_WASH AT_NEAR funcWashFemale;//女性清洗
/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/
//====真正水温====
const sint realWatHeatTemp[] =
{
	0, 35, 38, 41
};

//====臀部清洗参数====
//臀部喷杆清洗位置
const sint tab_HipWashNozzle[] =
{
	1700,
	1700, //L1
	2100, //L2
	2500, //L3
	2900, //L4
	2900  //L5
};

//臀部流量清洗位置
const sint tab_HipWashFlow[] =
{
	-1600,
	-1600, //L1
	-1600, //L2
	-1600  //L3
};

const FUNC_WASH_HARDWARE hipWashHardware =
{
	&nozzleStepmotor,
	&flowStepmotor,
	tab_HipWashNozzle,
	tab_HipWashFlow
};

//====女性清洗参数====
//女性喷杆清洗位置
const sint tab_FemaleWashNozzle[] =
{
	1800,
	1800, //L1
	2200, //L2
	2600, //L3
	3000, //L4
	3000  //L5
};

//女性流量清洗位置
const sint tab_FemaleWashFlow[] =
{
	1600,
	1600, //L1
	1600, //L2
	1600  //L3
};

const FUNC_WASH_HARDWARE femaleWashHardware =
{
	&nozzleStepmotor,
	&flowStepmotor,
	tab_FemaleWashNozzle,
	tab_FemaleWashFlow
};

//====清洗流量气泵占空比====
const uchar tab_WashPumpPercent[] =
{
	0,
	50, //L1
	75, //L2
	100 //L3
};

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

#define MOVE_WASH_OFFSET 150 //移动清洗前后偏差
#define WASH_STRONG_WEAK_GAP_TM 20 //强弱清洗间隔时间,单位100ms
#define WASH_COLD_TM 50 //冷热按摩冷水时间,单位100ms
#define WASH_HOT_TM 100 //冷热按摩冷水时间,单位100ms

/*****************************************************************************
 函 数 名: f_FuncWashNext
 功能描述  : 进入下一个流程
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncWashNext(FUNC_WASH *pDriver, FUNC_WASH_INDEX index)
{
    pDriver->index = index;
	pDriver->waitTm = 0;
	pDriver->flags.m_byte = 0;
	pDriver->bNeedPosBack = true; //默认收回
}

/*****************************************************************************
 函 数 名: f_FuncSetWashState
 功能描述  : 设置清洗
 输入参数: pDriver驱动指针
 		   state 开关状态
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_FuncSetWashState(FUNC_WASH *pDriver, STATE_INFO state)
{
    if (STATE_OFF == state)
    {
    	if (pDriver->index <= WASH_INDEX_WASH)
    	{
			f_FuncWashNext(pDriver, WASH_INDEX_BACK_FLOW);//结束流程
		}
		return true;
    }
    else
    {
		if (funcError.bModleWashErr 
		|| STATE_OFF == funcSit.state 
//		|| f_StepmotorResetIsOver(&nozzleStepmotor) == false
		|| f_StepmotorResetIsOver(&flowStepmotor) == false)//故障或离座或正在复位(仅流量)
		{
			if (pDriver->index <= WASH_INDEX_WASH)//当前正在清洗
	    	{
				f_FuncWashNext(pDriver, WASH_INDEX_BACK_FLOW);//结束流程
			}
		}
		else
		{
		    f_FuncWashNext(pDriver, WASH_INDEX_ORG);//启动流程
            pDriver->bNeedPosBack = false; //允许喷杆不复位就启动清洗(连续清洗)
            funcWashHip.bNeedPosBack = false;//喷杆无需缩回(允许喷杆不复位就启动清洗,连续清洗)【调用f_FuncWashNext会初始化标志,设置需要在调用之后】
            if (false == pDriver->bNeedPosBack) //无需喷杆回，则喷杆停止
            {
                f_StepmotorStop(pDriver->pHardware->pNozzleSM);
            }
			return true;
		}
    }
    return false;
}

/*****************************************************************************
 函 数 名: f_FuncWashChangePos
 功能描述  : 清洗改变位置
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncWashChangePos(FUNC_WASH *pDriver, sint tag)
{
    if(!f_StepmotorIsAtPos(pDriver->pHardware->pNozzleSM, tag))
	{
		//未到达当前位置，强制继续运行到目标位置
		f_StepmotorSetTarget(pDriver->pHardware->pNozzleSM, tag, true);
		pDriver->flags.m_bits.bPosAtTag = false;
	}
	else 
	{
		pDriver->flags.m_bits.bPosAtTag = true;
	}
}

/*****************************************************************************
 函 数 名: f_FuncWashChangeFlow
 功能描述  : 清洗改变流量位置
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncWashChangeFlow(FUNC_WASH *pDriver, sint tag)
{
    if(!f_StepmotorIsAtPos(pDriver->pHardware->pFlowSM, tag))
	{
		//未到达当前位置，强制继续运行到目标位置
		f_StepmotorSetTarget(pDriver->pHardware->pFlowSM, tag, true);
		pDriver->flags.m_bits.bFlowAtTag = false;
	}
	else 
	{
		pDriver->flags.m_bits.bFlowAtTag = true;
	}
}

/*****************************************************************************
 函 数 名: f_FuncWashPosCtrl
 功能描述  : 喷杆位置控制
 输入参数:
 返 回 值: 
 注     意: 结束是需要先调用下pDriver->bChangePos = true,使得喷杆归位到设置位置
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncWashPosCtrl(FUNC_WASH *pDriver)
{
	sint tag = 0;
	
    if (WASH_INDEX_WASH == pDriver->index)//当前正在清洗
    {
		if (pDriver->flags.m_bits.bEnMove)
		{
			if (pDriver->flags.m_bits.bMoveEnd)
			{
				tag = pDriver->pHardware->pTabPos[pDriver->posLevel] + MOVE_WASH_OFFSET;
			}
			else
			{
				tag = pDriver->pHardware->pTabPos[pDriver->posLevel] - MOVE_WASH_OFFSET;
			}
			
			if(!f_StepmotorIsAtPos(pDriver->pHardware->pNozzleSM, tag))
			{
				f_StepmotorSetTarget(pDriver->pHardware->pNozzleSM, tag, false);//非强制到位
			}
			else 
			{
				pDriver->flags.m_bits.bMoveEnd ^= true;
			}
		}
    }
    
	if (pDriver->index >= WASH_INDEX_SET_POS 
	&& pDriver->index <= WASH_INDEX_WASH)//喷杆伸出和清洗之间能调整
	{
	    if (pDriver->bChangePos)
	    {
	        pDriver->bChangePos = false;
	    	tag = pDriver->pHardware->pTabPos[pDriver->posLevel];
			if(!f_StepmotorIsAtPos(pDriver->pHardware->pNozzleSM, tag))
			{
				f_StepmotorSetTarget(pDriver->pHardware->pNozzleSM, tag, true);//强制到位
			}
	    }
    }
}

/*****************************************************************************
 函 数 名: f_FuncSetPos
 功能描述  : 设置管位
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月12日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncSetPos(FUNC_WASH *pDriver, FUNC_SET_LEVEL pos, uchar bForce)
{
    if (bForce 
    || (false == bForce && pos != pDriver->posLevel)) //防止极限位置反复设置
    {
        pDriver->posLevel = pos;
        pDriver->bChangePos = true;
    }
}

/*****************************************************************************
 函 数 名: f_FuncSetWashMove
 功能描述  : 设置移动清洗
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_FuncSetWashMove(FUNC_WASH *pDriver, STATE_INFO state)
{
	if (WASH_INDEX_WASH == pDriver->index)//当前正在清洗
	{
	    if (state != pDriver->flags.m_bits.bEnMove) //和当前功能状态不同
	    {
    		if (STATE_ON == state)
    		{
    			pDriver->flags.m_bits.bEnMove = true;	
    			pDriver->flags.m_bits.bMoveEnd = false; //先向前移动
    		}
    		else
    		{
    			pDriver->flags.m_bits.bEnMove = false;
    			pDriver->bChangePos = true; //防止关闭时喷杆位置不正确
    		}
    		return true;
		}
	}
	return false;
}

/*****************************************************************************
 函 数 名: f_FuncWashColdHeatCtrl
 功能描述  : 冷热按摩控制
 输入参数:
 返 回 值: 
 注     意: 100ms调用
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncWashColdHotCtrl(FUNC_WASH *pDriver)
{
    if (WASH_INDEX_WASH == pDriver->index)//当前正在清洗
    {
		if (pDriver->flags.m_bits.bEnColdHot)
		{
			f_AddU8Data(&(pDriver->coldHotTm));

			if (pDriver->bEnHeat)
			{
				if (pDriver->coldHotTm >= WASH_HOT_TM)
				{
					pDriver->coldHotTm = 0;
					pDriver->bEnHeat = false;
				}
			}
			else
			{
				if (pDriver->coldHotTm >= WASH_COLD_TM)
				{
					pDriver->coldHotTm = 0;
					pDriver->bEnHeat = true;
				}
			}
		}
		else 
		{
			pDriver->bEnHeat = true;
		}
    }
}

/*****************************************************************************
 函 数 名: f_FuncSetColdHeat
 功能描述  : 设置冷热清洗
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_FuncSetColdHot(FUNC_WASH *pDriver, STATE_INFO state)
{
    if (WASH_INDEX_WASH == pDriver->index)//当前正在清洗
	{
	    if (state != pDriver->flags.m_bits.bEnColdHot) //和当前功能状态不同
	    {
    		if (STATE_ON == state)
    		{
    			pDriver->flags.m_bits.bEnColdHot = true;		
    		}
    		else
    		{
    			pDriver->flags.m_bits.bEnColdHot = false;
    		}
    		pDriver->coldHotTm = WASH_HOT_TM; //启动后先启动冷冲洗
    		return true;
		}
	}
	return false;
}

/*****************************************************************************
 函 数 名: f_FuncWashFlowCtrl
 功能描述  : 清洗流量控制
 输入参数:
 返 回 值: 
 注     意: 100ms调用
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncWashFlowCtrl(FUNC_WASH *pDriver)
{
    sint tag = 0;
    
    if (WASH_INDEX_WASH == pDriver->index)//当前正在清洗
    {
		if (pDriver->flags.m_bits.bEnStrongWeak)
		{
			f_AddU8Data(&(pDriver->strongWeakTm));
			if (pDriver->strongWeakTm >= WASH_STRONG_WEAK_GAP_TM)
			{
				pDriver->strongWeakTm = 0;
				if (pDriver->flags.m_bits.bFlowMax)//从高到底
				{
					if (pDriver->strongWeakLevel > FUNC_SET_LEVEL_NULL)
					{
						pDriver->strongWeakLevel--;
					}
					else
					{
						pDriver->flags.m_bits.bFlowMax = false;
					}
				}
				else//从底到高
				{
					if (pDriver->strongWeakLevel < FUNC_SET_LEVEL_3)
					{
						pDriver->strongWeakLevel++;
					}
					else
					{
						pDriver->flags.m_bits.bFlowMax = true;
					}
				}
			}
			pDriver->setPumpPercent = tab_WashPumpPercent[pDriver->strongWeakLevel];
		}
		else 
		{
            //调整气泵
//			pDriver->setPumpPercent = tab_WashPumpPercent[pDriver->flowLevel];
            if (pDriver->flags.m_bits.bEnAirPump)
            {
                pDriver->setPumpPercent = 100;
            }
            else
            {
                pDriver->setPumpPercent = 0;
            }
		}
    }

    if (pDriver->index >= WASH_INDEX_SET_FLOW 
	&& pDriver->index <= WASH_INDEX_WASH)//流量调整和清洗之间能调整
	{
	    if (pDriver->bChangeFlow)
	    {
	        pDriver->bChangeFlow = false;
	    	tag = pDriver->pHardware->pTabFlow[pDriver->flowLevel];
			if(!f_StepmotorIsAtPos(pDriver->pHardware->pFlowSM, tag))
			{
				f_StepmotorSetTarget(pDriver->pHardware->pFlowSM, tag, true);//强制到位
			}
	    }
    }
}

/*****************************************************************************
 函 数 名: f_FuncSetFlow
 功能描述  : 设置流量
 输入参数:    
               
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月12日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncSetFlow(FUNC_WASH *pDriver, FUNC_SET_LEVEL flow, uchar bForce)
{
    if (bForce 
    || (false == bForce && flow != pDriver->flowLevel)) //防止极限位置反复设置
    {
        pDriver->flowLevel = flow;
        pDriver->bChangeFlow = true;
    }
}

/*****************************************************************************
 函 数 名: f_FuncSetPurge
 功能描述  : 设置气泵通便功能
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年6月12日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_FuncSetPurge(FUNC_WASH *pDriver, STATE_INFO state)
{   
    uchar ret = false;
    if (WASH_INDEX_WASH == pDriver->index)//当前正在清洗
    {
        pDriver->flags.m_bits.bEnAirPump = state;
        ret = true;
    }
    return ret;
}

/*****************************************************************************
 函 数 名: f_FuncSetStrongWeak
 功能描述  : 强弱按摩设置
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_FuncSetStrongWeak(FUNC_WASH *pDriver, STATE_INFO state)
{
    if (WASH_INDEX_WASH == pDriver->index)
    {
        if (state != pDriver->flags.m_bits.bEnStrongWeak) //和当前功能状态不同
        {
    		if (STATE_ON == state)
    		{
    			pDriver->flags.m_bits.bEnStrongWeak = true;
    			pDriver->strongWeakLevel = pDriver->flowLevel;
    			pDriver->strongWeakTm = 0;
    			pDriver->flags.m_bits.bFlowMax = false;
    		}
    		else
    		{
    			pDriver->flags.m_bits.bEnStrongWeak = false;
    		}
    		return true;
		}
    }
    
    return false;
}

/*****************************************************************************
 函 数 名: f_FuncWashDeal
 功能描述  : 清洗流程处理
 输入参数:
 返 回 值: 
 注     意: 100ms调用
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncWashStep(FUNC_WASH *pDriver)
{
	f_AddU8Data(&(pDriver->waitTm));
    switch (pDriver->index)
    {
		case WASH_INDEX_ORG://归原点
			//进水阀关闭、气泵关闭
			pDriver->bEnInwaterValve = false;
			pDriver->setPumpPercent = 0;
		
			//喷杆电机回原点
			if (pDriver->bNeedPosBack)//是否强制需要回
			{
				f_FuncWashChangePos(pDriver, SM_ORG_POS);
			}
			else
			{
				pDriver->flags.m_bits.bPosAtTag = true;
			}

			//流量电机回原点
			f_FuncWashChangeFlow(pDriver, SM_ORG_POS);

			//水温加热关闭
			pDriver->bEnHeat = false;

			//当前流程结束判断
			if (pDriver->flags.m_bits.bPosAtTag && pDriver->flags.m_bits.bFlowAtTag)
			{
				f_FuncWashNext(pDriver, WASH_INDEX_PER_WASH);
			}
			break;

		case WASH_INDEX_PER_WASH:
			//进水阀开启, 气泵关闭
			pDriver->bEnInwaterValve = true;
			pDriver->setPumpPercent = 0;

			//加热开启
			pDriver->bEnHeat = true;
			
			//当前流程结束判断
			if (pDriver->waitTm >= 30)//强制前清洗3S后伸出喷杆
			{
				f_FuncWashNext(pDriver, WASH_INDEX_SET_POS);
			}
			break;

		case WASH_INDEX_SET_POS:
			//进水阀开启, 气泵关闭
			pDriver->bEnInwaterValve = true;
			pDriver->setPumpPercent = 0;

			//加热开启
			pDriver->bEnHeat = true;

			//调整喷杆位置
			f_FuncWashChangePos(pDriver, pDriver->pHardware->pTabPos[pDriver->posLevel]);
			
			//当前流程结束判断
			if (pDriver->flags.m_bits.bPosAtTag)
			{
				f_FuncWashNext(pDriver, WASH_INDEX_SET_FLOW);
			}
			break;

		case WASH_INDEX_SET_FLOW:
			//进水阀开启, 气泵关闭
			pDriver->bEnInwaterValve = true;
			pDriver->setPumpPercent = 0;

			//加热开启
			pDriver->bEnHeat = true;

			//TUDO qbj 
//			if (pDriver->waitTm >= 70 
//			|| pDriver)//等待超时 或者 到达设置温度附近
			{
				//调整流量位置
				f_FuncWashChangeFlow(pDriver, pDriver->pHardware->pTabFlow[pDriver->flowLevel]);
			}
			
			//当前流程结束判断
			if (pDriver->flags.m_bits.bFlowAtTag)
			{
				f_FuncWashNext(pDriver, WASH_INDEX_WASH);

				//参数赋值需要在f_FuncWashNext后，因为f_FuncWashNext会清零参数
				pDriver->flags.m_bits.bRealStart = true; //开始真正清洗
			}
			break;
			
		case WASH_INDEX_WASH:
			//进水阀开启, 气泵开启(由f_FuncWashFlowCtrl控制)
			pDriver->bEnInwaterValve = true;

			//气泵、加热由f_FuncWashFlowCtrl和f_FuncWashColdHotCtrl
			
			//结束由外部控制
			break;

		case WASH_INDEX_BACK_FLOW:
            //进水阀关闭, 气泵关闭
            pDriver->bEnInwaterValve = false;
            pDriver->setPumpPercent = 0;

            //水温加热关闭
            pDriver->bEnHeat = false;

			//流量电机回原点
			f_FuncWashChangeFlow(pDriver, SM_ORG_POS);
			
			//当前流程结束判断
			if (pDriver->flags.m_bits.bFlowAtTag)//流量到位
			{
				f_FuncWashNext(pDriver, WASH_INDEX_BACK_POS);
			}
			break;
			
		case WASH_INDEX_BACK_POS:
			//进水阀开启, 气泵关闭
			pDriver->bEnInwaterValve = true;
			pDriver->setPumpPercent = 0;

			//水温加热关闭
			pDriver->bEnHeat = false;

			if (false == pDriver->flags.m_bits.bPosBackReset)
			{
				//喷杆先回缩复位(以最大位置复位)
				if (false == pDriver->flags.m_bits.bResetCurPos)
				{
				    //重设档位位置为喷杆向前OFFSET位置，这样会复位会多走回
				    pDriver->flags.m_bits.bResetCurPos = true;
    				f_StepmotorOffsetCurPos(pDriver->pHardware->pNozzleSM, SM_NOZZLE_MORE_OFFSET);
				}
				f_FuncWashChangePos(pDriver, SM_NOZZLE_MIN_POS);
				
				if (pDriver->flags.m_bits.bPosAtTag)
				{
					pDriver->flags.m_bits.bPosBackReset = true;
					pDriver->flags.m_bits.bPosAtTag = false;
				}
			}
			else
			{
				//喷杆电机回原点
				f_FuncWashChangePos(pDriver, SM_ORG_POS); //重洗回原点，会往前几步，防止喷杆受力
			}

			//当前流程结束判断
			if (pDriver->flags.m_bits.bPosBackReset 
			&& pDriver->flags.m_bits.bPosAtTag)//喷杆到位
			{
				f_FuncWashNext(pDriver, WASH_INDEX_BACK_WASH);
			}
			break;
			
		case WASH_INDEX_BACK_WASH:
			//进水阀开启, 气泵关闭
			pDriver->bEnInwaterValve = true;
			pDriver->setPumpPercent = 0;

			//水温加热关闭
			pDriver->bEnHeat = false;

			//当前流程结束判断
			if (pDriver->waitTm >= 30)//强制后清洗3S后结束
			{
				f_FuncWashNext(pDriver, WASH_INDEX_CLEAN);
			}
			break;

		case WASH_INDEX_CLEAN:
			//进水阀关闭, 气泵打开
			pDriver->bEnInwaterValve = false;
			pDriver->setPumpPercent = 100;

			//水温加热关闭
			pDriver->bEnHeat = false;
			
			//流量电机复位
			if (pDriver->flags.m_bits.bFlowReset == false)
			{
				pDriver->flags.m_bits.bFlowReset = true;
				f_StepmotorReset(pDriver->pHardware->pFlowSM);
			}

			//当前流程结束判断
			if (f_StepmotorResetIsOver(pDriver->pHardware->pFlowSM))//流量电机复位完成
			{
				f_FuncWashNext(pDriver, WASH_INDEX_END);
			}
			break;

		case WASH_INDEX_END://清洗结束
			//进水阀关闭, 气泵关闭
			pDriver->bEnInwaterValve = false;
			pDriver->setPumpPercent = 0;
		
			//水温加热关闭
			pDriver->bEnHeat = false;
			
			pDriver->flags.m_byte = 0;
			pDriver->bNeedPosBack = true;
			pDriver->bChangeFlow = false;
			pDriver->bChangePos = false;
			break;

		default:
			break;
    }
}

/*****************************************************************************
 函 数 名: f_FuncWashDeal
 功能描述  : 清洗相关处理
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月19日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncWashDeal(void)
{
	uchar percent;
	
    f_FuncWashStep(&funcWashHip);//臀部清洗处理
	f_FuncWashPosCtrl(&funcWashHip);
	f_FuncWashFlowCtrl(&funcWashHip);
	f_FuncWashColdHotCtrl(&funcWashHip);	

	f_FuncWashStep(&funcWashFemale);//女性清洗处理
	f_FuncWashPosCtrl(&funcWashFemale);
	f_FuncWashFlowCtrl(&funcWashFemale);
	f_FuncWashColdHotCtrl(&funcWashFemale);

	//====负载控制====
	//喷杆自洁控制
	if (functionInfo.bCleanPosCtrl)
	{
	    functionInfo.bCleanPosCtrl = false;
    	if(functionInfo.bSelfClean)
    	{
    		f_StepmotorSetTarget(&nozzleStepmotor, SM_NOZZLE_MAX_POS, true);//强制到最大
    	}
    	else
    	{
    		f_StepmotorSetTarget(&nozzleStepmotor, SM_ORG_POS, true);//强制恢复
    	}
	}
	
	//进水阀控制
	if (funcWashHip.bEnInwaterValve 
	|| funcWashFemale.bEnInwaterValve 
	|| functionInfo.bSelfClean 
	|| funcSit.bClean)
	{
		f_FuncSetInwaterValve(STATE_ON);	
//		f_FuncSetUV(STATE_ON);
	}
	else
	{
		f_FuncSetInwaterValve(STATE_OFF);
//		f_FuncSetUV(STATE_OFF);
	}

	//气泵控制
	percent = funcWashHip.setPumpPercent > funcWashFemale.setPumpPercent? funcWashHip.setPumpPercent:funcWashFemale.setPumpPercent;
	f_FuncSetAirPump(percent);

	//====水温处理====
    if ((funcWashHip.bEnHeat || funcWashFemale.bEnHeat) && functionInfo.waterTempLevel > FUNC_SET_LEVEL_NULL)
    {
		functionInfo.bEnHeat = true;
		functionInfo.outTempInfo.setTemp = realWatHeatTemp[functionInfo.waterTempLevel];
    }
    else
    {
		functionInfo.bEnHeat = false;
		functionInfo.outTempInfo.setTemp = 0;
    }
}

/*****************************************************************************
 函 数 名: f_FuncWashInit
 功能描述: 清洗驱动初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月11日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_FuncWashInit(FUNC_WASH *pDriver, const FUNC_WASH_HARDWARE *pHardware)
{
    f_Memset(pDriver, 0, sizeof(FUNC_WASH));
    pDriver->pHardware = pHardware;
    pDriver->index = WASH_INDEX_END;
    pDriver->bNeedPosBack = true;
}

