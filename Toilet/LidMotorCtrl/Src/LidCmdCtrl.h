#ifndef __LID_CMD_CTRL_H__
#define __LID_CMD_CTRL_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "LidMotorDriver.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
typedef enum
 {
	LID_RUN_CMD_NULL = 0,
	LID_RUN_CMD_ALL_OPEN,//�ǡ�Ȧȫ��
	LID_RUN_CMD_ALL_CLOSE,//�ǡ�Ȧȫ��
	LID_RUN_CMD_HALF,//�ǿ���Ȧ��
	LID_RUN_CMD_HANDLE //�ֶ�����
 }LID_MOTOR_CMD;//Ӧ�ò��·�����

 typedef enum
{
	SPEED_ADJUST_SEAT_FWD, //��Ȧ����
	SPEED_ADJUST_SEAT_REV, //��Ȧ����
	SPEED_ADJUST_TOP_FWD, //��������
	SPEED_ADJUST_TOP_REV //���Ƿ���
}LID_ADJUST_INDEX;

typedef struct 
{
	LID_MOTOR_CMD setCMD; //��������
	uint cmdRunTm; //��ǰ����ִ��ʱ��
	uint setMaxCmdTm; //���������������ʱ��
	LID_MOTOR_DRIVER seatLidMotor; //��Ȧ�������
	LID_MOTOR_DIR setSeatDir;//��Ȧ���Ʒ���
	uint lastSeatPos; //������Ȧλ��
	LID_MOTOR_DRIVER topLidMotor; //���ǵ������
	LID_MOTOR_DIR setTopDir;//�ϸǿ��Ʒ���
	uint lastTopPos; //�����ϸ�λ��
	uchar handleCheckTm; //�ֶ����Ǽ������
	LID_ADJUST_INDEX adjustIndex; //�ǰ��ٶȵ���˳��

	uchar bCmdSeatDeal :1; //�������ù��ܷ�Ȧ�����Ѵ���
	uchar bCmdTopDeal :1; //�������ù��ܷ��ǲ����Ѵ���
	uchar bSetSeatDir :1; //��Ҫ������Ȧ����
	uchar bSetTopDir :1; //��Ҫ�����ϸǷ���
	uchar badjustMode :1; //�ٶȵ���ģʽ
	uchar bWithMotor :1; //�����(���ز����ˣ�AD����ж�)
}LID_CMD_CTRL;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern LID_CMD_CTRL AT_NEAR lidCmdCtrl;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_LidCmdCtrlInit(void);
void f_LidCmdDeal(LID_CMD_CTRL *pDriver);
uchar f_LidCmdSetCmd(LID_CMD_CTRL *pDriver, LID_MOTOR_CMD cmd, uchar fource);
void f_LidCmdReset(void);


//�ٶȵ�����
void f_LidCmdIntoAdjust(void);
void f_LidCmdAddSpeed(void);
void f_LidCmdDecSpeed(void);
void f_LidCmdAddIndex(void);


#endif /* __LID_CMD_CTRL_H__ */
