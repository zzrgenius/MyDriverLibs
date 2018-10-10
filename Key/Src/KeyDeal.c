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
#include "HeadInclude.h"

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
		case KEY_SIGLE_HIP://臀部
			if (f_IsKeyState(KEY_RELEASE))
			{
				//调用后无释放信息产生
				f_SetKeyDealDone();

				functionInfo.keyCode = 0x50;
			}
			else if (f_IsKeyState(KEY_PRESS_3S))
			{
				//调用后无释放信息产生
				f_SetKeyDealDone();

				if (STATE_ON == funcSit.sitSwitch.state)//着座为强弱
				{
					functionInfo.keyCode = 0x51;
				}
				else //离座为喷杆自洁(仅伸出喷杆)
				{
					functionInfo.keyCode = 0x90;//自定义按键码
				}
			}
			break;
			
		case KEY_SIGLE_FEMAL:
			if (f_IsKeyState(KEY_RELEASE))
			{
				//调用后无释放信息产生
				f_SetKeyDealDone();

				functionInfo.keyCode = 0x52;
			}
			else if (f_IsKeyState(KEY_PRESS_3S))
			{
				//调用后无释放信息产生
				f_SetKeyDealDone();

				functionInfo.keyCode = 0x53;
			}
			break;

		case KEY_SIGLE_STOP:
			if (f_IsKeyState(KEY_RELEASE))
			{
				//调用后无释放信息产生
				f_SetKeyDealDone();

				if (SYS_STATE_STANDBY == systemInfo.sysState)
				{
					functionInfo.keyCode = 0x60; //开机
				}
 				else 
				{
					functionInfo.keyCode = 0x76; //停止
				}
			}
			else if (f_IsKeyState(KEY_PRESS_3S))
			{
				if (SYS_STATE_RUN == systemInfo.sysState)
				{
					//调用后无释放信息产生
					f_SetKeyDealDone();
					functionInfo.keyCode = 0x61; //关机
				}
			}
			break;
			
		case KEY_COMM_SIT://模拟着座
			if (f_IsKeyState(KEY_PRESSED))
			{
				//调用后无释放信息产生
				f_SetKeyDealDone();
				
				functionInfo.keyCode = 0x91; //蜂鸣声
			}
			else if (f_IsKeyState(KEY_PRESS_3S))
			{
				if (SYS_STATE_RUN == systemInfo.sysState)
				{
					//调用后无释放信息产生
					f_SetKeyDealDone();
					
					functionInfo.keyCode = 0x91; //蜂鸣声
					funcSit.bFourceSit = true; //模拟着座打开
				}
			}
			break;

		case KEY_COMM_INTO_AGEING://老化
			if (f_IsKeyState(KEY_PRESS_3S))
			{
				if (SYS_STATE_RUN == systemInfo.sysState 
				&& funcSit.bFourceSit) //必须先模拟着座
				{
					//调用后无释放信息产生
					f_SetKeyDealDone();
					
					functionInfo.keyCode = 0x92; //老化功能
				}
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


