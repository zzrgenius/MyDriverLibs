/*******************************************************************************
* File         : test_mid_uart_tx.h
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2018/1/12
* Description  : 串口中间件(接收模块)(测试中)
* Change Logs  : 
*******************************************************************************/
#ifndef __TEST_MID_UART_RX_20180112_H__
#define __TEST_MID_UART_RX_20180112_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define UART_TEST_STABILITY  0  // UART测试(稳定性测试)
/* Exported functions ------------------------------------------------------- */
void f_RxSupervisorInit(void);
void f_TimeNoReceiveTMR(void);
void f_DealReceiveData(void (*pf_RxDataProcessingCallback)(uint8_t *pData, uint8_t DataSize));
void f_INT_UART_RX(uint8_t (*pf_Read_UART_DR)(void));
/* Exported variables ------------------------------------------------------- */



#endif
