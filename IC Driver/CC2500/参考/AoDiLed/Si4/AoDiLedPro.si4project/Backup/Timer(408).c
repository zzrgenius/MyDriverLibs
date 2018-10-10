#define VAR_TIME_GLOBALS
#include "Include.h"

/*=========================================================
* 功能描述: Delay延时函数
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_Delay(uint rTime)
{
	uint i;
	for(i =0; i < rTime;i++)
	{
		NOP();
	}
}
// 10ms延时函数
/*void f_DelayMs(uchar rTime)
{
	tTime.delayCnt = rTime;
	while(tTime.delayCnt);
}*/

/*=========================================================
* 功能描述: 定时器1溢出中断
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
IT_HEADE void TIM1_OverFlowIRQHandler(void)//100us
{ 
	TIM1_SR1 &= (~0x01);
	TIM1_SR2 = 0;
	t1msFlag = 1;
	tTime.time10msCnt++;
	tTime.time30msCnt++;
	tTime.time200msCnt++;
	tTime.time500msCnt++;
	tTime.time1000msCnt++;
	//tTime.time1msCnt++;
	if(tTime.time10msCnt > 9)//10ms
	{
		tTime.time10msCnt = 0;
		t10msFlag = 1;   
	}
	if(tTime.time30msCnt > 29)//30ms
	{
		t30msFlag = 1;  
		tTime.time30msCnt = 0;
	}
	if(tTime.time200msCnt >199)//200ms
	{
		tTime.time200msCnt = 0;
		LedPowerFlickS ^= true;
		t200msFlag = 1;    
	}
	if(tTime.time500msCnt >499)//500ms
	{
		tTime.time500msCnt= 0;
		t500msFlag = 1;   
		LedWaterRFlickS ^=true;
		LedWaterBFlickS ^=true;
		LedWaterGFlickS ^=true;
		LedDryRFlickS ^=true;
	}
	if(tTime.time1000msCnt > 999)//1000ms
	{
		tTime.time1000msCnt = 0;
		t1sFlag = 1; 
    	}   
}
