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
uchar tempFilterCnt;

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/
#define AD_BASE_TEMP -10
//0位置 短路值;max位置开路值
const uint Tab_NTC_5KF3470[]=
{
	100,//传感器开路值
	750, 778, 806, 834, 864, 894, 924, 955, 986, 1018, //-10~-1
	1050, 1083, 1116, 1150, 1184, 1218, 1254, 1290, 1326, 1363, //0~9
	1401, 1438, 1476, 1515, 1553, 1592, 1631, 1670, 1709, 1749, //10~19
	1788, 1828, 1867, 1906, 1946, 1985, 2024, 2063, 2101, 2140, //20~29
	2178, 2216, 2254, 2291, 2328, 2364, 2401, 2436, 2472, 2507, //30~39
	2541, 2575, 2609, 2641, 2674, 2706, 2737, 2768, 2799, 2829, //40~49
	2858, 2887, 2915, 2942, 2969, 2995, 3022, 3047, 3072, 3096, //50~59
	3120,//60
	3900//传感器短路值
};

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
uint f_GetTemperatureIndex(uint getAD, const uint *pTable, uint size, uint degree)
{
	uint startIndex = 0;
	uint endIndex = size - 1;
	uchar upIndexFlag ;
	uint middle;
	uint findAD;
	int offset;
	uint index;

	if (pTable[0] < pTable[size -1])
	{
		//升序
		upIndexFlag = true;
	}
	else
	{
		//降序
		upIndexFlag = 0;
	}

	if ((upIndexFlag && getAD >= pTable[endIndex])
	|| (false == upIndexFlag && getAD <= pTable[endIndex])) //超过最大温度
	{
        index = endIndex*degree;
	}
	else if ((upIndexFlag && getAD <= pTable[startIndex])
	|| (false == upIndexFlag && getAD >= pTable[startIndex])) //低于最小温度
	{
        index = startIndex*degree;
	}
	else //检索
	{
    	while (startIndex <= endIndex)
    	{
    		middle = (startIndex + endIndex)/2;

    		if (getAD == pTable[middle])
    		{
    			break;
    		}
    		else if (getAD < pTable[middle])
    		{
    			if (true == upIndexFlag)
    			{
    				endIndex = middle -1;
    			}
    			else
    			{
    				startIndex = middle + 1;
    			}
    		}
    		else
    		{
    			if (true == upIndexFlag)
    			{
    				startIndex = middle + 1;
    			}
    			else
    			{
    				endIndex = middle -1;
    			}
    		}
    	}

    	//温度四舍五入处理
        findAD = pTable[middle];
    	index = middle*degree;
    	if (true == upIndexFlag) //升序
    	{
    	    if (findAD > getAD)
    	    {
                offset = findAD - getAD;//找到数据偏大的位置
                index -= offset/((pTable[middle] - pTable[middle - 1])/(degree+1) + 1); // 最后+1防止整除不对
    	    }
    	    else
    	    {
                offset = getAD - findAD;//找到数据偏小的位置
                index += offset/((pTable[middle + 1] - pTable[middle])/(degree+1) + 1); // 最后+1防止整除不对
    	    }   
    	}
    	else //降序
    	{
    	    if (findAD > getAD)
    	    {
                offset = findAD - getAD;//找到数据偏小的位置
                index += offset/((pTable[middle] - pTable[middle + 1])/(degree+1) + 1); // 最后+1防止整除不对
    	    }
    	    else
    	    {
                offset = getAD - findAD;//找到数据偏大的位置
                index -= offset/((pTable[middle - 1] - pTable[middle])/(degree+1) + 1); // 最后+1防止整除不对
    	    } 
    	}
	}

	return index;
}
 
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
	uint index;
	sint temperature;
	
    adValue = f_GetSensorAD(pDriver, pDriver->pHardware->channel);

    if ((pDriver->pHardware->isUp && adValue >= pDriver->pHardware->pTab_NTC[0])
    || (!pDriver->pHardware->isUp && adValue <= pDriver->pHardware->pTab_NTC[0]))//开路
    {
		pDriver->sensorInf.bShortFlag = false;
		pDriver->sensorInf.bOpenFlag = true;
    }
    else if ((pDriver->pHardware->isUp && adValue <= pDriver->pHardware->pTab_NTC[pDriver->pHardware->size - 1])
    || (!pDriver->pHardware->isUp && adValue >= pDriver->pHardware->pTab_NTC[pDriver->pHardware->size - 1]))//短路
    {
		pDriver->sensorInf.bShortFlag = true;
		pDriver->sensorInf.bOpenFlag = false;
    }
    else
    {
		pDriver->sensorInf.bShortFlag = false;
		pDriver->sensorInf.bOpenFlag = false;
		
	    //根据AD值查表,获取温度
	    index = f_GetTemperatureIndex(adValue, &pDriver->pHardware->pTab_NTC[1], pDriver->pHardware->size - 2, pDriver->pHardware->degree);
	    temperature = (sint)index + pDriver->pHardware->baseTemp;

	    if (pDriver->sensorInf.lastSensorTemp == temperature)
	    {
	    	pDriver->filterCnt ++;
	    	if (pDriver->filterCnt >= pDriver->pHardware->needFilterCnt)
	    	{
	    		pDriver->filterCnt = pDriver->pHardware->needFilterCnt;
				pDriver->sensorInf.sensorTemp = temperature;
			}
	    }
	    else 
	    {
			pDriver->filterCnt = 0;
	    }
	    pDriver->sensorInf.lastSensorTemp = temperature;
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

