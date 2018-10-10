#ifndef __SUB_FUNCTION_H__
#define __SUB_FUNCTION_H__

/*----------------------------------------------*
 * 包含头文件										  *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 数据类型定义										*
 *----------------------------------------------*/
typedef struct 
{
	uchar			second;
	uint			minute;
} MINUTE_DEF;//分钟结构体定义

typedef struct 
{
	uchar			second;	
	uchar			minute;
	uint			hour;
} HOUR_DEF;//小时结构体定义

/*----------------------------------------------*
 * 宏声明								    		*
 *----------------------------------------------*/
#define SETFLAG(VAR,DATA)			((VAR) |= (DATA))
#define CLRFLAG(VAR,DATA)			((VAR) &= (~(DATA)))
#define GETFLAG(VAR,DATA)			((VAR) & (DATA))

#define GetBitState(VAR,DATA)		(((VAR)&(DATA))?1:0)

#define SETBIT(VAR,Place)         ( (VAR) |= (1<<(Place)) )
#define CLRBIT(VAR,Place)         ( (VAR) &= ((1<<(Place))^255) )
#define CHGBIT(VAR,Place)         ( (VAR) ^= (1<<(Place)) )
#define AFFBIT(VAR,Place,Value)   ((Value) ? \
                                   ((VAR) |= (1<<(Place))) : \
                                   ((VAR) &= ((1<<(Place))^255)))
#define MSKBIT(Dest,Msk,Src)      ( Dest = ((Msk) & (Src)) | ((~(Msk)) & (Dest)) )

#define VALBIT(VAR,Place)         ((VAR) & (1<<(Place)))	

#define SETBITLONG(VAR,Place)         ( (VAR) |= ((unsigned long)(1)<<(Place)) )
#define CHGBITLONG(VAR,Place)     ( (VAR) ^= ((unsigned long)(1)<<(Place)) )
#define VALBITLONG(VAR,Place)     ((VAR) & ((unsigned long)(1)<<(Place)))

#define GetBit(VAR,Place)			((VAR)&(1<<(Place)))?1:0
#define GetBit_P(PADD,Place)		GetBit((*((uchar*)PADD + Place/8)),(Place%8))
#define ChgBit_P(PADD,Place)		CHGBIT((*((uchar*)PADD + Place/8)),(Place%8))
#define SetBit_P(PADD,Place)		SETBIT((*((uchar*)PADD + Place/8)),(Place%8))
#define ClrBit_P(PADD,Place)		CLRBIT((*((uchar*)PADD + Place/8)),(Place%8))

/*----------------------------------------------*
 * 模块级函数声明									    *
 *----------------------------------------------*/
void f_AddRunTimerHour(HOUR_DEF *pTime);
void f_AddRunTimerMinute(MINUTE_DEF *pTime);
void f_AddU16Data(uint *pData);
void f_AddU32Data(ulong *pData);
void f_AddU8Data(uchar *pData);
void f_DecU16Data(uint *pData);
void f_DecU32Data(ulong *pData);
void f_DecU8Data(uchar *pData);
void f_Memset(void *pData, uchar setValue, uint size);

#endif /* __SUBFUNCTION_H__ */

