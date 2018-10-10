#include "DataType.h"

/* =========================================================
* �� �� ��: stm8_UnlockEEPROM
* ��������: stm8����EEPROM
* ȫ�ֱ���:
* ��     ��:
* ��     ��: �ɹ���BOOL_TRUE, ʧ��:BOOL_FALSE
* �������:
* ע	    �⣺
* �޸�����			�޸���				�޸�˵��
* 2018-4-12		Ǯ�پ� 			��ɻ�������
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
* �� �� ��: stm8_UnlockEEPROM
* ��������: stm8����EEPROM
* ȫ�ֱ���: ��
* ��     ��: �ɹ���BOOL_TRUE, ʧ��:BOOL_FALSE
* ��     ��:
* �������:
* ע	�⣺��ͬ�����Ų��������������޸�
* �޸�����			�޸���				�޸�˵��
* 2014-4-12			Ǯ�پ� 			��ɻ�������
 =========================================================*/
void stm8_LockEEPROM(void)
{
	FLASH_IAPSR &= (~0x08);
}


