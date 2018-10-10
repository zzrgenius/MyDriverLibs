#ifndef __TIMER_H
#define __TIMER_H

#ifdef  VAR_TIME_GLOBALS
	#define  VAR_TIME_EXT
#else
	#define  VAR_TIME_EXT  extern
#endif

VAR_TIME_EXT AT_NEAR byte_def tTimeFlag;
#define	t1msFlag			tTimeFlag.m_bit.b0
#define	t10msFlag		tTimeFlag.m_bit.b1
#define	t100msFlag		tTimeFlag.m_bit.b2
#define	t200msFlag		tTimeFlag.m_bit.b3
#define	t500msFlag		tTimeFlag.m_bit.b4
#define	t1sFlag			tTimeFlag.m_bit.b5
#define	t30msFlag		tTimeFlag.m_bit.b6
typedef struct
{
	//uint    	time1msCnt;
	uchar	t10msTask;
	uchar    	time30msCnt;
	uchar	t100msTask;
	uchar 	time1sCnt;
	uchar	delayCnt;
	uchar 	time10msCnt;
	uchar 	time100msCnt;
	uchar 	time200msCnt;
	uint		time500msCnt;
	uint		time1000msCnt;
}TIME;	
VAR_TIME_EXT AT_NEAR TIME tTime;

VAR_TIME_EXT void f_Delay(uint rTime);
//VAR_TIME_EXT void f_DelayMs(uchar rTime);
VAR_TIME_EXT IT_HEADE void TIM1_OverFlowIRQHandler(void);
VAR_TIME_EXT IT_HEADE void TIM4_OverFlowIRQHandler(void);

#endif	//__TIMER_H
