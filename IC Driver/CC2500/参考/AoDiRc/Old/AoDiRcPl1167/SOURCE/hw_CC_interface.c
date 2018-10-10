#include "rf_hardware.h"
#include "my_rf_setting.h"
#include "hw_CC_reg.h"
#include "hw_cc_interface.h"
#include "hw_TI_CC.h" 
#include "Include.h"

/*=========================================================
* �� �� ��: halSpiWriteReg()
* ��������: ���ֽ�д��д����value��һ�������ĵ�ַ�Ĵ���addr
* ���÷���: halSpiWriteReg();
* ���ú���: 
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
* �� �� ��: halSpiWriteBurstReg()
* ��������: ����д�Ĵ���
* ���÷���: halSpiWriteReg();
* ���ú���: 
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
* �� �� ��: halSpiReadReg()
* ��������: ���Ĵ���ֵ
* ���÷���: halSpiReadReg();
* ���ú���: 
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
* �� �� ��: halSpiReadBurstReg()
* ��������: �������Ĵ���ֵ
* ���÷���: halSpiReadBurstReg();
* ���ú���: 
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
* �� �� ��: halSpiReadStatus()
* ��������: ��״̬�Ĵ�����ֵ
* ���÷���: halSpiReadStatus();
* ���ú���: 
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
* �� �� ��: halSpiStrobe()
* ��������: д״̬�Ĵ�����ֵ
* ���÷���: halSpiStrobe();
* ���ú���: 
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
* �� �� ��: TI_CC_WAIT()
* ��������: ��ʱ
* ���÷���: TI_CC_WAIT();
* ���ú���: 
=========================================================*/
void TI_CC_WAIT(Uint16 cycles)
{
	while(cycles>30)                          // 15 cycles consumed by overhead
	cycles = cycles - 6;                    // 6 cycles consumed each iteration
}
/*=========================================================
* �� �� ��: f_ResetCC2500()
* ��������: ��λCC2500оƬ
* ���÷���: f_ResetCC2500();
* ���ú���: 
=========================================================*/
void f_ResetCC2500(void)
{
	CC_SPI_TXBUF_SET(TI_CCxxx0_SRES);//send strobe
}
/*=========================================================
* �� �� ��: halPowerupResetCCxxxx()
* ��������: CCxxxx�ϵ��ʼ��,����1��ʧ�ܣ�����0���ɹ�
* ���÷���: TI_CC_Wait();
* ���ú���: 
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
* �� �� ��: HwSpiInit_BITBANG()
* ��������: Ӳ��SPI��ʼ���˿�
* ���÷���: HwSpiInit_BITBANG();
* ���ú���: 
=========================================================*/
void HwSpiInit_BITBANG(void)
{
	CC_CS_HIGH;
	CC_SIMO_LOW;
	CC_UCLK_LOW;
}
/*=========================================================
* �� �� ��: halSpiBitbangOut()
* ��������: ģ��spiд����
* ���÷���: HwSpiInit_BITBANG();
* ���ú���: 
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
* �� �� ��: halSpiBitbangOut()
* ��������: ģ��spiд����
* ���÷���: HwSpiInit_BITBANG();
* ���ú���: 
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


