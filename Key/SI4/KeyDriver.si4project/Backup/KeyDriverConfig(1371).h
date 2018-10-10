#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__

/*----------------------------------------------*
 * 按键名称定义  
 * 
 *说明：每个按键占1位，使用ulong(32位)表示，从0x00000001开始定义
 *----------------------------------------------*/
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
	KEY_IDLE = 0,
	KEY_PRESSED = 0x01,
	KEY_RELEASE = 0x02,
	KEY_STATE_1 = 0x04,//以下状态用于自定义
	KEY_STATE_2 = 0x08,
	KEY_STATE_3 = 0x10,
	KEY_STATE_4 = 0x20,
	KEY_STATE_5 = 0x40,
	KEY_STATE_5 = 0x80
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
