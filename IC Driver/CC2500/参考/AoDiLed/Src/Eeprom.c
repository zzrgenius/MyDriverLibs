/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : MCU_EEEROM.c
  版 本 号   : V1.0
  作    者   : zhufeng
  生成日期   : 2018年4月28日
  最近修改   :
  功能描述   : EEPROM文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容   : 创建文件

******************************************************************************/
#define VAR_EEPROM_GLOBAL
#include "Include.h"
/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

#if UCHAR_NO > 0
AT_NEAR uchar pBuff_uchar[UCHAR_NO];
#endif 
#if UINT_NO > 0
AT_NEAR uint pBuff_uint[UINT_NO];
#endif
#if ULONG_NO > 0
AT_NEAR ulong pBuff_ulong[ULONG_NO];
#endif

/*****************************************************************************
 函 数 名: f_pUnLockEeprom
 功能描述  : EEROM解锁
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_pUnLockEeprom(void)
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

/*****************************************************************************
 函 数 名: f_pLockEeprom
 功能描述  : EEROM上锁
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pLockEeprom(void)
{
	FLASH_IAPSR &= (~0x08);
}

/*****************************************************************************
 函 数 名: f_pWriteEeprom
 功能描述  : 向EEROM写入多个字节
 输入参数: uchar ADD     
             uchar iNO     
             uchar *iData  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pWriteEeprom(uchar ADD,uchar iNO,uchar *iData)
{
	ulong Start_ADD;
	if(f_pUnLockEeprom() == false)
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

/*****************************************************************************
 函 数 名: f_pReadEeprom
 功能描述  : 从EEROM的iADD开始读出iNO个字节数据
 输入参数: uchar iADD    
             uchar iNO     
             uchar *iData  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pReadEeprom(uchar iADD,uchar iNO,uchar *iData)
{
	ulong Start_ADD;
	Start_ADD = START_EEROM_ADD + iADD;
	while(iNO --)
	{
		*iData = *((@far uchar*)Start_ADD);
		iData ++;
		Start_ADD ++;
	}
}

/*****************************************************************************
 函 数 名: f_pReadOneTypeData
 功能描述  : 向EEROM读一个用户设置值
 输入参数: uchar iDataType    
             uchar iAddInEerom  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pReadOneTypeData(uchar iDataType,uchar iAddInEerom)
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
		iRealDataAdd = (const uchar *)pValuAdd_uint[iAddInEerom];
		iAddress = (iAddInEerom<<1) + UINT_START_ADD;
		iReadByte = 2;
	#endif
	}
	else if(iDataType == ULONG)
	{
	#if ULONG_NO > 0
		iRealDataAdd = (const uchar *)pValuAdd_ulong[iAddInEerom];
		iAddress = (iAddInEerom<<2) + ULONG_START_ADD;
		iReadByte = 4;
	#endif
	}
	if(iReadByte)
		f_pReadEeprom(iAddress,iReadByte,iRealDataAdd);
}

/*****************************************************************************
 函 数 名: f_pWriteOneDataEeprom
 功能描述  : 对比缓存间的数据，不一样时才把不一样的数据写入
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pWriteOneDataEeprom(void)
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
					iRealDataAdd = (const uchar *)pValuAdd_uint[iAddInEerom];
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
					iRealDataAdd = (const uchar *)pValuAdd_ulong[iAddInEerom];
					iAddress = (iAddInEerom<<2) + ULONG_START_ADD;
					break;
				}
			}		
		}	
	#endif
	if(iWriteByte)
	{
		f_pWriteEeprom(iAddress,iWriteByte,iRealDataAdd);
		iWriteByte = 0;
	}
}

/*****************************************************************************
 函 数 名: f_pWriteOneTypeData
 功能描述  : 向EEROM写一个用户设置值
 输入参数: uchar iDataType    
             uchar iAddInEerom  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pWriteOneTypeData(uchar iDataType,uchar iAddInEerom)
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
		iRealDataAdd = (const uchar *)pValuAdd_uint[iAddInEerom];
		iAddress = (iAddInEerom<<1) + UINT_START_ADD;
		iWriteByte = 2;
	#endif
	}
	else if(iDataType == ULONG)
	{
	#if ULONG_NO > 0
		iRealDataAdd = (const uchar *)pValuAdd_ulong[iAddInEerom];
		iAddress = (iAddInEerom<<2) + ULONG_START_ADD;
		iWriteByte = 4;
	#endif
	}
	if(iWriteByte)
		f_pWriteEeprom(iAddress,iWriteByte,iRealDataAdd);
}

/*****************************************************************************
 函 数 名: f_pReadAllDataEeprom
 功能描述  : 向EEROM读出所有的参数(数据表中的参数)
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pReadAllDataEeprom(void)
{
	static uchar i;
	#if UCHAR_NO > 0
		for(i=0;i< UCHAR_NO;i++)
		{
			f_pReadOneTypeData(UCHAR, i);
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
			f_pReadOneTypeData(UINT, i);
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
			f_pReadOneTypeData(ULONG, i);
			pBuff_ulong[i] = *(pValuAdd_ulong[i]);
			if((*(pValuAdd_ulong[i]) < TAB_Limit_ulong[i][0]) || (*(pValuAdd_ulong[i]) > TAB_Limit_ulong[i][1]))
			{
				*(pValuAdd_ulong[i]) = TAB_Limit_ulong[i][2];
				pBuff_ulong[i] = TAB_Limit_ulong[i][2];
			}
		}
	#endif	
}

/*****************************************************************************
 函 数 名: f_pWriteAllDataEeprom
 功能描述  : 写所有数据
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pWriteAllDataEeprom(void)
{
	static uchar i;
	uint iTemp;
	//初始化设置参数
	#if UCHAR_NO > 0
		for(i=0;i< UCHAR_NO;i++)
		{
			*(pValuAdd_uchar[i]) = TAB_Limit_uchar[i][2];
			pBuff_uchar[i] = TAB_Limit_uchar[i][2];
			f_pWriteOneTypeData(UCHAR, i);
		}
	#endif

	#if UINT_NO > 0
		for(i=0;i< UINT_NO;i++)
		{
			*(pValuAdd_uint[i]) = TAB_Limit_uint[i][2];
			pBuff_uint[i] = TAB_Limit_uint[i][2];
			f_pWriteOneTypeData(UINT, i);
		}
	#endif
	
	#if ULONG_NO > 0
		for(i=0;i< ULONG_NO;i++)
		{
			*(pValuAdd_ulong[i]) = TAB_Limit_ulong[i][2];
			pBuff_ulong[i] = TAB_Limit_ulong[i][2];
			f_pWriteOneTypeData(ULONG, i);
		}
	#endif
	iTemp = FIRST_POWER_ON_FLAG;
	f_pWriteEeprom(FIRST_POWER_ON_FLAG_ADD,2,(const uchar *)(&iTemp));
	f_pLockEeprom();
}

/*****************************************************************************
 函 数 名: f_pInitDataEeprom
 功能描述  : 恢复初始设置
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月28日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pInitDataEeprom(void)
{
	if(eFirstPowerON == FIRST_POWER_ON_FLAG)
	{
		f_pReadAllDataEeprom();
		//f_pWriteAllDataEeprom();
	}
	else
	{
		f_pWriteAllDataEeprom();
	}
}

