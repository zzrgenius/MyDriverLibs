#define VAR_CC2500_GLOBALS
#include "Include.h"

/*=========================================================
* 功能描述: Delay延时函数
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_Delay(uint rTime)
{
	uint i;
	for(i =0; i < rTime;i++)
	{
		NOP();
	}
}

/*=========================================================
* 功能描述: 模拟spi写数据
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar sSpiWrite(uchar data)
{
	uchar i;
	uchar rc = 0;
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
		rc <<= 1;
		if (CC_SOMI_IN)
		{
			rc |= 1;
		}
	}
	CC_UCLK_LOW;																							//clock low
	return rc;
}

/*=========================================================
* 功能描述:  模拟spi读数据
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar sSpiRead(void)
{
	uchar i;
	uchar data = 0;
	for(i = 0; i < 8; i++)
	{
		CC_UCLK_HIGH;	
		data <<= 1;
		if (CC_SOMI_IN)
		{
			data |= 1;
		}
		CC_UCLK_LOW;	
	}
	return data;
}

/*=========================================================
* 功能描述: 单字节写
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void sSpiWriteByte(uchar addr,uchar value)
{
	uint i;
	CC_CS_LOW;
	i = 0;
	while(CC_SOMI_IN)
	{
		//f_McuFeedDog();
		f_Delay(20);
		if (i ++ > 1000)
			break;
	}
	sSpiWrite(addr&0x7F);																		//wait for tx to finish
	sSpiWrite(value);
	CC_CS_HIGH;
}

/*=========================================================
* 功能描述: 连续写寄存器
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void sSpiWriteMore(uchar addr, uchar *buffer, uchar count)
{
	uint i;
	CC_CS_LOW;
	i = 0;
	while(CC_SOMI_IN)
	{
		//f_McuFeedDog();
		f_Delay(20);
		if (i ++ > 1000)
			break;
	}
	sSpiWrite(addr|TI_CCxxx0_WRITE_BURST);
	for(i = 0; i < count; i++)
	{
		sSpiWrite(buffer[i]);
	}
	CC_CS_HIGH;
}

/*=========================================================
* 功能描述: 读寄存器值
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar sSpiReadByte(uchar addr)
{
	uchar i_ReturnValue;
	uint i;
	CC_CS_LOW;
	i = 0;
	while(CC_SOMI_IN)
	{
		//f_McuFeedDog();
		f_Delay(20);
		if (i ++ > 1000)
			break;
	}
	sSpiWrite(addr|TI_CCxxx0_READ_SINGLE);							
	i_ReturnValue = sSpiRead();
	CC_CS_HIGH;
	return i_ReturnValue;
}

/*=========================================================
* 功能描述: 连续读寄存器值
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void sSpiReadMore(uchar addr, uchar *buffer, uchar count)
{
	uchar i;
	CC_CS_LOW;
	i = 0;
	while(CC_SOMI_IN)
	{
		//f_McuFeedDog();
		f_Delay(20);
		if (i ++ > 1000)
			break;
	}
	sSpiWrite(addr|TI_CCxxx0_READ_BURST);
	for(i = 0; i < count; i++)
	{
		buffer[i] = sSpiRead();
	}
	CC_CS_HIGH;
}

/*=========================================================
* 功能描述: 读状态寄存器的值
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar sSpiReadStatus(uchar addr)
{
	uchar i_ReturnValue;	
	uint i;
	CC_CS_LOW;
	i = 0;
	while(CC_SOMI_IN)
	{
		//f_McuFeedDog();
		f_Delay(20);
		if (i ++ > 1000)
			break;
	}
	sSpiWrite(addr|TI_CCxxx0_READ_BURST);
	i_ReturnValue = sSpiRead();
	CC_CS_HIGH;
	return i_ReturnValue;
}

/*=========================================================
* 功能描述: 写状态寄存器的值
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void sSpiWriteStatus(uchar strobe)
{
	uint i;
	CC_CS_LOW;
	i = 0;
	while(CC_SOMI_IN)
	{
		//f_McuFeedDog();
		f_Delay(20);
		if (i ++ > 1000)
			break;
	}
	sSpiWrite(strobe);
	CC_CS_HIGH;
}

/*=========================================================
* 功能描述: CC2500寄存器配置
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar CC2500_Settings_250k(unsigned char rf_channel) 
//uchar halRfConfig(const HAL_RF_CONFIG* rfConfig, const uchar* rfPaTable, const uchar rfPaTableLen)
{
	//2401MHz  Datarate=250Kbps  MSK  Dev=38.085938KHz  BW=541.666667KHz 
	sSpiWriteByte(TI_CCxxx0_FSCTRL1, 0x0A);// Frequency synthesizer control.
	sSpiWriteByte(TI_CCxxx0_FSCTRL0, 0x00);// Frequency synthesizer control.
	sSpiWriteByte(TI_CCxxx0_FREQ2, 0x5C);// Frequency control word, high byte.
	sSpiWriteByte(TI_CCxxx0_FREQ1, 0x58);// Frequency control word, middle byte.
	sSpiWriteByte(TI_CCxxx0_FREQ0, 0x9D);// Frequency control word, low byte.		
	sSpiWriteByte(TI_CCxxx0_MDMCFG4, 0x2D);// Modem configuration.
	sSpiWriteByte(TI_CCxxx0_MDMCFG3, 0x3B);// Modem configuration. 
	sSpiWriteByte(TI_CCxxx0_MDMCFG2, 0x73);// Modem configuration.	//2-fsk
	// Disables Manchester encoding/decoding.
	sSpiWriteByte(TI_CCxxx0_MDMCFG1, 0x23);// Modem configuration.  333.33KHz 
	sSpiWriteByte(TI_CCxxx0_MDMCFG0, 0xa4);// Modem configuration.
	sSpiWriteByte(TI_CCxxx0_CHANNR, rf_channel);// Channel number.
	sSpiWriteByte(TI_CCxxx0_DEVIATN, 0x00);// Modem deviation setting (when FSK modulation is enabled).
	sSpiWriteByte(TI_CCxxx0_FREND1, 0xB6);// Front end RX configuration.
	sSpiWriteByte(TI_CCxxx0_FREND0, 0x10);// Front end TX configuration.
	sSpiWriteByte(TI_CCxxx0_MCSM1, 0x30);//
	sSpiWriteByte(TI_CCxxx0_MCSM0, 0x08);//0X18 Never (manually calibrate using SCAL strobe)
	sSpiWriteByte(TI_CCxxx0_FOCCFG, 0x1D);// Frequency Offset Compensation Configuration.
	sSpiWriteByte(TI_CCxxx0_BSCFG, 0x1C);// Bit synchronization Configuration.
	sSpiWriteByte(TI_CCxxx0_AGCCTRL2, 0xC7);// AGC control.
	sSpiWriteByte(TI_CCxxx0_AGCCTRL1, 0x00);// AGC control.
	sSpiWriteByte(TI_CCxxx0_AGCCTRL0, 0xB0);// AGC control.
	sSpiWriteByte(TI_CCxxx0_FSCAL3, 0xEA);// Frequency synthesizer calibration.
	sSpiWriteByte(TI_CCxxx0_FSCAL2, 0x0A);// Frequency synthesizer calibration.
	sSpiWriteByte(TI_CCxxx0_FSCAL1, 0x00);// Frequency synthesizer calibration.
	sSpiWriteByte(TI_CCxxx0_FSCAL0, 0x11);// Frequency synthesizer calibration.
	sSpiWriteByte(TI_CCxxx0_FSTEST, 0x59);// Frequency synthesizer calibration.
	sSpiWriteByte(TI_CCxxx0_TEST2, 0x88);// Various test settings.
	sSpiWriteByte(TI_CCxxx0_TEST1, 0x31);// Various test settings.
	sSpiWriteByte(TI_CCxxx0_TEST0, 0x0B);// Various test settings.
	sSpiWriteByte(TI_CCxxx0_IOCFG2, 0x06);//Asserts when sync word has been sent / received, and de-asserts at the end of the packet. 
	sSpiWriteByte(TI_CCxxx0_IOCFG0, 0x06);//In RX, the pin will de-assert when the optional address check fails or the RX FIFO overflows.
	sSpiWriteByte(TI_CCxxx0_IOCFG1, 0x06);//In TX the pin will de-assert if the TX FIFO underflows.
	sSpiWriteByte(TI_CCxxx0_PKTCTRL1, 0x04);//Packet Automation Control No address check
	sSpiWriteByte(TI_CCxxx0_PKTCTRL0, 0x45);//Packet Automation Control
	//bit6 = 1: Turn data whitening on
	//Variable packet length mode. Packet length
	//configured by the first byte after sync word
	//Whitening off  Bit6              //CRC calculation in TX and CRC check in RX enabled
	//Normal mode, use FIFOs for RX and TX
	sSpiWriteByte(TI_CCxxx0_ADDR, 0x00);
	sSpiWriteByte(TI_CCxxx0_PKTLEN, 0xFF); 
	sSpiWriteByte(TI_CCxxx0_PATABLE, 0xFF);//配置功率  +1dBm	
	//CC2500  CC1101该寄存器的值都是一样的设定值
	if(sSpiReadByte(TI_CCxxx0_MDMCFG3) != 0x3B)return TRUE;
	return FALSE;     		//如果是初始化成功就返回FALSE
}

/*=========================================================
* 功能描述: 硬件SPI初始化端口
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void sSpiInitIO(void)
{
	CC_CS_HIGH;
	CC_SIMO_LOW;
	CC_UCLK_LOW;
}

/*=========================================================
* 功能描述: 设置外部中断
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void sSetInterrupt(void)
{
}

/*=========================================================
* 功能描述: 睡眠模式
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/     
void f_SleepCC2500(void)
{ 
	sSpiWriteStatus(TI_CCxxx0_SIDLE);
	sSpiWriteStatus(TI_CCxxx0_SPWD);
} 

/*=========================================================
* 功能描述: 配置为接收模式
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_RxCC2500(void)                  
{                    
	sSpiWriteStatus(TI_CCxxx0_SIDLE);
	sSpiWriteStatus(TI_CCxxx0_SFRX);
	sSpiWriteStatus(TI_CCxxx0_SRX);
} 

/*=========================================================
* 功能描述: 发送包
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_SendPacket(uchar *txBuffer, uchar size)       
{
	uint j=0;
	sSpiWriteStatus(TI_CCxxx0_SIDLE);
	sSpiWriteStatus(TI_CCxxx0_SFTX);
	sSpiWriteMore(TI_CCxxx0_TXFIFO,txBuffer,size);
	sSpiWriteStatus(TI_CCxxx0_STX);
	j=800;
	//while(!CC2500_SO)//需要330us才 最多等1ms
	while(!CC_SOMI_IN)
	{
		if(j-- == 0)break; 
	}
	j=2400;
	//while(CC2500_SO)//250Kbps 64Bytes*8=512Bits 约2ms发射完成，这里最多等3ms
	while(CC_SOMI_IN)
	{
		if(j-- == 0)break; 
	}
	//发送完成后自动进入IDLE状态
	return 0;
} 

/*=========================================================
* 功能描述: 接收包
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar halRfReceivePacket(uchar *rxBuffer, uchar *length)
{
	uchar status[2],packetLength,nTemp;
	nTemp = sSpiReadStatus(TI_CCxxx0_RXBYTES);
	if (nTemp & TI_CCxxx0_NUM_RXBYTES)
	{
		packetLength = sSpiReadByte(TI_CCxxx0_RXFIFO);//读包长度
		if (packetLength <= 62)
		{
			sSpiReadMore(TI_CCxxx0_RXFIFO,rxBuffer,packetLength);
			*length = packetLength;
			sSpiReadMore(TI_CCxxx0_RXFIFO,status,2);//read 2 appended status bytes (status[0]=RSSI,status[1]=LQI)
			sSpiWriteStatus(TI_CCxxx0_SFRX);
			if (status[1] & TI_CCxxx0_CRC_OK)
			{
				return 1;
			}
			else
			{
				f_RxCC2500();
				return 0;
			}
		}
		else
		{
			*length = 0;								
			f_RxCC2500();
			return 0;
		}  
	}
	else
	{
		*length = 0;										
		f_RxCC2500();
		return 0;
	}
}

/*=========================================================
* 功能描述: 上电初始化,返回1：失败，返回0：成功
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar sPowerReset(void)
{
	uint i;
	CC_UCLK_HIGH;																							//ADD
	CC_SIMO_LOW;
	CC_CS_LOW;
	f_Delay(20);
	CC_CS_HIGH;
	f_Delay(20000);
	CC_CS_LOW;
	i = 0;
	while(CC_SOMI_IN)
	{
		//f_McuFeedDog();
		f_Delay(20);
		if (i ++ > 1000)
			break;
	}
	if (i >= 1000)
	{
		CC_CS_HIGH;
			return 1;
	}
	sSpiWrite(TI_CCxxx0_SRES);
	f_Delay(20000);
	i = 0;
	while(CC_SOMI_IN)
	{
		//f_McuFeedDog();
		f_Delay(20);
		if (i ++ > 1000)
			break;
	}
	if (i >= 1000)
	{
		CC_CS_HIGH;
		return 1;
	}
	CC_CS_HIGH;
	return 0;	
}

/*=========================================================
* 功能描述: CC2500初始化
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar f_InitCC2500(uchar Channel)
{
	uchar nTemp;
	sSpiInitIO();	
	if(sPowerReset())return TRUE;//复位 
	if(CC2500_Settings_250k(Channel))return TRUE;
	sSetInterrupt();
	//f_RxCC2500();
	sSpiWriteStatus(TI_CCxxx0_SIDLE);
	sSpiWriteStatus(TI_CCxxx0_SCAL);//检验
	f_Delay(20000);
	return FALSE;
} 

/*=========================================================
* 功能描述: CC2500通道变更
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void SetCC2500_ChannelNumber(uchar number)
{
	sSpiWriteStatus(TI_CCxxx0_SIDLE);
	sSpiWriteByte(TI_CCxxx0_CHANNR, number);// Channel number.
	sSpiWriteStatus(TI_CCxxx0_SCAL);//检验
	//f_Delay(20000);
}
/*=========================================================
* 功能描述: CC2500重复初始化
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_ResetInit(void)
{
	if(Cc2500Inf.nCC2500ErrFlag == true)
	{
		Cc2500Inf.nCC2500ErrFlag = 0;
		//PB_CR2 = 0x00; //PE1外部中断
		//f_InitCC2500();			
	}
}
