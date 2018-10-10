/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : TempSensor.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��23��
  ����޸�   :
  ��������   : �¶ȴ�������ش���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��23��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "TempSensor.h"
#include "MCU_Hardware.h"
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

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/

/*****************************************************************************
 �� �� ��: f_GetSensorAD
 ��������  : ��ȡ������AD,ȥͷβȡƽ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��23��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uint f_GetSensorAD(TEMP_SENSOR_DRIVER *pDriver, uchar channel)
{
	return pDriver->pHardware->getAD(channel);
}

/*****************************************************************************
 �� �� ��: f_GetSensorTemp
 ��������  : ��ȡ�������¶�
 �������: 
 �� �� ֵ: 
 ע     ��: 100ms����һ��
 
 �޸���ʷ:
  1.��    ��   : 2018��4��23��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_GetSensorTemp(TEMP_SENSOR_DRIVER *pDriver)
{
	uint adValue;
	sint temperature;
	slong volt;
	
    adValue = f_GetSensorAD(pDriver, pDriver->pHardware->channel);

    if ((pDriver->pHardware->isUp && adValue >= pDriver->pHardware->openAD)
    || (!pDriver->pHardware->isUp && adValue <= pDriver->pHardware->openAD))//��·
    {
		pDriver->sensorInf.bShortFlag = false;
		pDriver->sensorInf.bOpenFlag = true;
    }
    else if ((pDriver->pHardware->isUp && adValue <= pDriver->pHardware->shortAD)
    || (!pDriver->pHardware->isUp && adValue >= pDriver->pHardware->shortAD))//��·
    {
		pDriver->sensorInf.bShortFlag = true;
		pDriver->sensorInf.bOpenFlag = false;
    }
    else
    {
		pDriver->sensorInf.bShortFlag = false;
		pDriver->sensorInf.bOpenFlag = false;

		//5*AD/1024 10bitAD ��ѹ����Ŵ�1000�� �����ѹ����5V ������Ҫ�޸ģ�Ŀǰ�ȹ̶���������������Ҫ�����Ƶ�Ӳ����
        volt = 5000*(slong)(adValue)>>12; 
	    temperature = pDriver->pHardware->getTempResult(volt, pDriver->pHardware->degree);

        pDriver->sensorInf.sensorTemp = f_RecurrenceAverageFilter(temperature, pDriver->filterWind, MAX_FILTER_WIND_CNT); //�˲�����
	    pDriver->sensorInf.realSensorTemp = temperature;
    }
}

/*****************************************************************************
 �� �� ��: f_TempSensorInit
 ��������  : �¶ȴ�����������ʼ��
 �������: pDriver:����ָ��
           pHardware:�ײ�Ӳ��ָ��
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��7��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_TempSensorInit(TEMP_SENSOR_DRIVER *pDriver, const TEMP_SENSOR_HARDWARE *pHardware)
{
    f_Memset(pDriver, 0, sizeof(TEMP_SENSOR_DRIVER));
	pDriver->pHardware = pHardware;
}

