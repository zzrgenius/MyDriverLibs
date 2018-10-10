#include "rf_hardware.h"
#include "my_rf_setting.h"
#include "hw_CC_reg.h"
#include "hw_cc_interface.h"
#include "hw_TI_CC.h" 
#include "Include.h"

/*=========================================================
* 函 数 名: halSpiWriteReg()
* 功能描述: 单字节写，写数据value到一个单独的地址寄存器addr
* 调用方法: halSpiWriteReg();
* 调用函数: 
=========================================================*/
void halSpiWriteReg(Uint8 addr,Uint8 value)
{
	unsigned int i;
	CC_CS_LOW;	//CS enable
	i = 0;
	while(CC_SOMI_REG_IN)//wait for ccxxxx ready
	{
		f_MCU_FeedDog();
		TI_CC_WAIT(30*12);
		if (i ++ > 1000)
			break;
	}
	CC_SPI_TXBUF_SET(addr&0x7F);//send address
	CC_SPI_WAIT_TXFIN;																				//wait for tx to finish
	CC_SPI_TXBUF_SET(value);//send data
	CC_SPI_WAIT_TXFIN;
	CC_CS_HIGH;
}
/*=========================================================
* 函 数 名: halSpiWriteBurstReg()
* 功能描述: 连续写寄存器
* 调用方法: halSpiWriteReg();
* 调用函数: 
=========================================================*/
void halSpiWriteBurstReg(Uint8 addr, Uint8 *buffer, Uint8 count)
{
	Uint16 i;
	CC_CS_LOW;//CS enable
	i = 0;
	while(CC_SOMI_REG_IN)	//wait for ccxxxx ready
	{
		f_MCU_FeedDog();
		TI_CC_WAIT(30*12);
		if (i ++ > 1000)
			break;
	}
	CC_SPI_TXBUF_SET(addr|TI_CCxxx0_WRITE_BURST);//send addr
	CC_SPI_WAIT_TXFIN;//wait for tx to finish
	for(i = 0; i < count; i++)
	{
		CC_SPI_TXBUF_SET(buffer[i]);
		CC_SPI_WAIT_TXBUF;
	}
	CC_SPI_WAIT_TXFIN;
	CC_CS_HIGH;
}
/*=========================================================
* 函 数 名: halSpiReadReg()
* 功能描述: 读寄存器值
* 调用方法: halSpiReadReg();
* 调用函数: 
=========================================================*/
Uint8 halSpiReadReg(Uint8 addr)
{
	Uint8 i_ReturnValue;
	unsigned int i;
	CC_CS_LOW;//CS enable
	i = 0;
	while(CC_SOMI_REG_IN)//wait for ccxxxx ready
	{
		f_MCU_FeedDog();
		TI_CC_WAIT(30*12);
		if (i ++ > 1000)
			break;
	}
	CC_SPI_TXBUF_SET(addr|TI_CCxxx0_READ_SINGLE);							
	CC_SPI_RXBUF_READ(i_ReturnValue);
	CC_CS_HIGH;
	return i_ReturnValue;
}
/*=========================================================
* 函 数 名: halSpiReadBurstReg()
* 功能描述: 连续读寄存器值
* 调用方法: halSpiReadBurstReg();
* 调用函数: 
=========================================================*/
void halSpiReadBurstReg(Uint8 addr, Uint8 *buffer, Uint8 count)
{
	Uint8 i;
	CC_CS_LOW;	//CS enable
	i = 0;
	while(CC_SOMI_REG_IN)//wait for ccxxxx ready
	{
		f_MCU_FeedDog();
		TI_CC_WAIT(30*12);
		if (i ++ > 1000)
			break;
	}
	CC_SPI_TXBUF_SET(addr|TI_CCxxx0_READ_BURST);
	CC_SPI_WAIT_TXFIN;
	CC_SPI_RX_FLAG_CLR;
	for(i = 0; i < count; i++)
	{
		CC_SPI_RXBUF_READ(buffer[i]);//store data from last data RX
	}
	CC_CS_HIGH;
}
/*=========================================================
* 函 数 名: halSpiReadStatus()
* 功能描述: 读状态寄存器的值
* 调用方法: halSpiReadStatus();
* 调用函数: 
=========================================================*/
Uint8 halSpiReadStatus(Uint8 addr)
{
	Uint8 i_ReturnValue;	
	unsigned int i;
	CC_CS_LOW;//CS enable
	i = 0;
	while(CC_SOMI_REG_IN)//wait for ccxxxx ready
	{
		f_MCU_FeedDog();
		TI_CC_WAIT(30*12);
		if (i ++ > 1000)
			break;
	}
	CC_SPI_TXBUF_SET(addr|TI_CCxxx0_READ_BURST);
	CC_SPI_WAIT_TXFIN;
	CC_SPI_RXBUF_READ(i_ReturnValue);
	CC_CS_HIGH;
	return i_ReturnValue;
}
/*=========================================================
* 函 数 名: halSpiStrobe()
* 功能描述: 写状态寄存器的值
* 调用方法: halSpiStrobe();
* 调用函数: 
=========================================================*/
void halSpiStrobe(Uint8 strobe)
{
	unsigned int i;
	CC_CS_LOW;//CS enable
	i = 0;
	while(CC_SOMI_REG_IN)//wait for ccxxxx ready
	{
		f_MCU_FeedDog();
		TI_CC_WAIT(30*12);
		if (i ++ > 1000)
			break;
	}
	CC_SPI_TXBUF_SET(strobe);
	CC_SPI_WAIT_TXFIN;
	CC_CS_HIGH;
}
/*=========================================================
* 函 数 名: TI_CC_WAIT()
* 功能描述: 延时
* 调用方法: TI_CC_WAIT();
* 调用函数: 
=========================================================*/
void TI_CC_WAIT(Uint16 cycles)
{
	while(cycles>30)                          // 15 cycles consumed by overhead
	cycles = cycles - 6;                    // 6 cycles consumed each iteration
}
/*=========================================================
* 函 数 名: f_ResetCC2500()
* 功能描述: 复位CC2500芯片
* 调用方法: f_ResetCC2500();
* 调用函数: 
=========================================================*/
void f_ResetCC2500(void)
{
	CC_SPI_TXBUF_SET(TI_CCxxx0_SRES);//send strobe
}
/*=========================================================
* 函 数 名: halPowerupResetCCxxxx()
* 功能描述: CCxxxx上电初始化,返回1：失败，返回0：成功
* 调用方法: TI_CC_Wait();
* 调用函数: 
=========================================================*/
unsigned char halPowerupResetCCxxxx(void)
{
	unsigned int i;
	CC_UCLK_HIGH;																							//ADD
	CC_SIMO_LOW;
	CC_CS_LOW;
	TI_CC_WAIT(30*12);
	CC_CS_HIGH;
	TI_CC_WAIT(150*12);
	CC_CS_LOW;
	i = 0;
	while(CC_SOMI_REG_IN)//wait for ccxxxx ready
	{
		f_MCU_FeedDog();
		TI_CC_WAIT(30*12);
		if (i ++ > 1000)
			break;
	}
	if (i >= 1000)//fail
	{
		CC_CS_HIGH;
			return 1;
	}
	CC_SPI_TXBUF_SET(TI_CCxxx0_SRES);//send strobe
	CC_SPI_WAIT_TXFIN;
	i = 0;
	while(CC_SOMI_REG_IN)//wait for CCxxx ready
	{
		f_MCU_FeedDog();
		TI_CC_WAIT(30*12);
		if (i ++ > 1000)
			break;
	}
	if (i >= 1000)//fail
	{
		CC_CS_HIGH;
		return 1;
	}
	CC_CS_HIGH;
	return 0;	//success
}
/*=========================================================
* 函 数 名: HwSpiInit_BITBANG()
* 功能描述: 硬件SPI初始化端口
* 调用方法: HwSpiInit_BITBANG();
* 调用函数: 
=========================================================*/
void HwSpiInit_BITBANG(void)
{
	CC_CS_HIGH;
	CC_SIMO_LOW;
	CC_UCLK_LOW;
}
/*=========================================================
* 函 数 名: halSpiBitbangOut()
* 功能描述: 模拟spi写数据
* 调用方法: HwSpiInit_BITBANG();
* 调用函数: 
=========================================================*/
Uint8 halSpiBitbangOut(Uint8 data)
{
	Uint8 i;
	Uint8 rc = 0;
	for(i = 0; i < 8; i++)
	{
		CC_UCLK_LOW;	
		if (data&0x80)
		{
			CC_SIMO_HIGH;
		}
		else
		{
			CC_SIMO_LOW;
		}
		data <<= 1;
		CC_UCLK_HIGH;	
		TI_CC_WAIT(5);
		rc <<= 1;
		if (CC_SOMI_IN)
		{
			rc |= 1;
		}
		TI_CC_WAIT(10);
	}
	CC_UCLK_LOW;																							//clock low
	return rc;
}
/*=========================================================
* 函 数 名: halSpiBitbangOut()
* 功能描述: 模拟spi写数据
* 调用方法: HwSpiInit_BITBANG();
* 调用函数: 
=========================================================*/
Uint8 halSpiBitbangIn(void)
{
	Uint8 i;
	Uint8 data = 0;
	for(i = 0; i < 8; i++)
	{
		CC_UCLK_HIGH;	
		data <<= 1;
		if (CC_SOMI_IN)
		{
			data |= 1;
			TI_CC_WAIT(20);	//clock high
		}
		CC_UCLK_LOW;	
		TI_CC_WAIT(20);	//clock low
	}
	return data;
}


