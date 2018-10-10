#ifndef __LID_MOTOR_DRIVER_H__
#define __LID_MOTOR_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "IoPwmDriver.h"

/*----------------------------------------------*
 * 前置声明                                         *
 *----------------------------------------------*/
struct lid_motor_driver;
typedef struct lid_motor_driver LID_MOTOR_DRIVER;

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
 typedef enum
 {
	MOTOR_DIR_STOP = 0,
	MOTOR_DIR_FWD,//电机正转
	MOTOR_DIR_REV//电机反转
 }LID_MOTOR_DIR;//翻盖电机方向

 typedef enum
 {
	LID_IN_RANGE_LOW = 0,//区域低
	LID_IN_RANGE_MID,//区域中
	LID_IN_RANGE_HIGH//区域高
 }LID_MOTOR_RANGE;

 typedef struct
 {
 	uint setRangeLow; //硬件检测低位置
 	uint setRangeHigh; //硬件检测高位置
 	uint lockOffset; //堵转检测变化偏差,在固定时间内,变化小于该值则认为堵转	
 	uint maxPos; //最大值(不管位置,可AD或霍尔个数)
 	uint minPos; //最小值(不管位置,可AD或霍尔个数)
 	uint handleOffset; //手动偏差
	void (*GetLidMotorPos)(LID_MOTOR_DRIVER *);//获取当前位置
	void (*MotorFwdEn)(STATE_INFO); //正转使能口
	void (*MotorRevEn)(STATE_INFO); //反转使能口
	
	uchar bIncrease :1;//位置由盖上到翻起是否采样值变大
 }LID_MOTOR_HARDWARE;//翻盖电机硬件驱动

#define SPEED_DEV_CNT 10ul //速度细分档位数
 typedef struct 
 {
	LID_MOTOR_DIR curDir;//当电机方向
	LID_MOTOR_DIR lastDir;//当电机方向缓存
	uint curAngle;//当前位置角度信息(可AD表示)
	uint lastAngle;//缓存位置角度信息(可AD表示)
	uchar posIndex; //位置分位序号
	LID_MOTOR_RANGE posRange;//所在位置范围
	uchar changeDirTm;//换向位置检测去抖时间
	uchar lockTm;//堵转检测时间
	uchar lockCnt; //堵转计数
	IO_PWM_DRIVER pwmFwdOut; //正转pwm输出
	IO_PWM_DRIVER pwmRevOut; //反转转pwm输出
	schar fwdOffset; //正向偏差值
	schar revOffset; //反向偏差偏差值
	uchar speedFwd[SPEED_DEV_CNT]; //正转每个阶段速度,由占空比表示
	uchar speedRev[SPEED_DEV_CNT]; //反每个阶段速度,由占空比表示
	
	uchar bEnLockCheck :1;//使能堵转检测
	uchar bRunning :1; //正在运行
	uchar bReset :1; //初始化复位位置
 }LID_MOTOR_DATA;

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
struct lid_motor_driver
{
	LID_MOTOR_DATA data;
	LID_MOTOR_HARDWARE const *pHardware;
};
 

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_LidMotorCtrl(LID_MOTOR_DRIVER *pDriver);
void f_LidMotorDriverInit(LID_MOTOR_DRIVER *pDriver, 
								  LID_MOTOR_HARDWARE *pHardware,
								  SetOut fwdOut,
								  SetOut revOut, 
								  uint period);
uchar f_LidMotorSetState(LID_MOTOR_DRIVER *pDriver, LID_MOTOR_DIR dir);
uchar f_LidMotorIsOverMid(LID_MOTOR_DRIVER *pDriver);
LID_MOTOR_DIR f_LidMotorHandleCheck(LID_MOTOR_DRIVER *pDriver, uint lastPos);
void f_LidMotorReset(LID_MOTOR_DRIVER *pDriver);
void f_LidMotorChangePos(LID_MOTOR_DRIVER *pDriver, uchar dir);

#endif /* __LID_MOTOR_DRIVER_H__ */
