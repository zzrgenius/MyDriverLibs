#ifndef __POWER_CONTROL_H__
#define __POWER_CONTROL_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
 #include "DataType.h"

/*----------------------------------------------*
 * 前置声明                                         *
 *----------------------------------------------*/
struct power_ctrl;
typedef struct power_ctrl POWER_CTRL;

/*----------------------------------------------*
 * 数据类型定义                                       *
 *----------------------------------------------*/
#define POWER_CTRL_GROUP_NUM	10//共分为10个大组

typedef enum
{
	POWER_CTRL_OFF = 0,
	POWER_CTRL_ON = !POWER_CTRL_OFF
}POWER_CTRL_STATE;
 
typedef struct
{
	uchar ctrlGroupIndex;//实际控制顺序，按波形组自然顺序
	uint  periodOnTm[POWER_CTRL_GROUP_NUM];//每个大周期开启的时间
	uint  periodTm; //控制周期时间
}POWER_CTRL_DRIVER_DATA;

typedef void (*PowerCtrlHardware)(POWER_CTRL *, POWER_CTRL_STATE);
	
typedef struct power_ctrl
{
	POWER_CTRL_DRIVER_DATA data;
	PowerCtrlHardware pHardwareFunc;
};

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
 void f_PowerCtrlCalc(POWER_CTRL * pPowerCtrl, uchar percent);
 void f_PowerCtrlOut(POWER_CTRL * pPowerCtrl);
 void f_PowerCtrlInit(POWER_CTRL *pPowerCtrl, const PowerCtrlHardware pFunc);

#endif /* __POWERCONTROL_H__ */
