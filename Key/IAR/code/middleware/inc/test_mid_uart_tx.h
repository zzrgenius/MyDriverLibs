/*******************************************************************************
* File         : test_mid_uart.h
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2018/1/10
* Description  : 串口发送中间件(测试阶段)
* Change Logs  : 
*******************************************************************************/
#ifndef __TEST_MID_UART_TX_20180110_H__
#define __TEST_MID_UART_TX_20180110_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum
{
    SUCCESS_ADD_GROUP = 0, // 组添加成功
    ERR_BUFF_OVERFLOW,     // 发送缓存越界
    ERR_GROUP_OVERFLOW,    // 组溢出
}AddTxGroup_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void f_TxSupervisorInit(void);
AddTxGroup_t f_AddTxGroup(uint8_t GroupIndex, uint8_t *pTxBuff, uint8_t BuffSize);
void f_INT_UART_TX(void (*pf_SendByte)(uint8_t),void (*pf_DisableTxINT)(void));
/* Exported variables ------------------------------------------------------- */



#endif
