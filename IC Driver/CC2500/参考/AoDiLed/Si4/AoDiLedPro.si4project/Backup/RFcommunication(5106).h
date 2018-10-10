#ifndef COMMUNICATION_H
#define COMMUNICATION_H

//常量定义
/* 定义接收字节数 */
#define RXD_TOTAL_BYTES				12

/* 定义发送字节数 */
#define TXD_TOTAL_BYTES				12

void f_GetSendBuffRF(void);
void f_DealRXD(void);
#endif
