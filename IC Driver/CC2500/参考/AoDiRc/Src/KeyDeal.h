#ifndef __KEYDEAL_H__
#define __KEYDEAL_H__

#ifdef  VAR_KEY_DEAL_GLOBALS
	#define  VAR_KEY_DEAL_EXT
#else
	#define  VAR_KEY_DEAL_EXT  extern
#endif
/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �������Ͷ���                                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
typedef union 
{
	uchar byte;
	struct 
	{
		uchar LedState		: 1;		//ҹ��״̬
		uchar MoveMassage 	: 1;		//�ƶ���Ħ
		uchar AutoFlushEn 	: 1;		//�Զ���ˮʹ��
	} mbit;

} state_def;
typedef enum 
{
	WATER_TEMP = 0, 
	DRY_TEMP, 
	SEAT_TEMP
} TEMP_OPT;
typedef struct 
{
	uchar			KeyNum; 						// ������һ����������
	state_def		SysState;						//ϵͳ״̬
	TEMP_OPT		TempOpt;						//�¶�ѡ��
	uchar			WaterTempGear;					//ˮ�µ�λ
	uchar			DryTempGear;					//���µ�λ
	uchar			SeatTempGear;					//���µ�λ
	uchar			NozzleGear; 					//��˵�λ
	uchar			ValveGear;						//ˮѹ��λ
	uchar 			RfSendFlag : 1;					//���͵�ƽ
} SYS_INF;
//VAR_KEY_DEAL_EXT SYS_INF SysInf __attribute__((at(0x1A0)));
VAR_KEY_DEAL_EXT SYS_INF SysInf;
VAR_KEY_DEAL_EXT void f_pKeyDeal(void);
#endif /* __KEYDEAL_H__ */
