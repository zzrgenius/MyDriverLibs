#ifndef __IR_CONTROL_H__
#define __IR_CONTROL_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 数据类型定义                                       *
 *----------------------------------------------*/
typedef enum
{
	IR_STEP_IDLE,
	IR_STEP_HEAD,
	IR_STEP_DATA,
	IR_STEP_END
}IR_COMMI_STEP;

typedef enum
{
	IR_READ_NULL = 0,
	IR_READ_HEAD,//引导吗
	IR_READ_END,//结束码
	IR_READ_BIT_0,//数据位0
	IR_READ_BIT_1//数据位1
}IR_READ_BIT_INFO;

#define IR_REV_BUF_NUM 10
#define IR_SEND_BUF_NUM 10
typedef struct
{
	IR_COMMI_STEP revStep;
	uchar revBitPos;//当前读取位位置
	uchar revByteCnt;//获取字节数
	uint  revLowTm; //接收低电平时间
	uint  revPeriodTm; //接收高电平时间
	uint  revLowTmBuf; //接收低电平时间缓存
	uint  revPeriodTmBuf; //接收高电平时间缓存
	uchar revNULLCnt; //接收错误数据次数
	uchar revBuf[IR_REV_BUF_NUM];
	
	uchar bRevOneBitOVer :1; //接收一个字节完成
	uchar bLastRevLevelState :1; //上次接收电平状态
	uchar bNeedDeal :1;
	
	IR_COMMI_STEP sendStep;//发送步骤
	uchar sendBitPos;//当前发送位位置
	uchar sendByteCnt; //当前发送字节数
	uchar needSendByte; //需要发送字节数
	uint sendTm; //当前发送时间
	uint setLowTm; //设置低电平时间
	uint setPeriodTm; //设置周期时间
	uchar sendBuf[IR_SEND_BUF_NUM];

	uchar bSendOneBitOver :1;//位数据发送完成
	uchar bSendSpecialCode :1;//发送特殊码(头码/尾码)
	uchar bSendOneByteOver :1;//当前一个字节发送完成
	
}IR_CONTROL_DRIVER;

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern IR_CONTROL_DRIVER irControlDriver;

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_IR_ControlDeal(void);
void f_IR_StartSend(uchar *pBuf, uchar len);
void f_IRControlInit(void);


#endif /* __IRCONTROL_H__ */
