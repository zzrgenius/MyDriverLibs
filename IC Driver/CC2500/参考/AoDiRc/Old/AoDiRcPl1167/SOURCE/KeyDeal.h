#ifndef __KEY_DEAL_H
#define __KEY_DEAL_H

#ifdef  VAR_KEY_DEAL_GLOBALS
	#define  VAR_KEY_DEAL_EXT
#else
	#define  VAR_KEY_DEAL_EXT  extern
#endif

VAR_KEY_DEAL_EXT void f_KeyDeal(void);

typedef union
{
	unsigned char byte;
	struct
	{
		unsigned char LedState : 1;		//夜灯状态
		unsigned char MoveMassage : 1;	//移动按摩
		unsigned char AutoFlushEn : 1;	//自动冲水使能
	}mbit;
}state_def;

typedef enum
{
	WATER_TEMP = 0,
	DRY_TEMP,
	SEAT_TEMP
}TEMP_OPT;

typedef struct
{
	unsigned char KeyNum;// 定义那一个按键被吓
	state_def SysState;	//系统状态
	TEMP_OPT TempOpt;	//温度选择
	unsigned char WaterTempGear;	//水温档位
	unsigned char DryTempGear;	//风温档位
	unsigned char SeatTempGear;	//座温档位
	unsigned char NozzleGear;		//喷杆档位
	unsigned char ValveGear;		//水压档位
	//unsigned char RfSendCnt;	//可以发送的次数
}SYS_INF;
VAR_KEY_DEAL_EXT AT_NEAR SYS_INF SysInf __attribute__((at(0x1A0)));

#endif //__KEY_DEAL_H
