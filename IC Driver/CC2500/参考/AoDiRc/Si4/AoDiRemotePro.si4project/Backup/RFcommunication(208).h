#ifndef __RF_H
#define __RF_H

#ifdef  VAR_RF_GLOBALS
	#define  VAR_RF_EXT
#else
	#define  VAR_RF_EXT  extern
#endif

//VAR_RF_EXT uchar ucCOMBuf[15]  __attribute__((at(0x1A0)));
VAR_RF_EXT uchar ucCOMBuf[15];

// ��������ֽ��� 
#define RXD_TOTAL_BYTES				12

// ���巢���ֽ��� 
#define TXD_TOTAL_BYTES				12

void f_GetSendBuffRF(void);

#endif //__RF_H