#ifndef __STEPMOTOR_HARDWARE_H__
#define __STEPMOTOR_HARDWARE_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "StepMotorDriver.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define SM_ORG_POS	0//ԭ��λ��

//��˵�����λ��
#define SM_NOZZLE_MIN_POS 	-10//����ԭ�����Сλ��
#define SM_NOZZLE_MAX_POS	4000//����ԭ������λ��
#define SM_NOZZLE_MORE_OFFSET 100 //�������ƫ��(��ϴ������˶��߻ز�)

//����������λ��
#define SM_FLOW_MIN_POS 	-1800//����ԭ�����Сλ��
#define SM_FLOW_MAX_POS		1800//����ԭ��Ĵ�λ��


/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern const STEPMOTOR_HARDWARE_DRIVER StepmotorHdSprayNozzle;
extern const STEPMOTOR_HARDWARE_DRIVER StepmotorHdSprayFlow;

extern const sint tab_ResetStep_Nozzle[];
extern const sint tab_ResetStep_Flow[];


/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/



#endif /* __STEPMOTOR_HARDWARE_H__ */
