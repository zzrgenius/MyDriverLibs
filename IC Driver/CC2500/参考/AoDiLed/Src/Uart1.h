#ifndef __UART1_H__
#define __UART1_H__

#ifdef  VAR_UART1_GLOBALS
	#define  VAR_UART1_EXT
#else
	#define  VAR_UART1_EXT  extern
#endif
/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �������Ͷ���                                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

#define UART1_CR2_REN_FALSE	UART1_CR2 &= ~0x04
#define UART1_CR2_TEN_FALSE	UART1_CR2 &= ~0x08
#define UART1_CR2_RIEN_FALSE	UART1_CR2 &= ~0x20
#define UART1_CR2_TIEN_FALSE	UART1_CR2 &= ~0x40

#define UART1_CR2_REN_TRUE		UART1_CR2 |= 0x04
#define UART1_CR2_TEN_TRUE		UART1_CR2 |= 0x08
#define UART1_CR2_RIEN_TRUE	UART1_CR2 |= 0x20
#define UART1_CR2_TIEN_TRUE	UART1_CR2 |= 0x40

#define UART1_DATA_CR1		UART1_CR1
#define UART1_DATA_CR2		UART1_CR2
#define UART1_DATA_CR3		UART1_CR3
#define UART1_DATA_DR		UART1_DR
#define UART1_DATA_SR		UART1_SR
#define UART1_DATA_BR2		UART1_BRR2
#define UART1_DATA_BR1		UART1_BRR1
#define SYS_CLOCK 16000000
//#define UART1_BAUT_RATE 2400 
#define UART1_BAUT_RATE 9600
typedef struct
{
	uchar jHead;						//ͷ��
	TEMP_LEVEL jSetWaterLevel;		//����ˮ���ȵȼ�
	DRY_STATE jSetDryLevel;			//���ú�ɼ��ȵȼ�
	TEMP_LEVEL jSetSeatLevel;			//������Ȧ���ȵȼ�
	uchar jPosState;					//��ǰ���
	uchar jLevelState;     				//��ǰˮѹ
	uchar jFunCmd;					//��������
	uchar jCheck;						//У����
}UART1_COM_TX;
VAR_UART1_EXT AT_NEAR UART1_COM_TX TxComBuff; //���ͽṹ��
typedef struct
{
	uchar nHead;						//ͷ��
	SYS_INIT	nInitInf;					//��ʼ����ƽ��־λ
	SYSTE_STATE	nSystemCurState;		//ϵͳ��ǰ״̬
	FUNC_STATE 	nCurFunc;			//��ǰ����
	eTEMP_CHANGE nTempChange : 1;	//���Ȱ�Ħ
	uchar nSwitchState : 1;				//��������״̬
	uint	nSystemErrInf;				//ϵͳ���ϱ�־
	uint	nSeatOffHour;				//����Сʱ
	uchar nSeatEn : 1;					//ģ������
	TEMP_LEVEL nSetWaterLevel;		//����ˮ���ȵȼ�
	DRY_STATE nSetDryLevel;			//���ú�ɼ��ȵȼ�
	TEMP_LEVEL nSetSeatLevel;			//������Ȧ���ȵȼ�
	uchar nPosState;					//��ǰ���
	uchar nLevelState;     				//��ǰˮѹ
	uchar nAddrFlag;					//��ַУ��
	uchar nFlushTimeState;     				//��ǰˮѹ
	uchar nCheck;						//У����
}UART1_COM_RX;
VAR_UART1_EXT AT_NEAR UART1_COM_RX RxComBuff; //���սṹ��

typedef struct
{
	uchar NeedSendFlag : 1;//�����ź�1
}NEED_SEND;//��Ҫ���͵��ź�����
VAR_UART1_EXT AT_NEAR NEED_SEND NeedSendInf;

#define UART1_MAX_BYTE 30 //�����Ҫ���͵����ݳ�����ֵ������Ҫ�Ӵ�
#define UART1_MAX_LINE  5
#define UART1_RX_GAP_TM 2 //ms ȡֵ�ڼ�ms~ʮ��ms
typedef struct
{
	uchar rUart1ComLine;	//��ǰͨ����
	uchar rUart1BuffLine;	//��ǰ������
	uchar rUart1UseLine;	//���õķ���֡����
	uchar rUart1ComPos;	//��ǰͨ���ֽ�λ��
	uint rUart1NoComCnt;//��ͨ�ż�ʱ
	uchar Uart1ComBuff[UART1_MAX_LINE][UART1_MAX_BYTE];
}UART1_COM_STATE;	
VAR_UART1_EXT AT_NEAR UART1_COM_STATE Uart1Tx;
VAR_UART1_EXT AT_NEAR UART1_COM_STATE Uart1Rx;

typedef struct
{
	uchar rUart1EnSendFlag : 1;//�����ͱ�־
	uchar rUart1EnAddLine : 1;//������ӵ�����
	uchar rUart1StartSend : 1;//��������
	uchar rUart1CommErrFlag : 1;//ͨ�Ź��ϱ�־
}UART1_COM_FLAG;
VAR_UART1_EXT AT_NEAR UART1_COM_FLAG Uart1ComFlag;

VAR_UART1_EXT void f_pUart1Init(uint baudRate);
VAR_UART1_EXT void f_pUart1SendDeal(BIG_STRUCT *pFuctionData);
VAR_UART1_EXT void f_pUart1ReceDeal(BIG_STRUCT *pFuctionData);
VAR_UART1_EXT void f_pUart1TimeCnt(void);
VAR_UART1_EXT IT_HEADE void UART1_TX_Interrupt(void);
VAR_UART1_EXT IT_HEADE void UART1_RX_Interrupt(void);

#endif /* __UART1_H__ */