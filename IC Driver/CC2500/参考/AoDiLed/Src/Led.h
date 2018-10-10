#ifndef __LED_H__
#define __LED_H__

#ifdef  VAR_LED_GLOBALS
	#define  VAR_LED_EXT
#else
	#define  VAR_LED_EXT  extern
#endif
/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 数据类型定义                                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/

#define LED_POWER(DATA)					PAO_2 = DATA 	// 电源	
#define LED_SEAT(DATA)					PDO_3 = DATA	//着座		
#define LED_TEMP_WATER_RED(DATA)			PDO_2 = DATA	//水温红色		
#define LED_TEMP_WATER_BULE(DATA)			PCO_7 = DATA	//水温蓝色
#define LED_TEMP_WATER_GREEN(DATA)		PCO_6 = DATA	//水温绿色
#define LED_TEMP_DRY_RED(DATA)			PCO_5 = DATA	//风温红色		
#define LED_TEMP_DRY_BULE(DATA)			PCO_4 = DATA	//风温蓝色
#define LED_TEMP_DRY_GREEN(DATA)			PCO_3 = DATA	//风温绿色
//#define LED_POWER(DATA)						PAO_3 = DATA 	// 电源	
//#define LED_SEAT(DATA)						PDO_3 = DATA	//着座		
//#define LED_TEMP_WATER_RED(DATA)			PDO_2 = DATA	//水温红色	
//#define LED_TEMP_WATER_RED(DATA)			PAO_3 = DATA	//水温红色
//#define LED_TEMP_WATER_BULE(DATA)			PCO_7 = DATA	//水温蓝色
//#define LED_TEMP_WATER_GREEN(DATA)			PCO_6 = DATA	//水温绿色
//#define LED_TEMP_DRY_RED(DATA)				PCO_4 = DATA	//风温红色		
//#define LED_TEMP_DRY_BULE(DATA)				PCO_3 = DATA	//风温蓝色
//#define LED_TEMP_DRY_GREEN(DATA)			PCO_5 = DATA	//风温绿色
	
typedef struct
{
	uchar InitNoWaterFlick : 1;
	uchar ErrLedFlick : 1;
	uchar WaterFlick : 1;
	uchar DryDisCnt;	//烘干LED灯显示
	uchar delaySeatDis : 1;
	uchar delayDrytDis : 1;
}LED_INF;
VAR_LED_EXT AT_NEAR LED_INF LedInf;

VAR_LED_EXT AT_NEAR byte_def LedDisIcon;

#define LedAllIcon				LedDisIcon.m_byte
#define LedPowerIcon			LedDisIcon.m_bit.b0
#define LedSeatIcon 			LedDisIcon.m_bit.b1
#define LedWaterRIcon			LedDisIcon.m_bit.b2
#define LedWaterBIcon			LedDisIcon.m_bit.b3
#define LedWaterGIcon			LedDisIcon.m_bit.b4
#define LedDryRIcon 			LedDisIcon.m_bit.b5
#define LedDryBIcon 			LedDisIcon.m_bit.b6
#define LedDryGIcon 			LedDisIcon.m_bit.b7
VAR_LED_EXT AT_NEAR byte_def LedDisFlickF;

#define LedAllFlickF			LedDisFlickF.m_byte
#define LedPowerFlickF			LedDisFlickF.m_bit.b0
#define LedSeatFlickF			LedDisFlickF.m_bit.b1
#define LedWaterRFlickF 		LedDisFlickF.m_bit.b2
#define LedWaterBFlickF 		LedDisFlickF.m_bit.b3
#define LedWaterGFlickF 		LedDisFlickF.m_bit.b4
#define LedDryRFlickF			LedDisFlickF.m_bit.b5
#define LedDryBFlickF			LedDisFlickF.m_bit.b6
#define LedDryGFlickF			LedDisFlickF.m_bit.b7
VAR_LED_EXT AT_NEAR byte_def LedDisFlickS;

#define LedAllFlickS			LedDisFlickS.m_byte
#define LedPowerFlickS			LedDisFlickS.m_bit.b0
#define LedSeatFlickS			LedDisFlickS.m_bit.b1
#define LedWaterRFlickS 		LedDisFlickS.m_bit.b2
#define LedWaterBFlickS 		LedDisFlickS.m_bit.b3
#define LedWaterGFlickS 		LedDisFlickS.m_bit.b4
#define LedDryRFlickS			LedDisFlickS.m_bit.b5
#define LedDryBFlickS			LedDisFlickS.m_bit.b6
#define LedDryGFlickS			LedDisFlickS.m_bit.b7

VAR_LED_EXT AT_NEAR byte_def LedDisPower500F;
#define LedPower500msF		 LedDisPower500F.m_byte
#define LedPower500msf		 LedDisPower500F.m_bit.b0

VAR_LED_EXT AT_NEAR byte_def LedDisPower500S;
#define LedPower500msS		 LedDisPower500S.m_byte
#define LedPower500mss 		 LedDisPower500S.m_bit.b0

VAR_LED_EXT void f_pLedInit(void);
VAR_LED_EXT void f_pLedDeal(BIG_STRUCT *pFuctionData);
VAR_LED_EXT void f_pLedDriveDeal(void);
#endif /* __LED_H__ */