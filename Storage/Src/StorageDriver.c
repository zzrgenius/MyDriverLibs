/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : StorageDriver.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月9日
  最近修改   :
  功能描述   : 数据存储相关
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月9日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "StorageDriver.h"
#include "SubFunction.h"
#include "StorageConfig.h"
#include "FlashToEEPROM.h"

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
STORAGE_DRIVER storageDriver;

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/
#define STORAGE_HEAD_SIZE sizeof(storageInitFlag)
const char storageInitFlag[] = "XDD_V2"; //存储参数版本号，每修改存储参数数量，修改一下版本号，用于重新初始化数据

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
#define CHANGE_BLOCK_ERROR_CNT 20//累积写失败次数，换分区
#define MAX_WRITE_TIMES 450000//芯片读写次数*1.5
#define BLOCK_RAMGE 1024

#define STORAGE_USE_FLASH //是否需要用flash存储

/*****************************************************************************
 函 数 名: f_StorageGetVersion
 功能描述  : 获取版本存储信息
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月29日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_StorageGetVersion(const uchar **pData, uchar *pSize)
{
    *pData = (const uchar *)storageInitFlag;
    *pSize = sizeof(storageInitFlag);
}


/*****************************************************************************
 函 数 名: f_StorageJudgeBlock
 功能描述: 判断当前存储区块是否适合存储，如果存储满，则换区块存储
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月9日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_StorageJudgeBlock(STORAGE_DRIVER *PDriver)
{
    int valueOffset;
    int i;

    PDriver->data.blockWriteCnt ++;

    //超过块写次数或者分区写错误次数太多则换分区
    if (PDriver->data.blockWriteCnt >= MAX_WRITE_TIMES || PDriver->data.writeErrCnt > CHANGE_BLOCK_ERROR_CNT)
    {
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            valueOffset += tab_StorageValue[i].valueSize;
        }
        valueOffset += 1;

        PDriver->data.blockWriteCnt = 0;
        PDriver->data.writeErrCnt = 0;

        //可正常切换存储区块,如果满了则一直写最后一个区块
        if (PDriver->data.baseAddr + valueOffset < BLOCK_RAMGE)
        {
            PDriver->data.baseAddr += valueOffset;
            //存储数据迁移到新区块
            for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
            {
                f_StorageWriteValues(PDriver, i, false);
            }
        }
        PDriver->pHardware->writeFunc(BASE_ADDR_OFFSET, sizeof(PDriver->data.baseAddr), (uchar *)&(PDriver->data.baseAddr));
    }

    //防止写入太频繁,累积50次写入
    if (PDriver->data.blockWriteCnt % 50 == 0)
    {
        f_StorageWriteValues(PDriver, STORAGE_INDEX_WRITE_CNT, false);
    }
}

/*****************************************************************************
 函 数 名: f_StorageWriteValues
 功能描述  : 存储写入变量
 输入参数: pDriver驱动指针
 		   index在表中序号
 		   check 是否检查块
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月9日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_StorageWriteValues(STORAGE_DRIVER *PDriver, uchar index, uchar check)
{
    uint realOffset;
    int i;

	if (check)//是否需要块检测，防止递归
	{
		#ifndef STORAGE_USE_FLASH
    	f_StorageJudgeBlock(PDriver);
		#endif
    }

    realOffset = PDriver->data.baseAddr;
    if (index > 0)
    {
        for (i = 0; i < index; i++)
        {
            realOffset += tab_StorageValue[i].valueSize;
        }
    }

    if (false == PDriver->pHardware->writeFunc(realOffset, tab_StorageValue[index].valueSize, (uchar *)tab_StorageValue[index].pValue))
    {
        PDriver->data.writeErrCnt++;
    }
}

/*****************************************************************************
 函 数 名: f_StorageReadValues
 功能描述  : 存储读数据
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月9日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_StorageReadValues(STORAGE_DRIVER *PDriver, uchar index)
{
    uint realOffset = PDriver->data.baseAddr;
    int i;

    if (index > 0)
    {
        for (i = 0; i < index; i++)
        {
            //计算当前变量的实际存储偏移量
            realOffset += tab_StorageValue[i].valueSize;
        }
    }
    PDriver->pHardware->readFunc(realOffset, tab_StorageValue[index].valueSize, (uchar *)tab_StorageValue[index].pValue);
}


/*****************************************************************************
 函 数 名: f_StoragerInit
 功能描述  : 存储初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月9日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_StoragerInit(STORAGE_DRIVER *PDriver, const STORAGE_HARDWARE *pHardware)
{
    char head[STORAGE_HEAD_SIZE];
    uint i;

    #ifdef STORAGE_USE_FLASH
        f_FlashToEEPROMInit(); //flash模拟eeprom初始化
    #endif

    //注册读写函数
    f_Memset(PDriver, 0, sizeof(STORAGE_DRIVER));
    PDriver->pHardware = pHardware;

    //读出头，判断是否为首次启动
    PDriver->pHardware->readFunc(HEAD_OFFSET, STORAGE_HEAD_SIZE, (uchar *)&head);
    if (f_CmpChars(head, storageInitFlag, STORAGE_HEAD_SIZE))
    {
        PDriver->pHardware->readFunc(BASE_ADDR_OFFSET, sizeof(PDriver->data.baseAddr), (uchar *)&(PDriver->data.baseAddr));

        //已初始化过，读出数据
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            f_StorageReadValues(PDriver, i);
        }

        //范围校验
        f_StorageRangeCheck();
    }
    else
    {
        //初始化偏移地址,并存储
        PDriver->data.baseAddr = BASE_ADDR_VALUE;
        PDriver->pHardware->writeFunc(BASE_ADDR_OFFSET, sizeof(PDriver->data.baseAddr), (uchar *)&(PDriver->data.baseAddr));

        //初始化数据并写入存储区
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            //初始化赋值
            f_MemCpy(tab_StorageValue[i].pValue, tab_StorageValue[i].pInitValue, tab_StorageValue[i].valueSize);

            //写入存储
            f_StorageWriteValues(PDriver, i, true);
        }
        PDriver->pHardware->writeFunc(HEAD_OFFSET, STORAGE_HEAD_SIZE, (const uchar *)storageInitFlag); //写首次上电信息
    }
}

