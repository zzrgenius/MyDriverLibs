#ifndef __SPI_DRIVER_H__
#define __SPI_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * ǰ������                                         *
 *----------------------------------------------*/
struct spi_driver;
typedef struct spi_driver SPI_DRIVER;

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
//Mode0��CPOL=0��CPHA=0
//Mode1��CPOL=0��CPHA=1
//Mode2��CPOL=1��CPHA=0
//Mode3��CPOL=1��CPHA=1
//CPOL=0����ʾ��SCLK=0ʱ���ڿ���̬��������Ч״̬����SCLK���ڸߵ�ƽʱ
//CPOL=1����ʾ��SCLK=1ʱ���ڿ���̬��������Ч״̬����SCLK���ڵ͵�ƽʱ
//CPHA=0����ʾ���ݲ������ڵ�1�����أ����ݷ����ڵ�2������
//CPHA=1����ʾ���ݲ������ڵ�2�����أ����ݷ����ڵ�1������

#define MODE0 //ѡ��ģʽ
 
typedef struct 
{
	void (*ClockOut)(STATE_INFO);
	STATE_INFO (*DataIn)(void);
	void (*DataOut)(STATE_INFO);
	void (*EnChip)(STATE_INFO);
	void (*Delay)(void);
}SPI_HARDWARE_DRIVER;//SPIӲ����������

typedef struct spi_driver
{
	const SPI_HARDWARE_DRIVER *pHardware;
};


/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_SPIDriverInit(SPI_DRIVER *pDriver, const SPI_HARDWARE_DRIVER *pHardware);
uint f_SPIReadData(SPI_DRIVER *pDriver, uchar length);
void f_SPIWriteData(SPI_DRIVER *pDriver, uint sendData, uchar length);
void f_SPIEnChip(SPI_DRIVER *pDriver, STATE_INFO state);

#endif /* __SPI_DRIVER_H__ */
