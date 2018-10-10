/******************************************************************************

					版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
	文 件 名	: TimerFlags.h
	版 本 号	: V1.0
	作	 者	 : 钱百静
	生成日期	 : 2018年4月13日
	最近修改	 :
	功能描述	 : 系统时基标志，用于定义不同时基、设置及获取
	函数列表	 :
	修改历史	 :
	1.日	 期	 : 2018年4月13日
	作 	 者	 : 钱百静
	修改内容	 : 创建文件

******************************************************************************/
#ifndef _TIME_FLAG_H_
#define _TIME_FLAG_H_


/*----------------------------------------------*
 * 包含头文件											*
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
* 模块级变量										 *
*----------------------------------------------*/
//系统基本时基，定时器产生滴答时间,用于主循环调用
typedef struct 
{
	uchar	bSys1MsFlag 	: 1;
	uchar	bSys5MsFlag 	: 1;
	uchar	bSys10MsFlag	: 1;
	uchar	bSys50MsFlag	: 1;
} SYS_TIME_BASE_BIT;

typedef union 
{	
	uchar			mbyte;
	SYS_TIME_BASE_BIT bits;
} SYS_TIME_BASE_FLAG;

//系统长时基，定时器产生滴答时间,用于主循环调用
typedef struct 
{
	uchar	bSys100MsFlag 	: 1;
	uchar	bSys200MsFlag 	: 1;
	uchar	bSys500MsFlag	: 1;
	uchar	bSys1SFlag		: 1;
	uchar	bSys1MinFlag	: 1;
} SYS_TIME_LONG_BIT;

typedef union 
{	
	uchar			mbyte;
	SYS_TIME_LONG_BIT bits;
} SYS_TIME_LONG_FLAG;

//自定义时基，用于主循环调用、中断调用，需要用户自行清零
typedef struct 
{
	ulong	bSelf30MsFlag 	: 1;
} SYS_TIME_SELF_BIT;

typedef union 
{	
	ulong			byte;
	SYS_TIME_SELF_BIT bits;
} SYS_TIME_SELF_FLAG;

/*
    //====1ms时基产生====
    sysTimeFlag.baseTimeFlag.bits.bSys1MsFlag = true;

	if (++sysTimeFlag.base5MsCnt >= 5)
	{
	    sysTimeFlag.base5MsCnt = 0;
		sysTimeFlag.baseTimeFlag.bits.bSys5MsFlag = true;
	}

	if (++sysTimeFlag.base10MsCnt >= 10)
	{
	    sysTimeFlag.base10MsCnt = 0;
		sysTimeFlag.baseTimeFlag.bits.bSys10MsFlag = true;
	}

	if (++sysTimeFlag.base50MsCnt >= 50)
	{
	    sysTimeFlag.base50MsCnt = 0;
		sysTimeFlag.baseTimeFlag.bits.bSys50MsFlag = true;
	}
*/

typedef struct 
{
	uchar			base5MsCnt; //中断内用变量独立，不用取余操作
	uchar			base10MsCnt;
	uchar			base50MsCnt;
	
	uchar			time10MsCnt;
	uchar			time100MsCnt;
	uchar			time1SCnt;
	uchar			selfTimeCnt;
	SYS_TIME_BASE_FLAG	baseTimeFlag;
	SYS_TIME_LONG_FLAG	longTimeFlag;
	SYS_TIME_SELF_FLAG	selfTimeFlag;
} SYS_TIME_FLAG;



/*----------------------------------------------*
 * 外部变量说明										*
 *----------------------------------------------*/
extern SYS_TIME_FLAG sysTimeFlag;

/*----------------------------------------------*
 * 宏定义											*
 *----------------------------------------------*/

#define f_IsSysTime1Ms()		(sysTimeFlag.baseTimeFlag.bits.bSys1MsFlag)
#define f_ClrSysTime1Ms()		sysTimeFlag.baseTimeFlag.bits.bSys1MsFlag = false
#define f_IsSysTime5Ms()		(sysTimeFlag.baseTimeFlag.bits.bSys5MsFlag)
#define f_ClrSysTime5Ms()		sysTimeFlag.baseTimeFlag.bits.bSys5MsFlag = false
#define f_IsSysTime10Ms()		(sysTimeFlag.baseTimeFlag.bits.bSys10MsFlag)
#define f_ClrSysTime10Ms()		sysTimeFlag.baseTimeFlag.bits.bSys10MsFlag = false
#define f_IsSysTime50Ms()		(sysTimeFlag.baseTimeFlag.bits.bSys50MsFlag)
#define f_ClrSysTime50Ms()		sysTimeFlag.baseTimeFlag.bits.bSys50MsFlag = false
#define f_IsSysTime100Ms()		(sysTimeFlag.longTimeFlag.bits.bSys100MsFlag)
#define f_ClrSysTime100Ms()		sysTimeFlag.longTimeFlag.bits.bSys100MsFlag = false
#define f_IsSysTime200Ms()		(sysTimeFlag.longTimeFlag.bits.bSys200MsFlag)
#define f_ClrSysTime200Ms()		sysTimeFlag.longTimeFlag.bits.bSys200MsFlag = false
#define f_IsSysTime500Ms()		(sysTimeFlag.longTimeFlag.bits.bSys500MsFlag)
#define f_ClrSysTime500Ms()		sysTimeFlag.longTimeFlag.bits.bSys500MsFlag = false
#define f_IsSysTime1s() 		(sysTimeFlag.longTimeFlag.bits.bSys1SFlag)
#define f_ClrSysTime1S()		sysTimeFlag.longTimeFlag.bits.bSys1SFlag = false
#define f_IsSysTime1Min()		(sysTimeFlag.longTimeFlag.bits.bSys1MinFlag)
#define f_ClrSysTime1Min()		sysTimeFlag.longTimeFlag.bits.bSys1MinFlag = false

#endif