/*******************************************************************************
* File         : adc_drive.h
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2018/01/10
* Description  : adc转换中间件
* Change Logs  : 
*******************************************************************************/
#ifndef __MID_ADC_20180110_H__
#define __MID_ADC_20180110_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct ADC_Samp_Struct
{
    uint8_t channl;       /* 通道号 */
    uint16_t *pAVG_Value; /* 指向平均值 */
}ADC_Samp_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
bool f_ADC_Pro(ADC_Samp_t *pData, uint8_t SampNum);
void f_ADC_Samping_INT(void);
/* Exported variables ------------------------------------------------------- */



#endif
