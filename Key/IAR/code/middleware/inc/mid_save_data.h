/*******************************************************************************
* File         : mid_save_data.h
* Version      : v1.0.0
* Author       : ��껺�
* CreateDate   : 2018/4/6
* Description  : �м��:��������
* Change Logs  : 
*******************************************************************************/
#ifndef __MID_SAVE_DATA_20180406_H__
#define __MID_SAVE_DATA_20180406_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#define SVAE_CONST_VALUE  0x55  // ����ĳ���ֵ,��������У��

// �������ݵ����ݽṹ,������Ŀ��ͬ,���Խ�����Ӧ����,�����ֽ�(constValue)�������ֽ�(checkSum),���뱣��
// ע�����޸ĸ����ݽṹʱ,��Ҫע��Ĭ��ֵ�Ƿ�ͬ���޸�
typedef struct SaveData_Struct
{
    uint8_t  constValue; // ����,����У��
    uint16_t motorStepRO;  // ������в���----RO���������
    uint16_t motorStepCW;  // ������в���----��ˮ���������
    uint8_t  checkSum;   // У���
}SaveData_t;
#define SAVE_DATA_SIZE   sizeof(SaveData_t)

// eeprom��ʼ��ַ
#define EERPEOM_START_ADDR   0x4000
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void f_ReadEEPROM(SaveData_t *pSaveData, const SaveData_t DefaultSaveData, uint8_t (*pf_ReadByte)(uint32_t));

void f_EnableWriteEEPROM(void);
void f_WriteEEPROM(SaveData_t *pSaveData, void (*pf_SaveDataCallback)(uint32_t, uint8_t *, uint8_t));
/* Exported variables ------------------------------------------------------- */



#endif
