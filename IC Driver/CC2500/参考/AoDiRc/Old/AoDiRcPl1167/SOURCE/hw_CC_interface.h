#ifndef HW_CC_INTERFACE_H 
#define HW_CC_INTERFACE_H

void halSpiWriteReg(Uint8 addr,Uint8 value);
void halSpiWriteBurstReg(Uint8 addr, Uint8 *buffer,Uint8 count);
Uint8 halSpiReadReg(Uint8 addr);
void halSpiReadBurstReg(Uint8 addr,Uint8 *buffer,Uint8 count);
Uint8 halSpiReadStatus(Uint8 addr);
void halSpiStrobe(Uint8 strobe);
void f_ResetCC2500(void);
unsigned char halPowerupResetCCxxxx(void);
void TI_CC_WAIT(Uint16 cycles);
Uint8 halSpiBitbangOut(Uint8 data);
Uint8 halSpiBitbangIn(void);
void HwSpiInit_BITBANG(void);

#endif //  __HW_CC_INTERFACE_H__
