#include "DataType.h"

/* =========================================================
* 函 数 名: stm8_UnlockEEPROM
* 功能描述: stm8解锁EEPROM
* 全局变量:
* 输     入:
* 返     回: 成功：BOOL_TRUE, 失败:BOOL_FALSE
* 处理过程:
* 注	    意：
* 修改日期			修改人				修改说明
* 2018-4-12		钱百静 			完成基本功能
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
* 函 数 名: stm8_UnlockEEPROM
* 功能描述: stm8解锁EEPROM
* 全局变量: 无
* 输     入: 成功：BOOL_TRUE, 失败:BOOL_FALSE
* 返     回:
* 处理过程:
* 注	意：不同按键排布，处理内容需修改
* 修改日期			修改人				修改说明
* 2014-4-12			钱百静 			完成基本功能
 =========================================================*/
void stm8_LockEEPROM(void)
{
	FLASH_IAPSR &= (~0x08);
}


