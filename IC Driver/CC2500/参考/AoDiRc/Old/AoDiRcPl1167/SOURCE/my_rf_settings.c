#include "rf_hardware.h"
#include "my_rf_setting.h"  

/*************************************************************
 Í·ÎÄ¼þ
***************************************************************************/

#if (RF_FRQ == 2400)
  #if (RF_BAND == 2400)
	const HAL_RF_CONFIG myRfConfig = {
	  	0x08,  // FSCTRL1       Frequency Synthesizer Control
	    0x00,  // FSCTRL0       Frequency Synthesizer Control
	    0x5D,  // FREQ2         Frequency Control Word, High Byte  5C
	    0x93,  // FREQ1         Frequency Control Word, Middle Byte 41
	    0xB1,  // FREQ0         Frequency Control Word, Low Byte C0
	    0x86,  // MDMCFG4       Modem Configuration			0x86:2400,0X87:4800 
	    0x83,  // MDMCFG3       Modem Configuration
	   	0x13,  // MDMCFG2       Modem Configuration
	    0x22,  // MDMCFG1       Modem Configuration
	    0xF8,  // MDMCFG0       Modem Configuration
	    0x00,  // CHANNR        Channel Number   2014-04-24 0X06
	    0x44,  // DEVIATN       Modem Deviation Setting 
	    0x56,  // FREND1        Front End RX Configuration
	    0x10,  // FREND0        Front End TX Configuration
	    
	    0x30,	 // MCSM1					ADD
	    0x18,  // MCSM0         Main Radio Control State Machine Configuration
	    
	    0x16,  // FOCCFG        Frequency Offset Compensation Configuration
	    0x6C,  // BSCFG         Bit Synchronization Configuration
	    0x03,  // AGCCTRL2      AGC Control
	    0x40,  // AGCCTRL1      AGC Control
	    0x91,  // AGCCTRL0      AGC Control
	    0xA9,  // FSCAL3        Frequency Synthesizer Calibration
	    0x0A,  // FSCAL2        Frequency Synthesizer Calibration
	    0x00,  // FSCAL1        Frequency Synthesizer Calibration
	    0x11,  // FSCAL0        Frequency Synthesizer Calibration
	    0x59,  // FSTEST        Frequency Synthesizer Calibration Control
	    0x88,  // TEST2         Various Test Settings
	    0x31,  // TEST1         Various Test Settings
	    0x0B,  // TEST0         Various Test Settings
	    
	    //0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
	    0x06,  // IOCFG2        GDO2 Output Pin Configuration
	    0x06,  // IOCFG1				ADD   
	    0x06,  // IOCFG0        GDO0 Output Pin Configuration
	    
	    0x04,  // PKTCTRL1      Packet Automation Control
	    0x05,  // PKTCTRL0      Packet Automation Control
	    0x00,  // ADDR          Device Address
	    0xFF,  // PKTLEN        Packet Length
	};
const HAL_RF_CONFIG myRfConfigSleep = {
	  	0x08,  // FSCTRL1       Frequency Synthesizer Control
	    0x00,  // FSCTRL0       Frequency Synthesizer Control
	    0x5D,  // FREQ2         Frequency Control Word, High Byte  5C
	    0x93,  // FREQ1         Frequency Control Word, Middle Byte 41
	    0xB1,  // FREQ0         Frequency Control Word, Low Byte C0
	    0x86,  // MDMCFG4       Modem Configuration			0x86:2400,0X87:4800 
	    0x83,  // MDMCFG3       Modem Configuration
	   	0x13,  // MDMCFG2       Modem Configuration
	    0x22,  // MDMCFG1       Modem Configuration
	    0xF8,  // MDMCFG0       Modem Configuration
	    0x00,  // CHANNR        Channel Number   2014-04-24 0X06
	    0x44,  // DEVIATN       Modem Deviation Setting 
	    0x56,  // FREND1        Front End RX Configuration
	    0x10,  // FREND0        Front End TX Configuration
	    
	    0x30,	 // MCSM1					ADD
	    0x18,  // MCSM0         Main Radio Control State Machine Configuration
	    
	    0x16,  // FOCCFG        Frequency Offset Compensation Configuration
	    0x6C,  // BSCFG         Bit Synchronization Configuration
	    0x03,  // AGCCTRL2      AGC Control
	    0x40,  // AGCCTRL1      AGC Control
	    0x91,  // AGCCTRL0      AGC Control
	    0xA9,  // FSCAL3        Frequency Synthesizer Calibration
	    0x0A,  // FSCAL2        Frequency Synthesizer Calibration
	    0x00,  // FSCAL1        Frequency Synthesizer Calibration
	    0x11,  // FSCAL0        Frequency Synthesizer Calibration
	    0x59,  // FSTEST        Frequency Synthesizer Calibration Control
	    0x88,  // TEST2         Various Test Settings
	    0x31,  // TEST1         Various Test Settings
	    0x0B,  // TEST0         Various Test Settings
	    
	    //0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
	    0x06,  // IOCFG2        GDO2 Output Pin Configuration
	    0x6F,  // IOCFG1				ADD   0X06
	    0x6F,  // IOCFG0        GDO0 Output Pin Configuration  0x06
	    
	    0x04,  // PKTCTRL1      Packet Automation Control
	    0x05,  // PKTCTRL0      Packet Automation Control
	    0x00,  // ADDR          Device Address
	    0xFF,  // PKTLEN        Packet Length
	};
	const Uint8 myPaTable[] = {0xFE};					//2014-04-24 0XFF
	const Uint8 myPaTableLen = 1;
	#endif             
#endif

// chipcon reg define*/
#if (RF_FRQ == 2400)
  #if (RF_BAND == 10000)
	const HAL_RF_CONFIG myRfConfig = {
	    0x06,  // FSCTRL1       Frequency Synthesizer Control
	    0x00,  // FSCTRL0       Frequency Synthesizer Control
	    0x5D,  // FREQ2         Frequency Control Word, High Byte
	    0x93,  // FREQ1         Frequency Control Word, Middle Byte
	    0xB1,  // FREQ0         Frequency Control Word, Low Byte
	    0x78,  // MDMCFG4       Modem Configuration
	    0x93,  // MDMCFG3       Modem Configuration
	    0x03,  // MDMCFG2       Modem Configuration
	    0x22,  // MDMCFG1       Modem Configuration
	    0xF8,  // MDMCFG0       Modem Configuration
	    0x06,  // CHANNR        Channel Number
	    0x44,  // DEVIATN       Modem Deviation Setting
	    0x56,  // FREND1        Front End RX Configuration
	    0x10,  // FREND0        Front End TX Configuration
	    
	    0x30,	 // MCSM1					ADD
	    0x18,  // MCSM0         Main Radio Control State Machine Configuration
	    
	    0x16,  // FOCCFG        Frequency Offset Compensation Configuration
	    0x6C,  // BSCFG         Bit Synchronization Configuration
	    0x43,  // AGCCTRL2      AGC Control
	    0x40,  // AGCCTRL1      AGC Control
	    0x91,  // AGCCTRL0      AGC Control
	    0xA9,  // FSCAL3        Frequency Synthesizer Calibration
	    0x0A,  // FSCAL2        Frequency Synthesizer Calibration
	    0x00,  // FSCAL1        Frequency Synthesizer Calibration
	    0x11,  // FSCAL0        Frequency Synthesizer Calibration
	    0x59,  // FSTEST        Frequency Synthesizer Calibration Control
	    0x88,  // TEST2         Various Test Settings
	    0x31,  // TEST1         Various Test Settings
	    0x0B,  // TEST0         Various Test Settings
	    
	    //0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
	    0x06,  // IOCFG2        GDO2 Output Pin Configuration
	    0x06,  // IOCFG1				ADD   
	    0x06,  // IOCFG0        GDO0 Output Pin Configuration
	    
	    0x04,  // PKTCTRL1      Packet Automation Control
	    0x45,  // PKTCTRL0      Packet Automation Control
	    0x00,  // ADDR          Device Address
	    0xFF,  // PKTLEN        Packet Length
	};
	const Uint8 myPaTable[] = {0xFF};
	const Uint8 myPaTableLen = 1;
	#endif             
#endif



////----------------------------------------------------
//// frq 433M */
//#if RF_FRQ == 433  
//
////----------------------------------------------------
//// frq 433M baud 1200 */
//#if RF_BAUD == 1200
//// Deviation = 5.157471 
//// Base frequency = 432.999817 
//// Carrier frequency = 432.999817 
//// Channel number = 0 
//// Carrier frequency = 432.999817 
//// Modulated = true 
//// Modulation format = GFSK 
//// Manchester enable = false 
//// Sync word qualifier mode = 30/32 sync word bits detected 
//// Preamble count = 4 
//// Channel spacing = 199.951172 
//// Carrier frequency = 432.999817 
//// Data rate = 1.19948 
//// RX filter BW = 58.035714 
//// Data format = Normal mode 
//// Length config = Variable packet length mode. Packet length configured by the first byte after sync word 
//// CRC enable = true 
//// Packet length = 255 
//// Device address = 0 
//// Address config = No address check 
//// CRC autoflush = false 
//// PA ramping = false 
//// TX power = 10 
//const HAL_RF_CONFIG myRfConfig = {
//    0x06,  // FSCTRL1       Frequency Synthesizer Control
//    0x00,  // FSCTRL0       Frequency Synthesizer Control
//    0x10,  // FREQ2         Frequency Control Word, High Byte
//    0xA7,  // FREQ1         Frequency Control Word, Middle Byte
//    0x62,  // FREQ0         Frequency Control Word, Low Byte
//    0xF5,  // MDMCFG4       Modem Configuration
//    0x83,  // MDMCFG3       Modem Configuration
//    0x13,  // MDMCFG2       Modem Configuration
//    0x22,  // MDMCFG1       Modem Configuration
//    0xF8,  // MDMCFG0       Modem Configuration
//    0x00,  // CHANNR        Channel Number
//    0x15,  // DEVIATN       Modem Deviation Setting
//    0x56,  // FREND1        Front End RX Configuration
//    0x10,  // FREND0        Front End TX Configuration
//    0x18,  // MCSM0         Main Radio Control State Machine Configuration
//    0x16,  // FOCCFG        Frequency Offset Compensation Configuration
//    0x6C,  // BSCFG         Bit Synchronization Configuration
//    0x03,  // AGCCTRL2      AGC Control
//    0x40,  // AGCCTRL1      AGC Control
//    0x91,  // AGCCTRL0      AGC Control
//    0xE9,  // FSCAL3        Frequency Synthesizer Calibration
//    0x2A,  // FSCAL2        Frequency Synthesizer Calibration
//    0x00,  // FSCAL1        Frequency Synthesizer Calibration
//    0x1F,  // FSCAL0        Frequency Synthesizer Calibration
//    0x59,  // FSTEST        Frequency Synthesizer Calibration Control
//    0x81,  // TEST2         Various Test Settings
//    0x35,  // TEST1         Various Test Settings
//    0x09,  // TEST0         Various Test Settings
//    0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
//    0x29,  // IOCFG2        GDO2 Output Pin Configuration
//    0x06,  // IOCFG0        GDO0 Output Pin Configuration
//    0x04,  // PKTCTRL1      Packet Automation Control
//    0x05,  // PKTCTRL0      Packet Automation Control
//    0x00,  // ADDR          Device Address
//    0xFF,  // PKTLEN        Packet Length
//};
//const Uint8 myPaTable[] = {0xc0};
//const Uint8 myPaTableLen = 1;
//
////----------------------------------------------------
//// frq 433M baud 2400 */
//#elif RF_BAUD == 2400
//
////----------------------------------------------------
//// frq 433M baud 4800 */
//#elif RF_BAUD == 4800
//// Deviation = 25.390625 
//// Base frequency = 432.999817 
//// Carrier frequency = 432.999817 
//// Channel number = 0 
//// Carrier frequency = 432.999817 
//// Modulated = true 
//// Modulation format = GFSK 
//// Manchester enable = false 
//// Sync word qualifier mode = 30/32 sync word bits detected 
//// Preamble count = 4 
//// Channel spacing = 199.951172 
//// Carrier frequency = 432.999817 
//// Data rate = 4.79794 
//// RX filter BW = 101.562500 
//// Data format = Normal mode 
//// Length config = Variable packet length mode. Packet length configured by the first byte after sync word 
//// CRC enable = true 
//// Packet length = 255 
//// Device address = 0 
//// Address config = No address check 
//// CRC autoflush = false 
//// PA ramping = false 
//// TX power = 10 
//const HAL_RF_CONFIG myRfConfig = {
//    0x06,  // FSCTRL1       Frequency Synthesizer Control
//    0x00,  // FSCTRL0       Frequency Synthesizer Control
//    0x10,  // FREQ2         Frequency Control Word, High Byte
//    0xA7,  // FREQ1         Frequency Control Word, Middle Byte
//    0x62,  // FREQ0         Frequency Control Word, Low Byte
//    0xC7,  // MDMCFG4       Modem Configuration
//    0x83,  // MDMCFG3       Modem Configuration
//    0x13,  // MDMCFG2       Modem Configuration
//    0x22,  // MDMCFG1       Modem Configuration
//    0xF8,  // MDMCFG0       Modem Configuration
//    0x00,  // CHANNR        Channel Number
//    0x40,  // DEVIATN       Modem Deviation Setting
//    0x56,  // FREND1        Front End RX Configuration
//    0x10,  // FREND0        Front End TX Configuration
//    0x18,  // MCSM0         Main Radio Control State Machine Configuration
//    0x16,  // FOCCFG        Frequency Offset Compensation Configuration
//    0x6C,  // BSCFG         Bit Synchronization Configuration
//    0x43,  // AGCCTRL2      AGC Control
//    0x40,  // AGCCTRL1      AGC Control
//    0x91,  // AGCCTRL0      AGC Control
//    0xE9,  // FSCAL3        Frequency Synthesizer Calibration
//    0x2A,  // FSCAL2        Frequency Synthesizer Calibration
//    0x00,  // FSCAL1        Frequency Synthesizer Calibration
//    0x1F,  // FSCAL0        Frequency Synthesizer Calibration
//    0x59,  // FSTEST        Frequency Synthesizer Calibration Control
//    0x81,  // TEST2         Various Test Settings
//    0x35,  // TEST1         Various Test Settings
//    0x09,  // TEST0         Various Test Settings
//    0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
//    0x29,  // IOCFG2        GDO2 Output Pin Configuration
//    0x06,  // IOCFG0        GDO0 Output Pin Configuration
//    0x04,  // PKTCTRL1      Packet Automation Control
//    0x05,  // PKTCTRL0      Packet Automation Control
//    0x00,  // ADDR          Device Address
//    0xFF,  // PKTLEN        Packet Length
//};
//
//const Uint8 myPaTable[] = {0xc0};
//const Uint8 myPaTableLen = 1;
////----------------------------------------------------
//// frq 433M baud 10000 */
//#elif RF_BAUD == 10000
//
////----------------------------------------------------
//// frq 433M baud 38400 */
//#elif RF_BAUD == 38400
//// Deviation = 20.629883 
//// Base frequency = 432.999817 
//// Carrier frequency = 432.999817 
//// Channel number = 0 
//// Carrier frequency = 432.999817 
//// Modulated = true 
//// Modulation format = GFSK 
//// Manchester enable = false 
//// Sync word qualifier mode = 30/32 sync word bits detected 
//// Preamble count = 4 
//// Channel spacing = 199.951172 
//// Carrier frequency = 432.999817 
//// Data rate = 38.3835 
//// RX filter BW = 101.562500 
//// Data format = Normal mode 
//// Length config = Variable packet length mode. Packet length configured by the first byte after sync word 
//// CRC enable = true 
//// Packet length = 255 
//// Device address = 0 
//// Address config = No address check 
//// CRC autoflush = false 
//// PA ramping = false 
//// TX power = 10 
//const HAL_RF_CONFIG myRfConfig = {
//    0x06,  // FSCTRL1       Frequency Synthesizer ControlFSCTRL1
//    0x00,  // FSCTRL0       Frequency Synthesizer ControlFSCTRL0
//    0x10,  // FREQ2         Frequency Control Word, High ByteFREQ2
//    0xA7,  // FREQ1         Frequency Control Word, Middle ByteFREQ1
//    0x62,  // FREQ0         Frequency Control Word, Low ByteFREQ0
//    0xCA,  // MDMCFG4       Modem ConfigurationMDMCFG4
//    0x83,  // MDMCFG3       Modem ConfigurationMDMCFG3
//    0x13,  // MDMCFG2       Modem ConfigurationMDMCFG2
//    0x22,  // MDMCFG1       Modem ConfigurationMDMCFG1
//    0xF8,  // MDMCFG0       Modem ConfigurationMDMCFG0
//    0x00,  // CHANNR        Channel NumberCHANNR
//    0x35,  // DEVIATN       Modem Deviation SettingDEVIATN
//    0x56,  // FREND1        Front End RX ConfigurationFREND1
//    0x10,  // FREND0        Front End TX ConfigurationFREND0
//    0x18,  // MCSM0         Main Radio Control State Machine ConfigurationMCSM0
//    0x16,  // FOCCFG        Frequency Offset Compensation ConfigurationFOCCFG
//    0x6C,  // BSCFG         Bit Synchronization ConfigurationBSCFG
//    0x43,  // AGCCTRL2      AGC ControlAGCCTRL2
//    0x40,  // AGCCTRL1      AGC ControlAGCCTRL1
//    0x91,  // AGCCTRL0      AGC ControlAGCCTRL0
//    0xE9,  // FSCAL3        Frequency Synthesizer CalibrationFSCAL3
//    0x2A,  // FSCAL2        Frequency Synthesizer CalibrationFSCAL2
//    0x00,  // FSCAL1        Frequency Synthesizer CalibrationFSCAL1
//    0x1F,  // FSCAL0        Frequency Synthesizer CalibrationFSCAL0
//    0x59,  // FSTEST        Frequency Synthesizer Calibration ControlFSTEST
//    0x81,  // TEST2         Various Test SettingsTEST2
//    0x35,  // TEST1         Various Test SettingsTEST1
//    0x09,  // TEST0         Various Test SettingsTEST0
//    0x07,  // FIFOTHR       RX FIFO and TX FIFO ThresholdsFIFOTHR
//    0x29,  // IOCFG2        GDO2 Output Pin ConfigurationIOCFG2
//    0x06,  // IOCFG0        GDO0 Output Pin ConfigurationIOCFG0
//    0x04,  // PKTCTRL1      Packet Automation ControlPKTCTRL1
//    0x05,  // PKTCTRL0      Packet Automation ControlPKTCTRL0
//    0x00,  // ADDR          Device AddressADDR
//    0xFF,  // PKTLEN        Packet LengthPKTLEN
//};
//const Uint8 myPaTable[] = {0xc0};
//const Uint8 myPaTableLen = 1;
//#else
//#error "Please select rf baud"
//#endif
//
////----------------------------------------------------
//// frq 470M */
//#elif RF_FRQ == 470
//
////----------------------------------------------------
//// frq 470M baud 1200 */
//#if RF_BAUD == 1200
//
////----------------------------------------------------
//// frq 470M baud 2400 */
//#elif RF_BAUD == 2400
//// Deviation = 5.157471 
//// Base frequency = 469.999908 
//// Carrier frequency = 469.999908 
//// Channel number = 0 
//// Carrier frequency = 469.999908 
//// Modulated = true 
//// Modulation format = GFSK 
//// Manchester enable = false 
//// Sync word qualifier mode = 30/32 sync word bits detected 
//// Preamble count = 4 
//// Channel spacing = 199.951172 
//// Carrier frequency = 469.999908 
//// Data rate = 2.39897 
//// RX filter BW = 58.035714 
//// Data format = Normal mode 
//// Length config = Variable packet length mode. Packet length configured by the first byte after sync word 
//// CRC enable = true 
//// Packet length = 20 
//// Device address = 0 
//// Address config = No address check 
//// CRC autoflush = false 
//// PA ramping = false 
//// TX power = 10 
//const HAL_RF_CONFIG myRfConfig = {
//    0x06,  // FSCTRL1       Frequency Synthesizer Control
//    0x00,  // FSCTRL0       Frequency Synthesizer Control
//    0x12,  // FREQ2         Frequency Control Word, High Byte
//    0x13,  // FREQ1         Frequency Control Word, Middle Byte
//    0xB1,  // FREQ0         Frequency Control Word, Low Byte
//    0xF6,  // MDMCFG4       Modem Configuration
//    0x83,  // MDMCFG3       Modem Configuration
//    0x13,  // MDMCFG2       Modem Configuration
//    0x22,  // MDMCFG1       Modem Configuration
//    0xF8,  // MDMCFG0       Modem Configuration
//    0x00,  // CHANNR        Channel Number
//    0x15,  // DEVIATN       Modem Deviation Setting
//    0x56,  // FREND1        Front End RX Configuration
//    0x10,  // FREND0        Front End TX Configuration
//    0x18,  // MCSM0         Main Radio Control State Machine Configuration
//    0x16,  // FOCCFG        Frequency Offset Compensation Configuration
//    0x6C,  // BSCFG         Bit Synchronization Configuration
//    0x43,  // AGCCTRL2      AGC Control
//    0x40,  // AGCCTRL1      AGC Control
//    0x91,  // AGCCTRL0      AGC Control
//    0xE9,  // FSCAL3        Frequency Synthesizer Calibration
//    0x0A,  // FSCAL2        Frequency Synthesizer Calibration
//    0x00,  // FSCAL1        Frequency Synthesizer Calibration
//    0x1F,  // FSCAL0        Frequency Synthesizer Calibration
//    0x59,  // FSTEST        Frequency Synthesizer Calibration Control
//    0x81,  // TEST2         Various Test Settings
//    0x35,  // TEST1         Various Test Settings
//    0x09,  // TEST0         Various Test Settings
//    0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
//    0x29,  // IOCFG2        GDO2 Output Pin Configuration
//    0x06,  // IOCFG0        GDO0 Output Configuration
//    0x04,  // PKTCTRL1      Packet Automation Control
//    0x05,  // PKTCTRL0      Packet Automation Control
//    0x00,  // ADDR          Device Address
//    0xff,  // PKTLEN        Packet Length
//};
//const Uint8 myPaTable[] = {0xc2};
//const Uint8 myPaTableLen = 1;
////----------------------------------------------------
//// frq 470M baud 4800 */
//#elif RF_BAUD == 4800
//// Deviation = 5.157471 
//// Base frequency = 469.999908 
//// Carrier frequency = 469.999908 
//// Channel number = 0 
//// Carrier frequency = 469.999908 
//// Modulated = true 
//// Modulation format = GFSK 
//// Manchester enable = false 
//// Sync word qualifier mode = 30/32 sync word bits detected 
//// Preamble count = 4 
//// Channel spacing = 199.951172 
//// Carrier frequency = 469.999908 
//// Data rate = 4.79794 
//// RX filter BW = 58.035714 
//// Data format = Normal mode 
//// CRC enable = true 
//// Whitening = false 
//// Device address = 0 
//// Address config = No address check 
//// CRC autoflush = false 
//// PA ramping = false 
//// TX power = 10 
//
//const HAL_RF_CONFIG myRfConfig = {
//    0x06,  // FSCTRL1       Frequency Synthesizer Control
//    0x00,  // FSCTRL0       Frequency Synthesizer Control
//    0x12,  // FREQ2         Frequency Control Word, High Byte
//    0x13,  // FREQ1         Frequency Control Word, Middle Byte
//    0xB1,  // FREQ0         Frequency Control Word, Low Byte
//    0xF7,  // MDMCFG4       Modem Configuration
//    0x83,  // MDMCFG3       Modem Configuration
//    0x13,  // MDMCFG2       Modem Configuration
//    0x22,  // MDMCFG1       Modem Configuration
//    0xF8,  // MDMCFG0       Modem Configuration
//    0x00,  // CHANNR        Channel Number
//    0x15,  // DEVIATN       Modem Deviation Setting
//    0x56,  // FREND1        Front End RX Configuration
//    0x10,  // FREND0        Front End TX Configuration
//    0x18,  // MCSM0         Main Radio Control State Machine Configuration
//    0x16,  // FOCCFG        Frequency Offset Compensation Configuration
//    0x6C,  // BSCFG         Bit Synchronization Configuration
//    0x43,  // AGCCTRL2      AGC Control
//    0x40,  // AGCCTRL1      AGC Control
//    0x91,  // AGCCTRL0      AGC Control
//    0xE9,  // FSCAL3        Frequency Synthesizer Calibration
//    0x0A,  // FSCAL2        Frequency Synthesizer Calibration
//    0x00,  // FSCAL1        Frequency Synthesizer Calibration
//    0x1F,  // FSCAL0        Frequency Synthesizer Calibration
//    0x59,  // FSTEST        Frequency Synthesizer Calibration Control
//    0x81,  // TEST2         Various Test Settings
//    0x35,  // TEST1         Various Test Settings
//    0x09,  // TEST0         Various Test Settings
//    0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
//    0x29,  // IOCFG2        GDO2 Output Pin Configuration
//    0x06,  // IOCFG0        GDO0 Output Configuration
//    0x04,  // PKTCTRL1      Packet Automation Control
//    0x05,  // PKTCTRL0      Packet Automation Control
//    0x00,  // ADDR          Device Address
//    0xff,  // PKTLEN        Packet Length
//};
//const Uint8 myPaTable[] = {0xc2};
//const Uint8 myPaTableLen = 1;
//
////----------------------------------------------------
//// frq 470M baud 10000 */
//#elif RF_BAUD == 10000
//// Deviation = 19.042969 
//// Base frequency = 469.999908 
//// Carrier frequency = 469.999908 
//// Channel number = 0 
//// Carrier frequency = 469.999908 
//// Modulated = true 
//// Modulation format = GFSK 
//// Manchester enable = false 
//// Sync word qualifier mode = 30/32 sync word bits detected 
//// Preamble count = 4 
//// Channel spacing = 199.951172 
//// Carrier frequency = 469.999908 
//// Data rate = 9.9926 
//// RX filter BW = 101.562500 
//// Data format = Normal mode 
//// Length config = Variable packet length mode. Packet length configured by the first byte after sync word 
//// CRC enable = true 
//// Packet length = no 
//// Device address = 0 
//// Address config = No address check 
//// CRC autoflush = false 
//// PA ramping = false 
//// TX power = 10 
//const HAL_RF_CONFIG myRfConfig = {
//    0x06,  // FSCTRL1       Frequency Synthesizer Control
//    0x00,  // FSCTRL0       Frequency Synthesizer Control
//    0x12,  // FREQ2         Frequency Control Word, High Byte
//    0x13,  // FREQ1         Frequency Control Word, Middle Byte
//    0xB1,  // FREQ0         Frequency Control Word, Low Byte
//    0xC8,  // MDMCFG4       Modem Configuration
//    0x93,  // MDMCFG3       Modem Configuration
//    0x13,  // MDMCFG2       Modem Configuration
//    0x22,  // MDMCFG1       Modem Configuration
//    0xF8,  // MDMCFG0       Modem Configuration
//    0x00,  // CHANNR        Channel Number
//    0x34,  // DEVIATN       Modem Deviation Setting
//    0x56,  // FREND1        Front End RX Configuration
//    0x10,  // FREND0        Front End TX Configuration
//    0x18,  // MCSM0         Main Radio Control State Machine Configuration
//    0x16,  // FOCCFG        Frequency Offset Compensation Configuration
//    0x6C,  // BSCFG         Bit Synchronization Configuration
//    0x43,  // AGCCTRL2      AGC Control
//    0x40,  // AGCCTRL1      AGC Control
//    0x91,  // AGCCTRL0      AGC Control
//    0xE9,  // FSCAL3        Frequency Synthesizer Calibration
//    0x0A,  // FSCAL2        Frequency Synthesizer Calibration
//    0x00,  // FSCAL1        Frequency Synthesizer Calibration
//    0x1F,  // FSCAL0        Frequency Synthesizer Calibration
//    0x59,  // FSTEST        Frequency Synthesizer Calibration Control
//    0x81,  // TEST2         Various Test Settings
//    0x35,  // TEST1         Various Test Settings
//    0x09,  // TEST0         Various Test Settings
//    0x07,  // FIFOTHR       RX FIFO and TX FIFO Thresholds
//    0x29,  // IOCFG2        GDO2 Output Pin Configuration
//    0x06,  // IOCFG0        GDO0 Output Configuration
//    0x04,  // PKTCTRL1      Packet Automation Control
//    0x05,  // PKTCTRL0      Packet Automation Control
//    0x00,  // ADDR          Device Address
//    0xff,  // PKTLEN        Packet Length
//};
//const Uint8 myPaTable[] = {0xc2};
//const Uint8 myPaTableLen = 1;
//#else
//#error "Please select rf baud"
//#endif
//#else
//#error "Please select rf Frequency"
//#endif

