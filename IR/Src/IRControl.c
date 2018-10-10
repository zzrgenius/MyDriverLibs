/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : IRControl.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��24��
  ����޸�   :
  ��������   : ���ⷢ�ͽ��մ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��24��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "IRControl.h"
#include "IRConfig.h"
#include "IO_Define.h"
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
IR_CONTROL_DRIVER irControlDriver;


/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/

/*****************************************************************************
 �� �� ��: f_IR_ReadLevel
 ��������  : ��ȡ��ƽʱ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��10��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_IR_ReadLevel(void)
{
    uchar ioState = IO_IR_IN;

    //��ʱ��ȡ(�½���)
//       irControlDriver.bLastRevLevelState != ioState
//    && false == ioState
    
    if (irControlDriver.revPeriodTmBuf >= IR_MAX_PERIOD_TM)//���ڳ���(�ж��ж��½���)
    {
		irControlDriver.bRevOneBitOVer = true;
		irControlDriver.revLowTm = irControlDriver.revLowTmBuf;
		irControlDriver.revPeriodTm = irControlDriver.revPeriodTmBuf;
		irControlDriver.revLowTmBuf = 0;
		irControlDriver.revPeriodTmBuf = 0;
    }

	//�ۻ����ں͵͵�ƽʱ��
	f_AddU16Data(&irControlDriver.revPeriodTmBuf); //����
    if (ioState == false)
    {
		f_AddU16Data(&irControlDriver.revLowTmBuf);
    }
    
    irControlDriver.bLastRevLevelState = ioState;
}

/*****************************************************************************
 �� �� ��: f_IR_ReadBit
 ��������  : �Ӻ����һ�����ڵ�ƽ
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��24��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
IR_READ_BIT_INFO f_IR_ReadBit(uint lowTm, uint periodTm)
{
	//�����ж� �͵�ƽ+����
	if (f_CalcU16Err(lowTm, IR_HEAD_LOW_TM) <= IR_READ_LOW_RANGE)//ͷ��͵�ƽ�ж�
	{
		if (f_CalcU16Err(periodTm, IR_HEAD_PERIOD_TM) <= IR_READ_PERIOD_RANGE)
		{
			return IR_READ_HEAD; //ͷ��
		}
	}
	else if (f_CalcU16Err(lowTm, IR_DATA_0_LOW_TM) <= IR_READ_LOW_RANGE)//��������
	{
		if (f_CalcU16Err(periodTm, IR_DATA_0_PERIOD_TM) <= IR_READ_PERIOD_RANGE)
		{
			return IR_READ_BIT_0; //����λ0
		}
		else if (f_CalcU16Err(periodTm, IR_DATA_1_PERIOD_TM) <= IR_READ_PERIOD_RANGE)
		{
			return IR_READ_BIT_1; //����λ1
		}
	}
	else if (f_CalcU16Err(lowTm, IR_END_LOW_TM) <= IR_READ_LOW_RANGE)//β��͵�ƽ�ж�
	{
		if (f_CalcU16Err(periodTm, IR_MAX_PERIOD_TM) <= IR_READ_PERIOD_RANGE) //β��ֻ�е͵�ƽ,��������ڽ���
		{
			return IR_READ_END; //β��
		}
	}

	return IR_READ_NULL;
}

/*****************************************************************************
 �� �� ��: f_IR_ReadByte
 ��������  : �Ӻ����ȡһ���ֽ�����
 �������:
 �� �� ֵ: true:����ֽڶ�ȡ;false���ڶ�ȡ
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��24��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_IR_ReadByte(uchar *pBuf, IR_READ_BIT_INFO revBit)
{
    if(IR_READ_BIT_0 == revBit || IR_READ_BIT_1 == revBit)
    {
    	irControlDriver.revBitPos ++;
    	(*pBuf) <<= 1;
		if (IR_READ_BIT_1 == revBit)
		{
			*pBuf |= 0x01;
		}
		
		if (irControlDriver.revBitPos >= 8)
		{
			irControlDriver.revBitPos = 0;
			return true;
		}
    }
    else
    {
		irControlDriver.revBitPos = 0;
    }
    return false;
}

/*****************************************************************************
 �� �� ��: f_IR_SendOneBit
 ��������  : ���ⷢ��һ��λ
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_IR_SendOneBit(uchar data)
{
	if (data)//����1
	{
		irControlDriver.setLowTm = IR_DATA_1_LOW_TM;
		irControlDriver.setPeriodTm = IR_DATA_1_PERIOD_TM;
	}
	else//����0
	{
		irControlDriver.setLowTm = IR_DATA_0_LOW_TM;
		irControlDriver.setPeriodTm = IR_DATA_0_PERIOD_TM;
	}
	irControlDriver.sendTm = 0;
	irControlDriver.bSendOneBitOver = false;
}

/*****************************************************************************
 �� �� ��: f_IR_SendByte
 ��������  : ����һ�ֽ�����
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_IR_SendByte(uchar data)
{
    if (false == irControlDriver.bSendOneByteOver)
    {
		if (irControlDriver.bSendOneBitOver)//��ǰλ�������
		{
			if (irControlDriver.sendBitPos >= 8)//��ǰ�ֽڷ������
			{
				irControlDriver.sendBitPos = 0;
				irControlDriver.bSendOneByteOver = true;
			}
			else 
			{
				f_IR_SendOneBit((data << irControlDriver.sendBitPos) & 0x80);//��λ����
				irControlDriver.sendBitPos ++;
			}
		}
    }
}

/*****************************************************************************
 �� �� ��: f_IR_SendLevel
 ��������  : ���͵�ƽ����
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_IR_SendLevel(void)
{
	if (false == irControlDriver.bSendOneBitOver)
	{
		f_AddU16Data(&(irControlDriver.sendTm));
	    if (irControlDriver.sendTm >= irControlDriver.setPeriodTm)
	    {
	    	//һ���������ڽ���
	    	IO_IR_OUT(true);
			irControlDriver.bSendOneBitOver = true;
	    }
	    else
	    {
		    if (irControlDriver.sendTm <= irControlDriver.setLowTm)
		    {
				IO_IR_OUT(false);		
		    }
		    else
		    {
				IO_IR_OUT(true);
		    }
	    }
    }
}


/*****************************************************************************
 �� �� ��: f_IR_ControlDeal
 ��������: ������մ���
 �������:
 �� �� ֵ: 
 ע     ��: 100us����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��24��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_IR_ControlDeal(void)
{
	IR_READ_BIT_INFO getBitInfo;

	f_IR_ReadLevel(); //��ȡ��ƽ
	if (irControlDriver.bRevOneBitOVer && irControlDriver.bNeedDeal == false)//���մ�����ɺ�ż�����
	{
		irControlDriver.bRevOneBitOVer = false;
		getBitInfo = f_IR_ReadBit(irControlDriver.revLowTm, irControlDriver.revPeriodTm);

		//ͷ��ǿ�����¶�ȡ����
		if (IR_READ_HEAD == getBitInfo)
		{
			irControlDriver.revStep = IR_STEP_HEAD;
		}
		
		//���մ���
		switch(irControlDriver.revStep)
		{
			case IR_STEP_HEAD:
				if (IR_READ_HEAD == getBitInfo)
				{
					irControlDriver.revStep = IR_STEP_DATA;
					irControlDriver.revByteCnt = 0;
					irControlDriver.revBitPos = 0;
					f_Memset(irControlDriver.revBuf, 0, sizeof(irControlDriver.revBuf));
				}
				break;

			case IR_STEP_DATA:
				if(f_IR_ReadByte(&irControlDriver.revBuf[irControlDriver.revByteCnt], getBitInfo))
				{
					if (irControlDriver.revByteCnt < IR_REV_BUF_NUM)
					{
						irControlDriver.revByteCnt++;
					}
					else
					{
						irControlDriver.revStep = IR_STEP_HEAD;
					}
				}

				if (IR_READ_NULL == getBitInfo)
				{
					irControlDriver.revNULLCnt++; //һ����е�ʱ�����մ���,�����ۻ����ʾ���ս���
				}
				else
				{
					irControlDriver.revNULLCnt = 0;
				}

				//���մ�������յ�β���ʾһ֡����
				if (irControlDriver.revNULLCnt >= 2 || IR_READ_END == getBitInfo)
				{
					irControlDriver.bNeedDeal = true;
					irControlDriver.revStep = IR_STEP_HEAD;
					irControlDriver.revNULLCnt = 0;
				}
				break;

			default:
				irControlDriver.revStep = IR_STEP_HEAD;
				break;
		}
	}

	//���ʹ���
	switch(irControlDriver.sendStep)
	{
		case IR_STEP_IDLE:
			irControlDriver.sendBitPos = 0;
			irControlDriver.sendByteCnt = 0;
			irControlDriver.bSendOneByteOver = false;
			irControlDriver.bSendOneBitOver = true;
			irControlDriver.bSendSpecialCode = false;
			irControlDriver.sendTm = 0;
			break;
			
		case IR_STEP_HEAD:
			if (!irControlDriver.bSendSpecialCode)
			{
				irControlDriver.bSendSpecialCode = true;
				irControlDriver.bSendOneBitOver = false;
				irControlDriver.setLowTm = IR_HEAD_LOW_TM;
				irControlDriver.setPeriodTm = IR_HEAD_PERIOD_TM;
				irControlDriver.sendTm = 0;
			}
			if (irControlDriver.bSendOneBitOver)
			{
				irControlDriver.sendStep = IR_STEP_DATA;
			}
			break;

		case IR_STEP_DATA:
			f_IR_SendByte(irControlDriver.sendBuf[irControlDriver.sendByteCnt]);

			if (irControlDriver.bSendOneByteOver)//��ǰ�ֽڷ������
			{
				irControlDriver.bSendOneByteOver = false;
				irControlDriver.sendByteCnt ++;
				if (irControlDriver.sendByteCnt >= irControlDriver.needSendByte)
				{
					irControlDriver.bSendSpecialCode = false;
					irControlDriver.sendStep = IR_STEP_END;
				}
			}
			break;

		case IR_STEP_END://����β��
			if (!irControlDriver.bSendSpecialCode)
			{
				irControlDriver.bSendSpecialCode = true;
				irControlDriver.bSendOneBitOver = false;
				irControlDriver.setLowTm = IR_END_LOW_TM;
				irControlDriver.setPeriodTm = IR_END_PERIOD_TM;
				irControlDriver.sendTm = 0;
			}
			if (irControlDriver.bSendOneBitOver)
			{
				irControlDriver.sendStep = IR_STEP_IDLE;
			}
			break;
			
	}
	f_IR_SendLevel();
}
/*****************************************************************************
 �� �� ��: f_IR_StartSend
 ��������  : ��������
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_IR_StartSend(uchar *pBuf, uchar len)
{
    if (IR_STEP_IDLE == irControlDriver.sendStep)
    {

		//��ȡ����
		f_MemCpy(irControlDriver.sendBuf, pBuf, len);
		irControlDriver.needSendByte = len;
		
		//��ʼ����
		irControlDriver.sendStep = IR_STEP_HEAD;
    }
}

/*****************************************************************************
 �� �� ��: f_IRControlInit
 ��������  : �����շ���ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��29��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_IRControlInit(void)
{
    IO_IR_OUT(true);
    f_Memset(&irControlDriver, 0, sizeof(IR_CONTROL_DRIVER));
    irControlDriver.sendStep = IR_STEP_IDLE;
    irControlDriver.revStep = IR_STEP_HEAD;
    irControlDriver.bLastRevLevelState = true; //Ĭ���ϴ��յ��ߵ�ƽ
}

