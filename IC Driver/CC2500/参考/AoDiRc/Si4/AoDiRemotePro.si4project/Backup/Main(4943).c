#define VAR_MAIN_GLOBALS
#include "Include.h"

uchar f_MCU_HT_ReadMore(uchar nReadAdd)
{
	uchar ReadData;

	_eea = nReadAdd;//设置EE地址
	_mp1 = 0x40;//设置EE指针
	__eec.bits.__rden = 1;//设置RDEN
	__eec.bits.__rd = 1;//开启读周期
	while(__eec.bits.__rd);//判断读结束
	NOP();
	NOP();
	NOP();
	_eec = 0;//清寄存器EEC
	ReadData = _eed;//读数据
	
	_mp1 = 0x00;//设置指针
	_eea = 0;
	_eed = 0;
	return ReadData;
}

void main(void)
{
	if(_to && _pdf)//看门狗休眠复位
	{
		GCC_NOP();
		GCC_NOP();
	}
	else
	{
		f_pSfrInit();
		PL1167_Init();
		ADDR[0] = f_MCU_HT_ReadMore(0);					//地址码1
		ADDR[1] = f_MCU_HT_ReadMore(1);					//地址码2		
		ADDR[2] = f_MCU_HT_ReadMore(2);					//地址码3
	}
	while(1)
	{
		f_pFeedDog();//喂狗
		f_SendBuffer();
		f_SendDeal();
		f_RfRecDeal();
		f_CalTm();
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
	//static unsigned char temp=0;
	if(b5msFlag)
	{
		b5msFlag = false;
	}
	if(b10msFlag)	//10ms到
	{
		b10msFlag = false;
		f_KeyScan();//按键扫描
		f_KeyDeal();//按键处理
		n50msCnt ++;
		if(n50msCnt >= 5)								//50ms meeted
		{
			n50msCnt = 0;
			b50msFlag = true;
			n1sCnt ++;
			if((n1sCnt % 2) == 0)						//100ms meeted
			{
				b100msFlag = true;
				f_Go_To_Halt();
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
		f_FreqDeal();
		/*if(temp == 0)
		{
			temp = 1;
			LED = 0;
		}
		else
		{
			temp = 0;
			LED = 1;
		}*/
	}
}

/*=========================================================
* 函 数 名：f_Go_To_Halt()
* 功能描述：将CC1101设置为睡眠模式，进入停止模式 
* 调用方法：
* 全局变量：
* 处理过程：
* 输		入：无
* 返		回：无
==========================================================*/
void f_Go_To_Halt(void)
{	
	if(nKeyWakeTm < 250)//按键唤醒时间
		nKeyWakeTm ++;
	if (!bInSleepFlag)
	{
		if(nKeyWakeTm >= 30)		/* 按键触发后3s后进入sleep模式 */
		{
			bInSleepFlag = true;
		}
		return;
	}
	//_t0on = 0;		//定时器0关闭																					//关闭定时器
	_adoff = 1;		//ad关闭
	KEY_COM1 = false;
	KEY_COM2 = false;
	KEY_COM3 = false;
	KEY_COM4 = false;
	_idlen = 0;			//休眠模式1->看门狗计数自动清0,时基定时器会关闭
														
	GCC_HALT();
	GCC_NOP();
	GCC_NOP();
	GCC_NOP();
	GCC_NOP();
	GCC_NOP();
}