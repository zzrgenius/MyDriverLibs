/*******************************************************************************
  * @file    stm8s_tim2.h
  * @author  钟昊翰
  * @version V1.0.0
  * @date    2017-09-25
  * @brief   该头文件为stm8s定时器3配置头文件
*******************************************************************************/

#ifndef __STM8S_TIM2_H__
#define __STM8S_TIM2_H__

#include"typedef.h"

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/** TIM2 Output Compare and PWM modes */
typedef enum
{
    TIM2_OCMODE_TIMING     = ((uint8_t)0x00),
    TIM2_OCMODE_ACTIVE     = ((uint8_t)0x10),
    TIM2_OCMODE_INACTIVE   = ((uint8_t)0x20),
    TIM2_OCMODE_TOGGLE     = ((uint8_t)0x30),
    TIM2_OCMODE_PWM1       = ((uint8_t)0x60),
    TIM2_OCMODE_PWM2       = ((uint8_t)0x70)
}TIM2_OCMode_TypeDef;

/** TIM2 Output Compare states */
typedef enum
{
    TIM2_OUTPUTSTATE_DISABLE           = ((uint8_t)0x00),
    TIM2_OUTPUTSTATE_ENABLE            = ((uint8_t)0x11)
}TIM2_OutputState_TypeDef;

/** TIM2 Output Compare Polarity */
typedef enum
{
    TIM2_OCPOLARITY_HIGH               = ((uint8_t)0x00),
    TIM2_OCPOLARITY_LOW                = ((uint8_t)0x22)
}TIM2_OCPolarity_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void f_TIM2_Init(void);

void TIM2_OC1Init(TIM2_OCMode_TypeDef TIM2_OCMode, 
                  TIM2_OutputState_TypeDef TIM2_OutputState, 
                  uint16_t TIM2_Pulse, 
                  TIM2_OCPolarity_TypeDef TIM2_OCPolarity);

void TIM2_OC1PreloadConfig(FunctionalState NewState);
/* Exported variables ------------------------------------------------------- */

#endif