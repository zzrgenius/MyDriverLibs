#ifndef __KEYDRIVER_H__
#define __KEYDRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

struct Key_Driver;

/*----------------------------------------------*
 * 数据类型定义                                       *
 *----------------------------------------------*/
 
//按键硬件驱动
typedef struct
{
	void (*GetKeys)(struct Key_Driver *pKeyDriver);
}KeyHardwareDriver;

//按键数据
typedef struct
{
	uint keyPressTm;
}KeyDriverData;
 
//按键驱动
typedef struct Key_Driver
{

	KeyHardwareDriver const *pHardDriver;
}KeyDriver;
 

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/




/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/

//按键驱动初始化注册函数
void f_KeyDriverInit();
 


#endif /* __KEYDRIVER_H__ */
