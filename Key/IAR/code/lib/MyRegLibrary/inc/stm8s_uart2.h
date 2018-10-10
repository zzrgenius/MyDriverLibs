/*******************************************************************************
  * @file    UART.h
  * @author  钟昊翰
  * @version V1.0.0
  * @date    2017-09-25
  * @brief   该头文件为串口配置头文件
*******************************************************************************/

#ifndef __STM8S_UART2_H__
#define __STM8S_UART2_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void f_UART2_Init(void);
void f_MCU_UART2SendByte(uint8_t ch);
uint8_t f_MCU_GetUART2ReceByte(void);

void f_EnableUART2TxINT(void);
void f_DisableUART2TxINT(void);
void f_EnableUART2RxINT(void);
void f_DisableUART2RxINT(void);
/* Exported variables ------------------------------------------------------- */

#endif