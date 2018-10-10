#ifndef __STEP_MOTOR_DRIVER_H__
#define __STEP_MOTOR_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�										  *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * ǰ������ 										*
 *----------------------------------------------*/
struct stepmotor_driver;
typedef struct stepmotor_driver STEPMOTER_DRIVER;

/*----------------------------------------------*
 * �������Ͷ���										*
 *----------------------------------------------*/
typedef struct 
{
	void(*StepmotorOut) (STEPMOTER_DRIVER *, uchar);
	uchar const *pTab_Step;//�����������������
	uchar const phaseCnt;//���õ�����
	uint const stepOPtTm;//����Ļ���ʱ��(���õ��ٶ�)
	uint const startOptTm; //��������ٶ�(Ǩ��)
	sint const *pTab_Reset;//��λ��
} STEPMOTOR_HARDWARE_DRIVER;

typedef union
{
	byte_8	byte;
	struct
	{
		byte_8 bInReset:1;//���ڸ�λ
		byte_8 bRunning:1;//��ת����
	}bits;
}STEPMOTOR_FLAG;

typedef enum
{
	STEPMOTOR_DIR_STOP = 0,
	STEPMOTOR_DIR_FWD,//��ת
	STEPMOTOR_DIR_REV//��ת
}STEPMOTOR_DIR;

typedef enum
{
	STEPMOTER_RESET_MAX = 0,
	STEPMOTER_RESET_MIN,
	STEPMOTER_RESET_ORG
}STEPMOTOR_RESET_STEP;

typedef struct
{
	uchar curPhase; //��ǰ����λ��	
	sint targetPosStep;//Ŀ��λ�ò���(�����0��λ��)
	sint curPosStep;//��ǰλ�ò���(�����0��λ��)
	uint stepOptCnt;//���������(�����ٶ�)
	uchar startStep; //������Ҫ���в���
	STEPMOTOR_DIR runDir;//���з���
	STEPMOTOR_RESET_STEP resetStep;//��λ����
	STEPMOTOR_FLAG	flag;
}STEPMOTOR_DRIVER_DATA;

/*----------------------------------------------*
 * ģ�鼶��������									  *
 *----------------------------------------------*/
struct stepmotor_driver
{
	STEPMOTOR_HARDWARE_DRIVER const *pHardware;
	STEPMOTOR_DRIVER_DATA data;
};


/*----------------------------------------------*
 * ģ�鼶��������									  *
 *----------------------------------------------*/
void f_StepmotorDriverInit(STEPMOTER_DRIVER *pDriver, const STEPMOTOR_HARDWARE_DRIVER *pHardware);
uchar f_StepmotorIsAtPos(STEPMOTER_DRIVER *pDriver, sint pos);
void f_StepmotorReset(STEPMOTER_DRIVER *pDriver);
uchar f_StepmotorResetIsOver(STEPMOTER_DRIVER *pDriver);
void f_StepmotorStopReset(STEPMOTER_DRIVER *pDriver);
void f_StepmotorResetDeal(STEPMOTER_DRIVER *pDriver);
void f_StepmotorOffsetCurPos(STEPMOTER_DRIVER *pDriver, sint offset);
void f_StepmotorRun(STEPMOTER_DRIVER *pDriver);
void f_StepmotorSetTarget(STEPMOTER_DRIVER *pDriver, sint pos, uchar bForce);
void f_StepmotorStop(STEPMOTER_DRIVER *pDriver);
uchar f_StepmotorIsRun(STEPMOTER_DRIVER *pDriver);



#endif /* __STEP_MOTOR_DRIVER_H__ */

