#ifndef __COMM_HARDWARE_H__
#define __COMM_HARDWARE_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "IO_Define.h"
#include "CommDriver.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern const COMM_HARDWARE uart1Hardware;
extern const COMM_HARDWARE uart2Hardware;

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_UART1_RevData(COMM_DRIVER *pDriver);
void f_UART1_SendData(COMM_DRIVER *pDriver);

void f_UART2_RevData(COMM_DRIVER *pDriver);
void f_UART2_SendData(COMM_DRIVER *pDriver);

#endif /* __COMM_HARDWARE_H__ */
