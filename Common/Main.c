/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : main.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��23��
  ����޸�   :
  ��������   : ��άXWT318���ذ���򣬺����¡���ɼ���;��������˵������;��ϴ���̿���;ˮ�¼��ȿ��Ƶ�
  �����б�   :
              
  �޸���ʷ   :
  1.��    ��   : 2018��4��23��
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
void f_SysTimeCalc(void);

/*----------------------------------------------*
 * ȫ�ֱ���                                         *
 *----------------------------------------------*/
SYS_TIME_FLAG sysTimeFlag;
SYSTEM_INFO systemInfo;

typedef union
{
	struct
	{
		uint bTask_1:1;
		uint bTask_2:1;
		uint bTask_3:1;
		uint bTask_4:1;
		uint bTask_5:1;
		uint bTask_6:1;
		uint bTask_7:1;
		uint bTask_8:1;
		uint bTask_9:1;
		uint bTask_10:1;
		uint rev:6;
	}m_bits;
	uint m_bytes;
}TAST_BALANCE; //����������
TAST_BALANCE balance100Ms; // ����������,��������÷�Ƭ
uchar balance100msCnt;

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
 
void main(void)
{
	f_Delay(3000);//�ϵ��ȵ�ƽ�ȶ�
	_DI();
	f_MCU_Init();
	f_FunctionInit();
	_EI();
	
	while (1)
	{
		f_MCU_FeedDog();//ι��

		//1ms���ܴ���
		if (f_IsSysTime1Ms())
		{
			f_ClrSysTime1Ms();
		}
		
		//10ms���ܴ���
		if (f_IsSysTime10Ms())
		{
			f_ClrSysTime10Ms();
			f_SysTimeCalc();//����ʱ��Ƭ

			balance100Ms.m_bytes |= (0x0001 << balance100msCnt);
			balance100msCnt++;
			if (balance100msCnt >= 10)
			{
				balance100msCnt = 0;
			}
		}

		//50ms
		if (f_IsSysTime50Ms())
		{
			f_ClrSysTime50Ms();
		}

		//100ms-��ʱ����ڴˣ���ɾ��
		if (f_IsSysTime100Ms())
		{
			f_ClrSysTime100Ms();
		}


		//100ms��������ƽƬ
		if (balance100Ms.m_bytes)
		{
			if (balance100Ms.m_bits.bTask_1)
			{
			}
			else if (balance100Ms.m_bits.bTask_2)
			{
				
			}
			else if (balance100Ms.m_bits.bTask_3)
			{
			}
			else if (balance100Ms.m_bits.bTask_4)
			{
				
			}
			else if (balance100Ms.m_bits.bTask_5)
			{
				
			}
			else if (balance100Ms.m_bits.bTask_6)
			{
				
			}
			else if (balance100Ms.m_bits.bTask_7)
			{
			}
			else if (balance100Ms.m_bits.bTask_8)
			{

			}
			else if (balance100Ms.m_bits.bTask_9)
			{
			}
			else if (balance100Ms.m_bits.bTask_10)
			{
			}
			
			balance100Ms.m_bytes = 0;
		}

		//500ms
		if (f_IsSysTime500Ms())
		{
			f_ClrSysTime500Ms();
		}

		//1S
		if (f_IsSysTime1s())
		{
			f_ClrSysTime1S();
			f_AddU8Data(&(systemInfo.powerOnTm));
		}
	}
}

/*****************************************************************************
 �� �� ��: f_SysTimeCalc
 ��������  : ϵͳʱ�����
 �������:
 �� �� ֵ: 
 ע     ��: 10ms����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��21��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_SysTimeCalc(void)
{
	if (sysTimeFlag.time10MsCnt % 10 == 0)
	{
		sysTimeFlag.longTimeFlag.bits.bSys100MsFlag = true;
	}

	if (sysTimeFlag.time10MsCnt % 20 == 0)
	{
		sysTimeFlag.longTimeFlag.bits.bSys200MsFlag = true;
	}

	if (++sysTimeFlag.time10MsCnt >= 20)
	{
		sysTimeFlag.time10MsCnt = 0;
	}

	if (f_IsSysTime100Ms())
	{
		if (sysTimeFlag.time100MsCnt % 5 == 0)
		{
			sysTimeFlag.longTimeFlag.bits.bSys500MsFlag = true;
		}

		if (sysTimeFlag.time100MsCnt % 10 == 0)
		{
			sysTimeFlag.longTimeFlag.bits.bSys1SFlag = true;
		}

		if (++sysTimeFlag.time100MsCnt >= 10)
		{
			sysTimeFlag.time100MsCnt = 0;
		}
	}

	if (f_IsSysTime1s())
	{
		if (sysTimeFlag.time1SCnt % 60 == 0)
		{
			sysTimeFlag.longTimeFlag.bits.bSys1MinFlag = true;
		}

		if (++sysTimeFlag.time1SCnt >= 60)
		{
			sysTimeFlag.time1SCnt = 0;
		}
	}
}
