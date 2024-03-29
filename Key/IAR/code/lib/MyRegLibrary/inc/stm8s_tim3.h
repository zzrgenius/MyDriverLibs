/*******************************************************************************
  * @file    stm8s_tim3.h
  * @author  钟昊翰
  * @version V1.0.0
  * @date    2017-09-25
  * @brief   该头文件为stm8s定时器3配置头文件
*******************************************************************************/

#ifndef __STM8S_TIM3_H__
#define __STM8S_TIM3_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TIM3_ICInit(void);
uint16_t TIM3_GetCapture1(void);
/* Exported variables ------------------------------------------------------- */

#endif