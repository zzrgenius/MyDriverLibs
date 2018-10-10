//---------------------------------------------------------------------------//
//
//! @file 	 my_fr_setting.h
//! @brief   Chipcon配置参数结构体，由SmartRF Studio提供 
//--------------------------------------------//
#ifndef MY_RF_SETTING_H
#define MY_RF_SETTING_H

//****************************************************************************
// 宏定义
//****************************************************************************/
// The following structure can be used when configuring the RF chip. SmartRF Studio
// can be used to export a predefined instance of this structure.
typedef struct {
    BYTE fsctrl1;    // Frequency synthesizer control.
    BYTE fsctrl0;    // Frequency synthesizer control.
    BYTE freq2;      // Frequency control word, high byte.
    BYTE freq1;      // Frequency control word, middle byte.
    BYTE freq0;      // Frequency control word, low byte.
    BYTE mdmcfg4;    // Modem configuration.
    BYTE mdmcfg3;    // Modem configuration.
    BYTE mdmcfg2;    // Modem configuration.
    BYTE mdmcfg1;    // Modem configuration.
    BYTE mdmcfg0;    // Modem configuration.
    BYTE channr;     // Channel number.
    BYTE deviatn;    // Modem deviation setting (when FSK modulation is enabled).
    BYTE frend1;     // Front end RX configuration.
    BYTE frend0;     // Front end RX configuration.
    BYTE mcsm1;			//add
    BYTE mcsm0;      // Main Radio Control State Machine configuration.
    BYTE foccfg;     // Frequency Offset Compensation Configuration.
    BYTE bscfg;      // Bit synchronization Configuration.
    BYTE agcctrl2;   // AGC control.
    BYTE agcctrl1;   // AGC control.
    BYTE agcctrl0;   // AGC control.
    BYTE fscal3;     // Frequency synthesizer calibration.
    BYTE fscal2;     // Frequency synthesizer calibration.
    BYTE fscal1;     // Frequency synthesizer calibration.
    BYTE fscal0;     // Frequency synthesizer calibration.
    BYTE fstest;     // Frequency synthesizer calibration.
    BYTE test2;      // Various test settings.
    BYTE test1;      // Various test settings.
    BYTE test0;      // Various test settings.
    //BYTE fifothr;    // RXFIFO and TXFIFO thresholds.
    BYTE iocfg2;     // GDO2 output pin configuration.
    BYTE iocfg0;    // GDO0 output pin configuration. Refer to SmartRF?Studio User Manual for detailed pseudo register explanation.
    BYTE iocfg1;		//ADD
    BYTE pktctrl1;   // Packet automation control.
    BYTE pktctrl0;   // Packet automation control.
    BYTE addr;       // Device address.
    BYTE pktlen;     // Packet length.

} HAL_RF_CONFIG;

#endif //  __MY_RF_SETTING_H__

