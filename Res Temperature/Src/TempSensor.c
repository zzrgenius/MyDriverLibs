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
uchar tempFilterCnt;

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/
#define AD_BASE_TEMP -10
//0λ�� ��·ֵ;maxλ�ÿ�·ֵ
const uint Tab_NTC_5KF3470[]=
{
	100,//��������·ֵ
	750, 778, 806, 834, 864, 894, 924, 955, 986, 1018, //-10~-1
	1050, 1083, 1116, 1150, 1184, 1218, 1254, 1290, 1326, 1363, //0~9
	1401, 1438, 1476, 1515, 1553, 1592, 1631, 1670, 1709, 1749, //10~19
	1788, 1828, 1867, 1906, 1946, 1985, 2024, 2063, 2101, 2140, //20~29
	2178, 2216, 2254, 2291, 2328, 2364, 2401, 2436, 2472, 2507, //30~39
	2541, 2575, 2609, 2641, 2674, 2706, 2737, 2768, 2799, 2829, //40~49
	2858, 2887, 2915, 2942, 2969, 2995, 3022, 3047, 3072, 3096, //50~59
	3120,//60
	3900//��������·ֵ
};

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
uint f_GetTemperatureIndex(uint getAD, const uint *pTable, uint size, uint degree)
{
	uint startIndex = 0;
	uint endIndex = size - 1;
	uchar upIndexFlag ;
	uint middle;
	uint findAD;
	int offset;
	uint index;

	if (pTable[0] < pTable[size -1])
	{
		//����
		upIndexFlag = true;
	}
	else
	{
		//����
		upIndexFlag = 0;
	}

	if ((upIndexFlag && getAD >= pTable[endIndex])
	|| (false == upIndexFlag && getAD <= pTable[endIndex])) //��������¶�
	{
        index = endIndex*degree;
	}
	else if ((upIndexFlag && getAD <= pTable[startIndex])
	|| (false == upIndexFlag && getAD >= pTable[startIndex])) //������С�¶�
	{
        index = startIndex*degree;
	}
	else //����
	{
    	while (startIndex <= endIndex)
    	{
    		middle = (startIndex + endIndex)/2;

    		if (getAD == pTable[middle])
    		{
    			break;
    		}
    		else if (getAD < pTable[middle])
    		{
    			if (true == upIndexFlag)
    			{
    				endIndex = middle -1;
    			}
    			else
    			{
    				startIndex = middle + 1;
    			}
    		}
    		else
    		{
    			if (true == upIndexFlag)
    			{
    				startIndex = middle + 1;
    			}
    			else
    			{
    				endIndex = middle -1;
    			}
    		}
    	}

    	//�¶��������봦��
        findAD = pTable[middle];
    	index = middle*degree;
    	if (true == upIndexFlag) //����
    	{
    	    if (findAD > getAD)
    	    {
                offset = findAD - getAD;//�ҵ�����ƫ���λ��
                index -= offset/((pTable[middle] - pTable[middle - 1])/(degree+1) + 1); // ���+1��ֹ��������
    	    }
    	    else
    	    {
                offset = getAD - findAD;//�ҵ�����ƫС��λ��
                index += offset/((pTable[middle + 1] - pTable[middle])/(degree+1) + 1); // ���+1��ֹ��������
    	    }   
    	}
    	else //����
    	{
    	    if (findAD > getAD)
    	    {
                offset = findAD - getAD;//�ҵ�����ƫС��λ��
                index += offset/((pTable[middle] - pTable[middle + 1])/(degree+1) + 1); // ���+1��ֹ��������
    	    }
    	    else
    	    {
                offset = getAD - findAD;//�ҵ�����ƫ���λ��
                index -= offset/((pTable[middle - 1] - pTable[middle])/(degree+1) + 1); // ���+1��ֹ��������
    	    } 
    	}
	}

	return index;
}
 
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
	uint index;
	sint temperature;
	
    adValue = f_GetSensorAD(pDriver, pDriver->pHardware->channel);

    if ((pDriver->pHardware->isUp && adValue >= pDriver->pHardware->pTab_NTC[0])
    || (!pDriver->pHardware->isUp && adValue <= pDriver->pHardware->pTab_NTC[0]))//��·
    {
		pDriver->sensorInf.bShortFlag = false;
		pDriver->sensorInf.bOpenFlag = true;
    }
    else if ((pDriver->pHardware->isUp && adValue <= pDriver->pHardware->pTab_NTC[pDriver->pHardware->size - 1])
    || (!pDriver->pHardware->isUp && adValue >= pDriver->pHardware->pTab_NTC[pDriver->pHardware->size - 1]))//��·
    {
		pDriver->sensorInf.bShortFlag = true;
		pDriver->sensorInf.bOpenFlag = false;
    }
    else
    {
		pDriver->sensorInf.bShortFlag = false;
		pDriver->sensorInf.bOpenFlag = false;
		
	    //����ADֵ���,��ȡ�¶�
	    index = f_GetTemperatureIndex(adValue, &pDriver->pHardware->pTab_NTC[1], pDriver->pHardware->size - 2, pDriver->pHardware->degree);
	    temperature = (sint)index + pDriver->pHardware->baseTemp;

	    if (pDriver->sensorInf.lastSensorTemp == temperature)
	    {
	    	pDriver->filterCnt ++;
	    	if (pDriver->filterCnt >= pDriver->pHardware->needFilterCnt)
	    	{
	    		pDriver->filterCnt = pDriver->pHardware->needFilterCnt;
				pDriver->sensorInf.sensorTemp = temperature;
			}
	    }
	    else 
	    {
			pDriver->filterCnt = 0;
	    }
	    pDriver->sensorInf.lastSensorTemp = temperature;
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

