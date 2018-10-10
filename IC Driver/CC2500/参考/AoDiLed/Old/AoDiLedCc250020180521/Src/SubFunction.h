#ifndef __SUBFUNTION_H
#define __SUBFUNTION_H

#ifdef   VAR_SUBFUNCTION_GLOBALS
	#define  VAR_SUBFUNCTION_EXT
#else
	#define  VAR_SUBFUNCTION_EXT  extern
#endif

VAR_SUBFUNCTION_EXT AT_NEAR uchar nReducedTime;			//��ʱ

/*#define SETBIT(VAR,Place)         	( VAR |= (1<<Place) )
#define CLRBIT(VAR,Place)        		( VAR &= ((1<<Place)^255) )
#define CHGBIT(VAR,Place)         	( VAR ^= (1<<Place) )
#define AFFBIT(VAR,Place,Value)   	((Value) ?  (VAR |= (1<<Place)) : (VAR &= ((1<<Place)^255)))
#define MSKBIT(Dest,Msk,Src)      	( Dest = (Msk & Src) | ((~Msk) & Dest) )
#define VALBIT(VAR,Place)         	(VAR & (1<<Place))	
#define SETBITLONG(VAR,Place)        ( VAR |= ((ulong)(1)<<Place) )
#define CHGBITLONG(VAR,Place)     	( VAR ^= ((ulong)(1)<<Place) )
#define VALBITLONG(VAR,Place)     	(VAR & ((ulong)(1)<<Place))	
#define SETBITINT(VAR,Place)         	( VAR |= ((uint)(1)<<Place) )
#define CHGBITINT(VAR,Place)     	( VAR ^= ((uint)(1)<<Place) )
#define VALBITINT(VAR,Place)     	(VAR & ((uint)(1)<<Place))	
#define CLRBITINT(VAR,Place)         	( VAR &= ((uint)(1<<Place)^65535) )*/
VAR_SUBFUNCTION_EXT void *f_Memcpy(void *dest,const void *src, uint nSize);
VAR_SUBFUNCTION_EXT uint f_CheckSum(uchar *nBuff,uchar nStartNo,uchar nEndNo);
VAR_SUBFUNCTION_EXT uint f_XorSum(uchar *nBuff,uchar nStartNo,uchar nEndNo);
VAR_SUBFUNCTION_EXT void f_GetSWState(uchar bIOstate, LEVEL_SWITCH_INF *pSwInf, uint needOnTm, uint needOffTm);
VAR_SUBFUNCTION_EXT void f_ClearRunTimeH(hour_def *nTempHourDef);		//������Сʱʱ��
VAR_SUBFUNCTION_EXT void f_ClearRunTimeM(minute_def *nTempMinDef);	//�����з�ʱ��
VAR_SUBFUNCTION_EXT void f_AddRunTimerM(minute_def *nTempMinDef);		//����ʱ����ۼ�
VAR_SUBFUNCTION_EXT void f_AddRunTimerH(hour_def *nTempHourDef);		//����ʱ��Сʱ�ۼ�
VAR_SUBFUNCTION_EXT void AddCharData(uchar *nTempCharBuff); 			//char �������ۼ�
VAR_SUBFUNCTION_EXT void DecCharData(uchar *nTempIntBuff);				//char �����ݵݼ�
VAR_SUBFUNCTION_EXT void AddIntData(uint *nTempIntBuff);   				 //int �������ۼ�
VAR_SUBFUNCTION_EXT void DecIntData(uint *nTempIntBuff);					//int �����ݵݼ�
VAR_SUBFUNCTION_EXT uchar AddTotalNum(uchar *nBuff,uchar nEndNo);		//�ۼ�ָ����Ŀ������
#endif		// __SUBFUNTION_H
