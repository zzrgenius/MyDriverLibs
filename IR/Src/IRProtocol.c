/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : IRProtocol.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��10��
  ����޸�   :
  ��������   : ����Э�鴦��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��10��
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
 �� �� ��: f_IRRevDataDeal
 ��������: ����������ݴ���
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��10��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_IRRevDataDeal(uchar *pData, uchar len)
{
	REMOTER_PROTOCOL revInfo;
	
    if (len != sizeof(REMOTER_PROTOCOL))
    {
		return;
    }

    f_MemCpy(&revInfo, pData, len);

    //====Э�����====
    //������
    functionInfo.keyCode = revInfo.keyCode;
    
    //ˮ��
    if (revInfo.waterLevel != functionInfo.waterTempLevel 
    && revInfo.waterLevel <= FUNC_SET_LEVEL_3)
    {
    	functionInfo.waterTempLevel = revInfo.waterLevel;
    	f_StorageWriteValues(&storageDriver, STORAGE_WATER_LEVEL, true);
    }

	//����
    if (revInfo.seatLevel != functionInfo.seatTempLevel 
    && revInfo.seatLevel <= FUNC_SET_LEVEL_3)
    {
    	functionInfo.seatTempLevel = revInfo.seatLevel;
    	f_StorageWriteValues(&storageDriver, STORAGE_SEAT_LEVEL, true);
    }

	//����
    if (revInfo.dryLevel != functionInfo.dryTempLevel 
    && revInfo.dryLevel <= FUNC_SET_LEVEL_3)
    {
    	functionInfo.dryTempLevel = revInfo.dryLevel;
    	f_StorageWriteValues(&storageDriver, STORAGE_DRY_LEVEL, true);
    }

    //��λ
    revInfo.nozzlePos += 1;//�豸��λL1~L4(ң�ع�λ0~3)
    if (revInfo.nozzlePos != functionInfo.setPos 
    && revInfo.nozzlePos <= FUNC_SET_LEVEL_4)
    {
    	functionInfo.setPos = revInfo.nozzlePos;
    	f_StorageWriteValues(&storageDriver, STORAGE_POS_LEVEL, true);
    }

    //����
    if (revInfo.flowLevel != functionInfo.setFlow 
    && revInfo.flowLevel <= FUNC_SET_LEVEL_3)
    {
    	functionInfo.setFlow = revInfo.flowLevel;
    	f_StorageWriteValues(&storageDriver, STORAGE_FLOW_LEVEL, true);
    }
}


