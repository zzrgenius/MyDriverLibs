/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : Led.c
  版 本 号   : V1.0
  作    者   : zhufeng
  生成日期   : 2018年5月8日
  最近修改   :
  功能描述   : LED灯显示
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月8日
    作    者   : zhufeng
    修改内容   : 创建文件

******************************************************************************/
#define VAR_LED_GLOBALS
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

/*****************************************************************************
 函 数 名: f_pLedDeal
 功能描述  : LED处理
 输入参数: BIG_STRUCT *pFuctionData  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月8日
    作    者   : zhufeng
    修改内容    : 新生成函数

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
 函 数 名: f_pLedInit
 功能描述  : LED初始化
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月8日
    作    者   : zhufeng
    修改内容    : 新生成函数

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
 函 数 名: f_pLedDriveDeal
 功能描述  : LED底层驱动
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月8日
    作    者   : zhufeng
    修改内容    : 新生成函数

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