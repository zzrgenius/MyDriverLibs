/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : CommDriver.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月8日
  最近修改   :
  功能描述   : 通信驱动，用于收发数据管理
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月8日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "CommDriver.h"
#include "SubFunction.h"
#include "CommProtocol.h"

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

/*****************************************************************************
 函 数 名: f_FindNextSendCMD
 功能描述  : 寻找下一个发送命令
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月8日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_FindNextSendCMD(COMM_DRIVER *pDriver)
{
    if (COMM_CMD_NULL != pDriver->sendData.curSendCMD)
	{
		//已重发完成
		if (pDriver->sendData.CMDSendCnt > COMM_GET_RETRY_CNT(pDriver->sendData.curSendCMD))
		{
			//是否需要循环发送
			if (COMM_IS_NEED_SYC(pDriver->sendData.curSendCMD))
			{
				//当前队列没有相同命令
				if (false == f_CommFindData(&(pDriver->sendData.queue), pDriver->sendData.curSendCMD))
				{
				
					 f_CommQueuePush(&(pDriver->sendData.queue), pDriver->sendData.curSendCMD);
				}
			}
		}
		else
		{
			return true;//继续当前命令
		}
    }
    return f_CommQueuePop(&(pDriver->sendData.queue), &(pDriver->sendData.curSendCMD));
}

/*****************************************************************************
 函 数 名: f_CommSendCMD
 功能描述  : 发送命令(内部命令)
 输入参数: pDriver驱动指针
 		   cmd需要发送命令
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月8日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_CommSendCMD(COMM_DRIVER *pDriver, QUEUE_DATA_TYPE cmd)
{
    return f_CommQueuePush(&(pDriver->sendData.queue), cmd);
}

/*****************************************************************************
 函 数 名: void f_CommDriverDeal(COMM_DRIVER *pDriver)
 功能描述  : 通信处理
 输入参数: pDriver驱动指针
 返 回 值: 
 注     意: 1ms调用
 
 修改历史:
  1.日    期   : 2018年4月19日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_CommDriverDeal(COMM_DRIVER *pDriver)
{
	COMM_FUNC_TAB const *pFuncTab = NULL;

	//发送部分
    f_AddU16Data(&(pDriver->sendData.noSendTm));
    switch(pDriver->sendData.sendState)
    {
		case COMM_SEND_STATE_IDLE://空闲	
			if (pDriver->sendData.noSendTm >= pDriver->pHardware->sendFrameItv)
			{
				//有命令需要发送(包括重发判断)
				if (f_FindNextSendCMD(pDriver))
				{
					pDriver->sendData.sendState = COMM_SEND_STATE_GET_BUFFER;
				}
			}
			break;

		case COMM_SEND_STATE_GET_BUFFER:
			//根据命令得到映射表
			pFuncTab = f_CommFindFuncTable(pDriver->sendData.curSendCMD);
			if (pFuncTab && pFuncTab->GetSendBuf)
			{
			    if (0 != pFuncTab->baudRate)//需要设置波特率
			    {
                    if (pDriver->pHardware->ChangeBaudRate) //硬件允许设置
                    {
                        pDriver->pHardware->ChangeBaudRate(pFuncTab->baudRate);
                    }
			    }
			    
				pFuncTab->GetSendBuf(pDriver);
				pDriver->sendData.sendState = COMM_SEND_STATE_START;
			}
			else
			{
				pDriver->sendData.sendState = COMM_SEND_STATE_IDLE;
			}
			break;

		case COMM_SEND_STATE_START:
			pDriver->sendData.noSendTm = 0;
			pDriver->sendData.CMDSendCnt ++;
			pDriver->sendData.sendState = COMM_SEND_STATE_SENDING;//防止进发送中断时状态不对，先赋值
			pDriver->pHardware->StartSend(pDriver);
			break;

		case COMM_SEND_STATE_SENDING:
			if (pDriver->sendData.noSendTm >= pDriver->pHardware->sendErrTm)
			{
				//发送超时,停止发送
				if (pDriver->pHardware->SetSendInterrupt)
				{
					pDriver->pHardware->SetSendInterrupt(false);
				}

				pDriver->sendData.sendState = COMM_SEND_STATE_OVER;
			}
			break;

		case COMM_SEND_STATE_OVER:
			if (pDriver->sendData.noSendTm >= pDriver->pHardware->waitReplyTm)
			{
				//等待应答超时
				pFuncTab = f_CommFindFuncTable(pDriver->sendData.curSendCMD);
				if (pFuncTab && pFuncTab->NoReplyDeal)
				{
					pFuncTab->NoReplyDeal(pDriver);
				}
				pDriver->sendData.sendState = COMM_SEND_STATE_IDLE;
			}
			break;
			
		case COMM_SEND_STATE_REPLY://该状态在接收处理函数中设置
			pDriver->sendData.sendState = COMM_SEND_STATE_IDLE;
			pDriver->sendData.curSendCMD = COMM_CMD_NULL;
			pDriver->sendData.CMDSendCnt = 0;
			f_Memset(pDriver->sendData.pBuffer->pBuffer, 0, pDriver->sendData.pBuffer->size);//发送缓存清零
			break;

		default:
			break;
    }

    //接收处理
    f_AddU16Data(&(pDriver->revData.noRevTm));
    switch(pDriver->revData.revState)
    {
		case COMM_REV_STATE_WAIT://等待接收	
			if ( pDriver->revData.noRevTm > 0
			&& (pDriver->revData.noRevTm % pDriver->pHardware->frameRevOverItv == 0))//帧间隔结束时间到
			{
				if (pDriver->revData.curRevNum > 0)
				{
					pDriver->revData.noRevTm = 0;
					pDriver->revData.revState = COMM_REV_STATE_OVER;
					if (pDriver->pHardware->SetRecInterrupt)
					{
						//单独缓存,故处理的时候接收关闭
						pDriver->pHardware->SetRecInterrupt(false);
					}
				}
			}
			break;

		case COMM_REV_STATE_OVER:
			if (f_CommRevDeal(pDriver))
			{
				//根据命令得到映射表
				pFuncTab = f_CommFindFuncTable(pDriver->revData.curRevCMD);
				//当前已收到发送命令应答
				if (pDriver->revData.curRevCMD == pDriver->sendData.curSendCMD)
				{
					pDriver->sendData.sendState = COMM_SEND_STATE_REPLY;
				}
				
				if (pFuncTab && pFuncTab->RevDataDeal)
				{
					//命令数据处理
					pFuncTab->RevDataDeal(pDriver);
				}
			}

			pDriver->revData.revState = COMM_REV_STATE_WAIT;
			pDriver->revData.noRevTm = 0;
			pDriver->revData.curRevNum = 0;
			if (pDriver->pHardware->SetRecInterrupt)
			{
				pDriver->pHardware->SetRecInterrupt(true);
			}
			//接收缓存清零
			f_Memset(pDriver->revData.pBuffer->pBuffer, 0, pDriver->revData.pBuffer->size);
			break;

		
		default:
			break;
    }
}

/*****************************************************************************
 函 数 名: f_CommDriverInit
 功能描述: 通信驱动初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月8日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_CommDriverInit(COMM_DRIVER *pDriver, 
							const COMM_HARDWARE *pHardware, 
							const COMM_FRAME_BUFFER *pSendBuf, 
							const COMM_FRAME_BUFFER *pRevBuf)
{
    f_Memset(pDriver, 0, sizeof(COMM_DRIVER));
    pDriver->pHardware = pHardware;
    pDriver->sendData.pBuffer = pSendBuf;
    pDriver->revData.pBuffer = pRevBuf;
    f_CommQueueInit(&(pDriver->sendData.queue));
}