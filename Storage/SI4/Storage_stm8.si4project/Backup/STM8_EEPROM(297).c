#include "STM8_EEPROM.h"
#include "STM8S105C_S.h"

#define STM8_EEPROM_START_ADD 0x40000


/* =========================================================
* 功能描述: stm8解锁EEPROM
* 输     入:
* 返     回: 成功：BOOL_TRUE, 失败:BOOL_FALSE
* 修改历史:
1、2018-3-25 	钱百静 			完成基本功能
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
* 功能描述: stm8锁定EEPROM
* 输     入:
* 返     回:
* 修改历史:
1、2018-3-25		钱百静 			完成基本功能
=========================================================*/
void stm8_LockEEPROM(void)
{
	FLASH_IAPSR &= (~0x08);
}

/* =========================================================
* 功能描述: 写数据到stm8的内部eeprom
* 输     入: offset:数据写入的相对偏移地址
            numb:写入字节数
            pData:数据指针
* 返     回: 成功：BOOL_TRUE, 失败:BOOL_FALSE
* 修改历史:
1、2018-3-25 	钱百静 			完成基本功能
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
* 功能描述: 从stm8的内部eeprom读取数据
* 输     入: offset:数据写入的相对偏移地址
            numb:读出字节数
            pData:数据指针
* 返     回: 成功：BOOL_TRUE, 失败:BOOL_FALSE
* 修改历史:
1、2018-3-25 	钱百静 			完成基本功能
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



