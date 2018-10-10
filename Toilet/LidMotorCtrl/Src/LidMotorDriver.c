/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : LidMotorDriver.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��20��
  ����޸�   :
  ��������   : ���ǵ������,������������Ͱ��Ȧ���ǡ���סʱλ��Ϊ0,ֱ��Ϊ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��20��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "LidMotorDriver.h"
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
#define LID_MOTOR_LOCK_TM 5//X10ms�����ת���ʱ��
#define LID_MOTOR_LOCK_CNT 2 //������⵽��ת����,�����ת
#define LID_MOTOR_CHANGE_DIR_TM 10//x10ms�����ֹ����תʱ��
 
/*****************************************************************************
 �� �� ��: f_LidMotorRangeCheck
 ��������  : �ǰ�������
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��13��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_LidMotorRangeCheck(LID_MOTOR_DRIVER *pDriver)
{
	//��ȡλ��ֵ
	pDriver->pHardware->GetLidMotorPos(pDriver);
	
	if (pDriver->data.curAngle > pDriver->pHardware->maxPos)
	{
		pDriver->data.curAngle = pDriver->pHardware->maxPos;
	}
	else if (pDriver->data.curAngle < pDriver->pHardware->minPos)
	{
		pDriver->data.curAngle = pDriver->pHardware->minPos;
	}


    //�����ж�
    if (pDriver->pHardware->bIncrease)//�����Ϸ����
    {
		if (pDriver->data.curAngle <= pDriver->pHardware->setRangeLow)
		{
			pDriver->data.posRange = LID_IN_RANGE_LOW;
		}
		else if (pDriver->data.curAngle >= pDriver->pHardware->setRangeHigh)
		{
			pDriver->data.posRange = LID_IN_RANGE_HIGH;
		}
		else 
		{
			pDriver->data.posRange = LID_IN_RANGE_MID;
		}
    }
    else 
    {
		if (pDriver->data.curAngle >= pDriver->pHardware->setRangeLow)
		{
			pDriver->data.posRange = LID_IN_RANGE_LOW;
		}
		else if (pDriver->data.curAngle <= pDriver->pHardware->setRangeHigh)
		{
			pDriver->data.posRange = LID_IN_RANGE_HIGH;
		}
		else 
		{
			pDriver->data.posRange = LID_IN_RANGE_MID;
		}
    }
}

/*****************************************************************************
 �� �� ��: f_LidMotorLockDeal
 ��������  : ��ת����
 �������:
 �� �� ֵ: 
 ע     ��: 10ms����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��20��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_LidMotorLockDeal(LID_MOTOR_DRIVER *pDriver)
{
	uint offset;
	uchar ret;
	uchar lock = false;

	//��ת���
	f_AddU8Data(&(pDriver->data.lockTm));
    if (pDriver->data.bEnLockCheck)
    {
		/*
			������ת,ʵ��λ��Ӧ������,�����ʱλ�ñ�С����С�����ֵ������Ϊ�Ѷ�ת�����ڷ�ת���෴��
			
		*/
		if (pDriver->data.lockTm >= LID_MOTOR_LOCK_TM)//��ת�����ʱ��
		{
    		pDriver->data.lockTm = 0;
    		if (MOTOR_DIR_FWD == pDriver->data.curDir)//��ǰ��ת
    		{
    			ret = f_CalcU16Offset(pDriver->data.curAngle, pDriver->data.lastAngle, &offset);
    		}
    		else//��ת
    		{
				ret = f_CalcU16Offset(pDriver->data.lastAngle, pDriver->data.curAngle, &offset);
    		}
    		pDriver->data.lastAngle = pDriver->data.curAngle;
    		
			if (pDriver->pHardware->bIncrease == ret)
			{
				//�仯��С����Ϊ��ת
				if (offset < pDriver->pHardware->lockOffset)
				{
					f_AddU8Data(&(pDriver->data.lockCnt));
				}
				else
				{
					pDriver->data.lockCnt = 0;
				}
			}
			else//����ת��,��Ϊ��ת
			{
				f_AddU8Data(&(pDriver->data.lockCnt));
			}

			if (pDriver->data.lockCnt >= LID_MOTOR_LOCK_CNT)
			{
				pDriver->data.curDir = MOTOR_DIR_STOP;

				if (pDriver->data.bReset) //��λʱ��ת��Ϊ�Ѿ���λ��λ
				{
				    pDriver->data.bReset = false;
                    if (pDriver->pHardware->bIncrease)
                    {
                        pDriver->data.curAngle = pDriver->pHardware->minPos;
                    }
                    else
                    {
                        pDriver->data.curAngle = pDriver->pHardware->maxPos;
                    }
				}
			}
		}
    }
    else
    {
		pDriver->data.lockTm = 0;
		pDriver->data.lastAngle = pDriver->data.curAngle;
    }
}

/*****************************************************************************
 �� �� ��: f_LidMotorHandleCheck
 ��������  : �ֶ����Ǽ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��15��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
LID_MOTOR_DIR f_LidMotorHandleCheck(LID_MOTOR_DRIVER *pDriver, uint lastPos)
{
	uint offset;
	uchar ret;
	
	ret = f_CalcU16Offset(pDriver->data.curAngle, lastPos, &offset);
    if (MOTOR_DIR_STOP == pDriver->data.curDir)
    {
		if (offset >= pDriver->pHardware->handleOffset)
		{
			if (pDriver->pHardware->bIncrease == ret)//�ֶ��Ϸ�
			{
				return MOTOR_DIR_FWD; //��ת
			}
			else//�ֶ��·�
			{
				return MOTOR_DIR_REV; //��ת
			}
		}	
    }
    return MOTOR_DIR_STOP;
}

/*****************************************************************************
 �� �� ��: f_LidMotorBreak
 ��������  : ɲ������
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_LidMotorBreak(LID_MOTOR_DRIVER *pDriver)
{
    //���е�ɲ�����̣����е�ɲ�� �ϱ��ȹ�,��ʱ10us�����ٿ����±�
		
    //�ϱ۹ر�
    pDriver->pHardware->MotorFwdEn(STATE_OFF); //��תʹ�ܹر�
    pDriver->pHardware->MotorRevEn(STATE_OFF); //��תʹ�ܹر�

    //��ʱ(��Ҫʵ�ʲ���)
    if (pDriver->data.bRunning)
    {
        f_Delay(50);
        pDriver->data.bRunning = false;
    }
    
    //�±۴򿪽ӵ�
    f_IoPwmDriverSetPercent(&(pDriver->data.pwmFwdOut), 100);
    f_IoPwmDriverSetPercent(&(pDriver->data.pwmRevOut), 100); 
}

/*****************************************************************************
 �� �� ��: f_LidMotorDeal
 ��������  : ���ǵ������
 �������:
 �� �� ֵ: 
 ע     ��: 10ms����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��20��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_LidMotorCtrl(LID_MOTOR_DRIVER *pDriver)
{
	schar percent;
	
	//�����ȥ��ʱ����ֹͣ״̬�������ת���
	if (MOTOR_DIR_STOP == pDriver->data.curDir)
	{
		pDriver->data.bEnLockCheck = false;
		pDriver->data.changeDirTm = 0;
	}
	else
	{
		if (pDriver->data.lastDir == pDriver->data.curDir)
		{
			f_AddU8Data(&(pDriver->data.changeDirTm));

			if (pDriver->data.changeDirTm >= LID_MOTOR_CHANGE_DIR_TM)
			{
				pDriver->data.bEnLockCheck = true;
			}
		}
		else
		{
			pDriver->data.bEnLockCheck = false;
			pDriver->data.changeDirTm = 0;
		}
	}

	f_LidMotorRangeCheck(pDriver); //AD�ɼ��������ж�
	f_LidMotorLockDeal(pDriver); //��ת���

	//��ȡ�����ٶȵ�λ
	if (pDriver->pHardware->bIncrease)//�����Ϸ����
	{
		pDriver->data.posIndex = SPEED_DEV_CNT*(pDriver->data.curAngle - pDriver->pHardware->minPos)/(pDriver->pHardware->maxPos - pDriver->pHardware->minPos);
	}
	else
	{
		pDriver->data.posIndex = SPEED_DEV_CNT*(pDriver->pHardware->maxPos - pDriver->data.curAngle)/(pDriver->pHardware->maxPos - pDriver->pHardware->minPos);
	}
	
	if (pDriver->data.posIndex >= SPEED_DEV_CNT)
	{
		pDriver->data.posIndex = SPEED_DEV_CNT - 1;
	}
	
	if (MOTOR_DIR_FWD == pDriver->data.curDir) //��ת����
	{
		percent = pDriver->data.speedFwd[pDriver->data.posIndex]; //��ȡ��ǰ�����ٶ�
		if (0 != percent)//�ٶȵ��� , 0Ϊ�˵�Ϊר��ɲ����,������
		{
		    //ɲ�����������̣��ȹ��±�, ��ʱ10us���ϣ����ϱ�����
		    pDriver->pHardware->MotorRevEn(STATE_ON); //��תʹ�ܿ���(���ڵ��ڹ�����ɲ��)
		    f_IoPwmDriverSetPercent(&(pDriver->data.pwmRevOut), 0); //��ת����ر�(�±۹ر�)
		    
		    //��ʱ(��Ҫʵ�ʲ���)
            if (false == pDriver->data.bRunning)
            {
                f_Delay(50);
                pDriver->data.bRunning = true;
            }
            
		    pDriver->pHardware->MotorFwdEn(STATE_ON); //����ʹ�ܴ�(�ϱ۴�)
		    
			percent	+= pDriver->data.fwdOffset; //���ݵ������ƫ����������ٶ�
			if (percent > 100)
			{
				percent = 100;
			}
			else if (percent < 0)
			{
				percent = 0;
			}
			f_IoPwmDriverSetPercent(&(pDriver->data.pwmFwdOut), (uchar)percent); //��ת�ٶȵ���
		}
		else //׼��ɲ��(2������ȫ�ӵأ���2���۴�)
		{
            f_LidMotorBreak(pDriver);
		}
	}
	else if (MOTOR_DIR_REV == pDriver->data.curDir) //��ת����
	{
		percent = pDriver->data.speedRev[pDriver->data.posIndex]; //��ȡ��ǰ�����ٶ�
		if (0 != percent)//�ٶȵ��� , 0Ϊ�˵�Ϊר��ɲ����,������
		{
		    //ɲ�����������̣��ȹ��±�, ��ʱ10us���ϣ����ϱ�����
		    pDriver->pHardware->MotorFwdEn(STATE_ON); //��תʹ�ܿ���(���ڵ��ڹ�����ɲ��)
		    f_IoPwmDriverSetPercent(&(pDriver->data.pwmFwdOut), 0); //��ת����ر�(�±۹ر�)
		    
		    //��ʱ(��Ҫʵ�ʲ���)
            if (false == pDriver->data.bRunning)
            {
                f_Delay(50);
                pDriver->data.bRunning = true;
            }
            
		    pDriver->pHardware->MotorRevEn(STATE_ON); //����ʹ�ܴ�(�ϱ۴�)
		    
			percent	+= pDriver->data.fwdOffset; //���ݵ������ƫ����������ٶ�
			if (percent > 100)
			{
				percent = 100;
			}
			else if (percent < 0)
			{
				percent = 0;
			}
			f_IoPwmDriverSetPercent(&(pDriver->data.pwmRevOut), (uchar)percent); //��ת�ٶȵ���
		}
		else //׼��ɲ��(2������ȫ�ӵأ���2���۴�)
		{
            f_LidMotorBreak(pDriver);
		}
	}
	else//ֹͣ
	{
		pDriver->pHardware->MotorFwdEn(STATE_OFF);
		pDriver->pHardware->MotorRevEn(STATE_OFF);
		f_IoPwmDriverSetPercent(&(pDriver->data.pwmFwdOut), 0);
		f_IoPwmDriverSetPercent(&(pDriver->data.pwmRevOut), 0);
		pDriver->data.bRunning = false;
	}
	
	pDriver->data.lastDir = pDriver->data.curDir;
}

/*****************************************************************************
 �� �� ��: f_LidMotorSetState
 ��������  : ���õ������״̬
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��15��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_LidMotorSetState(LID_MOTOR_DRIVER *pDriver, LID_MOTOR_DIR dir)
{
    if (pDriver->data.curDir != dir)//�л������
    {
        pDriver->data.bRunning = false; //ÿ���л�����Ҫ�ű��л���ʱ
    }
    
    pDriver->data.curDir = dir;

    if (MOTOR_DIR_STOP == dir)//��ǰҪ��ֹͣ,��λ����
    {
        pDriver->data.bReset = false;
    }
    
    return true;
}

/*****************************************************************************
 �� �� ��: f_LidMotorIsOverMid
 ��������  : �Ƿ񳬹��м�����
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��15��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_LidMotorIsOverMid(LID_MOTOR_DRIVER *pDriver)
{
    uint mid = (pDriver->pHardware->maxPos + pDriver->pHardware->minPos)/2;

    if (pDriver->pHardware->bIncrease)//�����Ϸ����
    {
		if (pDriver->data.curAngle > mid)
		{
			return true;
		}
    }
    else
    {
		if (pDriver->data.curAngle < mid)
		{
			return true;
		}
    }
    return false;
}

/*****************************************************************************
 �� �� ��: f_LidMotorReset
 ��������  : �ǰ帴λ
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��13��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_LidMotorReset(LID_MOTOR_DRIVER *pDriver)
{
    //���õ�ǰλ��Ϊ�������λ��
    if (pDriver->pHardware->bIncrease)
    {
        pDriver->data.curAngle = pDriver->pHardware->maxPos;
    }
    else
    {
        pDriver->data.curAngle = pDriver->pHardware->minPos;
    }

    //������λ
    pDriver->data.bReset = true;
}

/*****************************************************************************
 �� �� ��: f_LidMotorChangePos
 ��������  : ���ڻ����źŵĲ���
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: ���ⲿ�жϣ������ź�,�½��ش���
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��13��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_LidMotorChangePos(LID_MOTOR_DRIVER *pDriver, uchar dir)
{
    if (dir) //����
    {
        f_AddU16Data(&(pDriver->data.curAngle));
    }
    else //����
    {
        f_DecU16Data(&(pDriver->data.curAngle));
    }
}


/*****************************************************************************
 �� �� ��: f_LidMotorDriverInit
 ��������  : ���ǵ��������ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��15��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_LidMotorDriverInit(LID_MOTOR_DRIVER *pDriver, 
								  LID_MOTOR_HARDWARE *pHardware,
								  SetOut fwdOut,
								  SetOut revOut, 
								  uint period)
{
    f_Memset(pDriver, 0, sizeof(LID_MOTOR_DRIVER));
    pDriver->pHardware = pHardware;
    f_IoPwmDriverInit(&(pDriver->data.pwmFwdOut), fwdOut, period);
    f_IoPwmDriverInit(&(pDriver->data.pwmRevOut), revOut, period); 
}

