#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__



/*----------------------------------------------*
 * 按键名称定义  
 * 
 *说明：每个按键占1位，使用ulong(32位)表示，从0x00000001开始定义
 *----------------------------------------------*/
//单键定义
#define KEY_NAME_POWER 0x00000001//电源键
#define KEY_NAME_STOP  0x00000002//停止键
#define KEY_NAME_WASH  0x00000004//清洗键

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

#define KEY_PRESSED_1S KEY_STATE_1
#define KEY_PRESSED_3S KEY_STATE_2
#define KEY_PRESSED_5S KEY_STATE_3

/*----------------------------------------------*
 * 按键其他说明                                       *
 *----------------------------------------------*/



#endif
