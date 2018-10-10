#ifndef __UART1_H__
#define __UART1_H__

#ifdef  VAR_UART1_GLOBALS
	#define  VAR_UART1_EXT
#else
	#define  VAR_UART1_EXT  extern
#endif
/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 数据类型定义                                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
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
	uchar jHead;						//头码
	TEMP_LEVEL jSetWaterLevel;		//设置水加热等级
	DRY_STATE jSetDryLevel;			//设置烘干加热等级
	TEMP_LEVEL jSetSeatLevel;			//设置座圈加热等级
	uchar jPosState;					//当前喷杆
	uchar jLevelState;     				//当前水压
	uchar jFunCmd;					//功能命令
	uchar jCheck;						//校验码
}UART1_COM_TX;
VAR_UART1_EXT AT_NEAR UART1_COM_TX TxComBuff; //发送结构体
typedef struct
{
	uchar nHead;						//头码
	SYS_INIT	nInitInf;					//初始化电平标志位
	SYSTE_STATE	nSystemCurState;		//系统当前状态
	FUNC_STATE 	nCurFunc;			//当前功能
	eTEMP_CHANGE nTempChange : 1;	//冷热按摩
	uchar nSwitchState : 1;				//着座开关状态
	uint	nSystemErrInf;				//系统故障标志
	uint	nSeatOffHour;				//离座小时
	uchar nSeatEn : 1;					//模拟着座
	TEMP_LEVEL nSetWaterLevel;		//设置水加热等级
	DRY_STATE nSetDryLevel;			//设置烘干加热等级
	TEMP_LEVEL nSetSeatLevel;			//设置座圈加热等级
	uchar nPosState;					//当前喷杆
	uchar nLevelState;     				//当前水压
	uchar nAddrFlag;					//地址校验
	uchar nFlushTimeState;     				//当前水压
	uchar nCheck;						//校验码
}UART1_COM_RX;
VAR_UART1_EXT AT_NEAR UART1_COM_RX RxComBuff; //接收结构体

typedef struct
{
	uchar NeedSendFlag : 1;//发送信号1
}NEED_SEND;//需要发送的信号数量
VAR_UART1_EXT AT_NEAR NEED_SEND NeedSendInf;

#define UART1_MAX_BYTE 30 //如果需要发送的数据超过此值，则需要加大
#define UART1_MAX_LINE  5
#define UART1_RX_GAP_TM 2 //ms 取值在几ms~十几ms
typedef struct
{
	uchar rUart1ComLine;	//当前通信行
	uchar rUart1BuffLine;	//当前缓存行
	uchar rUart1UseLine;	//有用的发送帧总数
	uchar rUart1ComPos;	//当前通信字节位置
	uint rUart1NoComCnt;//无通信计时
	uchar Uart1ComBuff[UART1_MAX_LINE][UART1_MAX_BYTE];
}UART1_COM_STATE;	
VAR_UART1_EXT AT_NEAR UART1_COM_STATE Uart1Tx;
VAR_UART1_EXT AT_NEAR UART1_COM_STATE Uart1Rx;

typedef struct
{
	uchar rUart1EnSendFlag : 1;//允许发送标志
	uchar rUart1EnAddLine : 1;//允许添加到队列
	uchar rUart1StartSend : 1;//启动发送
	uchar rUart1CommErrFlag : 1;//通信故障标志
}UART1_COM_FLAG;
VAR_UART1_EXT AT_NEAR UART1_COM_FLAG Uart1ComFlag;

VAR_UART1_EXT void f_pUart1Init(uint baudRate);
VAR_UART1_EXT void f_pUart1SendDeal(BIG_STRUCT *pFuctionData);
VAR_UART1_EXT void f_pUart1ReceDeal(BIG_STRUCT *pFuctionData);
VAR_UART1_EXT void f_pUart1TimeCnt(void);
VAR_UART1_EXT IT_HEADE void UART1_TX_Interrupt(void);
VAR_UART1_EXT IT_HEADE void UART1_RX_Interrupt(void);

#endif /* __UART1_H__ */