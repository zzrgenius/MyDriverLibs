#ifndef __PL1167_DRIVER_H__
#define __PL1167_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern uchar PL1167SnedBuffer[];
extern uchar PL1167SendWaitTm;

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_PL1167Init(void);
void f_PL1167ChangeFreq(void);
void f_PL1167SendDeal(void);
void f_PL1167RevDeal(void);
void f_PL1167StartSend(void);
void f_PL1167InitReg(void);
void f_PL1167IntoSleep(void);

#endif /* __PL1167_DRIVER_H__ */
