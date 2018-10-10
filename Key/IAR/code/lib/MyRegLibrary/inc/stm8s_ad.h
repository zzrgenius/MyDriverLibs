/*******************************************************************************
  * @file    stm8s_ad.h
  * @author  钟昊翰
  * @version V1.0.0
  * @date    2017-09-25
  * @brief   该头文件为AD转换头文件
*******************************************************************************/

#ifndef __STM8S_AD_H__
#define __STM8S_AD_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum 
{
  ADC1_CHANNEL_0  = (uint8_t)0x00, /**< Analog channel 0 */
  ADC1_CHANNEL_1  = (uint8_t)0x01, /**< Analog channel 1 */
  ADC1_CHANNEL_2  = (uint8_t)0x02, /**< Analog channel 2 */
  ADC1_CHANNEL_3  = (uint8_t)0x03, /**< Analog channel 3 */
  ADC1_CHANNEL_4  = (uint8_t)0x04, /**< Analog channel 4 */
  ADC1_CHANNEL_5  = (uint8_t)0x05, /**< Analog channel 5 */
  ADC1_CHANNEL_6  = (uint8_t)0x06, /**< Analog channel 6 */
  ADC1_CHANNEL_7  = (uint8_t)0x07, /**< Analog channel 7 */
  ADC1_CHANNEL_8  = (uint8_t)0x08, /**< Analog channel 8 */
  ADC1_CHANNEL_9  = (uint8_t)0x09, /**< Analog channel 9 */
  ADC1_CHANNEL_12 = (uint8_t)0x0C /**< Analog channel 12 */ 
                 /* refer to product datasheet for channel 12 availability */
} ADC_Channel_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void f_ADC_Init(ADC_Channel_TypeDef Channel);
uint16_t f_ADC1_GetConversionValue(void);
/* Exported variables ------------------------------------------------------- */

#endif