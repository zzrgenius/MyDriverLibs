#include "rf_hardware.h"
#include "my_rf_setting.h"
#include "hw_CC_reg.h"
#include "hw_cc_interface.h"
#include "hw_TI_CC.h" 
#include "Include.h"
  
u_SYS_STAT0 SysState0;
unsigned char Buffer[15];
/*=========================================================
* 函 数 名: halRfConfig()
* 功能描述: CC1101寄存器配置
* 调用方法: halRfConfig();
* 调用函数: 
=========================================================*/
unsigned char halRfConfig(const HAL_RF_CONFIG* rfConfig, const Uint8* rfPaTable, const Uint8 rfPaTableLen)
{
	Uint8 i;
	halSpiWriteReg(TI_CCxxx0_FSCTRL1,  rfConfig->fsctrl1);    // Frequency synthesizer control.
	halSpiWriteReg(TI_CCxxx0_FSCTRL0,  rfConfig->fsctrl0);    // Frequency synthesizer control.
	halSpiWriteReg(TI_CCxxx0_FREQ2,    rfConfig->freq2);      // Frequency control word, high byte.
	halSpiWriteReg(TI_CCxxx0_FREQ1,    rfConfig->freq1);      // Frequency control word, middle byte.
	halSpiWriteReg(TI_CCxxx0_FREQ0,    rfConfig->freq0);      // Frequency control word, low byte.
	halSpiWriteReg(TI_CCxxx0_MDMCFG4,  rfConfig->mdmcfg4);    // Modem configuration.
	halSpiWriteReg(TI_CCxxx0_MDMCFG3,  rfConfig->mdmcfg3);    // Modem configuration.
	halSpiWriteReg(TI_CCxxx0_MDMCFG2,  rfConfig->mdmcfg2);    // Modem configuration.
	halSpiWriteReg(TI_CCxxx0_MDMCFG1,  rfConfig->mdmcfg1);    // Modem configuration.
	halSpiWriteReg(TI_CCxxx0_MDMCFG0,  rfConfig->mdmcfg0);    // Modem configuration.
	halSpiWriteReg(TI_CCxxx0_CHANNR,   rfConfig->channr);     // Channel number.
	halSpiWriteReg(TI_CCxxx0_DEVIATN,  rfConfig->deviatn);    // Modem deviation setting (when FSK modulation is enabled).
	halSpiWriteReg(TI_CCxxx0_FREND1,   rfConfig->frend1);     // Front end RX configuration.
	halSpiWriteReg(TI_CCxxx0_FREND0,   rfConfig->frend0);     // Front end RX configuration.
	halSpiWriteReg(TI_CCxxx0_MCSM1,    rfConfig->mcsm1);      //ADD  	
	halSpiWriteReg(TI_CCxxx0_MCSM0,    rfConfig->mcsm0);      // Main Radio Control State Machine configuration.
	halSpiWriteReg(TI_CCxxx0_FOCCFG,   rfConfig->foccfg);     // Frequency Offset Compensation Configuration.
	halSpiWriteReg(TI_CCxxx0_BSCFG,    rfConfig->bscfg);      // Bit synchronization Configuration.
	halSpiWriteReg(TI_CCxxx0_AGCCTRL2, rfConfig->agcctrl2);   // AGC control.
	halSpiWriteReg(TI_CCxxx0_AGCCTRL1, rfConfig->agcctrl1);   // AGC control.
	halSpiWriteReg(TI_CCxxx0_AGCCTRL0, rfConfig->agcctrl0);   // AGC control.
	halSpiWriteReg(TI_CCxxx0_FSCAL3,   rfConfig->fscal3);     // Frequency synthesizer calibration.
	halSpiWriteReg(TI_CCxxx0_FSCAL2,   rfConfig->fscal2);     // Frequency synthesizer calibration.
	halSpiWriteReg(TI_CCxxx0_FSCAL1,   rfConfig->fscal1);     // Frequency synthesizer calibration.
	halSpiWriteReg(TI_CCxxx0_FSCAL0,   rfConfig->fscal0);     // Frequency synthesizer calibration.
	halSpiWriteReg(TI_CCxxx0_FSTEST,   rfConfig->fstest);     // Frequency synthesizer calibration.
	halSpiWriteReg(TI_CCxxx0_TEST2,    rfConfig->test2);      // Various test settings.
	halSpiWriteReg(TI_CCxxx0_TEST1,    rfConfig->test1);      // Various test settings.
	halSpiWriteReg(TI_CCxxx0_TEST0,    rfConfig->test0);      // Various test settings.
	halSpiWriteReg(TI_CCxxx0_IOCFG2,   rfConfig->iocfg2);     // GDO2 output pin configuration.
	halSpiWriteReg(TI_CCxxx0_IOCFG0,   rfConfig->iocfg0);     // GDO0 output pin configuration.
	halSpiWriteReg(TI_CCxxx0_IOCFG1,   rfConfig->iocfg1); 		//GDO1 ADD
	halSpiWriteReg(TI_CCxxx0_PKTCTRL1, rfConfig->pktctrl1);   // Packet automation control.
	halSpiWriteReg(TI_CCxxx0_PKTCTRL0, rfConfig->pktctrl0);   // Packet automation control.
	halSpiWriteReg(TI_CCxxx0_ADDR,     rfConfig->addr);       // Device address.
	halSpiWriteReg(TI_CCxxx0_PKTLEN,   rfConfig->pktlen);     // Packet length.
	halSpiWriteBurstReg(TI_CCxxx0_PATABLE | TI_CCxxx0_WRITE_BURST, (Uint8 *)rfPaTable, rfPaTableLen);
	//CC2500  CC1101该寄存器的值都是一样的设定值   
	i = halSpiReadReg(TI_CCxxx0_MDMCFG3);
	if(i != 0x83)
	{
		return 1;    
	}
	else
	{
		return 0;     		//如果是初始化成功就返回FALSE 
	} 
}
/*=========================================================
* 函 数 名: halRfConfig()
* 功能描述: CC1101寄存器配置
* 调用方法: halRfConfig();
* 调用函数: 
=========================================================*/
void halRfReceiveSet(void)
{
	halSpiStrobe(TI_CCxxx0_SIDLE);
	f_MCU_FeedDog();
	halSpiStrobe(TI_CCxxx0_SFRX);
	TI_CC_WAIT(100);
	halSpiStrobe(TI_CCxxx0_SRX);
}
/*=========================================================
* 函 数 名: halRfConfig()
* 功能描述: GDO0=1,sync recevied,GDO0=0,end of packet
* 调用方法: halRfConfig();
* 调用函数: 
=========================================================*/
Uint8 halRfReceivePacket(Uint8 *rxBuffer, Uint8 *length)
{
	Uint8 status[2];
	Uint8 packetLength;
	Uint8 nTemp;
	nTemp = halSpiReadStatus(TI_CCxxx0_RXBYTES);
	if (nTemp & TI_CCxxx0_NUM_RXBYTES)
	{
		//read length byte
		packetLength = halSpiReadReg(TI_CCxxx0_RXFIFO);
		//read data from rx fifo and store in rxbuffer
		if (packetLength <= 62)
		{
			halSpiReadBurstReg(TI_CCxxx0_RXFIFO,rxBuffer,packetLength);
			*length = packetLength;
			//read 2 appended status bytes (status[0]=RSSI,status[1]=LQI)
			halSpiReadBurstReg(TI_CCxxx0_RXFIFO,status,2);
			//Flush rx fifo
			halSpiStrobe(TI_CCxxx0_SFRX);
			if (status[1] & TI_CCxxx0_CRC_OK)
			{
				return 1;
			}
			else
			{
				halSpiStrobe(TI_CCxxx0_SIDLE);		
				//flush rx fifo
				halSpiStrobe(TI_CCxxx0_SFRX);
				halSpiStrobe(TI_CCxxx0_SRX);
				return 0;
			}
		}
		else
		{
			*length = 0;								
			halSpiStrobe(TI_CCxxx0_SIDLE);		
			//flush rx fifo
			halSpiStrobe(TI_CCxxx0_SFRX);
			halSpiStrobe(TI_CCxxx0_SRX);
			return 0;
		}  
	}
	else
	{
		*length = 0;										
		halSpiStrobe(TI_CCxxx0_SIDLE);		
		//flush rx fifo
		halSpiStrobe(TI_CCxxx0_SFRX);
		halSpiStrobe(TI_CCxxx0_SRX);
		return 0;
	}
}
/*=========================================================
* 函 数 名: GDO0_HIGH_WAIT()
* 功能描述: wait for GDO0 to be set -> sync transmitted
* 调用方法: GDO0_HIGH_WAIT();
* 调用函数: 
=========================================================*/
Uint8 GDO0_HIGH_WAIT(Uint16 x)
{
	while(!(CC_GDO0_IN) && (x))
	{
		x--;      
		f_MCU_FeedDog();
		TI_CC_WAIT(100);
	}
	if(x)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*=========================================================
* 函 数 名: GDO0_LOW_WAIT()
* 功能描述: wait for GDO0 to be cleared -> end of packet
* 调用方法: GDO0_LOW_WAIT();
* 调用函数: 
=========================================================*/
Uint8 GDO0_LOW_WAIT(Uint16 x)
{
	while((CC_GDO0_IN) && (x))
	{
		x--;
		f_MCU_FeedDog();
		TI_CC_WAIT(100);
	}
	if (x)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
/*=========================================================
* 函 数 名: halRfSendPacket()
* 功能描述: The function implements polling of GDO0. First it waits for GD00 to be 
						set and then it waits for it to be cleared.
						This function can be used to transmit a packet with packet length up to 63 bytes
* 调用方法: halRfSendPacket();
* 调用函数: 
=========================================================*/
Uint8 halRfSendPacket(Uint8 *txBuffer, Uint8 size)       
{
	Uint8 rc;
	halSpiStrobe(TI_CCxxx0_SIDLE);	//for long time transmit reliable
	halSpiStrobe(TI_CCxxx0_SFTX);//test
	halSpiWriteBurstReg(TI_CCxxx0_TXFIFO,txBuffer,size);
	halSpiStrobe(TI_CCxxx0_STX);
	return rc;
}                                 


/*=========================================================
* 函 数 名: RF_RX()
* 功能描述: CC1101设置为接收状态
* 调用方法: RF_RX();
* 输    入：无
* 输    出：无
=========================================================*/
void RF_RX(void)                  
{                    
	Uint8 rc;         
	halRfReceiveSet();            
	SysState0.mbit.RFRxState = 1;
} 
/*=========================================================
* 函 数 名: RFSleep()
* 功能描述: CC1101设置为睡眠状态
* 调用方法: RFSleep();
* 输    入：无
* 输    出：无
=========================================================*/       
void RFSleep(void)
{ 
	halSpiStrobe(TI_CCxxx0_SIDLE);
	halSpiStrobe(TI_CCxxx0_SPWD);
}  
/*=========================================================
* 函 数 名: RFWorRegSet()
* 功能描述: CC1101Wor寄存器设置
* 调用方法: RFWorRegSet();
* 输    入：无
* 输    出：无
=========================================================*/ 
void RFWorRegSet(void)
{ 
	halSpiWriteReg(TI_CCxxx0_MDMCFG1,0x02); //2 byte 前导码 （唤醒帧为2byte前导码）
#if 1
	halSpiWriteReg(TI_CCxxx0_WORCTRL,     0x38);    //ENENT1=3  and   WOR_RES=0
	halSpiWriteReg(TI_CCxxx0_MCSM2,       0x05);    //RX_TIME=5 0.391%;
	halSpiWriteReg(TI_CCxxx0_WOREVT1,     0xff);    //ENENT = 65536
	halSpiWriteReg(TI_CCxxx0_WOREVT0,     0xff);
#endif
#if 0
	halSpiWriteReg(TI_CCxxx0_WORCTRL,   0x39); // ENENT1=3 and  WOR_RES=1
	halSpiWriteReg(TI_CCxxx0_MCSM2,     0x00); //RX_TIME=0; 
	halSpiWriteReg(TI_CCxxx0_WOREVT1,   0x03); //ENENT0=10400
	halSpiWriteReg(TI_CCxxx0_WOREVT0,   0x20); //此时接收占空比为1.95%，事件0周期为9.6S
#endif	
	halSpiWriteReg(TI_CCxxx0_IOCFG2,      0x24);  //test for wor
}   
/*=========================================================
* 函 数 名: RFWorRegReset()
* 功能描述: CC1101Wor寄存器复位
* 调用方法: RFWorRegReset();
* 输    入：无
* 输    出：无
=========================================================*/   
void RFWorRegReset(void)
{ 
	halSpiWriteReg(TI_CCxxx0_WORCTRL,0xF8);    //[7] RC_PD 重新置1，退出wor准备RX 
	halSpiWriteReg(TI_CCxxx0_MDMCFG1,0x22); //4 byte 前导码（数据帧为4byte前导码）  
}   
/*=========================================================
* 函 数 名: RFWorOn()
* 功能描述: CC1101Wor上电
* 调用方法: RFWorOn();
* 输    入：无
* 输    出：无
=========================================================*/     
void RFWorOn(void)
{
	halSpiStrobe(TI_CCxxx0_SIDLE);
	halSpiStrobe(TI_CCxxx0_SWOR);
}  

void f_SetExternInterrupt(void)
{
	/*PB_DDR &= ~0x20;   //设置PE1输入  
	PB_CR2 = 0x20; //PE1外部中断
	EXTI_CR1 |= 0x08;//PB口下降沿中断*/
}
/*=========================================================
* 函 数 名: f_InitCC2500()
* 功能描述: CC2500初始化
* 调用方法: f_InitCC2500();
* 输    入：无
* 输    出：无
=========================================================*/
void f_InitCC2500(void)
{
	unsigned char nTemp;
	HwSpiInit_BITBANG();	
	nTemp = halPowerupResetCCxxxx(); 
	if (nTemp == 1)																						//失败
	{
		return;
	} 
	nTemp = halRfConfig((const HAL_RF_CONFIG*)&myRfConfig,myPaTable,myPaTableLen);
	if (nTemp == 1)																						//失败
	{
		return;
	}
	f_SetExternInterrupt();
	//RF_RX();
} 

