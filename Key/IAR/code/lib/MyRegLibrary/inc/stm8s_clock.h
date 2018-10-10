/*******************************************************************************
  * @file    stm8s_clock.h
  * @author  钟昊翰
  * @version V1.0.0
  * @date    2017-xx-xx
  * @brief   该头文件为stm8s时钟配置头文件
*******************************************************************************/

#ifndef __STM8S_CLOCK_H__
#define __STM8S_CLOCK_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/**
* @brief   CLK Clock Source.
*/
typedef enum {
    CLK_SOURCE_HSI    = (uint8_t)0xE1, /*!< Clock Source HSI. */
    CLK_SOURCE_LSI    = (uint8_t)0xD2, /*!< Clock Source LSI. */
    CLK_SOURCE_HSE    = (uint8_t)0xB4 /*!< Clock Source HSE. */
} CLK_Source_TypeDef;

/**
  * @brief  Definition of Device on-chip RC oscillator frequencies
  */
#define HSI_VALUE   ((uint32_t)16000000) /*!< Typical Value of the HSI in Hz */
#define LSI_VALUE   ((uint32_t)128000)   /*!< Typical Value of the LSI in Hz */
#define HSE_VALUE ((uint32_t)8000000)    /* Value of the External oscillator in Hz*/
/* Exported functions ------------------------------------------------------- */
void f_ClockInit(void);
uint32_t f_LSIMeasurment(void);
/* Exported variables ------------------------------------------------------- */

#endif