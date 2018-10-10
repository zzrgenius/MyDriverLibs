/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : KeyDriverConfig.h
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月12日
  最近修改   :
  功能描述   : 按键配置，需要根据具体项目修改。
  			修改步骤：
  			1、修改按键名称定义中的单键、组合键(修改按键定义)
  			2、根据项目需要修改长按的自定义状态及时间，如1S等(修改自定义状态)
  			3、填写KeyDriverConfig.c中Tab_KeySelfState
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月12日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

#ifndef __KEY_DRIVER_CONFIG_H__
#define __KEY_DRIVER_CONFIG_H__

#include "DataType.h"

/*----------------------------------------------*
 * 按键名称定义  
 * 
 *说明：每个按键占1位，使用ulong(32位)表示，从0x00000001开始定义
 *----------------------------------------------*/
#define KEY_DRIVER_NO_KEY 0	//无按键状态
#define KEY_DRIVER_ALL_KEY 0xffffffff

//！！！！----修改按键定义----！！！！
//单键定义
#define KEY_SIGLE_POWER 0x00000001//电源键
#define KEY_SIGLE_STOP  0x00000002//停止键
#define KEY_SIGLE_WASH  0x00000004//清洗键

//组合键定义
#define KEY_COMM_RESER (KEY_SIGLE_POWER | KEY_SIGLE_STOP)//组合键复位

//独立处理按键定义
#define KEY_DRIVER_INDE_KEY_NUM	2//独立处理按键个数
#define KEY_INDE_HOT			0x00000008//热水键
#define KEY_INDE_COLD			0x00000010//冷水键
//！！！！-----------------------！！！！

/*----------------------------------------------*
 * 按键状态定义                                       *
 *----------------------------------------------*/
typedef enum 
{
	KEY_STATE_IDLE = 0,
	KEY_PRESSED = 0x01,
	KEY_RELEASE = 0x02,
	KEY_LOCKED  = 0x04,
	KEY_STATE_1 = 0x08,//以下状态用于自定义
	KEY_STATE_2 = 0x10,
	KEY_STATE_3 = 0x20,
	KEY_STATE_4 = 0x40,
	KEY_STATE_5 = 0x80,
	KEY_STATE_RESERVE = 0xff
}KEY_STATE;

#define f_GetKeyName()		(pKeyDriver->data.name)		
#define f_IsKeyState(State) (pKeyDriver->data.state & State)
#define f_SetKeyDealDone()	(pKeyDriver->data.keyDone |= pKeyDriver->data.name)
#define f_GetKeyDealDone(name)	((pKeyDriver->data.keyDone&name) != KEY_DRIVER_NO_KEY?true:false)
#define f_RemoveKey(key)	(pKeyDriver->data.mask &= ~(key))


//！！！！----修改自定义状态----！！！！
#define KEY_LOCK_TM 2000//按键长按卡住时长 20S

#define KEY_PRESS_1S KEY_STATE_1 //自定义长按状态1S
#define KEY_PRESS_1S_TM 100//*10ms

#define KEY_PRESS_3S KEY_STATE_2
#define KEY_PRESS_3S_TM 300//*10ms

#define KEY_PRESS_5S KEY_STATE_3
#define KEY_PRESS_5S_TM 500//*10ms
//！！！！-----------------------！！！！

typedef struct
{
	unsigned int stateTime;
	KEY_STATE selfState;
}KEY_SELF_STATE;//自定义按键状态

#define f_GetKeyStateTime(index)		(Tab_KeySelfState[index].stateTime)//获取对应名字按键时间
#define f_SetKeyTimeState(index)		(Tab_KeySelfState[index].selfState)//对达到时间的，赋值按键状态

/*----------------------------------------------*
 * 按键其他说明                                       *
 *----------------------------------------------*/
extern const KEY_SELF_STATE Tab_KeySelfState[];
extern const ulong Tab_IndeKeyValue[];

#endif

