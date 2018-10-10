/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : MCU_EEEROM.c
  �� �� ��   : V1.0
  ��    ��   : zhufeng
  ��������   : 2018��4��28��
  ����޸�   :
  ��������   : EEPROM�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����   : �����ļ�

******************************************************************************/
#define VAR_EEPROM_GLOBAL
#include "Include.h"
/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/

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

/*----------------------------------------------*
 * �궨��                                          *
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
 �� �� ��: f_pUnLockEeprom
 ��������  : EEROM����
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

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
 �� �� ��: f_pLockEeprom
 ��������  : EEROM����
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pLockEeprom(void)
{
	FLASH_IAPSR &= (~0x08);
}

/*****************************************************************************
 �� �� ��: f_pWriteEeprom
 ��������  : ��EEROMд�����ֽ�
 �������: uchar ADD     
             uchar iNO     
             uchar *iData  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

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
 �� �� ��: f_pReadEeprom
 ��������  : ��EEROM��iADD��ʼ����iNO���ֽ�����
 �������: uchar iADD    
             uchar iNO     
             uchar *iData  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

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
 �� �� ��: f_pReadOneTypeData
 ��������  : ��EEROM��һ���û�����ֵ
 �������: uchar iDataType    
             uchar iAddInEerom  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

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
 �� �� ��: f_pWriteOneDataEeprom
 ��������  : �ԱȻ��������ݣ���һ��ʱ�ŰѲ�һ��������д��
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pWriteOneDataEeprom(void)
{
	uchar i;
	static uchar iWriteByte;
	static uchar changeFlag = 0;//��ֵ�ı��˱�־λ
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
 �� �� ��: f_pWriteOneTypeData
 ��������  : ��EEROMдһ���û�����ֵ
 �������: uchar iDataType    
             uchar iAddInEerom  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

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
 �� �� ��: f_pReadAllDataEeprom
 ��������  : ��EEROM�������еĲ���(���ݱ��еĲ���)
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

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
 �� �� ��: f_pWriteAllDataEeprom
 ��������  : д��������
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pWriteAllDataEeprom(void)
{
	static uchar i;
	uint iTemp;
	//��ʼ�����ò���
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
 �� �� ��: f_pInitDataEeprom
 ��������  : �ָ���ʼ����
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��28��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

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

