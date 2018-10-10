/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : StorageDriver.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��9��
  ����޸�   :
  ��������   : ���ݴ洢���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��9��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "StorageDriver.h"
#include "SubFunction.h"
#include "StorageConfig.h"
#include "FlashToEEPROM.h"

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
STORAGE_DRIVER storageDriver;

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/
#define STORAGE_HEAD_SIZE sizeof(storageInitFlag)
const char storageInitFlag[] = "XDD_V2"; //�洢�����汾�ţ�ÿ�޸Ĵ洢�����������޸�һ�°汾�ţ��������³�ʼ������

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define CHANGE_BLOCK_ERROR_CNT 20//�ۻ�дʧ�ܴ�����������
#define MAX_WRITE_TIMES 450000//оƬ��д����*1.5
#define BLOCK_RAMGE 1024

#define STORAGE_USE_FLASH //�Ƿ���Ҫ��flash�洢

/*****************************************************************************
 �� �� ��: f_StorageGetVersion
 ��������  : ��ȡ�汾�洢��Ϣ
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��29��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_StorageGetVersion(const uchar **pData, uchar *pSize)
{
    *pData = (const uchar *)storageInitFlag;
    *pSize = sizeof(storageInitFlag);
}


/*****************************************************************************
 �� �� ��: f_StorageJudgeBlock
 ��������: �жϵ�ǰ�洢�����Ƿ��ʺϴ洢������洢����������洢
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��9��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_StorageJudgeBlock(STORAGE_DRIVER *PDriver)
{
    int valueOffset;
    int i;

    PDriver->data.blockWriteCnt ++;

    //������д�������߷���д�������̫���򻻷���
    if (PDriver->data.blockWriteCnt >= MAX_WRITE_TIMES || PDriver->data.writeErrCnt > CHANGE_BLOCK_ERROR_CNT)
    {
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            valueOffset += tab_StorageValue[i].valueSize;
        }
        valueOffset += 1;

        PDriver->data.blockWriteCnt = 0;
        PDriver->data.writeErrCnt = 0;

        //�������л��洢����,���������һֱд���һ������
        if (PDriver->data.baseAddr + valueOffset < BLOCK_RAMGE)
        {
            PDriver->data.baseAddr += valueOffset;
            //�洢����Ǩ�Ƶ�������
            for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
            {
                f_StorageWriteValues(PDriver, i, false);
            }
        }
        PDriver->pHardware->writeFunc(BASE_ADDR_OFFSET, sizeof(PDriver->data.baseAddr), (uchar *)&(PDriver->data.baseAddr));
    }

    //��ֹд��̫Ƶ��,�ۻ�50��д��
    if (PDriver->data.blockWriteCnt % 50 == 0)
    {
        f_StorageWriteValues(PDriver, STORAGE_INDEX_WRITE_CNT, false);
    }
}

/*****************************************************************************
 �� �� ��: f_StorageWriteValues
 ��������  : �洢д�����
 �������: pDriver����ָ��
 		   index�ڱ������
 		   check �Ƿ����
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��9��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_StorageWriteValues(STORAGE_DRIVER *PDriver, uchar index, uchar check)
{
    uint realOffset;
    int i;

	if (check)//�Ƿ���Ҫ���⣬��ֹ�ݹ�
	{
		#ifndef STORAGE_USE_FLASH
    	f_StorageJudgeBlock(PDriver);
		#endif
    }

    realOffset = PDriver->data.baseAddr;
    if (index > 0)
    {
        for (i = 0; i < index; i++)
        {
            realOffset += tab_StorageValue[i].valueSize;
        }
    }

    if (false == PDriver->pHardware->writeFunc(realOffset, tab_StorageValue[index].valueSize, (uchar *)tab_StorageValue[index].pValue))
    {
        PDriver->data.writeErrCnt++;
    }
}

/*****************************************************************************
 �� �� ��: f_StorageReadValues
 ��������  : �洢������
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��9��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_StorageReadValues(STORAGE_DRIVER *PDriver, uchar index)
{
    uint realOffset = PDriver->data.baseAddr;
    int i;

    if (index > 0)
    {
        for (i = 0; i < index; i++)
        {
            //���㵱ǰ������ʵ�ʴ洢ƫ����
            realOffset += tab_StorageValue[i].valueSize;
        }
    }
    PDriver->pHardware->readFunc(realOffset, tab_StorageValue[index].valueSize, (uchar *)tab_StorageValue[index].pValue);
}


/*****************************************************************************
 �� �� ��: f_StoragerInit
 ��������  : �洢��ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��9��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_StoragerInit(STORAGE_DRIVER *PDriver, const STORAGE_HARDWARE *pHardware)
{
    char head[STORAGE_HEAD_SIZE];
    uint i;

    #ifdef STORAGE_USE_FLASH
        f_FlashToEEPROMInit(); //flashģ��eeprom��ʼ��
    #endif

    //ע���д����
    f_Memset(PDriver, 0, sizeof(STORAGE_DRIVER));
    PDriver->pHardware = pHardware;

    //����ͷ���ж��Ƿ�Ϊ�״�����
    PDriver->pHardware->readFunc(HEAD_OFFSET, STORAGE_HEAD_SIZE, (uchar *)&head);
    if (f_CmpChars(head, storageInitFlag, STORAGE_HEAD_SIZE))
    {
        PDriver->pHardware->readFunc(BASE_ADDR_OFFSET, sizeof(PDriver->data.baseAddr), (uchar *)&(PDriver->data.baseAddr));

        //�ѳ�ʼ��������������
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            f_StorageReadValues(PDriver, i);
        }

        //��ΧУ��
        f_StorageRangeCheck();
    }
    else
    {
        //��ʼ��ƫ�Ƶ�ַ,���洢
        PDriver->data.baseAddr = BASE_ADDR_VALUE;
        PDriver->pHardware->writeFunc(BASE_ADDR_OFFSET, sizeof(PDriver->data.baseAddr), (uchar *)&(PDriver->data.baseAddr));

        //��ʼ�����ݲ�д��洢��
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            //��ʼ����ֵ
            f_MemCpy(tab_StorageValue[i].pValue, tab_StorageValue[i].pInitValue, tab_StorageValue[i].valueSize);

            //д��洢
            f_StorageWriteValues(PDriver, i, true);
        }
        PDriver->pHardware->writeFunc(HEAD_OFFSET, STORAGE_HEAD_SIZE, (const uchar *)storageInitFlag); //д�״��ϵ���Ϣ
    }
}

