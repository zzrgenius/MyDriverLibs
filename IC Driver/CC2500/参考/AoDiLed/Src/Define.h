#ifndef __DEFINE_H
#define __DEFINE_H

#ifdef  VAR_MAIN_GLOBALS
    #define  VAR_DEFINE_EXT
#else
    #define  VAR_DEFINE_EXT  extern
#endif

//除臭
typedef struct
{
	uchar deoFanState : 1;	//除臭风机状态
}DEO_INF;

//AD传感器
typedef struct
{
	sint setTemp;			//设置温度		
	sint sensorTemp;		//传感器温度
	sint lastSensorTemp;	//传感器温度缓存	
	sint showTemp;		//显示温度
	uchar bShortFlag : 1;	//短路故障标志	
	uchar bOpenFlag : 1;	//开路标志	
	sint setTempAD;		//设置温度对应AD
}SENSOR_INF;	//传感器信息
typedef struct
{
	SENSOR_INF EnvTemp;			//室温
	SENSOR_INF SeatTemp;		//座温
	SENSOR_INF InWaterTemp;		//进水温度
	SENSOR_INF OutWaterTemp;	//出水温度
	SENSOR_INF DryRotorAD;		//烘干风机堵转AD值
	SENSOR_INF BattAD;			//电池AD值
	SENSOR_INF LightAD;			//光敏
	SENSOR_INF SeatAdTemp;		//座圈AD
	SENSOR_INF LidAdTemp;		//上盖AD
}SENSOR_TEMP;

//着座开关
typedef struct
{
	uchar bSwitchState : 1;		//开关状态
	uchar bLastSwitchState : 1;	//开关状态
	uint nKeepOnTm;		//维持时间X100ms
	uint nKeepOffTm;	//维持时间X100ms
}LEVEL_SWITCH_INF;	//开关信息
typedef struct
{
	uchar SwitchSeatEn : 1;			//着座开关使能
	hour_def SeatOnTm;				//着座时间
  	hour_def SeatOffTm;				//脱座时间
  	LEVEL_SWITCH_INF seatSensorState;	//着座传感器状态	
}SWITCH_SEAT_INF;

// 夜灯
typedef struct
{
	uchar nightState : 1;				//夜灯状态
	uchar nightEn : 1;					//夜灯使能
	LEVEL_SWITCH_INF nightSensorState;//光敏状态
}SWITCH_NIGHT_INF;

//加热
typedef enum
{
	TEMP_OFF = 0,
	TEMP_LEVEL1,
	TEMP_LEVEL2,
	TEMP_LEVEL3
}TEMP_LEVEL;//温度设置等级
typedef enum
{
	DRY_OFF = 0,	
	DRY_LEVEL_1,		
	DRY_LEVEL_2,
	DRY_LEVEL_3
}DRY_STATE;	//烘干强弱状态
typedef struct
{
	uchar seatHeatState : 1;		//座圈加热状态
	uchar energySaveFlag : 1;		//节能
	TEMP_LEVEL setSeatLevel;		//设置座圈加热等级
}SEAT_HEAT;
typedef struct
{
	uchar waterHeatState : 1;		//水加热状态
	uchar waterHeatFlag : 1;		//是否开启加热
	TEMP_LEVEL setWaterLevel;		//设置水加热等级
	uint waterFlow;                  		//流量
	uchar waterPercentBuf;		//水温加热占空比
}WATER_HEAT;
typedef struct
{
	uchar dryFanState : 1;			//烘干风机状态
	uchar dryHeatState : 1;			//烘干加热状态
	DRY_STATE setDryLevel;		//设置烘干加热等级
	
	/*uchar dryFanEn : 1;			//烘干风机使能	
	uchar dryFanPeriodCnt;		//烘干风机周期计数
	uchar dryFanPwmPeriod;		//烘干风机前期慢慢启动PWM周期
	uchar enFanHeat : 1;			//加热丝允许打开
	uchar fanHeatTriac	: 1;			//加热丝可控硅打开
	uchar fanHeatOffTm;			//加热丝关闭时间100ms
	uchar fanOnTm;				//风扇打开时间100ms

	uchar dryPercentBuf;			//烘干加热占空比
	uchar sOffset;					//烘干加热补偿值*/
}DRY_HEAT;

typedef struct
{
	DRY_HEAT 	dryHeat;
	SEAT_HEAT 	seatHeat;
	WATER_HEAT waterHeat;
}HEAT_INF;

//清洗
typedef enum
{
	ORDER_POS_WATER_ORG = 0,     	//喷杆和调流阀如果不在原点则移动到原点
	ORDER_WATER_MOVE,           	 	//分配阀移动
	ORDER_WATER_TARGET,         		//分配阀到达指目标位置
	ORDER_PRO_HEAT,             	 	//预加热
	ORDER_POS_WATER_MOVE,		//喷杆和分配阀移动
	ORDER_POS_WATER_TARGET,	   	//流调阀回原点
	ORDER_WASH_START,		       //清洗开始
	ORDER_END_POS_BACK,           	//喷杆和分配阀退回
	ORDER_DRY_START,              		//启动烘干
	ORDER_WASH_ALL_END		    	//结束
}eWASH_ORDER;//清洗顺序

typedef struct
{
	eWASH_ORDER   washStep;	//洗涤步骤
	uint calcTm;	       //洗涤时间
	uint setWashTm;	//设置洗涤时间
	uchar timeCnt;		//多次按压计次
}sCLEAN_WASH_INF;//清洗信息

typedef enum
{
	WATER_LEVEL_0 = 0,	
	WATER_LEVEL_1,		
	WATER_LEVEL_2,
	WATER_LEVEL_3
}WATER_LEVEL;//水量大小

typedef enum
{
	POS_LEVEL_0 = 0,	
	POS_LEVEL_1,		
	POS_LEVEL_2,
	POS_LEVEL_3,
	POS_LEVEL_4,	
	POS_LEVEL_5,
	POS_LEVEL_6,
	POS_LEVEL_7
}POS_LEVEL;	//喷杆位置

typedef enum
{
	MODE_STAY = 0,	//固定位置
	MODE_MOVE		//移动
}eCLEAN_MODE;//移动按摩

typedef enum
{
	TEMP_NO_CHANGE = 0, //不变化
	TEMP_HOT_COLD		//冷热变化    
}eTEMP_CHANGE;//冷热按摩

typedef enum
{
	NO_STR_WEAK = 0, 	//正常
	NOMAL_STR_WEAK    	//强弱
}eSTR_WEAK; //强弱按摩

typedef enum
{
	POS_NO_CLEAR = 0,	//喷杆无动作
	POS_ORG,			//喷杆到原点
	POS_RUN_OUT,		//喷杆伸出
	POS_CLEAR,			//喷杆清洗
	POS_RESET			//喷杆复位
}NOZZLE_STEP;//喷杆自洁步骤

typedef struct
{
	NOZZLE_STEP NozzleStep;//喷杆自洁运行步骤
	unsigned char NozzleClearTime;//自洁时间
}eNOZZLE;   //喷口清洗

typedef struct
{
	/*uchar bStopWashFlag : 1;			//停止清洗
	uchar InWaterValve : 1;			//进水阀	
	uchar InWaterValveState : 1;		//进水阀状态
	uchar AirState : 1;					//空气泵
	uchar AirPwm;					//空气泵占空比
	uchar AirPwmCnt;					//空气泵占空比计数
	uchar ChangeWaterFlag : 1;			//分配阀动作改变标志位
	uchar ChangePosFlag : 1;			//喷杆动作改变标志位
	sCLEAN_WASH_INF PygaWash;		//臀洗
	sCLEAN_WASH_INF BidetWash;		//妇洗
	WATER_LEVEL	allWaterLevel[2];	   	 //所有功能强弱
    	POS_LEVEL allPosLevel[2];		   	 //所有功能喷杆位置
    	
	eCLEAN_MODE	 cleanMode;			//移动清洗模式
	uchar bMoveCnt;					//移动时间计数
	uchar bMoveModeEnd : 1;			//移动时间到位计数
	uchar rMoveModeFlag : 1;			//进入移动按摩标志位*/
	
	eTEMP_CHANGE bTempChange;    	//冷热模式
	/*uchar rTempChangeCnt;			//冷热时间计数
	uchar bTempChangeEnd : 1;		//冷热时间到位标志位
	uchar bTempChangeFlag : 1;		//进入冷热按摩标志位
	
	eSTR_WEAK bStrWeak;       			//强弱模式
	uchar rStrWeakCnt;				//开启强弱按摩循环时间计数
	uchar rStrWeakEnd : 1;				//强弱按摩到位标志位
	uchar rStrWeakFlag : 1;				//进入强弱按摩标志位
	
	eNOZZLE bNozzleClear;   			//喷口清洗*/
}WASH_INF;

//流量计
typedef struct
{
	uint flowMaxCnt;		//流量高计时
	uint flowMinCnt;		//流量低计时
	uint flowTotalCnt;	//脉冲个数
	uchar lastFlag : 1;		//之前电平
}FLOW_METER_INF;//流量计

//冲水
typedef enum
{
	NO_FLUSH = 0,			//冲洗未启动
	ONE_UP_TIME_CLEAR,	//第一上冲前时间清0
	UP_FLUSH_ONE,			//上冲
	ONE_DOWN_TIME_CLEAR,	//第一次下冲前时间清0
	DOWN_FLUSH,			//下冲
	SEN_UP_TIME_CLEAR,	//第二上冲前时间清0
	UP_FLUSH_SEN,			//第二次上冲
	CLOSE_FLUSH_TIME_CLEAR,//冲洗时间清0,
	CLOSE_FLUSH			//关闭
}FLUSH_STEP;
typedef struct
{
	uint bFlushTimeBuff[3];	//三步冲水时间
	uchar batterFlag : 1;	//电池供电
	uint flushTime; 		//冲水时间
	uchar bigFlush : 1;		//大冲或小冲标志位 为0时大冲
	uchar flushFlag : 1;	//是否冲水标志位
	uchar valveA : 1;		//阀1
	uchar valveB : 1;		//阀2

	uchar autoFlush;		//烘干时 、清洗后人体离开
	uchar FlushDelayDryFlag : 1;//冲水后延时开启烘干
	uchar FlushSeatOnOverTimeFlag;//着座超过时间标志位
	uchar FlushDryOnFlag;//烘干开启同时开启冲水标志位
	uchar FlushKeyOnFlag;//按键按下标志位
	FLUSH_STEP flushStep;	//冲洗步骤
	LEVEL_SWITCH_INF manFlushState;//男士小便冲水开关
}FLUSH_INF;	//冲洗结构体

//翻盖
typedef enum
{
	MOTOR_FASTD = 0,    //默认
	MOTOR_FORWARD,      //正向
	MOTOR_REVERSE       //反相         
}LS_RUN_STATE;      //翻盖工作状态

typedef struct
{
	uint SensorAd;//传感器AD值	
	uchar bShortFlag : 1;//短路故障标志	
	uchar bOpenFlag : 1;//开路标志	
}LS_AD;   //AD值

typedef enum
{
	POS_L = 0,  //水平位置
	POS_M,      //中间位置
	POS_H       //垂直位置
}LS_POS;//翻盖位置

typedef enum
{
	CMD_NORMAL = 0,//正常
	CMD_HALF,//半开
	CMD_OPEN,//全开
	CMD_CLOSE//全关
}LS_CMD;//翻盖命令

#define MOTOR_NO 2
typedef struct
{
	uchar lidCloseTm;	//关盖时间
	LS_RUN_STATE LastRunState[MOTOR_NO];//上次电机运行状态
	LS_RUN_STATE CurRunState[MOTOR_NO];//当前电机运行状态
	LS_AD CurAD[MOTOR_NO];//当前AD值
	LS_POS CurPos[MOTOR_NO];//当前位置
	LS_CMD LSCmdState;//命令状态
	uchar LSCmdFlag : 1;//命令电平
	uint InitHighAD[MOTOR_NO];//垂直初始值
	uint InitLowAD[MOTOR_NO];//水平初始值
	uchar Pwm[MOTOR_NO];//输出占空比
	uchar LSRelayFlag : 1;//继电器开合电平 
	uchar LSSeatSwitch : 1;//着座开关 用于接收外部着座信息
	uchar LSInfraredFlag : 1;//红外(脚感)信号
	uchar LSWaveFlag;//电平(1为开盖信号  2为关盖信号)
	uchar LSForFlag[MOTOR_NO];//正转堵转电平
	uchar LSRevFlag[MOTOR_NO];//翻转堵转电平
	uint LSForTime[MOTOR_NO];//正转堵转时间
	uint LSRevTime[MOTOR_NO];//反转堵转时间
	uchar ManLidSeatFalg : 1;//同时手动抬起盖圈后防止圈下落

	uchar LSInitFlag : 1;// 翻盖初始化电平信号
}LIDSEAT_STRUCT;

//按键
typedef enum
{//按键单按\组合状态
	KEY_FREE,
	KEY_COM_PRESS_1,
	KEY_COM_PRESS_2,
	KEY_COM_PRESS_3,
	KEY_COM_PRESS_4,
	KEY_COM_PRESS_5,
	KEY_COM_PRESS_6,
	KEY_COM_PRESS_7,
	KEY_COM_PRESS_8,
	KEY_SIGNAL_PRESS_1,
	KEY_SIGNAL_PRESS_2,
	KEY_SIGNAL_PRESS_3,
	KEY_SIGNAL_PRESS_4,
	KEY_SIGNAL_PRESS_5,
	KEY_SIGNAL_PRESS_6,
	KEY_SIGNAL_PRESS_7,
	KEY_SIGNAL_PRESS_8,
	KEY_SIGNAL_PRESS_9,
	KEY_SIGNAL_PRESS_10,
	KEY_SIGNAL_PRESS_11,
	KEY_SIGNAL_PRESS_12,
	KEY_SIGNAL_PRESS_13,
	KEY_SIGNAL_PRESS_14,
	KEY_SIGNAL_PRESS_15,
	KEY_SIGNAL_PRESS_16,
	KEY_SIGNAL_PRESS_17,
	KEY_SIGNAL_PRESS_18,
	KEY_SIGNAL_PRESS_19,
	KEY_SIGNAL_PRESS_20,
	KEY_SIGNAL_PRESS_21,
	KEY_SIGNAL_PRESS_22,
	KEY_SIGNAL_PRESS_23,
	KEY_SIGNAL_PRESS_24
}KEY_PRESSED_STATE;

typedef struct
{
	ulong nKeyInf;	//获取过来的原始按键信息
	uchar nKeyResultInf; //按键键输出结果
	uchar bKeyUsedFlag : 1; //按键结果被使用
	uchar bKeyFirstRelse : 1;//按键第一次被释放
	uchar bKeyPressFlag : 1;	//按键被按下标志
	KEY_PRESSED_STATE KeyPressName;	//按下按键名
	uint nKeyDownTm;//按键按下时间
	uint nNoKeyTm;//无按键按下时间
	uint nKeyRealDownTm;	//按键真实按下时间
	uchar nKeyStep;//扫描步骤
}KEY_SCAN_INF;

#endif	//__DEFINE_H