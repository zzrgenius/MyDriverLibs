#ifndef __CC2500_DRIVER_H__
#define __CC2500_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "SPIDriver.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
#define CC2500_SEND_LEN 32//发送缓存大小
#define CC2500_REV_LEN 64//接收缓存大小
#define CC2500_MAX_CHANNEL 4 //最大跳频通道数量

typedef struct
{
	SPI_DRIVER *spi;
	uchar channels[CC2500_MAX_CHANNEL]; //跳频切换通道号
	uchar curChannelIndex; //当前通道序号
	
	uchar needSendCnt;//共需要发送的次数
	uchar sendBuffer[CC2500_SEND_LEN]; //发送缓存
	uchar revBuffer[CC2500_REV_LEN]; //接收缓存

	uchar autoSleepTm; //自动进入休眠时间

	uchar bResetOK :1; //正常复位完成
	uchar bLastGD0 :1; //上次状态口
	uchar bRfSleep :1; //正在休眠
}CC250_DRIVER;


/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern CC250_DRIVER cc2500;

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_CC2500_ChangeChannel(void);
void f_CC2500_Init(SPI_DRIVER *spi);
void f_CC2500_IntoSleep(void);
void f_CC2500_AutoSleep(void);
void f_CC2500_ReciveDeal(void);
void f_CC2500_SendDeal(void);
void f_CC2500_StartSend(void);
void f_CC2500_SetRevMode(void);




#endif /* __CC2500_DRIVER_H__ */
