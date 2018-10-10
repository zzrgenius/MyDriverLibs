/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : StorageConfig.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月28日 星期一
  最近修改   :
  功能描述   : 存储参数表配置
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "StorageConfig.h"
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

//====初始化值====
const ulong initValue_0 = 0;
const SYSTEM_STATE initSysState = SYS_STATE_RUN;
const uchar initSaveFlag = 1;
const uint initRound_1_Tm = 70; //*100ms
const uint initBottomTm = 60; //*100ms
const uint initRound_2_Tm = 50; //*100ms

const STORAGE_TYPE tab_StorageValue[] =
{
    {(void *)&(storageDriver.data.blockWriteCnt), sizeof(storageDriver.data.blockWriteCnt), (void *)&initValue_0},//STORAGE_WriteCnt
    {(void *)&(systemInfo.sysState), sizeof(SYSTEM_STATE), (void *)&initSysState}, //系统状态
    {(void *)&(functionInfo.saveFlags.m_byte), sizeof(uchar), (void *)&initSaveFlag}, //自动翻盖、夜灯，默认自动翻盖开
    {(void *)&(funcFlush.saveFlushtm[FLUSH_ADJUST_WASH]), sizeof(uint), (void *)&initRound_1_Tm}, //洗刷时间
    {(void *)&(funcFlush.saveFlushtm[FLUSH_ADJUST_CLEAN]), sizeof(uint), (void *)&initBottomTm}, //排污时间
    {(void *)&(funcFlush.saveFlushtm[FLUSH_ADJUST_BACK]), sizeof(uint), (void *)&initRound_2_Tm} //回水时间
};

const uint storageTableSize = (sizeof(tab_StorageValue)/sizeof(tab_StorageValue[0]));

//====存储数据范围,需要一一对应====
//写数据
const RANGE_ULONG_TYPE writeCntRange = 
{	
	0, //最小
	0xffffffff //最大
};

//系统状态
const RANGE_UCHAR_TYPE systemStateRange = 
{   
    SYS_STATE_STANDBY, //最小
    SYS_STATE_SELFCHECK //最大
};

//系统状态
const RANGE_UCHAR_TYPE saveFlagsRange = 
{   
    0, //最小
    3 //最大
};

//冲洗时间范围
const RANGE_UINT_TYPE flushTmRange = 
{   
    40, //最小,单位100ms
    100 //最大,单位100ms
};

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/


/*****************************************************************************
 函 数 名: f_StorageRangeCheck
 功能描述  : 存储数据范围判断
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年6月4日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_StorageRangeCheck(void)
{
    if (storageDriver.data.blockWriteCnt < writeCntRange.min 
    || storageDriver.data.blockWriteCnt > writeCntRange.max )
    {
        storageDriver.data.blockWriteCnt = initValue_0;  
        f_StorageWriteValues(&storageDriver, STORAGE_INDEX_WRITE_CNT, true);
    }

    if (systemInfo.sysState < systemStateRange.min 
    || systemInfo.sysState > systemStateRange.max )
    {
        systemInfo.sysState = initSysState; 
        f_StorageWriteValues(&storageDriver, STORAGE_SYS_STATE, true);
    }

    if (functionInfo.saveFlags.m_byte < saveFlagsRange.min 
    || functionInfo.saveFlags.m_byte > saveFlagsRange.max )
    {
        functionInfo.saveFlags.m_byte = initSaveFlag;   
        f_StorageWriteValues(&storageDriver, STORAGE_SYS_FLAGS, true);
    }

    if (funcFlush.saveFlushtm[FLUSH_ADJUST_WASH] < flushTmRange.min 
    || funcFlush.saveFlushtm[FLUSH_ADJUST_WASH] > flushTmRange.max )
    {
		funcFlush.saveFlushtm[FLUSH_ADJUST_WASH] = initRound_1_Tm; 
        f_StorageWriteValues(&storageDriver, STORAGE_ROUND_1_TM, true);     
    }

    if (funcFlush.saveFlushtm[FLUSH_ADJUST_CLEAN] < flushTmRange.min 
    || funcFlush.saveFlushtm[FLUSH_ADJUST_CLEAN] > flushTmRange.max )
    {
		funcFlush.saveFlushtm[FLUSH_ADJUST_CLEAN] = initBottomTm; 
        f_StorageWriteValues(&storageDriver, STORAGE_BOTTOM_TM, true);    
    }

    if (funcFlush.saveFlushtm[FLUSH_ADJUST_BACK] < flushTmRange.min 
    || funcFlush.saveFlushtm[FLUSH_ADJUST_BACK] > flushTmRange.max )
    {
		funcFlush.saveFlushtm[FLUSH_ADJUST_BACK] = initRound_2_Tm; 
        f_StorageWriteValues(&storageDriver, STORAGE_ROUND_2_TM, true);    
    }
}


