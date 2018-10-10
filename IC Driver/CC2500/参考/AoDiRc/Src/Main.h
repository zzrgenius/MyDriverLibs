#ifndef __MAIN_H
#define __MAIN_H

#ifdef   VAR_MAIN_GLOBALS
	#define  VAR_MAIN_EXT
#else
	#define  VAR_MAIN_EXT  extern
#endif

//=================MUC=====================
#ifdef  USE_AT_NEAR
	#define  AT_NEAR @near
#else
	#define  AT_NEAR  volatile
#endif

//#define USE_AT_FAR						//使用@far

#ifdef  USE_AT_FAR
	#define  AT_FAR @far
#else
	#define  AT_FAR  
#endif

#define FALSE 	0
#define TRUE 		1
/*********************************************************************
* Interior Global Variables
********************************************************************/

VAR_MAIN_EXT TYPE_WORD nTime_Flag;
#define		 b5msFlag				nTime_Flag.m_bit.b0
#define		 b10msFlag		 	 	nTime_Flag.m_bit.b1
#define		 b50msFlag				nTime_Flag.m_bit.b2
#define		 b100msFlag	 	 	 	nTime_Flag.m_bit.b3
#define		 b250msFlag			 	nTime_Flag.m_bit.b4
#define		 b500msFlag				nTime_Flag.m_bit.b6
#define		 b1sFlag			 	nTime_Flag.m_bit.b7
#define		 bSleepLongTm			nTime_Flag.m_bit.b8
#define		 bInSleepFlag			nTime_Flag.m_bit.b9
#define		 bFirstOutSleepFlag		nTime_Flag.m_bit.b10
	
#define		 b1HzFlag				nTime_Flag.m_bit.b12//1HZ
#define		 b0d5HzFlag				nTime_Flag.m_bit.b13//1/2HZ
	
VAR_MAIN_EXT uchar nPowerOnTm;				//开机计时器
VAR_MAIN_EXT uchar nKeyWakeTm;					//按键唤醒时间
VAR_MAIN_EXT uchar nLowPowerCnt;			//低电压计数
VAR_MAIN_EXT uchar ADDR[3];


/*********************************************************************
* Extern Global Function
********************************************************************/

VAR_MAIN_EXT void main(void);						
VAR_MAIN_EXT void f_pCalTm(void);	
VAR_MAIN_EXT void f_pGoToHalt(void);

#endif 	// __MAIN_H