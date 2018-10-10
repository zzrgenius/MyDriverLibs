#ifndef __COMM_DRIVER_H__
#define __COMM_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "CommQueue.h"

/*----------------------------------------------*
 * 前置声明 										*
 *----------------------------------------------*/
struct comm_driver;
typedef struct comm_driver COMM_DRIVER;

/*----------------------------------------------*
 * 数据类型定义                                       *
 *----------------------------------------------*/
typedef struct
{
	uchar frameRevOverItv;//帧结束间隔时间,超过时间则认为已经帧接收结束,单位1ms
	uchar sendFrameItv;//帧发送间隔
	uchar sendErrTm; //帧发送失败时间
	uint  waitReplyTm; //等待应答超时时间
	
	void (*SetSendInterrupt)(uchar);//发送中断设置打开或关闭
	void (*SetRecInterrupt)(uchar);//接收中断设置打开或关闭
	void (*StartSend)(COMM_DRIVER*);//启动发送
	void (*ChangeBaudRate)(word_32); //更改波特率
}COMM_HARDWARE;//通信硬件配置

typedef enum
{
	COMM_SEND_STATE_IDLE = 0,//发送空闲状态
	COMM_SEND_STATE_GET_BUFFER,//获取缓存状态
	COMM_SEND_STATE_START,//启动发送
	COMM_SEND_STATE_SENDING,//正在发送
	COMM_SEND_STATE_OVER,//发送结束
	COMM_SEND_STATE_REPLY//得到应答
}COMM_SEND_STATE;//通信发送状态

typedef enum
{
	COMM_REV_STATE_WAIT = 0,//等待接收
	COMM_REV_STATE_OVER//接收结束
}COMM_REV_STATE;//接收状态

typedef struct
{
	uchar *pBuffer;//缓存地址
	const uint size;//缓存大小
}COMM_FRAME_BUFFER;//缓存信息

typedef struct
{
	COMM_SEND_STATE sendState;//当前发送状态
	COMM_FRAME_BUFFER const *pBuffer;
	uint noSendTm;//无发送时间
	uint needSendNum;//需要发送字节数
	uint curSendNum;//已发送字节数
	QUEUE_DATA_TYPE curSendCMD;//当前发送命令(内部命令)
	uchar CMDSendCnt;//命令发送计数
	COMM_QUEUE queue;//发送命令队列
}COMM_SEND_DATA;//发送用数据

typedef struct
{
	COMM_REV_STATE revState;//当前接收状态
	COMM_FRAME_BUFFER const *pBuffer;
	uint noRevTm;//无接收时间
	uint curRevNum;//当前接收到字节数
	QUEUE_DATA_TYPE curRevCMD;//解析后命令(内部命令)
}COMM_REV_DATA;//接收数据结构

typedef struct
{
    word_32 baudRate; //波特率
	uint internalCMD;//内部命令
	void (*RevDataDeal)(COMM_DRIVER *);//接收正确处理函数
	void (*GetSendBuf)(COMM_DRIVER *);//获取发送缓存
	void (*NoReplyDeal)(COMM_DRIVER *);//无应答处理函数
}COMM_FUNC_TAB; //功能处理函数结构

struct comm_driver
{
	COMM_SEND_DATA sendData;//发送相关数据
	COMM_REV_DATA revData;//接收相关数据
	COMM_HARDWARE const *pHardware;//硬件相关
};

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
#define COMM_CMD_NULL 0
//====内部命令构成====
//bit15表示是否循环重发
//bit12~15 保留
//bit8~11 重发次数
//bit0~7 内部命令序号(从1开始)
#define COMM_SET_CMD(syc, retryCnt, index) (((syc&(0x0001))<<15)|((retryCnt&(0x000f))<<8)|(index&0x000f))//命令组成
#define COMM_GET_RETRY_CNT(cmd) ((cmd>>8)&0x000f)//解析重发次数
#define COMM_IS_NEED_SYC(cmd) ((cmd>>15)&0x0001)//解析是否重发


/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_CommDriverInit(COMM_DRIVER *pDriver, 
							const COMM_HARDWARE *pHardware, 
							const COMM_FRAME_BUFFER *pSendBuf, 
							const COMM_FRAME_BUFFER *pRevBuf);
void f_CommDriverDeal(COMM_DRIVER *pDriver);
uchar f_CommSendCMD(COMM_DRIVER *pDriver, QUEUE_DATA_TYPE cmd);

#endif /* __COMM_DRIVER_H__ */
