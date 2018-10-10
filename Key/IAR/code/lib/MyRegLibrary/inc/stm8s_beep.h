/*******************************************************************************
  * @file    stm8s_beep.h
  * @author  钟昊翰
  * @version V1.0.0
  * @date    2017-09-25
  * @brief   该头文件为蜂鸣器配置头文件
*******************************************************************************/

#ifndef __STM8S_BEEP_H__
#define __STM8S_BEEP_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
  * @brief  BEEP Frequency selection
  */
typedef enum {
  BEEP_FREQUENCY_1KHZ = (uint8_t)0x00,  /*!< Beep signal output frequency equals to 1 KHz */
  BEEP_FREQUENCY_2KHZ = (uint8_t)0x01,  /*!< Beep signal output frequency equals to 2 KHz */
  BEEP_FREQUENCY_4KHZ = (uint8_t)0x02   /*!< Beep signal output frequency equals to 4 KHz */
} BEEP_Frequency_TypeDef;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define BEEP_CMD(_STATE_)  do{BEEP_CSR_bit.BEEPEN=(_STATE_);}while(0)
/* Exported functions ------------------------------------------------------- */
void f_BEEP_Init(BEEP_Frequency_TypeDef BEEP_Frequency);
/* Exported variables ------------------------------------------------------- */

#endif