#ifndef __LID_MOTOR_DRIVER_H__
#define __LID_MOTOR_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "IoPwmDriver.h"

/*----------------------------------------------*
 * ǰ������                                         *
 *----------------------------------------------*/
struct lid_motor_driver;
typedef struct lid_motor_driver LID_MOTOR_DRIVER;

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
 typedef enum
 {
	MOTOR_DIR_STOP = 0,
	MOTOR_DIR_FWD,//�����ת
	MOTOR_DIR_REV//�����ת
 }LID_MOTOR_DIR;//���ǵ������

 typedef enum
 {
	LID_IN_RANGE_LOW = 0,//�����
	LID_IN_RANGE_MID,//������
	LID_IN_RANGE_HIGH//�����
 }LID_MOTOR_RANGE;

 typedef struct
 {
 	uint setRangeLow; //Ӳ������λ��
 	uint setRangeHigh; //Ӳ������λ��
 	uint lockOffset; //��ת���仯ƫ��,�ڹ̶�ʱ����,�仯С�ڸ�ֵ����Ϊ��ת	
 	uint maxPos; //���ֵ(����λ��,��AD���������)
 	uint minPos; //��Сֵ(����λ��,��AD���������)
 	uint handleOffset; //�ֶ�ƫ��
	void (*GetLidMotorPos)(LID_MOTOR_DRIVER *);//��ȡ��ǰλ��
	void (*MotorFwdEn)(STATE_INFO); //��תʹ�ܿ�
	void (*MotorRevEn)(STATE_INFO); //��תʹ�ܿ�
	
	uchar bIncrease :1;//λ���ɸ��ϵ������Ƿ����ֵ���
 }LID_MOTOR_HARDWARE;//���ǵ��Ӳ������

#define SPEED_DEV_CNT 10ul //�ٶ�ϸ�ֵ�λ��
 typedef struct 
 {
	LID_MOTOR_DIR curDir;//���������
	LID_MOTOR_DIR lastDir;//��������򻺴�
	uint curAngle;//��ǰλ�ýǶ���Ϣ(��AD��ʾ)
	uint lastAngle;//����λ�ýǶ���Ϣ(��AD��ʾ)
	uchar posIndex; //λ�÷�λ���
	LID_MOTOR_RANGE posRange;//����λ�÷�Χ
	uchar changeDirTm;//����λ�ü��ȥ��ʱ��
	uchar lockTm;//��ת���ʱ��
	uchar lockCnt; //��ת����
	IO_PWM_DRIVER pwmFwdOut; //��תpwm���
	IO_PWM_DRIVER pwmRevOut; //��תתpwm���
	schar fwdOffset; //����ƫ��ֵ
	schar revOffset; //����ƫ��ƫ��ֵ
	uchar speedFwd[SPEED_DEV_CNT]; //��תÿ���׶��ٶ�,��ռ�ձȱ�ʾ
	uchar speedRev[SPEED_DEV_CNT]; //��ÿ���׶��ٶ�,��ռ�ձȱ�ʾ
	
	uchar bEnLockCheck :1;//ʹ�ܶ�ת���
	uchar bRunning :1; //��������
	uchar bReset :1; //��ʼ����λλ��
 }LID_MOTOR_DATA;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
struct lid_motor_driver
{
	LID_MOTOR_DATA data;
	LID_MOTOR_HARDWARE const *pHardware;
};
 

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_LidMotorCtrl(LID_MOTOR_DRIVER *pDriver);
void f_LidMotorDriverInit(LID_MOTOR_DRIVER *pDriver, 
								  LID_MOTOR_HARDWARE *pHardware,
								  SetOut fwdOut,
								  SetOut revOut, 
								  uint period);
uchar f_LidMotorSetState(LID_MOTOR_DRIVER *pDriver, LID_MOTOR_DIR dir);
uchar f_LidMotorIsOverMid(LID_MOTOR_DRIVER *pDriver);
LID_MOTOR_DIR f_LidMotorHandleCheck(LID_MOTOR_DRIVER *pDriver, uint lastPos);
void f_LidMotorReset(LID_MOTOR_DRIVER *pDriver);
void f_LidMotorChangePos(LID_MOTOR_DRIVER *pDriver, uchar dir);

#endif /* __LID_MOTOR_DRIVER_H__ */
