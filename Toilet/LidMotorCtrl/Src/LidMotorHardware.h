#ifndef __LID_MOTOR_HARDWARE_H__
#define __LID_MOTOR_HARDWARE_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "LidMotorDriver.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern const LID_MOTOR_HARDWARE seatLidHardware;
extern const LID_MOTOR_HARDWARE topLidHardware;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_SeatLidSetFwdSpeed(STATE_INFO state);
void f_SeatLidSetRevSpeed(STATE_INFO state);
void f_TopLidSetFwdSpeed(STATE_INFO state);
void f_TopLidSetRevSpeed(STATE_INFO state);

#endif /* __LID_MOTOR_HARDWARE_H__ */
