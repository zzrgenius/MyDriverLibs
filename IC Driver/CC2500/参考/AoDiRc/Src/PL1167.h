#ifndef __PL1167_H
#define __PL1167_H

#ifdef  VAR_PL1167_GLOBALS
	#define  VAR_PL1167_EXT
#else
	#define  VAR_PL1167_EXT  extern
#endif
/*#define SPICLK			_pd3
#define SPIMISO			_pd5
#define SPIMOSI			_pd2
#define SPICS				_pd4
#define PKT				_pb2
#define RFRST			_pd1  */

#define SPICLK			_pb1
#define SPIMISO			_pc1
#define SPIMOSI			_pb2
#define SPICS				_pc2
#define PKT				_pb0
#define RFRST			_pa4 

#define PRF_INIT_TAB_LEN 	 34
#define SEND_LEN				12
#define PRF_REG_RD			0x80

// 定义发送字节数 
#define TXD_TOTAL_BYTES				12

typedef struct
{
	uchar SendStart : 1;	//启动发送
	uchar SendFlag : 1;	//发送标志位
}SEND_INF;
VAR_PL1167_EXT SEND_INF SendInf;
VAR_PL1167_EXT uchar time1sCnt;

VAR_PL1167_EXT void f_pPL1167Init(void);
VAR_PL1167_EXT void f_pSendBuffer(void);
VAR_PL1167_EXT void f_pSendDeal(void);

VAR_PL1167_EXT void f_pRfRecDeal(void);
VAR_PL1167_EXT void f_pFreqDeal(void);
#endif //__PL1167_H