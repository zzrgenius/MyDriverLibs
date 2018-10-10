/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : CommHardware.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月8日
  最近修改   :
  功能描述   : 通信硬件相关
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月8日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "CommHardware.h"

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/


/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/
void f_UART1_SatrtSend(COMM_DRIVER *pDriver);
void f_UART1_SetRevInterrupt(uchar en);
void f_UART1_SetSendInterrupt(uchar en);
void f_UART1_ChangeBaudRate(word_32 baudRate);


void f_UART2_SatrtSend(COMM_DRIVER *pDriver);
void f_UART2_SetRevInterrupt(uchar en);
void f_UART2_SetSendInterrupt(uchar en);
void f_UART2_ChangeBaudRate(word_32 baudRate);

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/
//串口0硬件信息(wifi)
const COMM_HARDWARE uart1Hardware =
{
	15, //单帧结束间隔,单位1ms
	20, //帧发送间隔,单位1ms
	5, //单字节发送超时时间,单位1ms
	100, //等待应答超时时间,单位1ms
	f_UART1_SetSendInterrupt,
	f_UART1_SetRevInterrupt,
	f_UART1_SatrtSend,
	f_UART1_ChangeBaudRate //无该功能或无需动态修改可设置为NULL(以上参数以最小波特率设置)
};

//串口1硬件信息(即热模块\转接)
const COMM_HARDWARE uart2Hardware =
{
	15, //单帧结束间隔,单位1ms
	20, //帧发送间隔,单位1ms
	10, //单字节发送超时时间,单位1ms
	50, //等待应答超时时间,单位1ms
	f_UART2_SetSendInterrupt,
	f_UART2_SetRevInterrupt,
	f_UART2_SatrtSend,
	f_UART2_ChangeBaudRate //无该功能或无需动态修改可设置为NULL(以上参数以最小波特率设置)
};

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

//====UART1====

//启动发送函数
void f_UART1_SatrtSend(COMM_DRIVER *pDriver)
{
	pDriver->sendData.curSendNum = 0;
	usart_data_transmit(USART0, pDriver->sendData.pBuffer->pBuffer[pDriver->sendData.curSendNum]); //发送第一个数据
	if (pDriver->pHardware->SetSendInterrupt)
	{
		pDriver->pHardware->SetSendInterrupt(true); //使能发送
	}
}

//发送数据
void f_UART1_SendData(COMM_DRIVER *pDriver)
{
	if (COMM_SEND_STATE_SENDING == pDriver->sendData.sendState)
	{
		pDriver->sendData.curSendNum ++;
		if (pDriver->sendData.curSendNum >= pDriver->sendData.needSendNum)
		{
			pDriver->sendData.curSendNum = 0;
			pDriver->sendData.sendState = COMM_SEND_STATE_OVER;
			if (pDriver->pHardware->SetSendInterrupt)
			{
				pDriver->pHardware->SetSendInterrupt(false); 
			}
		}
		else
		{
			usart_data_transmit(USART0, pDriver->sendData.pBuffer->pBuffer[pDriver->sendData.curSendNum]);
		}
	}
	else 
	{
        if (pDriver->pHardware->SetSendInterrupt)
    	{
    		pDriver->pHardware->SetSendInterrupt(false); 
    	}
	}
	pDriver->sendData.noSendTm = 0;
}

//接收数据
uchar f_UART1_ReceByte(void)
{
	return (uchar)usart_data_receive(USART0);
}

void f_UART1_RevData(COMM_DRIVER *pDriver)
{
	uchar iTempRceData;
	iTempRceData = f_UART1_ReceByte();
	if (pDriver->revData.curRevNum < pDriver->revData.pBuffer->size)
	{
		pDriver->revData.pBuffer->pBuffer[pDriver->revData.curRevNum] = iTempRceData;
		pDriver->revData.curRevNum ++;
	}
	else
	{
		pDriver->revData.revState = COMM_REV_STATE_OVER;
		if (pDriver->pHardware->SetRecInterrupt)
		{
			//单独缓存,故处理的时候接收关闭
			pDriver->pHardware->SetRecInterrupt(false);
		}
	}
	pDriver->revData.noRevTm = 0;
}

//波特率设置
void f_UART1_ChangeBaudRate(word_32 baudRate)
{
    //以下顺序请务必注意
    usart_interrupt_disable(USART0, USART_INT_TC); //发送中断关闭
    usart_interrupt_disable(USART0, USART_INT_RBNE); //接收中断关闭
    usart_disable(USART0); //关闭串口
    usart_baudrate_set(USART0, baudRate); //波特率设置
    usart_enable(USART0); //打开串口
    usart_interrupt_enable(USART0, USART_INT_RBNE); //接收缓存非空中断
    usart_interrupt_enable(USART0, USART_INT_TC); //发送完成使能
}


//中断设置
void f_UART1_SetSendInterrupt(uchar en)
{
    if (en)
    {
        usart_interrupt_enable(USART0, USART_INT_TC); //发送完成中断
    }
    else
    {
        usart_interrupt_disable(USART0, USART_INT_TC); //发送完成中断
    }
}

void f_UART1_SetRevInterrupt(uchar en)
{
    if (en)
    {
        usart_interrupt_enable(USART0, USART_INT_RBNE); //接收非空中断
    }
    else
    {
        usart_interrupt_disable(USART0, USART_INT_RBNE); //接收非空中断
    }
}



//====UART2====

//启动发送函数
void f_UART2_SatrtSend(COMM_DRIVER *pDriver)
{
	pDriver->sendData.curSendNum = 0;
	usart_data_transmit(USART1, pDriver->sendData.pBuffer->pBuffer[pDriver->sendData.curSendNum]); //发送第一个数据
	if (pDriver->pHardware->SetSendInterrupt)
	{
		pDriver->pHardware->SetSendInterrupt(true); //使能发送
	}
}

//发送数据
void f_UART2_SendData(COMM_DRIVER *pDriver)
{
	if (COMM_SEND_STATE_SENDING == pDriver->sendData.sendState)
	{
		pDriver->sendData.curSendNum ++;
		if (pDriver->sendData.curSendNum >= pDriver->sendData.needSendNum)
		{
			pDriver->sendData.curSendNum = 0;
			pDriver->sendData.sendState = COMM_SEND_STATE_OVER;
			if (pDriver->pHardware->SetSendInterrupt)
			{
				pDriver->pHardware->SetSendInterrupt(false); 
			}
		}
		else
		{
			usart_data_transmit(USART1, pDriver->sendData.pBuffer->pBuffer[pDriver->sendData.curSendNum]);
		}
	}
	else
	{
        if (pDriver->pHardware->SetSendInterrupt)
		{
			pDriver->pHardware->SetSendInterrupt(false); 
		}
	}
	pDriver->sendData.noSendTm = 0;
}

//接收数据
uchar f_UART2_ReceByte(void)
{
	return (uchar)usart_data_receive(USART1);
}

void f_UART2_RevData(COMM_DRIVER *pDriver)
{
	uchar iTempRceData;
	iTempRceData = f_UART2_ReceByte();
	if (pDriver->revData.curRevNum < pDriver->revData.pBuffer->size)
	{
		pDriver->revData.pBuffer->pBuffer[pDriver->revData.curRevNum] = iTempRceData;
		pDriver->revData.curRevNum ++;
	}
	else
	{
		pDriver->revData.revState = COMM_REV_STATE_OVER;
		if (pDriver->pHardware->SetRecInterrupt)
		{
			//单独缓存,故处理的时候接收关闭
			pDriver->pHardware->SetRecInterrupt(false);
		}
	}
	pDriver->revData.noRevTm = 0;
}

//波特率设置
void f_UART2_ChangeBaudRate(word_32 baudRate)
{
    //以下顺序请务必注意
    usart_interrupt_disable(USART1, USART_INT_TC); //发送中断关闭
    usart_interrupt_disable(USART1, USART_INT_RBNE); //接收中断关闭
    usart_disable(USART1); //关闭串口
    usart_baudrate_set(USART1, baudRate); //波特率设置
    usart_enable(USART1); //打开串口
    usart_interrupt_enable(USART1, USART_INT_RBNE); //接收缓存非空中断
    usart_interrupt_enable(USART1, USART_INT_TC); //发送完成使能
    
}


//中断设置
void f_UART2_SetSendInterrupt(uchar en)
{
    if (en)
    {
        usart_interrupt_enable(USART1, USART_INT_TC); //发送完成中断
    }
    else
    {
        usart_interrupt_disable(USART1, USART_INT_TC); //发送完成中断
    }
}

void f_UART2_SetRevInterrupt(uchar en)
{
    if (en)
    {
        usart_interrupt_enable(USART1, USART_INT_RBNE); //接收非空中断
    }
    else
    {
        usart_interrupt_disable(USART1, USART_INT_RBNE); //接收非空中断
    }
}




