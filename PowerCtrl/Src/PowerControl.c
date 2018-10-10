/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : PowerControl.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月13日
  最近修改   :
  功能描述   : 用于含过零光耦的可控硅控制(如MOC3063M),可按一个半波精度控制。目前先按50HZ设计
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
 #include "DataType.h"
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
#define POWER_PERIOD_TM	100 //电源周期*0.1ms- 50HZ 
const uint setGroupPeriodTm	= POWER_CTRL_GROUP_NUM*POWER_PERIOD_TM;//每大组周期

//计算顺序表
const uchar tab_PowerCalcIndex[POWER_CTRL_GROUP_NUM]
={0, 5, 2, 7, 4, 9, 1, 6, 3, 8};


/*****************************************************************************
 函 数 名: void f_PowerCtrlOut(POWER_CTRL *pPowerCtrl)
 功能描述: 用于功率控制输出
 输入参数:
 返 回 值: 
 注     意: 100us中断调用
 
 修改历史:
  1.日    期   : 2018年4月14日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PowerCtrlOut(POWER_CTRL *pPowerCtrl)
{
    f_AddU16Data(&(pPowerCtrl->data.periodTm));

	//单个大周期未到
    if (pPowerCtrl->data.periodTm <= setGroupPeriodTm)
    {
   		if (NULL != pPowerCtrl->pHardwareFunc)
		{
			//底层硬件控制
			if (pPowerCtrl->data.periodTm <= pPowerCtrl->data.periodOnTm[pPowerCtrl->data.ctrlGroupIndex])
			{
				pPowerCtrl->pHardwareFunc(pPowerCtrl, POWER_CTRL_ON);
			}
			else
			{
				pPowerCtrl->pHardwareFunc(pPowerCtrl, POWER_CTRL_OFF);
			}
		}
    }
    else
    {
    	//单个大周期结束,转下一个周期
		pPowerCtrl->data.periodTm = 0;
		pPowerCtrl->data.ctrlGroupIndex ++;
		if (pPowerCtrl->data.ctrlGroupIndex >= POWER_CTRL_GROUP_NUM)
		{
			pPowerCtrl->data.ctrlGroupIndex = 0;
		}
    }
}

/*****************************************************************************
 函 数 名: f_PowerCtrlCalc
 功能描述  : 根据输入的功率百分比换算需要开启关闭时间              
 输入参数: pPowerCtrl:功率控制驱动指针;
 		   percent：控制百分比
 返 回 值: 
 注     意: 需要时调用
 
 修改历史:
  1.日    期   : 2018年4月14日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PowerCtrlCalc(POWER_CTRL *pPowerCtrl, uchar percent)
{
	uchar needOnGroupNum;
	uchar needOnPartNum;
	uchar i;

    //最大不超过100%
	if(percent > 100)
	{
		percent = 100;
	}

	needOnGroupNum = percent/POWER_CTRL_GROUP_NUM;//每组都开启时间部分	
	needOnPartNum = percent%POWER_CTRL_GROUP_NUM;//剩余部分

	//设置每组都加的百分比
	for(i = 0; i < POWER_CTRL_GROUP_NUM; i ++)
	{
		pPowerCtrl->data.periodOnTm[tab_PowerCalcIndex[i]] = (uint)(needOnGroupNum)*POWER_PERIOD_TM;
	}

    //剩余优先控制的组,每组加1%,既半个工频时间
    for(i = 0; i < needOnPartNum; i ++)
    {
        pPowerCtrl->data.periodOnTm[tab_PowerCalcIndex[i]] += POWER_PERIOD_TM;
    }
}

/*****************************************************************************
 函 数 名: f_PowerCtrlInit
 功能描述  : 功率控制驱动初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月14日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_PowerCtrlInit(POWER_CTRL *pPowerCtrl, const PowerCtrlHardware pFunc)
{
    f_Memset(pPowerCtrl, 0, sizeof(POWER_CTRL));
    pPowerCtrl->pHardwareFunc = pFunc;
}

