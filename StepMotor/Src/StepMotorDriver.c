/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : StepMotorDriver.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��18��
  ����޸�   :
  ��������   : ���������������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��18��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "StepMotorDriver.h"
#include "SubFunction.h"

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

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/

/*****************************************************************************
 �� �� ��: void f_StepmotorRun(STEPMOTER_DRIVER *pDriver)
 ��������  : ����������д���
 �������: pDriver ����ָ��
 �� �� ֵ: 
 ע     ��: 100us����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��18��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_StepmotorRun(STEPMOTER_DRIVER *pDriver)
{
    #define STEP_START_STEP 16 //��������(��Ť��Ǩ��)
	sint needRunStep;
	
	if (pDriver->data.curPosStep == pDriver->data.targetPosStep)
	{
		pDriver->data.stepOptCnt = 0;
		pDriver->data.startStep = 0;
		pDriver->data.runDir = STEPMOTOR_DIR_STOP;
		pDriver->data.flag.bits.bRunning = false;
		pDriver->pHardware->StepmotorOut(pDriver, 0); //�ر����
	}
	else//�����λ�÷����仯
	{
		f_AddU16Data(&(pDriver->data.stepOptCnt)); //�������
		
		if ( (pDriver->data.startStep <= STEP_START_STEP && pDriver->data.stepOptCnt > pDriver->pHardware->startOptTm)
		|| (pDriver->data.startStep > STEP_START_STEP && pDriver->data.stepOptCnt > pDriver->pHardware->stepOPtTm))
		{
			pDriver->data.stepOptCnt = 0;
			needRunStep = pDriver->data.targetPosStep - pDriver->data.curPosStep;
			f_AddU8Data(&(pDriver->data.startStep)); //��������
			
			if (needRunStep < 0)
			{
				//��Ҫ��ת
				pDriver->data.runDir = STEPMOTOR_DIR_REV;
				pDriver->data.curPosStep --;
				
				if (pDriver->data.curPhase > 0)
				{
					pDriver->data.curPhase--;
				}
				else
				{
					pDriver->data.curPhase = (pDriver->pHardware->phaseCnt - 1);
				}
			}
			else
			{
				//��Ҫ��ת
				pDriver->data.runDir = STEPMOTOR_DIR_FWD;
				pDriver->data.curPosStep ++;

				if (pDriver->data.curPhase < (pDriver->pHardware->phaseCnt - 1))
				{
					pDriver->data.curPhase ++;
				}
				else
				{
					pDriver->data.curPhase = 0;
				}
			}

			//�ײ����
			pDriver->data.flag.bits.bRunning = true;
			pDriver->pHardware->StepmotorOut(pDriver, pDriver->pHardware->pTab_Step[pDriver->data.curPhase]);
		}
	} 
}

/*****************************************************************************
 �� �� ��: void f_StepmotorSetTarget(STEPMOTER_DRIVER *pDriver, sint pos, uchar bForce)
 ��������  : ���ò���������þ���λ��
 �������: pDriver ����ָ��
 		   pos ����0��λ��
 		   bForce �Ƿ�ǿ���л�
 �� �� ֵ: 
 ע     ��: ��Ҫʱ����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��18��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_StepmotorSetTarget(STEPMOTER_DRIVER *pDriver, sint pos, uchar bForce)
{
	//ǿ���л�/��ǿ��ʱֻ�е�������е�ʱ���������µ�Ŀ��λ�ã�������Ч
	if (bForce || (!bForce && !pDriver->data.flag.bits.bRunning))
	{
    	pDriver->data.targetPosStep = pos;
    }
}

/*****************************************************************************
 �� �� ��: f_StepmotorStop
 ��������  : ���ֹͣ
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��21��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_StepmotorStop(STEPMOTER_DRIVER *pDriver)
{
    pDriver->data.targetPosStep = pDriver->data.curPosStep;
}

/*****************************************************************************
 �� �� ��: f_StepmotorIsRun
 ��������  : ����Ƿ���������
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��24��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_StepmotorIsRun(STEPMOTER_DRIVER *pDriver)
{
    return pDriver->data.flag.bits.bRunning;
}

/*****************************************************************************
 �� �� ��: void f_StepmotorIsAtPos(STEPMOTER_DRIVER *pDriver, sint pos)
 ��������  : �Ƿ��ڵ�ǰλ��
 �������: pDriver ����ָ��
 		   pos ����0��λ��
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��18��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_StepmotorIsAtPos(STEPMOTER_DRIVER *pDriver, sint pos)
{
    return (pDriver->data.curPosStep == pos)?true:false;
}

/*****************************************************************************
 �� �� ��: f_StepmotorReset
 ��������  : ���������λ
 �������:
 �� �� ֵ: 
 ע     ��: ��Ҫʱ����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��18��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_StepmotorReset(STEPMOTER_DRIVER *pDriver)
{
    pDriver->data.flag.bits.bInReset = true;
    pDriver->data.resetStep = STEPMOTER_RESET_MAX;
}

/*****************************************************************************
 �� �� ��: f_StepmotorOffsetCurPos
 ��������  : �������õ�ǰλ��(�Ե�ǰλ��ƫ��)
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��8��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_StepmotorOffsetCurPos(STEPMOTER_DRIVER *pDriver, sint offset)
{
    pDriver->data.targetPosStep += offset;
    if (pDriver->data.targetPosStep > pDriver->pHardware->pTab_Reset[STEPMOTER_RESET_MAX])
    {
        pDriver->data.targetPosStep = pDriver->pHardware->pTab_Reset[STEPMOTER_RESET_MAX];
    }
    else if (pDriver->data.targetPosStep < pDriver->pHardware->pTab_Reset[STEPMOTER_RESET_MIN])
    {
        pDriver->data.targetPosStep = pDriver->pHardware->pTab_Reset[STEPMOTER_RESET_MIN];
    }

    pDriver->data.curPosStep =  pDriver->data.targetPosStep;
}

/*****************************************************************************
 �� �� ��: f_StepmotorResetIsOver
 ��������  : �ж��Ƿ�λ���
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_StepmotorResetIsOver(STEPMOTER_DRIVER *pDriver)
{
    return pDriver->data.flag.bits.bInReset == false?true:false;
}

/*****************************************************************************
 �� �� ��: f_StepmotorStopReset
 ��������  : ֹͣ��λ
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_StepmotorStopReset(STEPMOTER_DRIVER *pDriver)
{
    pDriver->data.flag.bits.bInReset = false;
}


/*****************************************************************************
 �� �� ��: f_StepmotorResetDeal
 ��������  : ���������λ���̴���
 �������:
 �� �� ֵ: 
 ע     ��: 100ms����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��18��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_StepmotorResetDeal(STEPMOTER_DRIVER *pDriver)
{
    if (pDriver->data.flag.bits.bInReset)
    {
		if(!f_StepmotorIsAtPos(pDriver, pDriver->pHardware->pTab_Reset[pDriver->data.resetStep]))
		{
			//δ���ﵱǰλ�ã�ǿ�Ƽ������е�Ŀ��λ��
			f_StepmotorSetTarget(pDriver, pDriver->pHardware->pTab_Reset[pDriver->data.resetStep], true);
		}
		else
		{
			if (pDriver->data.resetStep < STEPMOTER_RESET_ORG)
			{
				//�������ȵ������->��С->ԭ��
				pDriver->data.resetStep++;
			}
			else
			{
				//��λ���
				pDriver->data.flag.bits.bInReset = false;
			}
		}
	}
}

/*****************************************************************************
 �� �� ��: void f_StepmotorDriverInit(STEPMOTER_DRIVER *pDriver, STEPMOTOR_HARDWARE_DRIVER *pHardware)
 ��������  : �������������ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: �״γ�ʼ��ʱ����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��18��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_StepmotorDriverInit(STEPMOTER_DRIVER *pDriver, const STEPMOTOR_HARDWARE_DRIVER *pHardware)
{
	f_Memset(pDriver, 0, sizeof(STEPMOTER_DRIVER));
	pDriver->pHardware = pHardware;
}

