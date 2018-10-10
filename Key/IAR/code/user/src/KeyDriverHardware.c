/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : KeyDriverHardware.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月11日
  最近修改   :
  功能描述   : 按键硬件转换，便于后续按键处理
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月11日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "KeyDriver.h"
#include "TimeFlag.h"
#include "drive.h"

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/
void f_GetKeys(KEY_DRIVER *pKeyDriver);

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/
const KEY_HARDWARE_DRIVER keyHardware
=
{
	5,//对应机械按键，建议10m获取一次去抖时间50ms，对应芯片读取建议50ms调用连续2次时间100ms
	f_GetKeys
};


/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
 #define KEY_SHAKE_CNT 5

#define READ_KEY_S1  PC_IDR_IDR3
#define READ_KEY_S2  PC_IDR_IDR4
#define READ_KEY_S3  PC_IDR_IDR5
#define READ_KEY_S4  PC_IDR_IDR6
#define READ_KEY_S5  PC_IDR_IDR7
#define READ_KEY_S6  PD_IDR_IDR2
#define READ_KEY_S7  PD_IDR_IDR3
#define READ_KEY_S8  PA_IDR_IDR1
#define READ_KEY_S9  PA_IDR_IDR2
/*****************************************************************************
 函 数 名: f_GetKeys
 功能描述: 
 输入参数: 无
 返 回 值: 
 注     意: 对于普通按键10ms一次，对于驱动芯片获取50ms一次
 
 修改历史:
  1.日    期   : 2018年4月12日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_GetKeys(KEY_DRIVER *pKeyDriver)
{
	ulong getKeyValue;
	static ulong lastGetKeyValue;
	static uchar curShakeCnt;//当前去抖时间
	
	if (f_IsSysTime10Ms())//10ms
	{
		getKeyValue = KEY_DRIVER_NO_KEY;
		//按键转换
		if (!READ_KEY_S1)//电源键
		{
			getKeyValue |= KEY_SIGLE_POWER;
		}

		if (!READ_KEY_S2)//停止键
		{
			getKeyValue |= KEY_SIGLE_STOP;
		}
                
                if (!READ_KEY_S3)//电源键
		{
			getKeyValue |= KEY_INDE_HOT;
		}

		if (!READ_KEY_S4)//停止键
		{
			getKeyValue |= KEY_INDE_COLD;
		}

		//按键状态去抖处理
		if (getKeyValue == lastGetKeyValue)
		{
			if (curShakeCnt < pKeyDriver->pHardDriver->keyShakeCnt)
			{
				curShakeCnt ++;
			}
			else
			{
				pKeyDriver->data.getKeys = getKeyValue;
			}
		}
		else
		{
			curShakeCnt = 0;
			lastGetKeyValue = getKeyValue;
		}
	}
}

