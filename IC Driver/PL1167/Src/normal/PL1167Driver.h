#ifndef __PL1167_DRIVER_H__
#define __PL1167_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern uchar PL1167SnedBuffer[];
extern uchar PL1167SendWaitTm;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_PL1167Init(void);
void f_PL1167ChangeFreq(void);
void f_PL1167SendDeal(void);
void f_PL1167RevDeal(void);
void f_PL1167StartSend(void);
void f_PL1167InitReg(void);
void f_PL1167IntoSleep(void);

#endif /* __PL1167_DRIVER_H__ */
