/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : main.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月23日
  最近修改   :
  功能描述   : 西维XWT318主控板程序，含坐温、烘干加热;流量、喷杆电机控制;清洗流程控制;水温加热控制等
  函数列表   :
              
  修改历史   :
  1.日    期   : 2018年4月23日
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
void f_SysTimeCalc(void);

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/
SYS_TIME_FLAG sysTimeFlag;
SYSTEM_INFO systemInfo;

typedef union
{
	struct
	{
		uint bTask_1:1;
		uint bTask_2:1;
		uint bTask_3:1;
		uint bTask_4:1;
		uint bTask_5:1;
		uint bTask_6:1;
		uint bTask_7:1;
		uint bTask_8:1;
		uint bTask_9:1;
		uint bTask_10:1;
		uint rev:6;
	}m_bits;
	uint m_bytes;
}TAST_BALANCE; //任务均衡分配
TAST_BALANCE balance100Ms; // 任务分配计数,将任务调用分片
uchar balance100msCnt;

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
 
void main(void)
{
	f_Delay(3000);//上电后等电平稳定
	_DI();
	f_MCU_Init();
	f_FunctionInit();
	_EI();
	
	while (1)
	{
		f_MCU_FeedDog();//喂狗

		//1ms功能处理
		if (f_IsSysTime1Ms())
		{
			f_ClrSysTime1Ms();
		}
		
		//10ms功能处理
		if (f_IsSysTime10Ms())
		{
			f_ClrSysTime10Ms();
			f_SysTimeCalc();//产生时间片

			balance100Ms.m_bytes |= (0x0001 << balance100msCnt);
			balance100msCnt++;
			if (balance100msCnt >= 10)
			{
				balance100msCnt = 0;
			}
		}

		//50ms
		if (f_IsSysTime50Ms())
		{
			f_ClrSysTime50Ms();
		}

		//100ms-长时间基于此，勿删除
		if (f_IsSysTime100Ms())
		{
			f_ClrSysTime100Ms();
		}


		//100ms均衡任务平片
		if (balance100Ms.m_bytes)
		{
			if (balance100Ms.m_bits.bTask_1)
			{
			}
			else if (balance100Ms.m_bits.bTask_2)
			{
				
			}
			else if (balance100Ms.m_bits.bTask_3)
			{
			}
			else if (balance100Ms.m_bits.bTask_4)
			{
				
			}
			else if (balance100Ms.m_bits.bTask_5)
			{
				
			}
			else if (balance100Ms.m_bits.bTask_6)
			{
				
			}
			else if (balance100Ms.m_bits.bTask_7)
			{
			}
			else if (balance100Ms.m_bits.bTask_8)
			{

			}
			else if (balance100Ms.m_bits.bTask_9)
			{
			}
			else if (balance100Ms.m_bits.bTask_10)
			{
			}
			
			balance100Ms.m_bytes = 0;
		}

		//500ms
		if (f_IsSysTime500Ms())
		{
			f_ClrSysTime500Ms();
		}

		//1S
		if (f_IsSysTime1s())
		{
			f_ClrSysTime1S();
			f_AddU8Data(&(systemInfo.powerOnTm));
		}
	}
}

/*****************************************************************************
 函 数 名: f_SysTimeCalc
 功能描述  : 系统时间计算
 输入参数:
 返 回 值: 
 注     意: 10ms调用
 
 修改历史:
  1.日    期   : 2018年4月21日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_SysTimeCalc(void)
{
	if (sysTimeFlag.time10MsCnt % 10 == 0)
	{
		sysTimeFlag.longTimeFlag.bits.bSys100MsFlag = true;
	}

	if (sysTimeFlag.time10MsCnt % 20 == 0)
	{
		sysTimeFlag.longTimeFlag.bits.bSys200MsFlag = true;
	}

	if (++sysTimeFlag.time10MsCnt >= 20)
	{
		sysTimeFlag.time10MsCnt = 0;
	}

	if (f_IsSysTime100Ms())
	{
		if (sysTimeFlag.time100MsCnt % 5 == 0)
		{
			sysTimeFlag.longTimeFlag.bits.bSys500MsFlag = true;
		}

		if (sysTimeFlag.time100MsCnt % 10 == 0)
		{
			sysTimeFlag.longTimeFlag.bits.bSys1SFlag = true;
		}

		if (++sysTimeFlag.time100MsCnt >= 10)
		{
			sysTimeFlag.time100MsCnt = 0;
		}
	}

	if (f_IsSysTime1s())
	{
		if (sysTimeFlag.time1SCnt % 60 == 0)
		{
			sysTimeFlag.longTimeFlag.bits.bSys1MinFlag = true;
		}

		if (++sysTimeFlag.time1SCnt >= 60)
		{
			sysTimeFlag.time1SCnt = 0;
		}
	}
}
