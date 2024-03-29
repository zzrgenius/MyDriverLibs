#ifndef __KEYDRIVER_H__
#define __KEYDRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

struct Key_Driver;

/*----------------------------------------------*
 * 定义                                           *
 *----------------------------------------------*/
 
//按键硬件驱动
typedef struct Key_Hardware_Driver
{
	void (*GetKeys)(struct Key_Driver *pKeyDriver);
}KeyHardwareDriver;
 
//按键驱动
typedef struct Key_Driver
{
	
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
