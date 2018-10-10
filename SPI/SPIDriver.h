#ifndef __SPI_DRIVER_H__
#define __SPI_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 前置声明                                         *
 *----------------------------------------------*/
struct spi_driver;
typedef struct spi_driver SPI_DRIVER;

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
//Mode0：CPOL=0，CPHA=0
//Mode1：CPOL=0，CPHA=1
//Mode2：CPOL=1，CPHA=0
//Mode3：CPOL=1，CPHA=1
//CPOL=0，表示当SCLK=0时处于空闲态，所以有效状态就是SCLK处于高电平时
//CPOL=1，表示当SCLK=1时处于空闲态，所以有效状态就是SCLK处于低电平时
//CPHA=0，表示数据采样是在第1个边沿，数据发送在第2个边沿
//CPHA=1，表示数据采样是在第2个边沿，数据发送在第1个边沿

#define MODE0 //选择模式
 
typedef struct 
{
	void (*ClockOut)(STATE_INFO);
	STATE_INFO (*DataIn)(void);
	void (*DataOut)(STATE_INFO);
	void (*EnChip)(STATE_INFO);
	void (*Delay)(void);
}SPI_HARDWARE_DRIVER;//SPI硬件驱动部分

typedef struct spi_driver
{
	const SPI_HARDWARE_DRIVER *pHardware;
};


/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_SPIDriverInit(SPI_DRIVER *pDriver, const SPI_HARDWARE_DRIVER *pHardware);
uint f_SPIReadData(SPI_DRIVER *pDriver, uchar length);
void f_SPIWriteData(SPI_DRIVER *pDriver, uint sendData, uchar length);
void f_SPIEnChip(SPI_DRIVER *pDriver, STATE_INFO state);

#endif /* __SPI_DRIVER_H__ */
