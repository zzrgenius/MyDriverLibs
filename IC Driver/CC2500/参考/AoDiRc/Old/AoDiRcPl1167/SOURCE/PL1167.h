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

// ���巢���ֽ��� 
#define TXD_TOTAL_BYTES				12

typedef struct
{
	uchar SendStart : 1;	//��������
	uchar SendFlag : 1;	//���ͱ�־λ
}SEND_INF;
VAR_PL1167_EXT SEND_INF SendInf;
VAR_PL1167_EXT uchar time1sCnt;

VAR_PL1167_EXT void PL1167_Init(void);
VAR_PL1167_EXT void f_SendBuffer(void);
VAR_PL1167_EXT void f_SendDeal(void);

VAR_PL1167_EXT void f_RfRecDeal(void);
VAR_PL1167_EXT void f_FreqDeal(void);
#endif //__PL1167_H