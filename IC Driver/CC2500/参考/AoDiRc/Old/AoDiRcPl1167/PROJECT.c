#define VAR_MAIN_GLOBALS
#include "HT66F018.h"
#include "Main.h"
//#include "Include.h"

void main()
{
	if(_to && _pdf)//看门狗休眠复位
	{
		GCC_NOP();
		GCC_NOP();
	}
	else
	{
	//	f_MCU_InitSfr();
	}
	while(1)
	{
	//	f_MCU_FeedDog();//喂狗
	}

}

/* =========================================================
* 函 数 名: void f_CalTm()
* 功能描述: 计算运行时间,如果到60秒则分加1,并保存各时间最大值
* 调用方法: f_CalTm();
* 调用函数: 无
* 全局变量: 
========================================================= */
void f_CalTm(void)
{
	if(b10msFlag)	//10ms到
	{
		b10msFlag = false;
		n50msCnt ++;
		if(n50msCnt >= 5)								//50ms meeted
		{
			n50msCnt = 0;
			b50msFlag = true;
			n1sCnt ++;
			if((n1sCnt % 2) == 0)						//100ms meeted
			{
				b100msFlag = true;
			}
			if((n1sCnt % 5) == 0)						//250ms meeted 
			{
				b250msFlag = true;
			}		
			if((n1sCnt % 10) == 0)						//500ms meeted 
			{
				b500msFlag = true;
				b1HzFlag ^= true;
			}
				
			if(n1sCnt >= 20)							//1s meeted
			{
				n1sCnt = 0;
				b1sFlag = true;
				b0d5HzFlag ^= true;
			}
		}
	}
	if(b100msFlag)	//100ms meeted
	{
		b100msFlag = false;
	}
	if(b250msFlag)
	{
		b250msFlag = false;
	}
	if(b500msFlag)
	{
		b500msFlag = false;
	}
	if(b1sFlag)	//1S meeted
	{
		b1sFlag = false;	
	}
}