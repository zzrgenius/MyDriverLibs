/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : TempSensor.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月23日
  最近修改   :
  功能描述   : 温度传感器相关处理
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月23日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "TempSensor.h"
#include "MCU_Hardware.h"
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

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

/*****************************************************************************
 函 数 名: f_GetSensorAD
 功能描述  : 获取传感器AD,去头尾取平均
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月23日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uint f_GetSensorAD(TEMP_SENSOR_DRIVER *pDriver, uchar channel)
{
	return pDriver->pHardware->getAD(channel);
}

/*****************************************************************************
 函 数 名: f_GetSensorTemp
 功能描述  : 获取传感器温度
 输入参数: 
 返 回 值: 
 注     意: 100ms调用一次
 
 修改历史:
  1.日    期   : 2018年4月23日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_GetSensorTemp(TEMP_SENSOR_DRIVER *pDriver)
{
	uint adValue;
	sint temperature;
	slong volt;
	
    adValue = f_GetSensorAD(pDriver, pDriver->pHardware->channel);

    if ((pDriver->pHardware->isUp && adValue >= pDriver->pHardware->openAD)
    || (!pDriver->pHardware->isUp && adValue <= pDriver->pHardware->openAD))//开路
    {
		pDriver->sensorInf.bShortFlag = false;
		pDriver->sensorInf.bOpenFlag = true;
    }
    else if ((pDriver->pHardware->isUp && adValue <= pDriver->pHardware->shortAD)
    || (!pDriver->pHardware->isUp && adValue >= pDriver->pHardware->shortAD))//短路
    {
		pDriver->sensorInf.bShortFlag = true;
		pDriver->sensorInf.bOpenFlag = false;
    }
    else
    {
		pDriver->sensorInf.bShortFlag = false;
		pDriver->sensorInf.bOpenFlag = false;

		//5*AD/1024 10bitAD 电压结果放大1000倍 如果电压不是5V 参数需要修改，目前先固定到驱动，后续需要可以移到硬件层
        volt = 5000*(slong)(adValue)>>12; 
	    temperature = pDriver->pHardware->getTempResult(volt, pDriver->pHardware->degree);

        pDriver->sensorInf.sensorTemp = f_RecurrenceAverageFilter(temperature, pDriver->filterWind, MAX_FILTER_WIND_CNT); //滤波次数
	    pDriver->sensorInf.realSensorTemp = temperature;
    }
}

/*****************************************************************************
 函 数 名: f_TempSensorInit
 功能描述  : 温度传感器驱动初始化
 输入参数: pDriver:驱动指针
           pHardware:底层硬件指针
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月7日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_TempSensorInit(TEMP_SENSOR_DRIVER *pDriver, const TEMP_SENSOR_HARDWARE *pHardware)
{
    f_Memset(pDriver, 0, sizeof(TEMP_SENSOR_DRIVER));
	pDriver->pHardware = pHardware;
}

