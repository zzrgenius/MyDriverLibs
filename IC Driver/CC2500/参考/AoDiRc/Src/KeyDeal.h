#ifndef __KEYDEAL_H__
#define __KEYDEAL_H__

#ifdef  VAR_KEY_DEAL_GLOBALS
	#define  VAR_KEY_DEAL_EXT
#else
	#define  VAR_KEY_DEAL_EXT  extern
#endif
/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 数据类型定义                                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
typedef union 
{
	uchar byte;
	struct 
	{
		uchar LedState		: 1;		//夜灯状态
		uchar MoveMassage 	: 1;		//移动按摩
		uchar AutoFlushEn 	: 1;		//自动冲水使能
	} mbit;

} state_def;
typedef enum 
{
	WATER_TEMP = 0, 
	DRY_TEMP, 
	SEAT_TEMP
} TEMP_OPT;
typedef struct 
{
	uchar			KeyNum; 						// 定义那一个按键被吓
	state_def		SysState;						//系统状态
	TEMP_OPT		TempOpt;						//温度选择
	uchar			WaterTempGear;					//水温档位
	uchar			DryTempGear;					//风温档位
	uchar			SeatTempGear;					//座温档位
	uchar			NozzleGear; 					//喷杆档位
	uchar			ValveGear;						//水压档位
	uchar 			RfSendFlag : 1;					//发送电平
} SYS_INF;
//VAR_KEY_DEAL_EXT SYS_INF SysInf __attribute__((at(0x1A0)));
VAR_KEY_DEAL_EXT SYS_INF SysInf;
VAR_KEY_DEAL_EXT void f_pKeyDeal(void);
#endif /* __KEYDEAL_H__ */
