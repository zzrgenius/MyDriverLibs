#ifndef __FUN_CWASH_H__
#define __FUNC_WASH_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "Function.h"
/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
typedef enum
{
	WASH_INDEX_ORG, //归原点
	WASH_INDEX_PER_WASH, //前清洗
	WASH_INDEX_SET_POS, //喷杆设置(喷杆位置、加热、等待加热)
	WASH_INDEX_SET_FLOW, //流量设置(流量最大，气泵档位)
	WASH_INDEX_WASH, //正常清洗(清洗时间、移动清洗)
	WASH_INDEX_BACK_FLOW, //流量回原点
	WASH_INDEX_BACK_POS, //喷杆回原点(喷杆回缩,同时清洗)
	WASH_INDEX_BACK_WASH, //喷杆回退冲洗
	WASH_INDEX_CLEAN, //后自洁(喷杆到位进水关闭、气泵打开流量复位)
	WASH_INDEX_END //清洗结束
}FUNC_WASH_INDEX; //清洗顺序

typedef struct 
{
	STEPMOTER_DRIVER *pNozzleSM; //喷杆步进电机驱动指针	
	STEPMOTER_DRIVER *pFlowSM; //流量步进电机驱动指针
	const sint *pTabPos; //喷杆位置
	const sint *pTabFlow; //流量位置
}FUNC_WASH_HARDWARE; //硬件驱动

typedef struct
{
	FUNC_WASH_INDEX index; //流程
	uchar waitTm; //流程等待时间
	FUNC_WASH_HARDWARE const *pHardware; //硬件驱动
	FUNC_SET_LEVEL posLevel; //喷杆档位
	FUNC_SET_LEVEL flowLevel; //流量档位
	FUNC_SET_LEVEL flowLevelSave; //流量缓存(一键SPA用)
	uchar strongWeakTm;//强弱时间
	FUNC_SET_LEVEL strongWeakLevel; //强弱当前档位
	uchar coldHotTm;//冷热时间
	uchar setPumpPercent; //设置气泵百分比
	
	union
	{
		struct 
		{
			uint bPosAtTag :1; //喷杆电机在目标位置
			uint bFlowAtTag :1; //流量电机在目标位置
			uint bRealStart :1; //真正清洗流程到(WASH_INDEX_WASH)
			uint bEnStrongWeak :1; //强弱交替按摩
			uint bFlowMax :1; //流量已到最大
			uint bEnMove :1; //移动清洗
			uint bMoveEnd :1; //移动清洗是否到端
			uint bEnColdHot :1; //冷热按摩
			uint bPosBackReset :1; //喷杆回退复位
			uint bResetCurPos :1; //当前位置重设
			uint bFlowReset :1; //流量电机复位
			uint bEnAirPump :1; //使能空气泵通便
		}m_bits;
		uint m_byte;
	}flags;//一些临时标志(会自动清除)

	uchar bNeedPosBack :1; //切换时是否要喷杆回缩
	uchar bEnHeat :1; //使能水温加热
	uchar bChangePos :1; //喷杆位置改变(调整位置)
	uchar bChangeFlow :1; //流量位置改变(调整流量)
	uchar bEnInwaterValve :1; //使能进水阀
}FUNC_WASH; //清洗驱动

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern FUNC_WASH AT_NEAR funcWashHip;//臀部清洗
extern FUNC_WASH AT_NEAR funcWashFemale;//女性清洗
extern const FUNC_WASH_HARDWARE hipWashHardware;
extern const FUNC_WASH_HARDWARE femaleWashHardware;
/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_FuncWashDeal(void);
void f_FuncWashInit(FUNC_WASH *pDriver, const FUNC_WASH_HARDWARE *pHardware);
uchar f_FuncSetWashState(FUNC_WASH *pDriver, STATE_INFO state);
void f_FuncWashNext(FUNC_WASH *pDriver, FUNC_WASH_INDEX index);
void f_FuncWashPosCtrl(FUNC_WASH *pDriver);
void f_FuncWashFlowCtrl(FUNC_WASH *pDriver);
void f_FuncWashColdHotCtrl(FUNC_WASH *pDriver);
uchar f_FuncSetStrongWeak(FUNC_WASH *pDriver, STATE_INFO state);
uchar f_FuncSetWashMove(FUNC_WASH *pDriver, STATE_INFO state);
uchar f_FuncSetColdHot(FUNC_WASH *pDriver, STATE_INFO state);
void f_FuncSetPos(FUNC_WASH *pDriver, FUNC_SET_LEVEL pos, uchar bForce);
void f_FuncSetFlow(FUNC_WASH *pDriver, FUNC_SET_LEVEL flow, uchar bForce);
uchar f_FuncSetPurge(FUNC_WASH *pDriver, STATE_INFO state);

#endif /* __FUNC_WASH_H__ */
