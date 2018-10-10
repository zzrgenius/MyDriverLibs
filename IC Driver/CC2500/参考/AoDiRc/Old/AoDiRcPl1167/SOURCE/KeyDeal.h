#ifndef __KEY_DEAL_H
#define __KEY_DEAL_H

#ifdef  VAR_KEY_DEAL_GLOBALS
	#define  VAR_KEY_DEAL_EXT
#else
	#define  VAR_KEY_DEAL_EXT  extern
#endif

VAR_KEY_DEAL_EXT void f_KeyDeal(void);

typedef union
{
	unsigned char byte;
	struct
	{
		unsigned char LedState : 1;		//ҹ��״̬
		unsigned char MoveMassage : 1;	//�ƶ���Ħ
		unsigned char AutoFlushEn : 1;	//�Զ���ˮʹ��
	}mbit;
}state_def;

typedef enum
{
	WATER_TEMP = 0,
	DRY_TEMP,
	SEAT_TEMP
}TEMP_OPT;

typedef struct
{
	unsigned char KeyNum;// ������һ����������
	state_def SysState;	//ϵͳ״̬
	TEMP_OPT TempOpt;	//�¶�ѡ��
	unsigned char WaterTempGear;	//ˮ�µ�λ
	unsigned char DryTempGear;	//���µ�λ
	unsigned char SeatTempGear;	//���µ�λ
	unsigned char NozzleGear;		//��˵�λ
	unsigned char ValveGear;		//ˮѹ��λ
	//unsigned char RfSendCnt;	//���Է��͵Ĵ���
}SYS_INF;
VAR_KEY_DEAL_EXT AT_NEAR SYS_INF SysInf __attribute__((at(0x1A0)));

#endif //__KEY_DEAL_H
