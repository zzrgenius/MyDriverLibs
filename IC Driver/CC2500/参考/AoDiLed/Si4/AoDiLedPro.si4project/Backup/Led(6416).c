/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : Led.c
  �� �� ��   : V1.0
  ��    ��   : zhufeng
  ��������   : 2018��5��8��
  ����޸�   :
  ��������   : LED����ʾ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��8��
    ��    ��   : zhufeng
    �޸�����   : �����ļ�

******************************************************************************/
#define VAR_LED_GLOBALS
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

/*****************************************************************************
 �� �� ��: f_pLedDeal
 ��������  : LED����
 �������: BIG_STRUCT *pFuctionData  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��8��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pLedDeal(BIG_STRUCT *pFuctionData)
{
	static uchar LedInitCnt = 0;
	static uchar LedNoWatrFlag = 0;
	static uchar LedNoWaterCnt = 0;
	if((pFuctionData->bInitInf== rSYS_INIT_NO) || (pFuctionData->bInitInf == rSYS_INIT_HLAF))
	{
		LedPowerIcon = true;
		if(LedInitCnt < 29)
		{
			LedInitCnt++;
			LedSeatIcon = true;
			LedWaterRIcon = true;
			LedWaterBIcon = true;
			LedWaterGIcon = true;
			LedDryRIcon = true;
			LedDryBIcon = true;
			LedDryGIcon = true;
		}
		else
		{
			LedSeatIcon = false;
			LedWaterRIcon = false;
			LedWaterBIcon = false;
			LedWaterGIcon = false;
			LedDryRIcon = false;
			LedDryBIcon = false;
			LedDryGIcon = false;
		}
	}
	else if(pFuctionData->bInitInf == rSYS_INIT_OK)
	{
		if(LedNoWatrFlag == 0)
		{
			if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
			{
				LedNoWaterCnt++;
				LedPowerFlickF = true;
				if(LedNoWaterCnt > 32)
				{
					LedNoWatrFlag = 1;
				}
			}
			else
			{
				LedNoWatrFlag = 1;
			}
		}
		else
		{
			if(pFuctionData->SystemCurState == STANDBY_STATE)
			{
				LedAllIcon = 0x00;
//				if(pFuctionData->flushTimeState > 0)
//				{
//					LedSeatIcon = true;
//				}
			}
			else if(pFuctionData->SystemCurState == RUNNING_STATE)
			{
				if(pFuctionData->seatInf.SeatOffTm.hour >= 24)
				{
					LedAllIcon = 0x00;
				}
				else
				{
					LedPowerIcon = true;
					if(pFuctionData->seatInf.seatSensorState.bSwitchState == SW_ON
					||pFuctionData->seatInf.SwitchSeatEn == true
					||pFuctionData->flushTimeState > 0)
					{
						LedSeatIcon = true;
					}
					else
					{
						LedSeatIcon = false;
					}
					if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_OFF)
					{
//						if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
//						{
//							LedWaterRFlickF = true;
//							LedWaterBFlickF = true;
//							LedWaterGFlickF = true;
//						}
//						else
//						{
							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
							{
								LedWaterRIcon = false;
								LedWaterBIcon = false;
								LedWaterGIcon = false;
							}
							else
							{
								LedWaterRFlickF = true;
								LedWaterBFlickF = true;
								LedWaterGFlickF = true;
							}
//						}
					}
					else if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_LEVEL1)
					{
//						if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
//						{
//							LedWaterBFlickF = true;
//						}
//						else
//						{
							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
							{
								LedWaterBIcon = true;
							}
							else
							{
								LedWaterBFlickF = true;								
							}
//						}
						LedWaterRIcon = false;
						LedWaterGIcon = false;
					}
					else if(pFuctionData->heatInf.waterHeat.setWaterLevel == TEMP_LEVEL2)
					{
//						if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
//						{
//							LedWaterGFlickF = true;	
//						}
//						else
//						{
							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
							{
								LedWaterGIcon = true;
							}
							else
							{
								LedWaterGFlickF = true;									
							}
							
//						}
						LedWaterRIcon = false;
						LedWaterBIcon = false;
					}
					else
					{
//						if(pFuctionData->systemErrInf.flag.bNoWaterErr == true)
//						{
//							LedWaterRFlickF = true;	
//						}
//						else
//						{
							if(pFuctionData->WashInf.bTempChange == TEMP_NO_CHANGE)
							{
								LedWaterRIcon = true;
							}
							else
							{
								LedWaterRFlickF = true;									
							}
//						}
						LedWaterGIcon = false;
						LedWaterBIcon = false;
					}
					if(pFuctionData->systemErrInf.flag.bSeatTempHighErr)
					{
						if(pFuctionData->heatInf.seatHeat.setSeatLevel == TEMP_OFF)
						{
							LedWaterRFlickF = true;
							LedWaterBFlickF = true;
							LedWaterGFlickF = true;
						}
						else if(pFuctionData->heatInf.seatHeat.setSeatLevel == TEMP_LEVEL1)
						{
							LedDryRIcon = false;
							LedDryGIcon = false;
							LedWaterBFlickF = true;
						}
						else  if(pFuctionData->heatInf.seatHeat.setSeatLevel == TEMP_LEVEL2)
						{
							LedDryRIcon = false;
							LedDryBIcon = false;
							LedWaterGFlickF = true;
						}
						else
						{
							LedDryGIcon = false;
							LedDryBIcon = false;
							LedWaterRFlickF = true;
						}
					}
					else
					{
						if(LedInf.DryDisCnt > 0)
						{
							if(pFuctionData->heatInf.dryHeat.setDryLevel == DRY_OFF)
							{
								LedDryRIcon = false;
								LedDryBIcon = false;
								LedDryGIcon = false;
							}
							else if(pFuctionData->heatInf.dryHeat.setDryLevel == DRY_LEVEL_1)
							{
								LedDryRIcon = false;
								LedDryBIcon = true;
								LedDryGIcon = false;
							}
							else if(pFuctionData->heatInf.dryHeat.setDryLevel == DRY_LEVEL_2)
							{
								LedDryRIcon = false;
								LedDryBIcon = false;
								LedDryGIcon = true;			
							}
							else
							{
								LedDryRIcon = true;
								LedDryBIcon = false;
								LedDryGIcon = false;			
							}
						}
						else
						{
							if(TxComBuff.jSetSeatLevel == TEMP_OFF)
//							if(pFuctionData->heatInf.seatHeat.setSeatLevel == TEMP_OFF)
							{
								LedDryRIcon = false;
								LedDryBIcon = false;
								LedDryGIcon = false;
							}
							else if(TxComBuff.jSetSeatLevel == TEMP_LEVEL1)
//							else if(pFuctionData->heatInf.seatHeat.setSeatLevel == TEMP_LEVEL1)
							{
								LedDryRIcon = false;
								LedDryBIcon = true;
								LedDryGIcon = false;
							}
							else if(TxComBuff.jSetSeatLevel == TEMP_LEVEL2)
							//else if(pFuctionData->heatInf.seatHeat.setSeatLevel == TEMP_LEVEL2)
							{
								LedDryRIcon = false;
								LedDryBIcon = false;
								LedDryGIcon = true;				
							}
							else
							{
								LedDryRIcon = true;
								LedDryBIcon = false;
								LedDryGIcon = false;			
							}
						}
					}
				}
			}
			else if(pFuctionData->SystemCurState == TEST_MODE_STATE)
			{
				LedPowerIcon = true;
				if(pFuctionData->seatInf.seatSensorState.bSwitchState == SW_ON
				||pFuctionData->seatInf.SwitchSeatEn == true)
				{
					LedSeatIcon = true;
				}
				else
				{
					LedSeatIcon = false;
				}
				if(pFuctionData->curFunInf.curFunc == FUNC_SPANY)
				{
					LedWaterRFlickF = true;
				}
				else if(pFuctionData->curFunInf.curFunc == FUNC_WOMAN 
				||pFuctionData->curFunInf.curFunc == FUNC_DRY)
				{
					LedDryRFlickF = true;
				}
			}
		}
	}
}

/*****************************************************************************
 �� �� ��: f_pLedInit
 ��������  : LED��ʼ��
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��8��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pLedInit(void)
{
	LED_POWER(1);
	LED_SEAT(1);
	LED_TEMP_WATER_RED(1);
	LED_TEMP_WATER_BULE(1);
	LED_TEMP_WATER_GREEN(1);
	LED_TEMP_DRY_RED(1);
	LED_TEMP_DRY_BULE(1);
	LED_TEMP_DRY_GREEN(1);
}

/*****************************************************************************
 �� �� ��: f_pLedDriveDeal
 ��������  : LED�ײ�����
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��8��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pLedDriveDeal(void)
{
	LED_POWER(1);
	LED_SEAT(1);
	LED_TEMP_WATER_RED(1);
	LED_TEMP_WATER_BULE(1);
	LED_TEMP_WATER_GREEN(1);
	LED_TEMP_DRY_RED(1);
	LED_TEMP_DRY_BULE(1);
	LED_TEMP_DRY_GREEN(1);
	if(LedPowerIcon || (LedPowerFlickF && LedPowerFlickS))
	{
		LED_POWER(0);
	}
	if(LedSeatIcon || (LedSeatFlickF && LedSeatFlickS))
	{
		LED_SEAT(0);
	}
	if(LedWaterRIcon || (LedWaterRFlickF && LedWaterRFlickS))
	{
		LED_TEMP_WATER_RED(0);
	}
	if(LedWaterBIcon || (LedWaterBFlickF && LedWaterRFlickS))
	{
		LED_TEMP_WATER_BULE(0);
	}
	if(LedWaterGIcon || (LedWaterGFlickF && LedWaterGFlickS))
	{
		LED_TEMP_WATER_GREEN(0);
	}
	if(LedDryRIcon || (LedDryRFlickF && LedDryRFlickS))
	{
		LED_TEMP_DRY_RED(0);
	}
	if(LedDryBIcon || (LedDryBFlickF && LedDryBFlickS))
	{
		LED_TEMP_DRY_BULE(0);
	}
	if(LedDryGIcon || (LedDryGFlickF && LedDryGFlickS))
	{
		LED_TEMP_DRY_GREEN(0);
	}
	LedAllIcon = 0x00;
	LedAllFlickF = 0x00;
}