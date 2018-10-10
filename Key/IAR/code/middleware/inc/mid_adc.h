/*******************************************************************************
* File         : adc_drive.h
* Version      : v1.0.0
* Author       : ��껺�
* CreateDate   : 2018/01/10
* Description  : adcת���м��
* Change Logs  : 
*******************************************************************************/
#ifndef __MID_ADC_20180110_H__
#define __MID_ADC_20180110_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct ADC_Samp_Struct
{
    uint8_t channl;       /* ͨ���� */
    uint16_t *pAVG_Value; /* ָ��ƽ��ֵ */
}ADC_Samp_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
bool f_ADC_Pro(ADC_Samp_t *pData, uint8_t SampNum);
void f_ADC_Samping_INT(void);
/* Exported variables ------------------------------------------------------- */



#endif
