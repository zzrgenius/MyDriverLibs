/*******************************************************************************
* File         : mid_tds_tmp.h
* Version      : v1.0.0
* Author       : ��껺�
* CreateDate   : 2017/12/14
* Description  : TDS(���¶Ȳ���)����ͷ�ļ�
* Change Logs  : 
*******************************************************************************/
#ifndef __MID_TDS_TMP_20171214_H__
#define __MID_TDS_TMP_20171214_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* TDS��Ϣ */
typedef struct TDS_Inf_Struct
{
    uint16_t  TDS_CaptureTm;  //����ʱ��
	uint16_t  TDS_Freq;       //Ƶ��
	uint16_t  freqCnt;
	uint16_t  freqCntBuf;
	uint16_t  TDS_Value;
//	uint8_t   noITCnt;      // ���ⲿ�жϴ���
//	SENSOR_INF waterTemp;   // �¶�
    
	uint8_t   bCaptureEn : 1;
	uint8_t   bEnCalcTDS : 1;
    uint8_t   overflow   : 1;
}TDS_Inf_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void f_EnCapture(FunctionalState TDS_State);

uint16_t f_ReadTDS_Value(void);

void f_TDS_Deal(TDS_Inf_t *pTDS_Inf,int16_t Tmp);
void f_TDS_FreqCNT(uint16_t *pTDS_FreqCnt);

void f_TDS_Intl(void);
/* Exported variables ------------------------------------------------------- */
extern TDS_Inf_t tdsOutWater;


#endif
