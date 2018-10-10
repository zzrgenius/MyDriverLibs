#ifndef __STEP_MOTOR_DRIVER_H__
#define __STEP_MOTOR_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件										  *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 前置声明 										*
 *----------------------------------------------*/
struct stepmotor_driver;
typedef struct stepmotor_driver STEPMOTER_DRIVER;

/*----------------------------------------------*
 * 数据类型定义										*
 *----------------------------------------------*/
typedef struct 
{
	void(*StepmotorOut) (STEPMOTER_DRIVER *, uchar);
	uchar const *pTab_Step;//步进电机运行拍数表
	uchar const phaseCnt;//设置的拍数
	uint const stepOPtTm;//电机的换步时间(设置的速度)
	uint const startOptTm; //电机启动速度(迁入)
	sint const *pTab_Reset;//复位表
} STEPMOTOR_HARDWARE_DRIVER;

typedef union
{
	byte_8	byte;
	struct
	{
		byte_8 bInReset:1;//正在复位
		byte_8 bRunning:1;//正转运行
	}bits;
}STEPMOTOR_FLAG;

typedef enum
{
	STEPMOTOR_DIR_STOP = 0,
	STEPMOTOR_DIR_FWD,//正转
	STEPMOTOR_DIR_REV//反转
}STEPMOTOR_DIR;

typedef enum
{
	STEPMOTER_RESET_MAX = 0,
	STEPMOTER_RESET_MIN,
	STEPMOTER_RESET_ORG
}STEPMOTOR_RESET_STEP;

typedef struct
{
	uchar curPhase; //当前拍数位置	
	sint targetPosStep;//目标位置步数(相对于0点位置)
	sint curPosStep;//当前位置步数(相对于0点位置)
	uint stepOptCnt;//换步数间隔(运行速度)
	uchar startStep; //启动需要运行步数
	STEPMOTOR_DIR runDir;//运行方向
	STEPMOTOR_RESET_STEP resetStep;//复位步骤
	STEPMOTOR_FLAG	flag;
}STEPMOTOR_DRIVER_DATA;

/*----------------------------------------------*
 * 模块级变量声明									  *
 *----------------------------------------------*/
struct stepmotor_driver
{
	STEPMOTOR_HARDWARE_DRIVER const *pHardware;
	STEPMOTOR_DRIVER_DATA data;
};


/*----------------------------------------------*
 * 模块级函数声明									  *
 *----------------------------------------------*/
void f_StepmotorDriverInit(STEPMOTER_DRIVER *pDriver, const STEPMOTOR_HARDWARE_DRIVER *pHardware);
uchar f_StepmotorIsAtPos(STEPMOTER_DRIVER *pDriver, sint pos);
void f_StepmotorReset(STEPMOTER_DRIVER *pDriver);
uchar f_StepmotorResetIsOver(STEPMOTER_DRIVER *pDriver);
void f_StepmotorStopReset(STEPMOTER_DRIVER *pDriver);
void f_StepmotorResetDeal(STEPMOTER_DRIVER *pDriver);
void f_StepmotorOffsetCurPos(STEPMOTER_DRIVER *pDriver, sint offset);
void f_StepmotorRun(STEPMOTER_DRIVER *pDriver);
void f_StepmotorSetTarget(STEPMOTER_DRIVER *pDriver, sint pos, uchar bForce);
void f_StepmotorStop(STEPMOTER_DRIVER *pDriver);
uchar f_StepmotorIsRun(STEPMOTER_DRIVER *pDriver);



#endif /* __STEP_MOTOR_DRIVER_H__ */

