#include "STM8_EEPROM.h"
#include "STM8S105C_S.h"

#define STM8_EEPROM_START_ADD 0x40000


/* =========================================================
* ��������: stm8����EEPROM
* ��     ��:
* ��     ��: �ɹ���BOOL_TRUE, ʧ��:BOOL_FALSE
* �޸���ʷ:
1��2018-3-25 	Ǯ�پ� 			��ɻ�������
=========================================================*/
e_bool stm8_UnlockEEPROM(void)
{
	uint iCnt = 0;

	FLASH_CR1 |= 0x01;
	if(FLASH_IAPSR & 0x08)
	{
        return BOOL_TRUE;
	}
	else
	{
		FLASH_DUKR = 0xAE;
		FLASH_DUKR = 0x56;
	}

	while(!(FLASH_IAPSR & 0x08))
	{
		iCnt ++;
		if(iCnt >= 5000)
		{
			return BOOL_FALSE;
		}
	}
	return BOOL_TRUE;
}

/* =========================================================
* ��������: stm8����EEPROM
* ��     ��:
* ��     ��:
* �޸���ʷ:
1��2018-3-25		Ǯ�پ� 			��ɻ�������
=========================================================*/
void stm8_LockEEPROM(void)
{
	FLASH_IAPSR &= (~0x08);
}

/* =========================================================
* ��������: д���ݵ�stm8���ڲ�eeprom
* ��     ��: offset:����д������ƫ�Ƶ�ַ
            numb:д���ֽ���
            pData:����ָ��
* ��     ��: �ɹ���BOOL_TRUE, ʧ��:BOOL_FALSE
* �޸���ʷ:
1��2018-3-25 	Ǯ�پ� 			��ɻ�������
=========================================================*/
e_bool stm8_WriteToEEPROM(uint offset, uchar numb, const uchar *pData)
{
	word_32 writeAddr;

	if (numb == 0)
	{
        return BOOL_FALSE;
	}

	if(stm8_UnlockEEPROM())
    {
        writeAddr = STM8_EEPROM_START_ADD + offset;

        while (numb --)
        {
            *((@far uchar*)(writeAddr)) = *pData;
            writeAddr ++;
            pData ++;
        };
        stm8_LockEEPROM();

        return BOOL_TRUE;
    }

    return BOOL_FALSE;
}

/* =========================================================
* ��������: ��stm8���ڲ�eeprom��ȡ����
* ��     ��: offset:����д������ƫ�Ƶ�ַ
            numb:�����ֽ���
            pData:����ָ��
* ��     ��: �ɹ���BOOL_TRUE, ʧ��:BOOL_FALSE
* �޸���ʷ:
1��2018-3-25 	Ǯ�پ� 			��ɻ�������
=========================================================*/
void stm8_ReadFromEEPROM(uint offset, uchar numb, uchar *pData)
{
	word_32 writeAddr;
	writeAddr = STM8_EEPROM_START_ADD + offset;
	while (numb --)
    {
        *pData; = *((@far uchar*)(writeAddr));
        writeAddr ++;
        pData ++;
    };
}



