/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : IRProtocol.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月10日
  最近修改   :
  功能描述   : 红外协议处理
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
 函 数 名: f_IRRevDataDeal
 功能描述: 红外结束数据处理
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月10日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_IRRevDataDeal(uchar *pData, uchar len)
{
	REMOTER_PROTOCOL revInfo;
	
    if (len != sizeof(REMOTER_PROTOCOL))
    {
		return;
    }

    f_MemCpy(&revInfo, pData, len);

    //====协议解析====
    //按键码
    functionInfo.keyCode = revInfo.keyCode;
    
    //水温
    if (revInfo.waterLevel != functionInfo.waterTempLevel 
    && revInfo.waterLevel <= FUNC_SET_LEVEL_3)
    {
    	functionInfo.waterTempLevel = revInfo.waterLevel;
    	f_StorageWriteValues(&storageDriver, STORAGE_WATER_LEVEL, true);
    }

	//坐温
    if (revInfo.seatLevel != functionInfo.seatTempLevel 
    && revInfo.seatLevel <= FUNC_SET_LEVEL_3)
    {
    	functionInfo.seatTempLevel = revInfo.seatLevel;
    	f_StorageWriteValues(&storageDriver, STORAGE_SEAT_LEVEL, true);
    }

	//风温
    if (revInfo.dryLevel != functionInfo.dryTempLevel 
    && revInfo.dryLevel <= FUNC_SET_LEVEL_3)
    {
    	functionInfo.dryTempLevel = revInfo.dryLevel;
    	f_StorageWriteValues(&storageDriver, STORAGE_DRY_LEVEL, true);
    }

    //管位
    revInfo.nozzlePos += 1;//设备管位L1~L4(遥控管位0~3)
    if (revInfo.nozzlePos != functionInfo.setPos 
    && revInfo.nozzlePos <= FUNC_SET_LEVEL_4)
    {
    	functionInfo.setPos = revInfo.nozzlePos;
    	f_StorageWriteValues(&storageDriver, STORAGE_POS_LEVEL, true);
    }

    //流量
    if (revInfo.flowLevel != functionInfo.setFlow 
    && revInfo.flowLevel <= FUNC_SET_LEVEL_3)
    {
    	functionInfo.setFlow = revInfo.flowLevel;
    	f_StorageWriteValues(&storageDriver, STORAGE_FLOW_LEVEL, true);
    }
}


