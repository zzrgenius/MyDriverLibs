/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : FuncFlushDeal.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��9��
  ����޸�   :
  ��������   : ��ˮ��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��9��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "HeadInclude.h"

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
FUNC_FLUSH AT_NEAR funcFlush;

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define VALUE_DELAY_TO_BREAK_TM 2//�����غ󣬹�λɲ��״̬ʱ��,��λ10ms

#define ROUND_FLUSH_TM 10//����ڳ�ˮʱ��,��λ100ms

#define FLUSH_BATTERY_LOW_AD 410//��ص�����,Լ6V
#define FLUSH_BATTERY_LOW_OFFSET 40//��ص�ػز�

#define FLUSH_BOTH_TM 10//��ϴ�ص�ʱ��(����������ۺͻ�ˮ֮���ʱ���ص�),��λ100ms

//====�ײ�Ӳ������====
//��ڷ�����
void f_FuncFlushRoundValve(FLUSH_VALVE_STATE state)
{
	if (FLUSH_VALVE_ON == state)
	{
		ROUND_VALVE_A(true);
		ROUND_VALVE_B(false);
	}
	else if (FLUSH_VALVE_OFF == state)
	{
		ROUND_VALVE_A(false);
		ROUND_VALVE_B(true);
	}
	else if (FLUSH_VALVE_BRAKE == state)
	{
		ROUND_VALVE_A(true);
		ROUND_VALVE_B(true);
	}
}

//�ײ�������
void f_FuncFlushBottomValve(FLUSH_VALVE_STATE state)
{
	if (FLUSH_VALVE_ON == state)
	{
		BOTTOM_VALVE_A(true);
		BOTTOM_VALVE_B(false);
	}
	else if (FLUSH_VALVE_OFF == state)
	{
		BOTTOM_VALVE_A(false);
		BOTTOM_VALVE_B(true);
	}
	else if (FLUSH_VALVE_BRAKE == state)
	{
		BOTTOM_VALVE_A(true);
		BOTTOM_VALVE_B(true);
	}
}

/*****************************************************************************
 �� �� ��: f_FuncFlushValveCtrl
 ��������  : ��ˮ������
 �������:
 �� �� ֵ: 
 ע     ��: 10msʱ��
 
 �޸���ʷ:
  1.��    ��   : 2018��5��10��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncFlushValveCtrl(void)
{
	//��ڷ�
	f_AddU8Data(&funcFlush.roundValve.dealyToBreakTm);
    if (funcFlush.roundValve.bState != funcFlush.roundValve.bLastState)
    {
		funcFlush.roundValve.dealyToBreakTm = 0;
		if (funcFlush.roundValve.bState)
		{
			funcFlush.roundValve.setValve = FLUSH_VALVE_ON;//��
			funcFlush.roundValve.lastSetValve= FLUSH_VALVE_ON;//��
		}
		else
		{
			funcFlush.roundValve.setValve = FLUSH_VALVE_OFF;//��
			funcFlush.roundValve.lastSetValve = FLUSH_VALVE_OFF;//��
		}
    }
    funcFlush.roundValve.bLastState = funcFlush.roundValve.bState;
    if (funcFlush.roundValve.dealyToBreakTm >= VALUE_DELAY_TO_BREAK_TM)
    {
		funcFlush.roundValve.setValve = FLUSH_VALVE_BRAKE;//ɲ��
    }
    f_FuncFlushRoundValve(funcFlush.roundValve.setValve);

    //�ײ���
	f_AddU8Data(&funcFlush.bottomValve.dealyToBreakTm);
    if (funcFlush.bottomValve.bState != funcFlush.bottomValve.bLastState)
    {
		funcFlush.bottomValve.dealyToBreakTm = 0;
		if (funcFlush.bottomValve.bState)
		{
			funcFlush.bottomValve.setValve = FLUSH_VALVE_ON;//��
			funcFlush.bottomValve.lastSetValve = FLUSH_VALVE_ON;//��
		}
		else
		{
			funcFlush.bottomValve.setValve = FLUSH_VALVE_OFF;//��
			funcFlush.bottomValve.lastSetValve = FLUSH_VALVE_OFF;//��
		}
    }
    funcFlush.bottomValve.bLastState = funcFlush.bottomValve.bState;
    if (funcFlush.bottomValve.dealyToBreakTm >= VALUE_DELAY_TO_BREAK_TM)
    {
		funcFlush.bottomValve.setValve = FLUSH_VALVE_BRAKE;//ɲ��
    }
    f_FuncFlushBottomValve(funcFlush.bottomValve.setValve);
}


/*****************************************************************************
 �� �� ��: f_FuncFlushDeal
 ��������: ��ˮ����
 �������: 
 �� �� ֵ: 
 ע     ��: 10ms����
 
 �޸���ʷ:
  1.��    ��   : 2018��5��9��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncFlushDeal(void)
{
    uint minTm;
    
	//�޵������ʱ����ˮ��������
	if (funcFlush.bPowerOff && funcFlush.bLowPower)
	{
		funcFlush.curStep = FLUSH_SREQ_STOP;
	}
	
	f_AddU16Data(&funcFlush.flushTm);
    switch (funcFlush.curStep)
    {
		case FLUSH_SREQ_STOP:
			funcFlush.roundValve.bState = false;//��ڷ��ر�
			funcFlush.bottomValve.bState = false;//�ײ����ر�

			if (FLUSH_VALVE_OFF == funcFlush.roundValve.lastSetValve 
			&& FLUSH_VALVE_BRAKE == funcFlush.roundValve.setValve
			&& FLUSH_VALVE_OFF == funcFlush.bottomValve.lastSetValve 
			&& FLUSH_VALVE_BRAKE == funcFlush.bottomValve.setValve)//�����л�ɲ��(�ӹ��е�ɲ��)
			{
				//�رյ�Դ
				MAIN_POWER_LOCK(false);
				VALE_POWER_LOCK(false);
			}
			break;
			
		case FLUSH_SREQ_START:
			funcFlush.flushTm = 0;
			funcFlush.curStep = FLUSH_SREQ_ROUND_1;

			//�򿪵�Դ
			MAIN_POWER_LOCK(true);
			VALE_POWER_LOCK(true);
			break;
			
		case FLUSH_SREQ_ROUND_1:
			if (funcFlush.flushTm >= funcFlush.setRound_1_Tm)
			{
				funcFlush.flushTm = 0;
				funcFlush.curStep = FLUSH_SREQ_BOTTOM;
			}
			else
			{
				funcFlush.roundValve.bState = true;
				funcFlush.bottomValve.bState = false;
			}
			break;

		case FLUSH_SREQ_BOTTOM:
			if (funcFlush.flushTm >= funcFlush.setBottomTm)
			{
				funcFlush.flushTm = 0;
				funcFlush.curStep = FLUSH_SREQ_ROUND_2;

                if (0 != funcFlush.setBottomTm)
                {
                    minTm = funcFlush.setBottomTm < FLUSH_BOTH_TM?funcFlush.setBottomTm:FLUSH_BOTH_TM;  
                    //��һ�����̼�ȥ�ص�ʱ��
    				if (funcFlush.setRound_2_Tm <= minTm)
    				{
                        funcFlush.setRound_2_Tm = 0;
    				}
    				else
    				{
                        funcFlush.setRound_2_Tm -= minTm; 
    				}
				}
			}
			else
			{
				funcFlush.bottomValve.bState = true;
				funcFlush.roundValve.bState = false;

				if (funcFlush.setBottomTm - funcFlush.flushTm <= FLUSH_BOTH_TM) //�ص�ʱ��
				{
				    if (funcFlush.setBottomTm - funcFlush.flushTm <= funcFlush.setRound_2_Tm)
				    {
                        funcFlush.roundValve.bState = true;
                    }
				}
			}
			break;

		case FLUSH_SREQ_ROUND_2:
			if (funcFlush.flushTm >= funcFlush.setRound_2_Tm)
			{
				funcFlush.flushTm = 0; 
				funcFlush.curStep = FLUSH_SREQ_STOP;
			}
			else
			{
				funcFlush.roundValve.bState = true;
				funcFlush.bottomValve.bState = false;
			}
			break;
			
		default:
			funcFlush.curStep = FLUSH_SREQ_STOP;
			break;
	
    }
}

/*****************************************************************************
 �� �� ��: f_FuncSetFlushMode
 ��������  : ���ó�ˮģʽ����Ӧ������ˮʱ��
 �������: cmd ��ˮ����
 �� �� ֵ: true������ˮ;false:����ʧ��
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��10��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_FuncSetFlushMode(FUNC_FLUSH_CMD cmd)
{
	//�޵������ʱ���޷�������ˮ
	if (funcFlush.bPowerOff && funcFlush.bLowPower)
	{
		return false;
	}

	//���������
    if (FLUSH_CMD_NULL == cmd)//ֹͣ
    {
		if (funcFlush.curStep != FLUSH_SREQ_STOP)
		{
			funcFlush.curStep = FLUSH_SREQ_STOP;
			return true;
		}
    }
    else if (FLUSH_CMD_ROUND == cmd)//��������ڳ�ˮ
    {
		if (funcFlush.curStep == FLUSH_SREQ_STOP)//��ǰ�޳�ˮ
		{
			funcFlush.curStep = FLUSH_SREQ_START;
			funcFlush.setRound_1_Tm = 0;
			funcFlush.setBottomTm = 0;
			funcFlush.setRound_2_Tm = ROUND_FLUSH_TM;
			return true;
		}
    }
    else if (FLUSH_CMD_NORMAL == cmd)//���������+�ײ�+��ڳ�ˮ
    {
		if (funcFlush.curStep == FLUSH_SREQ_STOP)//��ǰ�޳�ˮ
		{
			funcFlush.curStep = FLUSH_SREQ_START;
			funcFlush.setRound_1_Tm = funcFlush.saveFlushtm[FLUSH_ADJUST_WASH];
			funcFlush.setBottomTm = funcFlush.saveFlushtm[FLUSH_ADJUST_CLEAN];
            funcFlush.setRound_2_Tm = funcFlush.saveFlushtm[FLUSH_ADJUST_BACK];
			return true;
		}
    }
    return false;
}

/*****************************************************************************
 �� �� ��: f_FuncSetFlushTm
 ��������  : ͨ������ʱ��������Ƴ�ˮ(��f_FuncSetFlushMode�������)
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: �̶�ʱ����ã����ܵ���Ӱ��
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��18��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_FuncSetFlushTm(uint tm_wash, uint tm_clean, uint tm_back)
{
    //�޵������ʱ���޷�������ˮ
	if (funcFlush.bPowerOff && funcFlush.bLowPower)
	{
		return false;
	}

	if (funcFlush.curStep == FLUSH_SREQ_STOP)//��ǰ�޳�ˮ
	{
		funcFlush.curStep = FLUSH_SREQ_START;
		funcFlush.setRound_1_Tm = tm_wash;
		funcFlush.setBottomTm = tm_clean;
		funcFlush.setRound_2_Tm = tm_back;
		return true;
	}
	return false;
}

/*****************************************************************************
 �� �� ��: f_FuncFlushPowerCheck
 ��������  : ��ˮ��Դ���,������������޵��ˮ�͵���ʱ��������ˮ
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��10��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncFlushPowerCheck(void)
{
    if (POWER_CUT_CHECK)
    {
    	if (false == funcFlush.bPowerOff)
    	{
			f_Delay(10); //ȥ��
			if (POWER_CUT_CHECK)
			{
				funcFlush.bPowerOff = true;	
			}
		}
    }
    else 
    {
		funcFlush.bPowerOff = false;	
    }
}

/*****************************************************************************
 �� �� ��: f_FuncFlushBatteryCheck
 ��������  : ��ˮ��ص��
 �������:
 �� �� ֵ: 
 ע     ��: 100ms����
 
 �޸���ʷ:
  1.��    ��   : 2018��5��10��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncFlushBatteryCheck(void)
{
	funcFlush.batteryAD = f_MCU_GetAD(BATTERY_LOW_CHECK_CHANNEL);

    //�ж�
    if (funcFlush.batteryAD <= FLUSH_BATTERY_LOW_AD)
    {
		f_AddU8Data(&funcFlush.batteryOffCnt);
		funcFlush.batteryOnCnt = 0;

		if (funcFlush.batteryOffCnt >= 4)
		{
			funcFlush.bLowPower = true;
		}
    }
    else if (funcFlush.batteryAD >= FLUSH_BATTERY_LOW_AD + FLUSH_BATTERY_LOW_OFFSET)
    {
		f_AddU8Data(&funcFlush.batteryOnCnt);
		funcFlush.batteryOffCnt = 0;

		if (funcFlush.batteryOnCnt >= 4)
		{
			funcFlush.bLowPower = false;
		}
    }
}

/*****************************************************************************
 �� �� ��: f_FuncFlushInit
 ��������  : ��ˮ���ܳ�ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��10��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncFlushInit(void)
{
    f_Memset(&funcFlush, 0, sizeof(FUNC_FLUSH));

	//====2�����ϵ�󣬹ر�һ��====
	//�򿪵�Դ
	MAIN_POWER_LOCK(true);
	VALE_POWER_LOCK(true);
	funcFlush.roundValve.bLastState = true;
	funcFlush.bottomValve.bLastState = true;
	funcFlush.roundValve.setValve = FLUSH_VALVE_OFF;
	funcFlush.bottomValve.setValve = FLUSH_VALVE_OFF;
}

