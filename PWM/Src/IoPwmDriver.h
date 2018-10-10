#ifndef __IO_PWM_DRIVER_H__
#define __IO_PWM_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
typedef void (*SetOut)(STATE_INFO);

typedef struct 
{
	uint setHighTm; //设置高电平时间
	uint setPeriodTm; //设置周期时间
	uint curTm; //当前计算时间
	uint fourceHighTm; //强制输出高次数
	uint setFourceHighTm;
	uchar bFourceHigh:1; //强制输出高

	SetOut IO_OUT; //硬件输出
}IO_PWM_DRIVER;//模拟pwm输出
/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_IoPwmDriverInit(IO_PWM_DRIVER *pDriver, SetOut io, uint period);
void f_IoPwmDriverOut(IO_PWM_DRIVER *pDriver);
void f_IoPwmDriverSetFource(IO_PWM_DRIVER *pDriver, uint tm);
void f_IoPwmDriverSetPercent(IO_PWM_DRIVER *pDriver, uchar percent);

#endif /* __IO_PWM_DRIVER_H__ */
