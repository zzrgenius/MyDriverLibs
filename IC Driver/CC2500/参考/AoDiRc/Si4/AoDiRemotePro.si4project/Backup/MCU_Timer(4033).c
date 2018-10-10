#define VAR_TIMER_GLOBALS
#include "Include.h"

static unsigned char n1msCnt = 0;

//stm定时中断
void __attribute((interrupt(0x0c))) f_Time0_ISR(void)
{
	if(_t0af==1)
	{
		_t0af=0;
		
		n1msCnt ++;
		if(n1msCnt % 5 == 0)
		{
			b5msFlag = true;
		}
		if(n1msCnt >= 10)
		{
			n1msCnt = 0;
			b10msFlag = true;
		}
	}
	
}

//stm定时中断
/*void __attribute((interrupt(0x10))) f_Time2_ISR(void)
{
	if(_t2af==1)
	{
		_t2af=0;

		#ifndef ISM_CHECK_MODE
			f_JudgeOneBitSend();//ISM模块发送判断	
		#endif
	}
	
}*/
