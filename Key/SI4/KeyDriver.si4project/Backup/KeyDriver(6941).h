#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "KeyDriverConfig.h"

/*----------------------------------------------*
 * 前置声明                                         *
 *----------------------------------------------*/
struct Key_Driver;

/*----------------------------------------------*
 * 数据类型定义                                       *
 *----------------------------------------------*/
 
//按键硬件驱动
typedef struct
{
	uchar keyShakeCnt;
	void (*GetKeys)(struct Key_Driver *pKeyDriver);
}KEY_HARDWARE_DRIVER;

//按键处理阶段
typedef enum 
{
	KEY_DEAL_INIT = 0,
	KEY_DEAL_IDLE,
	KEY_DEAL_PRESS,
	KEY_DEAL_WATE_RELEASE//等待释放
}KEY_DEAL_STEP;

//按键处理标志
typedef union
{
	byte_8 byte;
	struct
	{
		byte_8 bDealDone	:1; //按键已处理标志
		byte_8 bHasKey		:1; //有按键按下
	}bit;
}KEY_FLAG;

//按键数据
typedef struct
{
	uint 		pressTm;//按键按下时间
	ulong 		name;
	ulong 		newName;
	KEY_STATE 	state;
}KEY_DRIVER_DATA;

//回调函数指针
typedef void (*KeyDriverCallback)(struct Key_Driver *pKeyDriver);
 
//按键驱动
typedef struct Key_Driver
{
	KEY_DRIVER_DATA	data;		//按键处理数据
	KEY_DEAL_STEP	dealStep;	//按键处理步骤
	KEY_FLAG		flag;		//按键相关标志位
	KEY_HARDWARE_DRIVER const *pHardDriver;//按键硬件驱动指针
	KeyDriverCallback dealCallback;//按键处理回调函数指针
}KEY_DRIVER;
 

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_KeyDriverInit(KEY_DRIVER       *pKeyDriver,
							KEY_HARDWARE_DRIVER const *pKeyDriverHardware, 
							KeyDriverCallback const pKeyDealFunc);
void f_KeyDriverDeal(KEY_DRIVER *pKeyDriver);


#endif /* __KEYDRIVER_H__ */
