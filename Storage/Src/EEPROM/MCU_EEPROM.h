#ifndef STM8_EEPROM_H
#define STM8_EEPROM_H

#include "DataType.h"
#include "StorageDriver.h"

void f_MCU_ReadFromEEPROM(uint offset, uchar numb, uchar *pData);
uchar f_MCU_WriteToEEPROM(uint offset, uchar numb, const uchar *pData);

extern const STORAGE_HARDWARE storageHardware;

#endif