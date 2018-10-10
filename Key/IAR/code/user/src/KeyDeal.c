/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : KeyDeal.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月12日
  最近修改   :
  功能描述   : 按键功能应用处理，根据不同项目处理对应按键状态
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月12日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "KeyDeal.h"

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/
extern const KEY_HARDWARE_DRIVER keyHardware;

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/
KEY_DRIVER keyDriver;
int testValue = 0;

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
 函 数 名: f_KeyDeal
 功能描述  : 按键处理函数
 输入参数: 无
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月12日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_KeyDeal(KEY_DRIVER *pKeyDriver)
{
	switch(f_GetKeyName())
	{
		case KEY_SIGLE_POWER:
			if (f_IsKeyState(KEY_RELEASE))
			{
				f_SetKeyDealDone();

				//处理代码
                                testValue ++;
				
			}
                        else if (f_IsKeyState(KEY_PRESS_5S))
			{
				f_SetKeyDealDone();

				//处理代码
				
				
			}
			break;

		case KEY_SIGLE_STOP:
			if (f_IsKeyState(KEY_RELEASE))
			{
				f_SetKeyDealDone();
				//处理代码
                                testValue --;
				
			}
			break;

		case KEY_SIGLE_WASH:
			if (f_IsKeyState(KEY_PRESSED))
			{
				f_SetKeyDealDone();
				//处理代码
				
			}
			break;

		case KEY_COMM_RESER:
			if (f_IsKeyState(KEY_PRESS_1S))
			{
				f_SetKeyDealDone();
				//处理代码
                                testValue += 10;
				
			}
			break;
                        
                 case KEY_INDE_HOT:
			if (f_IsKeyState(KEY_PRESS_1S))
			{
				f_SetKeyDealDone();
				//处理代码
                                testValue += 3;
				
			}
			break;
                        
                 case KEY_INDE_COLD:
			if (f_IsKeyState(KEY_PRESSED))
			{
				f_SetKeyDealDone();
				//处理代码
				testValue -= 3;
			}
			break;

		default:
			break;
	} 
}

/*****************************************************************************
 函 数 名: f_KeyDealInit
 功能描述  : 按键按功能处理初始化
 输入参数: 无
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月12日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_KeyDealInit(void)
{
    f_KeyDriverInit(&keyDriver, &keyHardware, f_KeyDeal);
}


