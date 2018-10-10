#ifndef __FUNC_FLUSH_DEAL_H__
#define __FUNC_FLUSH_DEAL_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
typedef enum 
{
	FLUSH_SREQ_STOP, //冲水停止
	FLUSH_SREQ_START, //启动冲水
	FLUSH_SREQ_ROUND_1, //第一次裙边冲水
	FLUSH_SREQ_BOTTOM, //底部冲水
	FLUSH_SREQ_ROUND_2 //第二次裙边冲水
}FUNC_FLUSH_SREQ;

typedef enum
{
	FLUSH_CMD_NULL, //无冲水
	FLUSH_CMD_ROUND, //润壁冲水
	FLUSH_CMD_NORMAL //润壁+底部+润壁
}FUNC_FLUSH_CMD;//冲水命令

typedef enum
{
	FLUSH_VALVE_OFF,//关
	FLUSH_VALVE_ON,//开
	FLUSH_VALVE_BRAKE//刹车
}FLUSH_VALVE_STATE;

typedef enum
{
	FLUSH_ADJUST_WASH, //洗刷
	FLUSH_ADJUST_CLEAN, //排污
	FLUSH_ADJUST_BACK, //回水
	FLUSH_ADJUST_OVER //调节结束
}FLUSH_ADJUST_INDEX;//冲洗时间调整顺序

typedef struct 
{
	uchar dealyToBreakTm; // 开启关闭后需要定时到刹车状态
	FLUSH_VALVE_STATE setValve;
	FLUSH_VALVE_STATE lastSetValve;
	
	uchar bState:1; //当前状态(硬件状态)
	uchar bLastState:1;//缓存状态(硬件状态)
}FUNC_FLUSH_VALVE;
 
typedef struct 
{
	FUNC_FLUSH_SREQ curStep;//当前顺序
	uint flushTm; //当前冲水时间,单位100ms
	uint setRound_1_Tm; //设置第一次润壁冲水时间
	uint setBottomTm; //设置底部冲水时间
	uint setRound_2_Tm; //设置第二次润壁冲水时间
	FUNC_FLUSH_VALVE roundValve; //润壁阀
	FUNC_FLUSH_VALVE bottomValve; //底部阀
	uint batteryAD; //电池电量AD
	uchar batteryOnCnt;//电量正常计数
	uchar batteryOffCnt;//电量低计数

	uint saveFlushtm[FLUSH_ADJUST_OVER];//掉电保存的冲洗时间
	FLUSH_ADJUST_INDEX adjustIndex; //调节顺序
	
	uchar bPowerOff:1; //冲水过程中掉电
	uchar bLowPower:1; //电池电压过低
	uchar bAdjust :1; //调节模式
}FUNC_FLUSH;

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern FUNC_FLUSH AT_NEAR funcFlush;
/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_FuncFlushValveCtrl(void);
void f_FuncFlushDeal(void);
void f_FuncFlushInit(void);
uchar f_FuncSetFlushMode(FUNC_FLUSH_CMD cmd);
uchar f_FuncSetFlushTm(uint tm_wash, uint tm_clean, uint tm_back);
void f_FuncFlushBatteryCheck(void);
void f_FuncFlushPowerCheck(void);

#endif /* __FUNC_FLUSH_DEAL_H__ */
