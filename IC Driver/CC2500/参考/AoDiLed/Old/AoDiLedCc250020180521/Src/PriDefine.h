#ifndef __PRIEDEFINE_H
#define __PRIEDEFINE_H

#ifdef  VAR_MAIN_GLOBALS
    #define  VAR_PRIDEFINE_EXT
#else
    #define  VAR_PRIDEFINE_EXT  extern
#endif

//初始化状态
typedef enum
{
	rSYS_INIT_NO = 0,   	//初始化未开始
	rSYS_INIT_HLAF,    	//初始化上半段完成
	rSYS_INIT_OK,       	//初始化完成
	rSYS_INIT_FLUSH     	//无电冲水
}SYS_INIT; //初始化状态

//系统状态
typedef enum
{
	STANDBY_STATE = 0,		//待机状态
	RUNNING_STATE,			//运行状态
	TEST_MODE_STATE,		//老化状态
	SELFCHECK_STATE		//自检状态
}SYSTE_STATE;			//系统状态

//功能状态
typedef enum
{
	FUNC_NULL = 0,	//无功能
	FUNC_SPANY,	//臀部冲洗
	FUNC_WOMAN,	//女性
	FUNC_DRY		//暖风
}FUNC_STATE;//功能状态
typedef struct
{
	uint 		runTm;          		//运行时间
	FUNC_STATE 	curFunc;		//当前功能
	FUNC_STATE 	lastCurFunc;    //上次功能
	uchar	levelState;     		//当前水压
	uchar 	posState;		//当前喷杆
}FUNC_INF;//功能信息

//控制标志位
typedef union
{
	uchar byte;
	struct
	{
		uchar energySave  : 1;//节能标志
	}flag;
}OTHER_INF;//其他控制标志位

//故障
typedef union
{
	uint byte;
	struct
	{
		uchar bWaterTempHighErr : 1;	//水温过高故障
		uchar bSeatTempHighErr : 1;	//座温过高故障
		uchar bDryTempHighErr : 1;		//室温过温故障
		uchar bNoWaterErr : 1;			//缺水故障	
		uchar bHeatCommunErr : 1;    	//即热通信故障
		uchar bUartCommunErr: 1;		//主板与转接板通信故障
		uchar bDrySpeedErr : 1;         	//风机速度错误
		uchar bBattErr : 1;             		//电池开路或者电量低报警
		uchar bErrNoRun : 1;    			//异常标志位断掉强电
	}flag;
}SYSTEM_ERR;//系统故障标志

//异常计数
typedef struct
{
	uchar bNoWaterCnt;	//无水异常计数
}ERR_CNT;//异常计数

//接收到的按键值
typedef enum
{
	KEY_CMD_NO = 0,//无按键按下
	KEY_CMD_PYGAL_SH,//臀洗短按
	KEY_CMD_PYGAL_RE,	//臀洗短按松开
	KEY_CMD_PYGAL_LO,//臀洗长按
	KEY_CMD_BIDET_SH,//妇洗短按
	KEY_CMD_BIDET_RE,//妇洗短按松开
	KEY_CMD_BIDET_LO,//妇洗长按
	KEY_CMD_STOP_SH,//停止短按
	KEY_CMD_STOP_RE,//停止短按松开
	KEY_CMD_STOP_LO,//停止长按
	KEY_CMD_PYGAL_BIDET1, // 臀洗加妇洗按键1
	KEY_CMD_PYGAL_BIDET2, // 臀洗加妇洗按键2
	KEY_CMD_BIDET_STOP1, // 妇洗加停止按键1
	KEY_CMD_BIDET_STOP2 // 妇洗加停止按键2
}KEY_CMD_INF;

//地址调整
typedef struct
{
	uchar addrFlag : 1;		//地址信号
}ADDR_INF;

typedef struct
{
	uchar heatComErrFlick : 1;
	uchar zeroCrossErrFlick : 1;
}ERR_FLICK_INF;


typedef struct
{
	SYS_INIT			bInitInf;		//初始化电平标志位
	SYSTE_STATE		SystemCurState;	//系统当前状态
	FUNC_INF	 		curFunInf;		//当前功能信息
	//OTHER_INF 		otherInf;		//其他控制标志
	//DEO_INF 		deoInf;			//除臭
	HEAT_INF 		heatInf;			//加热
	SWITCH_SEAT_INF seatInf;			//着座
	//SWITCH_NIGHT_INF nightInf;		//夜灯
	//SENSOR_TEMP 	sensorInf;		//温度传感器
	WASH_INF 		WashInf;		//清洗
	//FLOW_METER_INF	flowMeterInf;	//流量计
	//FLUSH_INF		flushInf;			//冲水
	SYSTEM_ERR		systemErrInf;	//系统故障标志
	//ERR_CNT			ErrCntInf;		//异常计数
	//LIDSEAT_STRUCT   LidSeatInf;		//翻盖电机
	//KEY_CMD_INF 		KeyCmdInf;		//按键命令
	//KEY_SCAN_INF 	KeyScanInf;		//按键
	uchar AddressRf[3];
	ADDR_INF		addrInf;			//地址信号
	uchar 			flushTimeState;	//冲水时间调整
	ERR_FLICK_INF	errFlickInf;
}BIG_STRUCT;
VAR_PRIDEFINE_EXT AT_NEAR BIG_STRUCT machineInf;

#endif //__PRIEDEFINE_H
