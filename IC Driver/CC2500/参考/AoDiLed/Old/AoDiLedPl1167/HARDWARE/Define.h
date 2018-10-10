#ifndef __DEFINE_H
#define __DEFINE_H

#ifdef  VAR_MAIN_GLOBALS
    #define  VAR_DEFINE_EXT
#else
    #define  VAR_DEFINE_EXT  extern
#endif

//����
typedef struct
{
	uchar deoFanState : 1;	//�������״̬
}DEO_INF;

//AD������
typedef struct
{
	sint setTemp;			//�����¶�		
	sint sensorTemp;		//�������¶�
	sint lastSensorTemp;	//�������¶Ȼ���	
	sint showTemp;		//��ʾ�¶�
	uchar bShortFlag : 1;	//��·���ϱ�־	
	uchar bOpenFlag : 1;	//��·��־	
	sint setTempAD;		//�����¶ȶ�ӦAD
}SENSOR_INF;	//��������Ϣ
typedef struct
{
	SENSOR_INF EnvTemp;			//����
	SENSOR_INF SeatTemp;		//����
	SENSOR_INF InWaterTemp;		//��ˮ�¶�
	SENSOR_INF OutWaterTemp;	//��ˮ�¶�
	SENSOR_INF DryRotorAD;		//��ɷ����תADֵ
	SENSOR_INF BattAD;			//���ADֵ
	SENSOR_INF LightAD;			//����
	SENSOR_INF SeatAdTemp;		//��ȦAD
	SENSOR_INF LidAdTemp;		//�ϸ�AD
}SENSOR_TEMP;

//��������
typedef struct
{
	uchar bSwitchState : 1;		//����״̬
	uchar bLastSwitchState : 1;	//����״̬
	uint nKeepOnTm;		//ά��ʱ��X100ms
	uint nKeepOffTm;	//ά��ʱ��X100ms
}LEVEL_SWITCH_INF;	//������Ϣ
typedef struct
{
	uchar SwitchSeatEn : 1;			//��������ʹ��
	hour_def SeatOnTm;				//����ʱ��
  	hour_def SeatOffTm;				//����ʱ��
  	LEVEL_SWITCH_INF seatSensorState;	//����������״̬	
}SWITCH_SEAT_INF;

// ҹ��
typedef struct
{
	uchar nightState : 1;				//ҹ��״̬
	uchar nightEn : 1;					//ҹ��ʹ��
	LEVEL_SWITCH_INF nightSensorState;//����״̬
}SWITCH_NIGHT_INF;

//����
typedef enum
{
	TEMP_OFF = 0,
	TEMP_LEVEL1,
	TEMP_LEVEL2,
	TEMP_LEVEL3
}TEMP_LEVEL;//�¶����õȼ�
typedef enum
{
	DRY_OFF = 0,	
	DRY_LEVEL_1,		
	DRY_LEVEL_2,
	DRY_LEVEL_3
}DRY_STATE;	//���ǿ��״̬
typedef struct
{
	uchar seatHeatState : 1;		//��Ȧ����״̬
	uchar energySaveFlag : 1;		//����
	TEMP_LEVEL setSeatLevel;		//������Ȧ���ȵȼ�
}SEAT_HEAT;
typedef struct
{
	uchar waterHeatState : 1;		//ˮ����״̬
	uchar waterHeatFlag : 1;		//�Ƿ�������
	TEMP_LEVEL setWaterLevel;		//����ˮ���ȵȼ�
	uint waterFlow;                  		//����
	uchar waterPercentBuf;		//ˮ�¼���ռ�ձ�
}WATER_HEAT;
typedef struct
{
	uchar dryFanState : 1;			//��ɷ��״̬
	uchar dryHeatState : 1;			//��ɼ���״̬
	DRY_STATE setDryLevel;		//���ú�ɼ��ȵȼ�
	
	/*uchar dryFanEn : 1;			//��ɷ��ʹ��	
	uchar dryFanPeriodCnt;		//��ɷ�����ڼ���
	uchar dryFanPwmPeriod;		//��ɷ��ǰ����������PWM����
	uchar enFanHeat : 1;			//����˿�����
	uchar fanHeatTriac	: 1;			//����˿�ɿع��
	uchar fanHeatOffTm;			//����˿�ر�ʱ��100ms
	uchar fanOnTm;				//���ȴ�ʱ��100ms

	uchar dryPercentBuf;			//��ɼ���ռ�ձ�
	uchar sOffset;					//��ɼ��Ȳ���ֵ*/
}DRY_HEAT;

typedef struct
{
	DRY_HEAT 	dryHeat;
	SEAT_HEAT 	seatHeat;
	WATER_HEAT waterHeat;
}HEAT_INF;

//��ϴ
typedef enum
{
	ORDER_POS_WATER_ORG = 0,     	//��˺͵������������ԭ�����ƶ���ԭ��
	ORDER_WATER_MOVE,           	 	//���䷧�ƶ�
	ORDER_WATER_TARGET,         		//���䷧����ָĿ��λ��
	ORDER_PRO_HEAT,             	 	//Ԥ����
	ORDER_POS_WATER_MOVE,		//��˺ͷ��䷧�ƶ�
	ORDER_POS_WATER_TARGET,	   	//��������ԭ��
	ORDER_WASH_START,		       //��ϴ��ʼ
	ORDER_END_POS_BACK,           	//��˺ͷ��䷧�˻�
	ORDER_DRY_START,              		//�������
	ORDER_WASH_ALL_END		    	//����
}eWASH_ORDER;//��ϴ˳��

typedef struct
{
	eWASH_ORDER   washStep;	//ϴ�Ӳ���
	uint calcTm;	       //ϴ��ʱ��
	uint setWashTm;	//����ϴ��ʱ��
	uchar timeCnt;		//��ΰ�ѹ�ƴ�
}sCLEAN_WASH_INF;//��ϴ��Ϣ

typedef enum
{
	WATER_LEVEL_0 = 0,	
	WATER_LEVEL_1,		
	WATER_LEVEL_2,
	WATER_LEVEL_3
}WATER_LEVEL;//ˮ����С

typedef enum
{
	POS_LEVEL_0 = 0,	
	POS_LEVEL_1,		
	POS_LEVEL_2,
	POS_LEVEL_3,
	POS_LEVEL_4,	
	POS_LEVEL_5,
	POS_LEVEL_6,
	POS_LEVEL_7
}POS_LEVEL;	//���λ��

typedef enum
{
	MODE_STAY = 0,	//�̶�λ��
	MODE_MOVE		//�ƶ�
}eCLEAN_MODE;//�ƶ���Ħ

typedef enum
{
	TEMP_NO_CHANGE = 0, //���仯
	TEMP_HOT_COLD		//���ȱ仯    
}eTEMP_CHANGE;//���Ȱ�Ħ

typedef enum
{
	NO_STR_WEAK = 0, 	//����
	NOMAL_STR_WEAK    	//ǿ��
}eSTR_WEAK; //ǿ����Ħ

typedef enum
{
	POS_NO_CLEAR = 0,	//����޶���
	POS_ORG,			//��˵�ԭ��
	POS_RUN_OUT,		//������
	POS_CLEAR,			//�����ϴ
	POS_RESET			//��˸�λ
}NOZZLE_STEP;//����Խಽ��

typedef struct
{
	NOZZLE_STEP NozzleStep;//����Խ����в���
	unsigned char NozzleClearTime;//�Խ�ʱ��
}eNOZZLE;   //�����ϴ

typedef struct
{
	/*uchar bStopWashFlag : 1;			//ֹͣ��ϴ
	uchar InWaterValve : 1;			//��ˮ��	
	uchar InWaterValveState : 1;		//��ˮ��״̬
	uchar AirState : 1;					//������
	uchar AirPwm;					//������ռ�ձ�
	uchar AirPwmCnt;					//������ռ�ձȼ���
	uchar ChangeWaterFlag : 1;			//���䷧�����ı��־λ
	uchar ChangePosFlag : 1;			//��˶����ı��־λ
	sCLEAN_WASH_INF PygaWash;		//��ϴ
	sCLEAN_WASH_INF BidetWash;		//��ϴ
	WATER_LEVEL	allWaterLevel[2];	   	 //���й���ǿ��
    	POS_LEVEL allPosLevel[2];		   	 //���й������λ��
    	
	eCLEAN_MODE	 cleanMode;			//�ƶ���ϴģʽ
	uchar bMoveCnt;					//�ƶ�ʱ�����
	uchar bMoveModeEnd : 1;			//�ƶ�ʱ�䵽λ����
	uchar rMoveModeFlag : 1;			//�����ƶ���Ħ��־λ*/
	
	eTEMP_CHANGE bTempChange;    	//����ģʽ
	/*uchar rTempChangeCnt;			//����ʱ�����
	uchar bTempChangeEnd : 1;		//����ʱ�䵽λ��־λ
	uchar bTempChangeFlag : 1;		//�������Ȱ�Ħ��־λ
	
	eSTR_WEAK bStrWeak;       			//ǿ��ģʽ
	uchar rStrWeakCnt;				//����ǿ����Ħѭ��ʱ�����
	uchar rStrWeakEnd : 1;				//ǿ����Ħ��λ��־λ
	uchar rStrWeakFlag : 1;				//����ǿ����Ħ��־λ
	
	eNOZZLE bNozzleClear;   			//�����ϴ*/
}WASH_INF;

//������
typedef struct
{
	uint flowMaxCnt;		//�����߼�ʱ
	uint flowMinCnt;		//�����ͼ�ʱ
	uint flowTotalCnt;	//�������
	uchar lastFlag : 1;		//֮ǰ��ƽ
}FLOW_METER_INF;//������

//��ˮ
typedef enum
{
	NO_FLUSH = 0,			//��ϴδ����
	ONE_UP_TIME_CLEAR,	//��һ�ϳ�ǰʱ����0
	UP_FLUSH_ONE,			//�ϳ�
	ONE_DOWN_TIME_CLEAR,	//��һ���³�ǰʱ����0
	DOWN_FLUSH,			//�³�
	SEN_UP_TIME_CLEAR,	//�ڶ��ϳ�ǰʱ����0
	UP_FLUSH_SEN,			//�ڶ����ϳ�
	CLOSE_FLUSH_TIME_CLEAR,//��ϴʱ����0,
	CLOSE_FLUSH			//�ر�
}FLUSH_STEP;
typedef struct
{
	uint bFlushTimeBuff[3];	//������ˮʱ��
	uchar batterFlag : 1;	//��ع���
	uint flushTime; 		//��ˮʱ��
	uchar bigFlush : 1;		//����С���־λ Ϊ0ʱ���
	uchar flushFlag : 1;	//�Ƿ��ˮ��־λ
	uchar valveA : 1;		//��1
	uchar valveB : 1;		//��2

	uchar autoFlush;		//���ʱ ����ϴ�������뿪
	uchar FlushDelayDryFlag : 1;//��ˮ����ʱ�������
	uchar FlushSeatOnOverTimeFlag;//��������ʱ���־λ
	uchar FlushDryOnFlag;//��ɿ���ͬʱ������ˮ��־λ
	uchar FlushKeyOnFlag;//�������±�־λ
	FLUSH_STEP flushStep;	//��ϴ����
	LEVEL_SWITCH_INF manFlushState;//��ʿС���ˮ����
}FLUSH_INF;	//��ϴ�ṹ��

//����
typedef enum
{
	MOTOR_FASTD = 0,    //Ĭ��
	MOTOR_FORWARD,      //����
	MOTOR_REVERSE       //����         
}LS_RUN_STATE;      //���ǹ���״̬

typedef struct
{
	uint SensorAd;//������ADֵ	
	uchar bShortFlag : 1;//��·���ϱ�־	
	uchar bOpenFlag : 1;//��·��־	
}LS_AD;   //ADֵ

typedef enum
{
	POS_L = 0,  //ˮƽλ��
	POS_M,      //�м�λ��
	POS_H       //��ֱλ��
}LS_POS;//����λ��

typedef enum
{
	CMD_NORMAL = 0,//����
	CMD_HALF,//�뿪
	CMD_OPEN,//ȫ��
	CMD_CLOSE//ȫ��
}LS_CMD;//��������

#define MOTOR_NO 2
typedef struct
{
	uchar lidCloseTm;	//�ظ�ʱ��
	LS_RUN_STATE LastRunState[MOTOR_NO];//�ϴε������״̬
	LS_RUN_STATE CurRunState[MOTOR_NO];//��ǰ�������״̬
	LS_AD CurAD[MOTOR_NO];//��ǰADֵ
	LS_POS CurPos[MOTOR_NO];//��ǰλ��
	LS_CMD LSCmdState;//����״̬
	uchar LSCmdFlag : 1;//�����ƽ
	uint InitHighAD[MOTOR_NO];//��ֱ��ʼֵ
	uint InitLowAD[MOTOR_NO];//ˮƽ��ʼֵ
	uchar Pwm[MOTOR_NO];//���ռ�ձ�
	uchar LSRelayFlag : 1;//�̵������ϵ�ƽ 
	uchar LSSeatSwitch : 1;//�������� ���ڽ����ⲿ������Ϣ
	uchar LSInfraredFlag : 1;//����(�Ÿ�)�ź�
	uchar LSWaveFlag;//��ƽ(1Ϊ�����ź�  2Ϊ�ظ��ź�)
	uchar LSForFlag[MOTOR_NO];//��ת��ת��ƽ
	uchar LSRevFlag[MOTOR_NO];//��ת��ת��ƽ
	uint LSForTime[MOTOR_NO];//��ת��תʱ��
	uint LSRevTime[MOTOR_NO];//��ת��תʱ��
	uchar ManLidSeatFalg : 1;//ͬʱ�ֶ�̧���Ȧ���ֹȦ����

	uchar LSInitFlag : 1;// ���ǳ�ʼ����ƽ�ź�
}LIDSEAT_STRUCT;

//����
typedef enum
{//��������\���״̬
	KEY_FREE,
	KEY_COM_PRESS_1,
	KEY_COM_PRESS_2,
	KEY_COM_PRESS_3,
	KEY_COM_PRESS_4,
	KEY_COM_PRESS_5,
	KEY_COM_PRESS_6,
	KEY_COM_PRESS_7,
	KEY_COM_PRESS_8,
	KEY_SIGNAL_PRESS_1,
	KEY_SIGNAL_PRESS_2,
	KEY_SIGNAL_PRESS_3,
	KEY_SIGNAL_PRESS_4,
	KEY_SIGNAL_PRESS_5,
	KEY_SIGNAL_PRESS_6,
	KEY_SIGNAL_PRESS_7,
	KEY_SIGNAL_PRESS_8,
	KEY_SIGNAL_PRESS_9,
	KEY_SIGNAL_PRESS_10,
	KEY_SIGNAL_PRESS_11,
	KEY_SIGNAL_PRESS_12,
	KEY_SIGNAL_PRESS_13,
	KEY_SIGNAL_PRESS_14,
	KEY_SIGNAL_PRESS_15,
	KEY_SIGNAL_PRESS_16,
	KEY_SIGNAL_PRESS_17,
	KEY_SIGNAL_PRESS_18,
	KEY_SIGNAL_PRESS_19,
	KEY_SIGNAL_PRESS_20,
	KEY_SIGNAL_PRESS_21,
	KEY_SIGNAL_PRESS_22,
	KEY_SIGNAL_PRESS_23,
	KEY_SIGNAL_PRESS_24
}KEY_PRESSED_STATE;

typedef struct
{
	ulong nKeyInf;	//��ȡ������ԭʼ������Ϣ
	uchar nKeyResultInf; //������������
	uchar bKeyUsedFlag : 1; //���������ʹ��
	uchar bKeyFirstRelse : 1;//������һ�α��ͷ�
	uchar bKeyPressFlag : 1;	//���������±�־
	KEY_PRESSED_STATE KeyPressName;	//���°�����
	uint nKeyDownTm;//��������ʱ��
	uint nNoKeyTm;//�ް�������ʱ��
	uint nKeyRealDownTm;	//������ʵ����ʱ��
	uchar nKeyStep;//ɨ�貽��
}KEY_SCAN_INF;

#endif	//__DEFINE_H