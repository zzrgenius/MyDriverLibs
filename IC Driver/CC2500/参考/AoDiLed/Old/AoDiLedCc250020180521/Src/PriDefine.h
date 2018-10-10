#ifndef __PRIEDEFINE_H
#define __PRIEDEFINE_H

#ifdef  VAR_MAIN_GLOBALS
    #define  VAR_PRIDEFINE_EXT
#else
    #define  VAR_PRIDEFINE_EXT  extern
#endif

//��ʼ��״̬
typedef enum
{
	rSYS_INIT_NO = 0,   	//��ʼ��δ��ʼ
	rSYS_INIT_HLAF,    	//��ʼ���ϰ�����
	rSYS_INIT_OK,       	//��ʼ�����
	rSYS_INIT_FLUSH     	//�޵��ˮ
}SYS_INIT; //��ʼ��״̬

//ϵͳ״̬
typedef enum
{
	STANDBY_STATE = 0,		//����״̬
	RUNNING_STATE,			//����״̬
	TEST_MODE_STATE,		//�ϻ�״̬
	SELFCHECK_STATE		//�Լ�״̬
}SYSTE_STATE;			//ϵͳ״̬

//����״̬
typedef enum
{
	FUNC_NULL = 0,	//�޹���
	FUNC_SPANY,	//�β���ϴ
	FUNC_WOMAN,	//Ů��
	FUNC_DRY		//ů��
}FUNC_STATE;//����״̬
typedef struct
{
	uint 		runTm;          		//����ʱ��
	FUNC_STATE 	curFunc;		//��ǰ����
	FUNC_STATE 	lastCurFunc;    //�ϴι���
	uchar	levelState;     		//��ǰˮѹ
	uchar 	posState;		//��ǰ���
}FUNC_INF;//������Ϣ

//���Ʊ�־λ
typedef union
{
	uchar byte;
	struct
	{
		uchar energySave  : 1;//���ܱ�־
	}flag;
}OTHER_INF;//�������Ʊ�־λ

//����
typedef union
{
	uint byte;
	struct
	{
		uchar bWaterTempHighErr : 1;	//ˮ�¹��߹���
		uchar bSeatTempHighErr : 1;	//���¹��߹���
		uchar bDryTempHighErr : 1;		//���¹��¹���
		uchar bNoWaterErr : 1;			//ȱˮ����	
		uchar bHeatCommunErr : 1;    	//����ͨ�Ź���
		uchar bUartCommunErr: 1;		//������ת�Ӱ�ͨ�Ź���
		uchar bDrySpeedErr : 1;         	//����ٶȴ���
		uchar bBattErr : 1;             		//��ؿ�·���ߵ����ͱ���
		uchar bErrNoRun : 1;    			//�쳣��־λ�ϵ�ǿ��
	}flag;
}SYSTEM_ERR;//ϵͳ���ϱ�־

//�쳣����
typedef struct
{
	uchar bNoWaterCnt;	//��ˮ�쳣����
}ERR_CNT;//�쳣����

//���յ��İ���ֵ
typedef enum
{
	KEY_CMD_NO = 0,//�ް�������
	KEY_CMD_PYGAL_SH,//��ϴ�̰�
	KEY_CMD_PYGAL_RE,	//��ϴ�̰��ɿ�
	KEY_CMD_PYGAL_LO,//��ϴ����
	KEY_CMD_BIDET_SH,//��ϴ�̰�
	KEY_CMD_BIDET_RE,//��ϴ�̰��ɿ�
	KEY_CMD_BIDET_LO,//��ϴ����
	KEY_CMD_STOP_SH,//ֹͣ�̰�
	KEY_CMD_STOP_RE,//ֹͣ�̰��ɿ�
	KEY_CMD_STOP_LO,//ֹͣ����
	KEY_CMD_PYGAL_BIDET1, // ��ϴ�Ӹ�ϴ����1
	KEY_CMD_PYGAL_BIDET2, // ��ϴ�Ӹ�ϴ����2
	KEY_CMD_BIDET_STOP1, // ��ϴ��ֹͣ����1
	KEY_CMD_BIDET_STOP2 // ��ϴ��ֹͣ����2
}KEY_CMD_INF;

//��ַ����
typedef struct
{
	uchar addrFlag : 1;		//��ַ�ź�
}ADDR_INF;

typedef struct
{
	uchar heatComErrFlick : 1;
	uchar zeroCrossErrFlick : 1;
}ERR_FLICK_INF;


typedef struct
{
	SYS_INIT			bInitInf;		//��ʼ����ƽ��־λ
	SYSTE_STATE		SystemCurState;	//ϵͳ��ǰ״̬
	FUNC_INF	 		curFunInf;		//��ǰ������Ϣ
	//OTHER_INF 		otherInf;		//�������Ʊ�־
	//DEO_INF 		deoInf;			//����
	HEAT_INF 		heatInf;			//����
	SWITCH_SEAT_INF seatInf;			//����
	//SWITCH_NIGHT_INF nightInf;		//ҹ��
	//SENSOR_TEMP 	sensorInf;		//�¶ȴ�����
	WASH_INF 		WashInf;		//��ϴ
	//FLOW_METER_INF	flowMeterInf;	//������
	//FLUSH_INF		flushInf;			//��ˮ
	SYSTEM_ERR		systemErrInf;	//ϵͳ���ϱ�־
	//ERR_CNT			ErrCntInf;		//�쳣����
	//LIDSEAT_STRUCT   LidSeatInf;		//���ǵ��
	//KEY_CMD_INF 		KeyCmdInf;		//��������
	//KEY_SCAN_INF 	KeyScanInf;		//����
	uchar AddressRf[3];
	ADDR_INF		addrInf;			//��ַ�ź�
	uchar 			flushTimeState;	//��ˮʱ�����
	ERR_FLICK_INF	errFlickInf;
}BIG_STRUCT;
VAR_PRIDEFINE_EXT AT_NEAR BIG_STRUCT machineInf;

#endif //__PRIEDEFINE_H
