#ifndef __STEPMOTOR_HARDWARE_H__
#define __STEPMOTOR_HARDWARE_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "StepMotorDriver.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
#define SM_ORG_POS	0//原点位置

//喷杆电机相关位置
#define SM_NOZZLE_MIN_POS 	-10//基于原点的最小位置
#define SM_NOZZLE_MAX_POS	4000//基于原点的最大位置
#define SM_NOZZLE_MORE_OFFSET 100 //喷杆重设偏差(清洗结束喷杆多走回步)

//流量电机相关位置
#define SM_FLOW_MIN_POS 	-1800//基于原点的最小位置
#define SM_FLOW_MAX_POS		1800//基于原点的大位置


/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern const STEPMOTOR_HARDWARE_DRIVER StepmotorHdSprayNozzle;
extern const STEPMOTOR_HARDWARE_DRIVER StepmotorHdSprayFlow;

extern const sint tab_ResetStep_Nozzle[];
extern const sint tab_ResetStep_Flow[];


/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/



#endif /* __STEPMOTOR_HARDWARE_H__ */
