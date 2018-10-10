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
  			1、修改按键名称定义中的单键、组合键
  			2、根据项目需要修改长按的自定义状态及时间，如1S等
  			3、填写KeyDriverConfig.c中Tab_KeySelfState
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月12日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

#ifndef __KEY_DRIVER_CONFIG_H__
#define __KEY_DRIVER_CONFIG_H__

/*----------------------------------------------*
 * 按键名称定义  
 * 
 *说明：每个按键占1位，使用ulong(32位)表示，从0x00000001开始定义
 *----------------------------------------------*/
#define KEY_DRIVER_NO_KEY 0	//无按键状态
 
//单键定义
#define KEY_SIGLE_POWER 0x00000001//电源键
#define KEY_SIGLE_STOP  0x00000002//停止键
#define KEY_SIGLE_WASH  0x00000004//清洗键

//组合键定义
#define KEY_COMM_RESER (KEY_SIGLE_POWER | KEY_SIGLE_STOP)//组合键复位

/*----------------------------------------------*
 * 按键状态定义                                       *
 *----------------------------------------------*/
typedef enum 
{
	KEY_STATE_IDLE = 0,
	KEY_PRESSED = 0x01,
	KEY_RELEASE = 0x02,
	KEY_STATE_1 = 0x04,//以下状态用于自定义
	KEY_STATE_2 = 0x08,
	KEY_STATE_3 = 0x10,
	KEY_STATE_4 = 0x20,
	KEY_STATE_5 = 0x40,
	KEY_STATE_6 = 0x80
}KeyState;

#define KEY_PRESS_1S KEY_STATE_1
#define KEY_PRESS_1S_TM 100//*10ms

#define KEY_PRESS_3S KEY_STATE_2
#define KEY_PRESS_3S_TM 300//*10ms

#define KEY_PRESS_5S KEY_STATE_3
#define KEY_PRESS_5S_TM 500//*10ms

typedef struct
{
	unsigned int stateTime;
	KeyState selfState;
}KeySelfState;//自定义按键状态

#define GetTime(nKey)		(Tab_KeySelfState[nKey].stateTime)//获取对应名字按键时间
#define SetTimeInf(nKey)	(Tab_KeySelfState[nKey].selfState)//对达到时间的，赋值按键状态

/*----------------------------------------------*
 * 按键其他说明                                       *
 *----------------------------------------------*/
extern const KeySelfState Tab_KeySelfState[];


#endif
