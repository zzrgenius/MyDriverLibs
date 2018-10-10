/******************************************************************************

					��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
	�� �� ��	: TimerFlags.h
	�� �� ��	: V1.0
	��	 ��	 : Ǯ�پ�
	��������	 : 2018��4��13��
	����޸�	 :
	��������	 : ϵͳʱ����־�����ڶ��岻ͬʱ�������ü���ȡ
	�����б�	 :
	�޸���ʷ	 :
	1.��	 ��	 : 2018��4��13��
	�� 	 ��	 : Ǯ�پ�
	�޸�����	 : �����ļ�

******************************************************************************/
#ifndef _TIME_FLAG_H_
#define _TIME_FLAG_H_


/*----------------------------------------------*
 * ����ͷ�ļ�											*
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
* ģ�鼶����										 *
*----------------------------------------------*/
//ϵͳ����ʱ������ʱ�������δ�ʱ��,������ѭ������
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

//ϵͳ��ʱ������ʱ�������δ�ʱ��,������ѭ������
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

//�Զ���ʱ����������ѭ�����á��жϵ��ã���Ҫ�û���������
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
    //====1msʱ������====
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
	uchar			base5MsCnt; //�ж����ñ�������������ȡ�����
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
 * �ⲿ����˵��										*
 *----------------------------------------------*/
extern SYS_TIME_FLAG sysTimeFlag;

/*----------------------------------------------*
 * �궨��											*
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