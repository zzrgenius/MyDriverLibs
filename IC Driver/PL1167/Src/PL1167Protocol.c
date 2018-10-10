/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : PL1167Protocol.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月24日
  最近修改   :
  功能描述   : PL1167协议处理
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月24日
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

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/
PROCOTOL_XI_MA_RC procotolXiMaRC;//西马遥控器协议
uchar machineID[MACHINE_CODE_LEN];//机器配对码

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/
uint dealFrameCnt;


/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/


/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
#define COMM_HEAD_LEN 10
#define FRAME_INDEX_POS 3
#define MACHINE_CODE_POS 4

//西马遥控器相关
#define XIMA_RC_CMD_CODE 0x0f//西马遥控命令码
#define PACKET_LEN sizeof(PROCOTOL_XI_MA_RC)//内部封包大小(实际需要转红外的协议)
#define XIMA_FRAME_LEN (PACKET_LEN + COMM_HEAD_LEN + 1)//整帧数据大小(通用头长度+封包长度+校验和)

//配对命令相关
#define MATCH_CMD_CODE 0x0A//配对命令码
#define MATCH_FRAME_LEN	XIMA_FRAME_LEN//配对帧长度




/*****************************************************************************
 函 数 名: f_CompareValue
 功能描述  : 比较2个数组是否相等
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月29日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_CompareValue(uchar *pSrc, uchar *pDst, uchar len)
{
	uchar i;
	
    for (i = 0; i < len; i++)
    {
		if (*pSrc != *pDst)
		{
			return false;
		}
		pDst++;
		pSrc++;
    }
    return true;
}

/*****************************************************************************
 函 数 名: f_IsRevMachineID
 功能描述  : 判断是否为保留ID，0~10为保留ID，可以用于生产等，这些ID不校验不存储
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月3日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_IsRevMachineID(const uchar *pData, uchar len)
{
    uchar i;

    for (i = 1; i < len; i ++)
    {
		if (0 != pData[i])//前面数据全为0
		{
			return false;
		}
    }

    if (pData[0] <= 10)
    {
		return true;
    }
    return false;
}
 
/*****************************************************************************
 函 数 名: f_PL1167_GetSendBuffer
 功能描述  : 获取发送数据缓存
 输入参数: pBuf:缓存指针;len缓存长度
 返 回 值: 实际发送数据长度
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月23日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_PL1167_GetSendBuffer(uchar *pBuf, uint len)
{
	static uchar frameIndex = 0;//帧序号,每次发送加1
	/*
		传输协议
		Head + MachineID + 封包协议 + CheckSum
		0x33
		封包协议：西马
		头码		机型码		数据1	     数据2	数据3  	数据4	    结束码
		0xEE	0x59	Data0	Data1	Data2	Data3	0x55

		数据1：
		Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
		电源		停止		烘干		女性清洗	臀部清洗	喷杆高	喷杆中	喷杆低

		数据2：
		Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
				坐温高	  	坐温中		坐温低				水温高		水温中	水温低

		数据3：
		Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
				冲水		宽幅		喷杆清洗	液晶背光   	夜灯		按摩		保存
	*/

	f_Memset(pBuf, 0, len);
    f_Memset(&procotolXiMaRC, 0, PACKET_LEN);
    
	//====内部协议头码====
	pBuf[0] = 0x55;
	pBuf[1] = 0xaa;
	pBuf[2] = 0xf0;
	pBuf[FRAME_INDEX_POS] = frameIndex++;
	
//	pBuf[4] = functionData.machineID[0];
//	pBuf[5] = functionData.machineID[1];
//	pBuf[6] = functionData.machineID[2];

	//====数据转化====
	procotolXiMaRC.machineCode = 0x59;
	procotolXiMaRC.endCode = 0x55;
	
	//功能
	
	
	//====载入缓存====
	f_MemCpy(&pBuf[COMM_HEAD_LEN], &procotolXiMaRC, PACKET_LEN);
	
	//====校验和====
	pBuf[XIMA_FRAME_LEN - 1] = f_CalcAddSum(pBuf, XIMA_FRAME_LEN - 1);
	
    return XIMA_FRAME_LEN;
}

/*****************************************************************************
 函 数 名: f_PL1167_RevProtocolDeal
 功能描述  : 接收到数据包后处理
 输入参数: pData数据缓存
 		   len缓存长度
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月24日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_PL1167_RevProtocolDeal(uchar *pData, uchar len)
{
	static uchar frameIndex = 100;//遥控器从0开始,防止一致
	
	if (len < XIMA_FRAME_LEN)
	{
		return false;
	}

    if (len > 3 && 0x55 == pData[0] && 0xaa == pData[1])
    {
    	if (MATCH_CMD_CODE == pData[2])//配对模式
    	{
			if (pData[MATCH_FRAME_LEN - 1] == f_CalcAddSum(pData, MATCH_FRAME_LEN - 1))
			{
				//防止连续发送帧收到生效
				if (frameIndex != pData[FRAME_INDEX_POS])
				{
					frameIndex = pData[FRAME_INDEX_POS];
					//当前正在配对模式
					if (SYS_STATE_MATCH == systemInfo.sysState)
					{
						//读取遥控ID
						f_MemCpy(machineID, &pData[MACHINE_CODE_POS], MACHINE_CODE_LEN);

						//判断是否为保留ID
						if (false == f_IsRevMachineID(machineID, MACHINE_CODE_LEN))
						{
							//存储遥控ID
							f_MCU_WriteToEEPROM(0, MACHINE_CODE_LEN, machineID);

							//发送功能停止(主要是为了蜂鸣)
							f_IR_StartSend(&pData[COMM_HEAD_LEN], PACKET_LEN);

							//配对结束，进入正常功能
							systemInfo.sysState = SYS_STATE_RUN;
						}
					}
				}
			}
    	}
    	else if (XIMA_RC_CMD_CODE == pData[2])//正常模式
    	{
			if (pData[XIMA_FRAME_LEN - 1] == f_CalcAddSum(pData, XIMA_FRAME_LEN - 1))
			{
				//防止连续发送帧收到生效
				if (frameIndex != pData[FRAME_INDEX_POS])
				{
					frameIndex = pData[FRAME_INDEX_POS];
					dealFrameCnt ++;

					//比较当前ID(保留ID直接校验通过)
					if (f_IsRevMachineID(&pData[MACHINE_CODE_POS], MACHINE_CODE_LEN) 
					|| f_CompareValue(machineID, &pData[MACHINE_CODE_POS], MACHINE_CODE_LEN))
					{
						//红外发送数据启动
						f_IR_StartSend(&pData[COMM_HEAD_LEN], PACKET_LEN);
					}
					return true;
				}
			}
		}
    }
    return false;
}

