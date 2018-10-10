/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : StorageConfig.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��28�� ����һ
  ����޸�   :
  ��������   : �洢����������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��28�� ����һ
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "StorageConfig.h"
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

//====��ʼ��ֵ====
const ulong initValue_0 = 0;
const SYSTEM_STATE initSysState = SYS_STATE_RUN;
const uchar initSaveFlag = 1;
const uint initRound_1_Tm = 70; //*100ms
const uint initBottomTm = 60; //*100ms
const uint initRound_2_Tm = 50; //*100ms

const STORAGE_TYPE tab_StorageValue[] =
{
    {(void *)&(storageDriver.data.blockWriteCnt), sizeof(storageDriver.data.blockWriteCnt), (void *)&initValue_0},//STORAGE_WriteCnt
    {(void *)&(systemInfo.sysState), sizeof(SYSTEM_STATE), (void *)&initSysState}, //ϵͳ״̬
    {(void *)&(functionInfo.saveFlags.m_byte), sizeof(uchar), (void *)&initSaveFlag}, //�Զ����ǡ�ҹ�ƣ�Ĭ���Զ����ǿ�
    {(void *)&(funcFlush.saveFlushtm[FLUSH_ADJUST_WASH]), sizeof(uint), (void *)&initRound_1_Tm}, //ϴˢʱ��
    {(void *)&(funcFlush.saveFlushtm[FLUSH_ADJUST_CLEAN]), sizeof(uint), (void *)&initBottomTm}, //����ʱ��
    {(void *)&(funcFlush.saveFlushtm[FLUSH_ADJUST_BACK]), sizeof(uint), (void *)&initRound_2_Tm} //��ˮʱ��
};

const uint storageTableSize = (sizeof(tab_StorageValue)/sizeof(tab_StorageValue[0]));

//====�洢���ݷ�Χ,��Ҫһһ��Ӧ====
//д����
const RANGE_ULONG_TYPE writeCntRange = 
{	
	0, //��С
	0xffffffff //���
};

//ϵͳ״̬
const RANGE_UCHAR_TYPE systemStateRange = 
{   
    SYS_STATE_STANDBY, //��С
    SYS_STATE_SELFCHECK //���
};

//ϵͳ״̬
const RANGE_UCHAR_TYPE saveFlagsRange = 
{   
    0, //��С
    3 //���
};

//��ϴʱ�䷶Χ
const RANGE_UINT_TYPE flushTmRange = 
{   
    40, //��С,��λ100ms
    100 //���,��λ100ms
};

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/


/*****************************************************************************
 �� �� ��: f_StorageRangeCheck
 ��������  : �洢���ݷ�Χ�ж�
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��4��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_StorageRangeCheck(void)
{
    if (storageDriver.data.blockWriteCnt < writeCntRange.min 
    || storageDriver.data.blockWriteCnt > writeCntRange.max )
    {
        storageDriver.data.blockWriteCnt = initValue_0;  
        f_StorageWriteValues(&storageDriver, STORAGE_INDEX_WRITE_CNT, true);
    }

    if (systemInfo.sysState < systemStateRange.min 
    || systemInfo.sysState > systemStateRange.max )
    {
        systemInfo.sysState = initSysState; 
        f_StorageWriteValues(&storageDriver, STORAGE_SYS_STATE, true);
    }

    if (functionInfo.saveFlags.m_byte < saveFlagsRange.min 
    || functionInfo.saveFlags.m_byte > saveFlagsRange.max )
    {
        functionInfo.saveFlags.m_byte = initSaveFlag;   
        f_StorageWriteValues(&storageDriver, STORAGE_SYS_FLAGS, true);
    }

    if (funcFlush.saveFlushtm[FLUSH_ADJUST_WASH] < flushTmRange.min 
    || funcFlush.saveFlushtm[FLUSH_ADJUST_WASH] > flushTmRange.max )
    {
		funcFlush.saveFlushtm[FLUSH_ADJUST_WASH] = initRound_1_Tm; 
        f_StorageWriteValues(&storageDriver, STORAGE_ROUND_1_TM, true);     
    }

    if (funcFlush.saveFlushtm[FLUSH_ADJUST_CLEAN] < flushTmRange.min 
    || funcFlush.saveFlushtm[FLUSH_ADJUST_CLEAN] > flushTmRange.max )
    {
		funcFlush.saveFlushtm[FLUSH_ADJUST_CLEAN] = initBottomTm; 
        f_StorageWriteValues(&storageDriver, STORAGE_BOTTOM_TM, true);    
    }

    if (funcFlush.saveFlushtm[FLUSH_ADJUST_BACK] < flushTmRange.min 
    || funcFlush.saveFlushtm[FLUSH_ADJUST_BACK] > flushTmRange.max )
    {
		funcFlush.saveFlushtm[FLUSH_ADJUST_BACK] = initRound_2_Tm; 
        f_StorageWriteValues(&storageDriver, STORAGE_ROUND_2_TM, true);    
    }
}


