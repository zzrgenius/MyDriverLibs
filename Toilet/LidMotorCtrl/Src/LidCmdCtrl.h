#ifndef __LID_CMD_CTRL_H__
#define __LID_CMD_CTRL_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "LidMotorDriver.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
typedef enum
 {
	LID_RUN_CMD_NULL = 0,
	LID_RUN_CMD_ALL_OPEN,//盖、圈全开
	LID_RUN_CMD_ALL_CLOSE,//盖、圈全关
	LID_RUN_CMD_HALF,//盖开、圈关
	LID_RUN_CMD_HANDLE //手动操作
 }LID_MOTOR_CMD;//应用层下发命令

 typedef enum
{
	SPEED_ADJUST_SEAT_FWD, //翻圈正向
	SPEED_ADJUST_SEAT_REV, //翻圈反向
	SPEED_ADJUST_TOP_FWD, //翻盖正向
	SPEED_ADJUST_TOP_REV //翻盖反向
}LID_ADJUST_INDEX;

typedef struct 
{
	LID_MOTOR_CMD setCMD; //设置命令
	uint cmdRunTm; //当前命令执行时间
	uint setMaxCmdTm; //允许最大允许命令时间
	LID_MOTOR_DRIVER seatLidMotor; //翻圈电机驱动
	LID_MOTOR_DIR setSeatDir;//座圈控制方向
	uint lastSeatPos; //缓存座圈位置
	LID_MOTOR_DRIVER topLidMotor; //翻盖电机驱动
	LID_MOTOR_DIR setTopDir;//上盖控制方向
	uint lastTopPos; //缓存上盖位置
	uchar handleCheckTm; //手动翻盖检测周期
	LID_ADJUST_INDEX adjustIndex; //盖板速度调节顺序

	uchar bCmdSeatDeal :1; //当中设置功能翻圈部分已处理
	uchar bCmdTopDeal :1; //当中设置功能翻盖部分已处理
	uchar bSetSeatDir :1; //需要设置座圈方向
	uchar bSetTopDir :1; //需要设置上盖方向
	uchar badjustMode :1; //速度调节模式
	uchar bWithMotor :1; //带电机(负载插上了，AD检测判断)
}LID_CMD_CTRL;

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern LID_CMD_CTRL AT_NEAR lidCmdCtrl;

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_LidCmdCtrlInit(void);
void f_LidCmdDeal(LID_CMD_CTRL *pDriver);
uchar f_LidCmdSetCmd(LID_CMD_CTRL *pDriver, LID_MOTOR_CMD cmd, uchar fource);
void f_LidCmdReset(void);


//速度调节用
void f_LidCmdIntoAdjust(void);
void f_LidCmdAddSpeed(void);
void f_LidCmdDecSpeed(void);
void f_LidCmdAddIndex(void);


#endif /* __LID_CMD_CTRL_H__ */
