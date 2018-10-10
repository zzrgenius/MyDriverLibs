#define MCU_EEROM_TYPE_GLOBAL
#include "Include.h"

#if UCHAR_NO > 0
AT_NEAR uchar pBuff_uchar[UCHAR_NO];
#endif 
#if UINT_NO > 0
AT_NEAR uint pBuff_uint[UINT_NO];
#endif
#if ULONG_NO > 0
AT_NEAR ulong pBuff_ulong[ULONG_NO];
#endif

/*=========================================================
* 功能描述: EEROM解锁
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar UnLockEeprom(void)
{
	uint iCnt;
	iCnt = 0;
	FLASH_CR1 |= 0x01;
	if(FLASH_IAPSR & 0x08)
	{
		return true;
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
			return false;
		}
	}
	return true;
}

/*=========================================================
* 功能描述: EEROM上锁
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void LockEeprom(void)
{
	FLASH_IAPSR &= (~0x08);
}

/*=========================================================
* 功能描述: 向EEROM写入多个字节
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void WriteEeprom(uchar ADD,uchar iNO,uchar *iData)
{
	ulong Start_ADD;
	if(UnLockEeprom() == false)
	{
		return;
	}
	Start_ADD = START_EEROM_ADD + ADD;
	while(iNO)
	{
		*((@far uchar*)Start_ADD) = *iData;
		Start_ADD ++;
		iData ++;
		iNO --;
	}
}

/*=========================================================
* 功能描述: 从EEROM的iADD开始读出iNO个字节数据
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void ReadEeprom(uchar iADD,uchar iNO,uchar *iData)
{
	unsigned long Start_ADD;
	Start_ADD = START_EEROM_ADD + iADD;
	while(iNO --)
	{
		*iData = *((@far uchar*)Start_ADD);
		iData ++;
		Start_ADD ++;
	}
}

/*=========================================================
* 功能描述: 向EEROM读一个用户设置值
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_ReadOneTypeData(uchar iDataType,uchar iAddInEerom)
{
	uchar iReadByte;
	const uchar *iRealDataAdd;
	uchar iAddress;
	iReadByte = 0;
	if(iDataType == UCHAR)
	{
	#if UCHAR_NO > 0
		iRealDataAdd = pValuAdd_uchar[iAddInEerom];
		iAddress = iAddInEerom + UCHAR_START_ADD;
		iReadByte = 1;
	#endif
	}
	else if(iDataType == UINT)
	{
	#if UINT_NO > 0
		iRealDataAdd = (const unsigned char *)pValuAdd_uint[iAddInEerom];
		iAddress = (iAddInEerom<<1) + UINT_START_ADD;
		iReadByte = 2;
	#endif
	}
	else if(iDataType == ULONG)
	{
	#if ULONG_NO > 0
		iRealDataAdd = (const unsigned char *)pValuAdd_ulong[iAddInEerom];
		iAddress = (iAddInEerom<<2) + ULONG_START_ADD;
		iReadByte = 4;
	#endif
	}
	if(iReadByte)
		ReadEeprom(iAddress,iReadByte,iRealDataAdd);
}

/*=========================================================
* 功能描述: 对比缓存间的数据，不一样时才把不一样的数据写入
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_WriteOneDataEeprom(void)
{
	uchar i;
	static uchar iWriteByte;
	static uchar changeFlag = 0;//数值改变了标志位
	static uchar iAddInEerom;
	const uchar *iRealDataAdd;
	static uchar iAddress;
	#if UCHAR_NO > 0
	for(i=0;i<UCHAR_NO;i++)
	{
		if(pBuff_uchar[i] != *(pValuAdd_uchar[i]))
		{
			pBuff_uchar[i] = *(pValuAdd_uchar[i]);
			iWriteByte = 1;
			iAddInEerom = i;
			iRealDataAdd = pValuAdd_uchar[iAddInEerom];
			iAddress = iAddInEerom + UCHAR_START_ADD;
			break;
		}
	}
	#endif
	#if UINT_NO > 0
		if(iWriteByte == 0)
		{
			for(i=0;i<UINT_NO;i++)
			{
				if(pBuff_uint[i] != *(pValuAdd_uint[i]))
				{
					pBuff_uint[i] = *(pValuAdd_uint[i]);
					iWriteByte = 2;
					iAddInEerom = i;
					iRealDataAdd = (const unsigned char *)pValuAdd_uint[iAddInEerom];
					iAddress = (iAddInEerom<<1) + UINT_START_ADD;
					break;
				}
			}		
		}
	#endif
	#if ULONG_NO > 0
		if(iWriteByte == 0)
		{
			for(i=0;i<ULONG_NO;i++)
			{
				if(pBuff_ulong[i] != *(pValuAdd_ulong[i]))
				{
					pBuff_ulong[i] = *(pValuAdd_ulong[i]);
					iWriteByte = 4;
					iAddInEerom = i;
					iRealDataAdd = (const unsigned char *)pValuAdd_ulong[iAddInEerom];
					iAddress = (iAddInEerom<<2) + ULONG_START_ADD;
					break;
				}
			}		
		}	
	#endif
	if(iWriteByte)
	{
		WriteEeprom(iAddress,iWriteByte,iRealDataAdd);
		iWriteByte = 0;
	}
}

/*=========================================================
* 功能描述: 向EEROM写一个用户设置值
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_WriteOneTypeData(uchar iDataType,uchar iAddInEerom)
{
	uchar iWriteByte;
	const uchar *iRealDataAdd;
	uchar iAddress;
	iWriteByte = 0;
	if(iDataType == UCHAR)
	{
	#if UCHAR_NO > 0
		iRealDataAdd = pValuAdd_uchar[iAddInEerom];
		iAddress = iAddInEerom + UCHAR_START_ADD;
		iWriteByte = 1;
	#endif
	}
	else if(iDataType == UINT)
	{
	#if UINT_NO > 0
		iRealDataAdd = (const unsigned char *)pValuAdd_uint[iAddInEerom];
		iAddress = (iAddInEerom<<1) + UINT_START_ADD;
		iWriteByte = 2;
	#endif
	}
	else if(iDataType == ULONG)
	{
	#if ULONG_NO > 0
		iRealDataAdd = (const unsigned char *)pValuAdd_ulong[iAddInEerom];
		iAddress = (iAddInEerom<<2) + ULONG_START_ADD;
		iWriteByte = 4;
	#endif
	}
	if(iWriteByte)
		WriteEeprom(iAddress,iWriteByte,iRealDataAdd);
}

/*=========================================================
* 功能描述: 向EEROM读出所有的参数(数据表中的参数)
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_ReadAllDataEeprom(void)
{
	static uchar i;
	#if UCHAR_NO > 0
		for(i=0;i< UCHAR_NO;i++)
		{
			f_ReadOneTypeData(UCHAR, i);
			pBuff_uchar[i] = *(pValuAdd_uchar[i]);
			if((*(pValuAdd_uchar[i]) < TAB_Limit_uchar[i][0]) || (*(pValuAdd_uchar[i]) > TAB_Limit_uchar[i][1]))
			{
				*(pValuAdd_uchar[i]) = TAB_Limit_uchar[i][2];
				pBuff_uchar[i] = TAB_Limit_uchar[i][2];
			}
		}
	#endif
	#if UINT_NO > 0
		for(i=0;i< UINT_NO;i++)
		{
			f_ReadOneTypeData(UINT, i);
			pBuff_uint[i] = *(pValuAdd_uint[i]);
			if((*(pValuAdd_uint[i]) < TAB_Limit_uint[i][0]) || (*(pValuAdd_uint[i]) > TAB_Limit_uint[i][1]))
			{
				*(pValuAdd_uint[i]) = TAB_Limit_uint[i][2];
				pBuff_uint[i] = TAB_Limit_uint[i][2];
			}
		}
	#endif
	#if ULONG_NO > 0
		for(i=0;i<ULONG_NO;i++)
		{
			f_ReadOneTypeData(ULONG, i);
			pBuff_ulong[i] = *(pValuAdd_ulong[i]);
			if((*(pValuAdd_ulong[i]) < TAB_Limit_ulong[i][0]) || (*(pValuAdd_ulong[i]) > TAB_Limit_ulong[i][1]))
			{
				*(pValuAdd_ulong[i]) = TAB_Limit_ulong[i][2];
				pBuff_ulong[i] = TAB_Limit_ulong[i][2];
			}
		}
	#endif	
}

/*=========================================================
* 功能描述: 写所有数据
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_WriteAllDataEeprom(void)
{
	static uchar i;
	uint iTemp;
	//初始化设置参数
	#if UCHAR_NO > 0
		for(i=0;i< UCHAR_NO;i++)
		{
			*(pValuAdd_uchar[i]) = TAB_Limit_uchar[i][2];
			pBuff_uchar[i] = TAB_Limit_uchar[i][2];
			f_WriteOneTypeData(UCHAR, i);
		}
	#endif

	#if UINT_NO > 0
		for(i=0;i< UINT_NO;i++)
		{
			*(pValuAdd_uint[i]) = TAB_Limit_uint[i][2];
			pBuff_uint[i] = TAB_Limit_uint[i][2];
			f_WriteOneTypeData(UINT, i);
		}
	#endif
	
	#if ULONG_NO > 0
		for(i=0;i< ULONG_NO;i++)
		{
			*(pValuAdd_ulong[i]) = TAB_Limit_ulong[i][2];
			pBuff_ulong[i] = TAB_Limit_ulong[i][2];
			f_WriteOneTypeData(ULONG, i);
		}
	#endif
	iTemp = FIRST_POWER_ON_FLAG;
	WriteEeprom(FIRST_POWER_ON_FLAG_ADD,2,(const unsigned char *)(&iTemp));
	LockEeprom();
}

/*=========================================================
* 功能描述: 恢复初始设置
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_InitDataEeprom(void)
{
	if(eFirstPowerON == FIRST_POWER_ON_FLAG)
	{
		f_ReadAllDataEeprom();
		//f_WriteAllDataEeprom();
	}
	else
	{
		f_WriteAllDataEeprom();
	}
}

