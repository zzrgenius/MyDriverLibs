#ifndef __IO_PWM_DRIVER_H__
#define __IO_PWM_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
typedef void (*SetOut)(STATE_INFO);

typedef struct 
{
	uint setHighTm; //���øߵ�ƽʱ��
	uint setPeriodTm; //��������ʱ��
	uint curTm; //��ǰ����ʱ��
	uint fourceHighTm; //ǿ������ߴ���
	uint setFourceHighTm;
	uchar bFourceHigh:1; //ǿ�������

	SetOut IO_OUT; //Ӳ�����
}IO_PWM_DRIVER;//ģ��pwm���
/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_IoPwmDriverInit(IO_PWM_DRIVER *pDriver, SetOut io, uint period);
void f_IoPwmDriverOut(IO_PWM_DRIVER *pDriver);
void f_IoPwmDriverSetFource(IO_PWM_DRIVER *pDriver, uint tm);
void f_IoPwmDriverSetPercent(IO_PWM_DRIVER *pDriver, uchar percent);

#endif /* __IO_PWM_DRIVER_H__ */
