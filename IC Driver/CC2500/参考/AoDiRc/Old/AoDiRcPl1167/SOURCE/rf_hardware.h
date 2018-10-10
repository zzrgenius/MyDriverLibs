#ifndef RF_HARDWARE_H
#define RF_HARDWARE_H

//****************************************************************************
// 宏定义
//****************************************************************************/
#define Uint8  unsigned char
#define BYTE unsigned char
#define Uint16 unsigned int
#define int8	char
#define int16	 int

//chipcon */
#define RF_FRQ    2400														//2.4G 不能加入M,加入报错误
//#define RF_BAND   10000 												//10K
#define RF_BAND		2400														//2.4K

#define  __SPI_INTF_BITBANG__

#ifdef  __SPI_INTF_BITBANG__ 
extern Uint8 halSpiBitbangOut(Uint8 data);
extern Uint8 halSpiBitbangIn(void);
extern void HwSpiInit_BITBANG(void);

#define HW_SPI_RXBUF_BITBANG
#define HW_SPI_TXBUF_BITBANG

#define HW_SPI_WAIT_RXFIN_BITBANG   		asm("nop")
#define HW_SPI_WAIT_TXFIN_BITBANG   		asm("nop")
#define HW_SPI_WAIT_TXBUF_BITBANG   		asm("nop")
#define HW_SPI_TXBUF_SET_BITBANG(x) 		halSpiBitbangOut((x))
#define HW_SPI_RXBUF_READ_BITBANG(x) 		(x) = halSpiBitbangIn() 
#endif

#ifdef  __SPI_INTF_BITBANG__
#define     CC_SPI_WAIT_RXFIN           HW_SPI_WAIT_RXFIN_BITBANG  
#define     CC_SPI_WAIT_TXFIN           HW_SPI_WAIT_TXFIN_BITBANG  
#define     CC_SPI_WAIT_TXBUF           HW_SPI_WAIT_TXBUF_BITBANG  
#define     CC_SPI_TXBUF_SET(x)         HW_SPI_TXBUF_SET_BITBANG(x)
#define     CC_SPI_RXBUF_READ(x)        HW_SPI_RXBUF_READ_BITBANG(x)
#define     CC_SPI_RX_FLAG_CLR          
#endif
//----------------------------------------------------
// Spi IO define*/                  
#define CC_SOMI_REG_IN			_pc1
#define CC_SOMI_IN				_pc1
#define CC_GDO0_IN           	_pb0

#define CC_UCLK_HIGH			(_pb1 = 1)
#define CC_UCLK_LOW				(_pb1 = 0)
#define CC_SIMO_HIGH			(_pb2 = 1)
#define CC_SIMO_LOW				(_pb2 = 0)

#define CC_CS_HIGH       		(_pc2 = 1)	        
#define CC_CS_LOW              	(_pc2 = 0)

//#define GDO2_HIGH_WAIT           while(!PC_IN4)
//#define GDO2_LOW_WAIT            while(PC_IN4)

#endif //  __RF_HARDWARE_H__

