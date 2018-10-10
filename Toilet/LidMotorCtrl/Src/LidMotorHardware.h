#ifndef __LID_MOTOR_HARDWARE_H__
#define __LID_MOTOR_HARDWARE_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "LidMotorDriver.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern const LID_MOTOR_HARDWARE seatLidHardware;
extern const LID_MOTOR_HARDWARE topLidHardware;

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_SeatLidSetFwdSpeed(STATE_INFO state);
void f_SeatLidSetRevSpeed(STATE_INFO state);
void f_TopLidSetFwdSpeed(STATE_INFO state);
void f_TopLidSetRevSpeed(STATE_INFO state);

#endif /* __LID_MOTOR_HARDWARE_H__ */
