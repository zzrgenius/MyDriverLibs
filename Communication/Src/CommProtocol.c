/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : CommProtocol.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月8日
  最近修改   :
  功能描述   : 通信协议相关数据，主要用于串口
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月8日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "HeadInclude.h"

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/
void f_CommFuncIheatGetBuf(COMM_DRIVER *pDriver);
void f_CommFuncIheatRevDeal(COMM_DRIVER *pDriver);
void f_CommFuncChangeGetBuf(COMM_DRIVER *pDriver);
void f_CommFuncChangeRevDeal(COMM_DRIVER *pDriver);

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/
//====功能回调表====
#define COMM_FUC_TAB_SIZE (sizeof(tab_commFunc)/sizeof(COMM_FUNC_TAB))
const COMM_FUNC_TAB tab_commFunc[] =
{
	//即热通信
	{
	    2400u,//如果同一个串口不需要修改可设置为0,同时将硬件驱动的波特率修改函数设为NULL
		COMM_CMD_IHEAT, //内部命令
		f_CommFuncIheatRevDeal,//接收处理函数
		f_CommFuncIheatGetBuf,//发送处理函数
		f_CheckIheatCommErr//无应答处理函数
	},

	//转接板通信
	{
	    9600u,
		COMM_CMD_CHANGE, //内部命令
		f_CommFuncChangeRevDeal,//接收处理函数
		f_CommFuncChangeGetBuf,//发送处理函数
		f_CheckChangeCommErr//无应答处理函数
	}
};

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
//====协议发送、接收处理函数====
//即热发送协议
void f_CommFuncIheatGetBuf(COMM_DRIVER *pDriver)
{
	PROTOCOL_IHEAT_SEND sendData;
	f_Memset(&sendData, 0, sizeof(PROTOCOL_IHEAT_SEND));
	//数据转换
	sendData.headCode = FRAME_IHEAT_HEAD;
	sendData.add = 0xf0;
	sendData.mode = 0x81;
	sendData.endCode = 0x34;
	sendData.setTempLSB = (uchar)(functionInfo.outTempInfo.setTemp * 10);
	sendData.setTempMSB = (uchar)((functionInfo.outTempInfo.setTemp * 10) >> 8);
	sendData.bOnOff = functionInfo.bEnHeat;
	sendData.xorValue = f_CalcXOR((uchar *)&(sendData.add), sizeof(PROTOCOL_IHEAT_SEND) - 3);//校验数据
	
	//加载缓存
	f_Memset(pDriver->sendData.pBuffer->pBuffer, 0, pDriver->sendData.pBuffer->size);
	f_MemCpy(pDriver->sendData.pBuffer->pBuffer, &sendData, sizeof(PROTOCOL_IHEAT_SEND));
	pDriver->sendData.needSendNum = sizeof(PROTOCOL_IHEAT_SEND);//发送长度
}

//即热接收协议
void f_CommFuncIheatRevDeal(COMM_DRIVER *pDriver)
{
	PROTOCOL_IHEAT_REV revData;
	f_Memset(&revData, 0, sizeof(PROTOCOL_IHEAT_REV));
	f_MemCpy(&revData, pDriver->revData.pBuffer->pBuffer, sizeof(PROTOCOL_IHEAT_REV));
	funcError.iheatNoReplyCnt = 0;
	
	//数据转换
	functionInfo.curWaterFlow = revData.flowMSB;
	functionInfo.curWaterFlow <<= 8;
	functionInfo.curWaterFlow += revData.flowLSB;

	functionInfo.outTempInfo.sensorTemp = revData.OutTempMSB;
	functionInfo.outTempInfo.sensorTemp <<= 8;
	functionInfo.outTempInfo.sensorTemp += revData.OutTempLSB;
	functionInfo.outTempInfo.sensorTemp /= 10; //过来的温度放大了10倍
	functionInfo.outTempInfo.bOpenFlag = revData.bErrorOutTempOpen;
	functionInfo.outTempInfo.bShortFlag = revData.bErrorOutTempShort;

	functionInfo.inTempInfo.sensorTemp = revData.InTempMSB;
	functionInfo.inTempInfo.sensorTemp <<= 8;
	functionInfo.inTempInfo.sensorTemp += revData.InTempLSB;
	functionInfo.inTempInfo.sensorTemp /= 10; //过来的温度放大了10倍
	functionInfo.inTempInfo.bOpenFlag = revData.bErrorInTempOpen;
	functionInfo.inTempInfo.bShortFlag = revData.bErrorInTempShort;
}

//转接板发送协议
void f_CommFuncChangeGetBuf(COMM_DRIVER *pDriver)
{
	PROTOCOL_CHANGE_SEND sendData;
	f_Memset(&sendData, 0, sizeof(PROTOCOL_CHANGE_SEND));
	//数据转换
	sendData.headCode = 0x55;
	sendData.mode = 1;
	sendData.sysState = (uchar)(systemInfo.sysState);
	sendData.curFunc = (uchar)(functionInfo.curFunction);
	sendData.lidCMD = (uchar)(functionInfo.sendLidCmd);
	sendData.keyCode = functionInfo.reSendKey; //按键值回传
	sendData.adjustIndex = (uchar)funcFlush.adjustIndex;
	
	sendData.bFlushState = funcFlush.curStep == FLUSH_SREQ_STOP?false:true;
	sendData.bWashMove = (funcWashHip.flags.m_bits.bEnMove || funcWashFemale.flags.m_bits.bEnMove);
	sendData.bStrongWeak = (funcWashHip.flags.m_bits.bEnStrongWeak || funcWashFemale.flags.m_bits.bEnStrongWeak);
	sendData.bColdHot = (funcWashHip.flags.m_bits.bEnColdHot || funcWashFemale.flags.m_bits.bEnColdHot);
	sendData.bErrNoWater = funcError.bErrNoWater;
	sendData.bKeyDryIO = FLUSH_KEY;
	sendData.bFlushAdjust = funcFlush.bAdjust;
	sendData.bFourceSit = funcSit.bFourceSit;

	sendData.xorValue = f_CalcXOR((uchar *)&(sendData.headCode), sizeof(PROTOCOL_CHANGE_SEND) - 1);//校验数据
	
	//加载缓存
	f_Memset(pDriver->sendData.pBuffer->pBuffer, 0, pDriver->sendData.pBuffer->size);
	f_MemCpy(pDriver->sendData.pBuffer->pBuffer, &sendData, sizeof(PROTOCOL_CHANGE_SEND));
	pDriver->sendData.needSendNum = sizeof(PROTOCOL_CHANGE_SEND);//发送长度
}

//转接板接收协议
void f_CommFuncChangeRevDeal(COMM_DRIVER *pDriver)
{
	PROTOCOL_CHANGE_REV revData;
	f_Memset(&revData, 0, sizeof(PROTOCOL_CHANGE_REV));
	f_MemCpy(&revData, pDriver->revData.pBuffer->pBuffer, sizeof(PROTOCOL_CHANGE_REV));
	funcError.changeNoReplyCnt = 0;
	
	//数据转换
	functionInfo.getKeyCode = revData.keyCode;
	functionInfo.reSendKey = revData.keyCode;
	funcSeatHeat.sensorInfo.sensorTemp = revData.seatTemp;
	funcSeatHeat.sensorInfo.bOpenFlag = revData.bErrSeatTempOpen;
	funcSeatHeat.sensorInfo.bShortFlag = revData.bErrSeatTempShort;

	if (functionInfo.sendLidCmd == revData.lidCmd)//转接板已收到命令
	{
		functionInfo.sendLidCmd = LID_RUN_CMD_NULL;
	}
	functionInfo.lidCmd = (LID_MOTOR_CMD)(revData.lidCmd);
	
	functionInfo.waterTempLevel = (FUNC_SET_LEVEL)(revData.waterLevel);//水温档位
	funcSeatHeat.level = (FUNC_SET_LEVEL)(revData.seatLevel);//座温档位
	funcDry.level = (FUNC_SET_LEVEL)(revData.dryLevel);//风温温档位
	functionInfo.setPos = (FUNC_SET_LEVEL)(revData.nozzlePos);//管位
	functionInfo.setFlow = (FUNC_SET_LEVEL)(revData.flowPos);//流量
	functionInfo.topLidRange = (LID_MOTOR_RANGE)(revData.topLidRange); //上盖位置
	functionInfo.seatLidRange = (LID_MOTOR_RANGE)(revData.seatLidRange); //座圈位置
	
	funcSit.state = (STATE_INFO)(revData.bSitState || funcSit.bFourceSit);
	functionInfo.bHasPerson = revData.bHasPerson;
	functionInfo.bChangeBoardKey = revData.bKeyPressed;
}

//====接口功能函数====

/*****************************************************************************
 函 数 名: f_CommFindFuncTable
 功能描述  : 根据命令查找相关处理函数
 输入参数:
 返 回 值: 
 注     意: 不修改
 
 修改历史:
  1.日    期   : 2018年5月8日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
COMM_FUNC_TAB const * f_CommFindFuncTable(QUEUE_DATA_TYPE cmd)
{
	uchar i;
	COMM_FUNC_TAB const * pTable = NULL;
    for (i = 0; i < COMM_FUC_TAB_SIZE; i++)
    {
		if (tab_commFunc[i].internalCMD == cmd)
		{
			pTable = &tab_commFunc[i];
			break;
		}
    }
    return pTable;
}

/*****************************************************************************
 函 数 名: f_CommRevDeal
 功能描述  : 接收处理函数
 输入参数:
 返 回 值: 
 注     意: 根据命令修改
 
 修改历史:
  1.日    期   : 2018年5月8日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_CommRevDeal(COMM_DRIVER *pDriver)
{
    if (pDriver->revData.pBuffer->pBuffer[0] == FRAME_IHEAT_HEAD 
     && pDriver->revData.pBuffer->pBuffer[1] == FRAME_IHEAT_ADD)
    {
		if (pDriver->revData.pBuffer->pBuffer[PFRAME_IHEAT_REV_LEN - 2] == f_CalcXOR(&pDriver->revData.pBuffer->pBuffer[PFRAME_IHEAT_ADD_POS], PFRAME_IHEAT_REV_LEN - 3))
		{
			//即热接收判断
			pDriver->revData.curRevCMD = COMM_CMD_IHEAT;
			return true;
		}
    }
    else if (pDriver->revData.pBuffer->pBuffer[0] == FRAME_CHANGE_HEAD)
    {
		if (pDriver->revData.pBuffer->pBuffer[PFRAME_CHANGE_REV_LEN - 1] == f_CalcXOR(pDriver->revData.pBuffer->pBuffer, PFRAME_CHANGE_REV_LEN - 1))
		{
			//转接板接收判断
			pDriver->revData.curRevCMD = COMM_CMD_CHANGE;
			return true;
		}
		else
		{
			pDriver->revData.curRevCMD = 0;
		}
    }
    return false;
}
