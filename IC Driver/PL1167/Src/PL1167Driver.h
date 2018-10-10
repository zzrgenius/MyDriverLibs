#ifndef __PL1167_DRIVER_H__
#define __PL1167_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "SPIDriver.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
#define PL1167_SEND_LEN 20//发送缓存大小
#define PL1167_REV_LEN 20//接收缓存大小
typedef struct
{
	SPI_DRIVER spi;
	uchar sendWaitTm;//启动发送后等待发送超时时间
	uchar needSendCnt;//共需要发送的次数
	uchar sendBuffer[PL1167_SEND_LEN]; //发送缓存
	uchar revBuffer[PL1167_REV_LEN]; //接收缓存

	uchar bStartWait :1; //开始发送等待
}PL1167_DRIVER;

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
PL1167_DRIVER pl1167;

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_PL1167Init(void);
void f_PL1167ChangeFreq(void);
void f_PL1167SendDeal(void);
void f_PL1167RevDeal(void);
void f_PL1167StartSend(void);
void f_PL1167InitReg(void);
void f_PL1167IntoSleep(void);

#endif /* __PL1167_DRIVER_H__ */
