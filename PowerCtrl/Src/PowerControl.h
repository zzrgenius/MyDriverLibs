#ifndef __POWER_CONTROL_H__
#define __POWER_CONTROL_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
 #include "DataType.h"

/*----------------------------------------------*
 * ǰ������                                         *
 *----------------------------------------------*/
struct power_ctrl;
typedef struct power_ctrl POWER_CTRL;

/*----------------------------------------------*
 * �������Ͷ���                                       *
 *----------------------------------------------*/
#define POWER_CTRL_GROUP_NUM	10//����Ϊ10������

typedef enum
{
	POWER_CTRL_OFF = 0,
	POWER_CTRL_ON = !POWER_CTRL_OFF
}POWER_CTRL_STATE;
 
typedef struct
{
	uchar ctrlGroupIndex;//ʵ�ʿ���˳�򣬰���������Ȼ˳��
	uint  periodOnTm[POWER_CTRL_GROUP_NUM];//ÿ�������ڿ�����ʱ��
	uint  periodTm; //��������ʱ��
}POWER_CTRL_DRIVER_DATA;

typedef void (*PowerCtrlHardware)(POWER_CTRL *, POWER_CTRL_STATE);
	
typedef struct power_ctrl
{
	POWER_CTRL_DRIVER_DATA data;
	PowerCtrlHardware pHardwareFunc;
};

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
 void f_PowerCtrlCalc(POWER_CTRL * pPowerCtrl, uchar percent);
 void f_PowerCtrlOut(POWER_CTRL * pPowerCtrl);
 void f_PowerCtrlInit(POWER_CTRL *pPowerCtrl, const PowerCtrlHardware pFunc);

#endif /* __POWERCONTROL_H__ */
