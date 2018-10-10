/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "Storage.h"
#include "STM8_EEPROM.h"

main()
{
	storageInit(stm8_WriteToEEPROM, stm8_ReadFromEEPROM);
	while (1);
}