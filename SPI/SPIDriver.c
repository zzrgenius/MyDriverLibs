/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : SPIDriver.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月21日
  最近修改   :
  功能描述   : SIP总线驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月21日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "SPIDriver.h"
#include "SubFunction.h"
#include "IO_Define.h"

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
#define SPI_DL_TM 0

/*****************************************************************************
 函 数 名: void f_SPIWriteData(uint sendData, uchar length)
 功能描述  : SPI总线写数据
 输入参数:
 返 回 值: sendData:发送数据;length：发送位数
 注     意: 最多2字节
 
 修改历史:
  1.日    期   : 2018年4月21日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_SPIWriteData(SPI_DRIVER *pDriver, uint sendData, uchar length)
{
	schar i;

	for (i = length - 1; i >= 0; i--)
	{
	    #if defined(MODE0) //下降沿写
		    pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE1) //上升沿写
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE2) //上升沿写
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE3) //下降沿写
		    pDriver->pHardware->ClockOut(STATE_ON);
		#endif
		
		if ((sendData>>i)&(0x0001))//发送高位
		{
			pDriver->pHardware->DataOut(STATE_ON);
		}
		else
		{
			pDriver->pHardware->DataOut(STATE_OFF);
		}
		#if (SPI_DL_TM > 0)
			pDriver->pHardware->Delay();
		#endif
		#if defined(MODE0) 
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE1)
		    pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE2)
		    pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE3)
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#endif
		#if (SPI_DL_TM > 0)
			pDriver->pHardware->Delay();
		#endif
	}
}

/*****************************************************************************
 函 数 名: uint f_SPIReadData(uchar length)
 功能描述  : 从SPI总线上读取一个字节
 输入参数: length 发送位长度
 返 回 值: 读取数据
 注     意: 最多2字节
 
 修改历史:
  1.日    期   : 2018年4月21日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uint f_SPIReadData(SPI_DRIVER *pDriver, uchar length)
{
    uint getData = 0;
    uchar i;

    for (i = 0; i < length; i++)
    {
		#if defined(MODE0) //上升沿读
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE1) //下降沿读
		    pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE2) //下降沿读
		    pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE3) //上升沿读
		    pDriver->pHardware->ClockOut(STATE_OFF);
		#endif
		
		#if (SPI_DL_TM > 0)
			pDriver->pHardware->Delay();
		#endif
		
		getData <<= 1;
		if (pDriver->pHardware->DataIn())
		{
			getData |= 0x0001;
		}
		
        #if defined(MODE0)
            pDriver->pHardware->ClockOut(STATE_ON);
		#elif defined(MODE1)
            pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE2)
            pDriver->pHardware->ClockOut(STATE_OFF);
		#elif defined(MODE3)
            pDriver->pHardware->ClockOut(STATE_ON);
		#endif

    }
    return getData;
}

/*****************************************************************************
 函 数 名: f_SPIEnChip
 功能描述  : SPI使能选择
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月23日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_SPIEnChip(SPI_DRIVER *pDriver, STATE_INFO state)
{
    pDriver->pHardware->EnChip(state);
}

/*****************************************************************************
 函 数 名: f_SPIDriverInit
 功能描述  : SPI驱动初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月23日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_SPIDriverInit(SPI_DRIVER *pDriver, const SPI_HARDWARE_DRIVER *pHardware)
{
    f_Memset(pDriver, 0, sizeof(SPI_DRIVER));
    pDriver->pHardware = pHardware;
}

