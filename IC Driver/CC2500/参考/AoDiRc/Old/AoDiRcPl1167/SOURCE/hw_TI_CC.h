#ifndef HW_TI_CC_H__ 
#define HW_TI_CC_H__


//****************************************************************************
// 头文件
//****************************************************************************/

//****************************************************************************
// 函数申明 
//****************************************************************************/
void halRfReceiveSet(void);
unsigned char halRfConfig(const HAL_RF_CONFIG *rfConfig, const Uint8 *rfPaTable,const Uint8 rfPaTableLen);
Uint8 halRfReceivePacket(Uint8 *rxBuffer, Uint8 *length);//@"INFO";
Uint8 halRfSendPacket(Uint8 *txBuffer, Uint8 size) ;
void f_InitCC2500(void);
void RF_RX(void);
void RFSleep(void);
void RFWorRegSet(void);
void RFWorRegReset(void);
void RFWorOn(void);

//****************************************************************************
// 变量申明 
//****************************************************************************/
extern const HAL_RF_CONFIG myRfConfig;
extern const HAL_RF_CONFIG myRfConfigSleep;
extern const Uint8 myPaTable[];
extern const Uint8 myPaTableLen;

typedef union 
{
	unsigned char all;
	struct
	{
		unsigned char RFRxFinished:	1;
		unsigned char RFTxFinished:	1;
		unsigned char RFRxState:		1;
		unsigned char RFTxState:		1;
		unsigned char RFPwdState:		1;
		unsigned char RFRxWorState:	1;	
	}mbit;
}u_SYS_STAT0;
extern u_SYS_STAT0 SysState0;
extern unsigned char Buffer[15];

#endif //  __HW_TI_CC_H__


