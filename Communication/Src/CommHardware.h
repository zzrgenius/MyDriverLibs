#ifndef __COMM_HARDWARE_H__
#define __COMM_HARDWARE_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "IO_Define.h"
#include "CommDriver.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern const COMM_HARDWARE uart1Hardware;
extern const COMM_HARDWARE uart2Hardware;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_UART1_RevData(COMM_DRIVER *pDriver);
void f_UART1_SendData(COMM_DRIVER *pDriver);

void f_UART2_RevData(COMM_DRIVER *pDriver);
void f_UART2_SendData(COMM_DRIVER *pDriver);

#endif /* __COMM_HARDWARE_H__ */
