/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : SPIDriver.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��21��
  ����޸�   :
  ��������   : SIP��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��21��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "SPIDriver.h"
#include "SubFunction.h"
#include "IO_Define.h"

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
#define SPI_DL_TM 0

/*****************************************************************************
 �� �� ��: void f_SPIWriteData(uint sendData, uchar length)
 ��������  : SPI����д����
 �������:
 �� �� ֵ: sendData:��������;length������λ��
 ע     ��: ���2�ֽ�
 
 �޸���ʷ:
  1.��    ��   : 2018��4��21��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_SPIWriteData(SPI_DRIVER *pDriver, uint sendData, uchar length)
{
	schar i;

	for (i = length - 1; i >= 0; i--)
	{
	    #if defined(MODE0) //�½���д
		    pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE1) //������д
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE2) //������д
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE3) //�½���д
		    pDriver->pHardware->ClockOut(STATE_ON);
		#endif
		
		if ((sendData>>i)&(0x0001))//���͸�λ
		{
			pDriver->pHardware->DataOut(STATE_ON);
		}
		else
		{
			pDriver->pHardware->DataOut(STATE_OFF);
		}
		#if (SPI_DL_TM > 0)
			pDriver->pHardware->Delay();
		#endif
		#if defined(MODE0) 
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE1)
		    pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE2)
		    pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE3)
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#endif
		#if (SPI_DL_TM > 0)
			pDriver->pHardware->Delay();
		#endif
	}
}

/*****************************************************************************
 �� �� ��: uint f_SPIReadData(uchar length)
 ��������  : ��SPI�����϶�ȡһ���ֽ�
 �������: length ����λ����
 �� �� ֵ: ��ȡ����
 ע     ��: ���2�ֽ�
 
 �޸���ʷ:
  1.��    ��   : 2018��4��21��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uint f_SPIReadData(SPI_DRIVER *pDriver, uchar length)
{
    uint getData = 0;
    uchar i;

    for (i = 0; i < length; i++)
    {
		#if defined(MODE0) //�����ض�
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE1) //�½��ض�
		    pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE2) //�½��ض�
		    pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE3) //�����ض�
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#endif
		
		#if (SPI_DL_TM > 0)
			pDriver->pHardware->Delay();
		#endif
		
		getData <<= 1;
		if (pDriver->pHardware->DataIn())
		{
			getData |= 0x0001;
		}
		
        #if defined(MODE0)
            pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE1)
            pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE2)
            pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE3)
            pDriver->pHardware->ClockOut(STATE_ON);
		#endif

    }
    return getData;
}

/*****************************************************************************
 �� �� ��: f_SPIEnChip
 ��������  : SPIʹ��ѡ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��23��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_SPIEnChip(SPI_DRIVER *pDriver, STATE_INFO state)
{
    pDriver->pHardware->EnChip(state);
}

/*****************************************************************************
 �� �� ��: f_SPIDriverInit
 ��������  : SPI������ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��23��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_SPIDriverInit(SPI_DRIVER *pDriver, const SPI_HARDWARE_DRIVER *pHardware)
{
    f_Memset(pDriver, 0, sizeof(SPI_DRIVER));
    pDriver->pHardware = pHardware;
}

