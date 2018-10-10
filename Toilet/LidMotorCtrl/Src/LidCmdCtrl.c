/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : LidCmdCtrl.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��15��
  ����޸�   :
  ��������   : ���������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��15��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "HeadInclude.h"
#include "LidMotorHardware.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/
LID_CMD_CTRL AT_NEAR lidCmdCtrl;

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/
//�ٶȵ���˳��
schar* const tab_speedIndex[] =
{
	&lidCmdCtrl.seatLidMotor.data.fwdOffset,
	&lidCmdCtrl.seatLidMotor.data.revOffset,
	&lidCmdCtrl.topLidMotor.data.fwdOffset,
	&lidCmdCtrl.topLidMotor.data.revOffset
};

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/

/*****************************************************************************
 �� �� ��: f_LidCmdSetCmd
 ��������  : ���õ�ǰ����
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��15��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_LidCmdSetCmd(LID_CMD_CTRL *pDriver, LID_MOTOR_CMD cmd, uchar fource)
{
	uchar ret = false;
	
	pDriver->cmdRunTm = 0;
    pDriver->bCmdSeatDeal = false;
    pDriver->bCmdTopDeal = false;
    
    //ǿ��
	if (fource || LID_RUN_CMD_NULL == cmd)
	{
		pDriver->setCMD = cmd;
	    ret = true;
	}
	else
	{
		if (STATE_ON == funcSit.sitSwitch.state
		|| SYS_STATE_STANDBY == systemInfo.sysState)//����/�ػ�������Ч/�Ѳ���pDriver->bWithMotor
		{
			pDriver->setCMD = LID_RUN_CMD_NULL;
		}
		else
		{
		    pDriver->setCMD = cmd;
		    ret = true;
		    
	    }
	}
    return ret;
}

/*****************************************************************************
 �� �� ��: f_LidCmdDeal
 ��������  : ���Ƿ�Ȧ�����
 �������:
 �� �� ֵ: 
 ע     ��: 10ms
 
 �޸���ʷ:
  1.��    ��   : 2018��5��15��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_LidCmdDeal(LID_CMD_CTRL *pDriver)
{
	LID_MOTOR_DIR dir;

	//====�ֶ��ж�(�������ж�)====
	if (STATE_OFF == funcSit.sitSwitch.state
	&& systemInfo.powerOnTm > 1)//�ϵ�1S�ȶ���
	{
		pDriver->handleCheckTm++;
		if (pDriver->handleCheckTm >= 5)// 50ms���һ��
		{
			pDriver->handleCheckTm = 0;
			
			//��Ȧ�ֶ��ж�
		    dir = f_LidMotorHandleCheck(&pDriver->seatLidMotor, pDriver->lastSeatPos);
	    	pDriver->lastSeatPos = pDriver->seatLidMotor.data.curAngle;

		    if (MOTOR_DIR_REV == dir)//��ת
		    {
		    	f_LidCmdSetCmd(pDriver, LID_RUN_CMD_HANDLE, false); //�ֶ�
		    	pDriver->setSeatDir = MOTOR_DIR_REV;
		    	pDriver->bSetSeatDir = true;
		    }
		    else if (MOTOR_DIR_FWD == dir)//��ת
		    {
				f_LidCmdSetCmd(pDriver, LID_RUN_CMD_ALL_OPEN, false); //ȫ��
		    }
		   
		    //�����ֶ��ж�
		    dir = f_LidMotorHandleCheck(&pDriver->topLidMotor, pDriver->lastTopPos);
		    pDriver->lastTopPos = pDriver->topLidMotor.data.curAngle;
		    if (MOTOR_DIR_REV == dir)//��ת
		    {
				f_LidCmdSetCmd(pDriver, LID_RUN_CMD_ALL_CLOSE, false); //ȫ��
		    }
		    else if (MOTOR_DIR_FWD == dir)//��ת
		    {
		    	f_LidCmdSetCmd(pDriver, LID_RUN_CMD_HANDLE, false); //�ֶ�
		    	pDriver->setTopDir = MOTOR_DIR_FWD;
		    	pDriver->bSetTopDir = true;
		    }
	    }
    }
    else
    {
		pDriver->lastSeatPos = pDriver->seatLidMotor.data.curAngle;
		pDriver->lastTopPos = pDriver->topLidMotor.data.curAngle;
    }

	//====�����====
    if (LID_RUN_CMD_ALL_OPEN == pDriver->setCMD)//ȫ��
    {
    	MOTOR_RELAY(STATE_ON);
    	//�����з���
    	if (pDriver->bCmdTopDeal == false)
    	{
    		pDriver->bCmdTopDeal = true;
    		pDriver->setTopDir = MOTOR_DIR_FWD;
    		pDriver->bSetTopDir = true;
    	}

		//�ϸ������е���λ������,��Ȧ����
    	if (f_LidMotorIsOverMid(&pDriver->topLidMotor) == true)
    	{
			if (pDriver->bCmdSeatDeal == false)
	    	{
	    		pDriver->bCmdSeatDeal = true;
	    		pDriver->setSeatDir = MOTOR_DIR_FWD;
	    		pDriver->bSetSeatDir = true;
	    	}
    	}
    }
    else if (LID_RUN_CMD_ALL_CLOSE == pDriver->setCMD)//ȫ��
    {
    	MOTOR_RELAY(STATE_ON);
    	//�����з�Ȧ
    	if (pDriver->bCmdSeatDeal == false)
    	{
    		pDriver->bCmdSeatDeal = true;
    		pDriver->setSeatDir = MOTOR_DIR_REV;
    		pDriver->bSetSeatDir = true;
    	}

		//��Ȧ�����е���λ������,�ǰ�����
    	if (f_LidMotorIsOverMid(&pDriver->seatLidMotor) == false)
    	{
			if (pDriver->bCmdTopDeal == false)
	    	{
	    		pDriver->bCmdTopDeal = true;
	    		pDriver->setTopDir = MOTOR_DIR_REV;
	    		pDriver->bSetTopDir = true;
	    	}
    	}
    }
    else if (LID_RUN_CMD_HALF == pDriver->setCMD)//�뿪
    {
    	MOTOR_RELAY(STATE_ON);
    	//��Ȧ
    	if (pDriver->bCmdSeatDeal == false)
    	{
    		pDriver->bCmdSeatDeal = true;
    		pDriver->setSeatDir = MOTOR_DIR_REV;
    		pDriver->bSetSeatDir = true;
    	}

		//����
		if (pDriver->bCmdTopDeal == false)
    	{
    		pDriver->bCmdTopDeal = true;
    		pDriver->setTopDir = MOTOR_DIR_FWD;
    		pDriver->bSetTopDir = true;
    	}
    }

    
    if (LID_RUN_CMD_NULL != pDriver->setCMD)//��ֹͣ
    {
    	MOTOR_RELAY(STATE_ON);
    }
    else 
    {
    	MOTOR_RELAY(STATE_OFF);
    	pDriver->setSeatDir = MOTOR_DIR_STOP;
    	pDriver->setTopDir = MOTOR_DIR_STOP;
    	pDriver->bSetSeatDir = true;
    	pDriver->bSetTopDir = true;
    }
    
    if (LID_RUN_CMD_NULL != pDriver->setCMD)//�������ʱ���˳��ж�
	{
		f_AddU16Data(&pDriver->cmdRunTm);
	    if (pDriver->cmdRunTm >= pDriver->setMaxCmdTm)
	    {
			pDriver->setCMD = LID_RUN_CMD_NULL;
	    }
    }

    //====���õ������====
    if (pDriver->bSetSeatDir)
    {
    	pDriver->bSetSeatDir = false;
    	f_LidMotorSetState(&pDriver->seatLidMotor, pDriver->setSeatDir);
    }

    if (pDriver->bSetTopDir)
    {
    	pDriver->bSetTopDir = false;
    	f_LidMotorSetState(&pDriver->topLidMotor, pDriver->setTopDir);
    }

	//====ʵ�ʵ������====
	f_LidMotorCtrl(&pDriver->seatLidMotor); // ��Ȧ�������
	f_LidMotorCtrl(&pDriver->topLidMotor); // ���ǵ������

	//====��������ж�=====
    if (MOTOR_DIR_STOP == pDriver->topLidMotor.data.curDir 
    && MOTOR_DIR_STOP == pDriver->seatLidMotor.data.curDir)//�������ֹͣ
    {
		pDriver->setCMD = LID_RUN_CMD_NULL;
    }
}

/*****************************************************************************
 �� �� ��: f_LidCmdReset
 ��������  : ��λ�ǰ�
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��13��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_LidCmdReset(void)
{
    //���е����ʼ����λ(��Ի���)
//    f_LidMotorReset(&lidCmdCtrl.seatLidMotor);
    f_LidMotorReset(&lidCmdCtrl.topLidMotor);
    f_LidCmdSetCmd(&lidCmdCtrl, LID_RUN_CMD_ALL_CLOSE, true); //ǿ�ƺϸ�
}

/*****************************************************************************
 �� �� ��: f_LidCmdCtrlInit
 ��������  : ����������Ƴ�ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��15��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_LidCmdCtrlInit(void)
{
	f_Memset(&lidCmdCtrl, 0, sizeof(LID_CMD_CTRL));
    f_LidMotorDriverInit(&lidCmdCtrl.seatLidMotor, &seatLidHardware, f_SeatLidSetFwdSpeed, f_SeatLidSetRevSpeed, 100);//����10ms
    f_LidMotorDriverInit(&lidCmdCtrl.topLidMotor, &topLidHardware, f_TopLidSetFwdSpeed, f_TopLidSetRevSpeed, 100);//����10ms
    lidCmdCtrl.setMaxCmdTm = 500; //���������������ʱ��5S

    //��λ�ǰ�
    f_LidCmdReset();

    //====�ٶȳ�ʼ��ֵ====
    //��Ȧ����
    lidCmdCtrl.seatLidMotor.data.speedFwd[0] = 100;
    lidCmdCtrl.seatLidMotor.data.speedFwd[1] = 90;
    lidCmdCtrl.seatLidMotor.data.speedFwd[2] = 80;
    lidCmdCtrl.seatLidMotor.data.speedFwd[3] = 70;
    lidCmdCtrl.seatLidMotor.data.speedFwd[4] = 60;
    lidCmdCtrl.seatLidMotor.data.speedFwd[5] = 50;
    lidCmdCtrl.seatLidMotor.data.speedFwd[6] = 30;
    lidCmdCtrl.seatLidMotor.data.speedFwd[7] = 20;
    lidCmdCtrl.seatLidMotor.data.speedFwd[8] = 10;
    lidCmdCtrl.seatLidMotor.data.speedFwd[9] = 0;
    //��Ȧ����
    lidCmdCtrl.seatLidMotor.data.speedRev[0] = 10;
    lidCmdCtrl.seatLidMotor.data.speedRev[1] = 10;
    lidCmdCtrl.seatLidMotor.data.speedRev[2] = 15;
    lidCmdCtrl.seatLidMotor.data.speedRev[3] = 20;
    lidCmdCtrl.seatLidMotor.data.speedRev[4] = 25;
    lidCmdCtrl.seatLidMotor.data.speedRev[5] = 30;
    lidCmdCtrl.seatLidMotor.data.speedRev[6] = 35;
    lidCmdCtrl.seatLidMotor.data.speedRev[7] = 40;
    lidCmdCtrl.seatLidMotor.data.speedRev[8] = 45;
    lidCmdCtrl.seatLidMotor.data.speedRev[9] = 50;

    //��������
    lidCmdCtrl.topLidMotor.data.speedFwd[0] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[1] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[2] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[3] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[4] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[5] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[6] = 80;
    lidCmdCtrl.topLidMotor.data.speedFwd[7] = 40;
    lidCmdCtrl.topLidMotor.data.speedFwd[8] = 10;
    lidCmdCtrl.topLidMotor.data.speedFwd[9] = 0;
    //���Ƿ���(�ǰ�Ƚ��أ���Ҫ��ɲ��)
    lidCmdCtrl.topLidMotor.data.speedRev[0] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[1] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[2] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[3] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[4] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[5] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[6] = 10;
    lidCmdCtrl.topLidMotor.data.speedRev[7] = 30;
    lidCmdCtrl.topLidMotor.data.speedRev[8] = 60;
    lidCmdCtrl.topLidMotor.data.speedRev[9] = 90;
}

//====�����ٶ���====

/*****************************************************************************
 �� �� ��: f_LidCmdIntoAdjust
 ��������  : ����ǰ��ٶȵ���ģʽ
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��23��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_LidCmdIntoAdjust(void)
{
    lidCmdCtrl.adjustIndex = SPEED_ADJUST_SEAT_FWD;
	lidCmdCtrl.badjustMode = true;
}

/*****************************************************************************
 �� �� ��: f_LidCmdAddSpeed
 ��������  : �ٶ�����
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��23��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_LidCmdAddSpeed(void)
{
	if (*tab_speedIndex[lidCmdCtrl.adjustIndex] < speedOffsetRange.max)
	{
	    (*tab_speedIndex[lidCmdCtrl.adjustIndex])++;
	    f_StorageWriteValues(&storageDriver, STORAGE_SEAT_FWD_OFFSET + lidCmdCtrl.adjustIndex, true);
    }
}

/*****************************************************************************
 �� �� ��: f_LidCmdDecSpeed
 ��������  : �ٶȼ�С
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��23��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_LidCmdDecSpeed(void)
{
	if (*tab_speedIndex[lidCmdCtrl.adjustIndex] > speedOffsetRange.min)
	{
	    (*tab_speedIndex[lidCmdCtrl.adjustIndex])--;
	    f_StorageWriteValues(&storageDriver, STORAGE_SEAT_FWD_OFFSET + lidCmdCtrl.adjustIndex, true);
    }
}

/*****************************************************************************
 �� �� ��: f_LidCmdAddIndex
 ��������  : �����������
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��23��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_LidCmdAddIndex(void)
{
    if (lidCmdCtrl.adjustIndex < SPEED_ADJUST_TOP_REV)
	{
		lidCmdCtrl.adjustIndex++;
	}
	else
	{
		lidCmdCtrl.badjustMode = false;
	}
}

