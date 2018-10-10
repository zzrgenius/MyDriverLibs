#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "KeyDriverConfig.h"

struct Key_Driver;

/*----------------------------------------------*
 * 数据类型定义                                       *
 *----------------------------------------------*/
 
//按键硬件驱动
typedef struct
{
	uchar keyShakeCnt;
	void (*GetKeys)(struct Key_Driver *pKeyDriver);
}KeyHardwareDriver;

//按键处理阶段
typedef enum 
{
	KEY_DEAL_INIT = 0,
	KEY_DEAL_IDLE,
	KEY_DEAL_PRESS,
	KEY_DEAL_WATE_RELEASE//等待释放
}KeyDealStep;

//按键处理标志
typedef union
{
	byte_8 byte;
	struct
	{
		byte_8 bKeyDeal		:1; //按键已处理标志
		byte_8 bHasKey		:1; //有按键按下
	}bit;
}KeyFlags;

//按键数据
typedef struct
{
	uint 	keyPressTm;//按键按下时间
	ulong 	keyName;
	ulong 	newKeyName;
	KeyState keyState;
}KeyDriverData;
 
//按键驱动
typedef struct Key_Driver
{
	KeyDriverData	keyData;
	KeyDealStep		keyDealStep;
	KeyFlags		keyFlag;
	KeyHardwareDriver const *pHardDriver;
}KeyDriver;
 

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/




/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/

//按键驱动初始化注册函数
void f_KeyDriverInit(KeyDriver const *pKeyDriver);
 


#endif /* __KEYDRIVER_H__ */
