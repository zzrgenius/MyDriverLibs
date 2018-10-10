#ifndef __PL1167_H
#define __PL1167_H

#ifdef  VAR_PL1167_GLOBALS
	#define  VAR_PL1167_EXT
#else
	#define  VAR_PL1167_EXT  extern
#endif
/*#define SPICLK			PDO_6//IO_BIT_ALIAS(&PD_ODR,5) 
#define SPIMISO			PCI_3//IO_BIT_ALIAS(&PD_IDR,3) 	
#define SPIMOSI			PDO_4//IO_BIT_ALIAS(&PD_ODR,4)
#define SPICS				PAO_1//IO_BIT_ALIAS(&PD_ODR,6)
#define PKT				PDI_2//IO_BIT_ALIAS(&PD_IDR,2)
#define RFRST				PDO_3//IO_BIT_ALIAS(&PC_ODR,7)*/
#define SPICLK			PAO_2//IO_BIT_ALIAS(&PD_ODR,5) 
#define SPIMISO			PBI_4//IO_BIT_ALIAS(&PD_IDR,3) 	
#define SPIMOSI			PBO_5//IO_BIT_ALIAS(&PD_ODR,4)
#define SPICS				PAO_1//IO_BIT_ALIAS(&PD_ODR,6)
#define PKT				PDI_1//IO_BIT_ALIAS(&PD_IDR,2)
//#define PKT				PDI_2//IO_BIT_ALIAS(&PD_IDR,2)
#define RFRST			PDO_4//IO_BIT_ALIAS(&PC_ODR,7)

//#define IR_SEND(DATA)   	PDO_5 = DATA	   

#define PRF_INIT_TAB_LEN 35
#define PRF_REG_RD		0x80

VAR_PL1167_EXT uchar testPL;

VAR_PL1167_EXT void PL1167_Init(void);
//VAR_PL1167_EXT IT_HEADE void PDExtInterrupt(void);
VAR_PL1167_EXT void f_RfRecDeal(void);
VAR_PL1167_EXT void f_FreqDeal(void);
//VAR_PL1167_EXT void f_IrSendDeal(BIG_STRUCT *pFuctionData);
#endif //__PL1167_H