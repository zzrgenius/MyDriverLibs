#ifndef __FUNC_FLUSH_DEAL_H__
#define __FUNC_FLUSH_DEAL_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
typedef enum 
{
	FLUSH_SREQ_STOP, //��ˮֹͣ
	FLUSH_SREQ_START, //������ˮ
	FLUSH_SREQ_ROUND_1, //��һ��ȹ�߳�ˮ
	FLUSH_SREQ_BOTTOM, //�ײ���ˮ
	FLUSH_SREQ_ROUND_2 //�ڶ���ȹ�߳�ˮ
}FUNC_FLUSH_SREQ;

typedef enum
{
	FLUSH_CMD_NULL, //�޳�ˮ
	FLUSH_CMD_ROUND, //��ڳ�ˮ
	FLUSH_CMD_NORMAL //���+�ײ�+���
}FUNC_FLUSH_CMD;//��ˮ����

typedef enum
{
	FLUSH_VALVE_OFF,//��
	FLUSH_VALVE_ON,//��
	FLUSH_VALVE_BRAKE//ɲ��
}FLUSH_VALVE_STATE;

typedef enum
{
	FLUSH_ADJUST_WASH, //ϴˢ
	FLUSH_ADJUST_CLEAN, //����
	FLUSH_ADJUST_BACK, //��ˮ
	FLUSH_ADJUST_OVER //���ڽ���
}FLUSH_ADJUST_INDEX;//��ϴʱ�����˳��

typedef struct 
{
	uchar dealyToBreakTm; // �����رպ���Ҫ��ʱ��ɲ��״̬
	FLUSH_VALVE_STATE setValve;
	FLUSH_VALVE_STATE lastSetValve;
	
	uchar bState:1; //��ǰ״̬(Ӳ��״̬)
	uchar bLastState:1;//����״̬(Ӳ��״̬)
}FUNC_FLUSH_VALVE;
 
typedef struct 
{
	FUNC_FLUSH_SREQ curStep;//��ǰ˳��
	uint flushTm; //��ǰ��ˮʱ��,��λ100ms
	uint setRound_1_Tm; //���õ�һ����ڳ�ˮʱ��
	uint setBottomTm; //���õײ���ˮʱ��
	uint setRound_2_Tm; //���õڶ�����ڳ�ˮʱ��
	FUNC_FLUSH_VALVE roundValve; //��ڷ�
	FUNC_FLUSH_VALVE bottomValve; //�ײ���
	uint batteryAD; //��ص���AD
	uchar batteryOnCnt;//������������
	uchar batteryOffCnt;//�����ͼ���

	uint saveFlushtm[FLUSH_ADJUST_OVER];//���籣��ĳ�ϴʱ��
	FLUSH_ADJUST_INDEX adjustIndex; //����˳��
	
	uchar bPowerOff:1; //��ˮ�����е���
	uchar bLowPower:1; //��ص�ѹ����
	uchar bAdjust :1; //����ģʽ
}FUNC_FLUSH;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern FUNC_FLUSH AT_NEAR funcFlush;
/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_FuncFlushValveCtrl(void);
void f_FuncFlushDeal(void);
void f_FuncFlushInit(void);
uchar f_FuncSetFlushMode(FUNC_FLUSH_CMD cmd);
uchar f_FuncSetFlushTm(uint tm_wash, uint tm_clean, uint tm_back);
void f_FuncFlushBatteryCheck(void);
void f_FuncFlushPowerCheck(void);

#endif /* __FUNC_FLUSH_DEAL_H__ */
