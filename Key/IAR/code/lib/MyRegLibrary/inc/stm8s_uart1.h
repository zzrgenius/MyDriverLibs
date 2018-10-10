/*******************************************************************************
  * @file    UART.h
  * @author  ��껺�
  * @version V1.0.0
  * @date    2017-09-25
  * @brief   ��ͷ�ļ�Ϊ��������ͷ�ļ�
*******************************************************************************/

#ifndef __STM8S_UART1_H__
#define __STM8S_UART1_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void f_UART1_Init(void);
void f_MCU_UART1SendByte(uint8_t ch);
uint8_t f_MCU_GetUART1ReceByte(void);

void f_EnableUART1TxINT(void);
void f_DisableUART1TxINT(void);
void f_EnableUART1RxINT(void);
void f_DisableUART1RxINT(void);
/* Exported variables ------------------------------------------------------- */

#endif