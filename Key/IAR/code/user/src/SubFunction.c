/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : SubFunction.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月13日
  最近修改   :
  功能描述   : 公用小程序及一些公用宏
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
 #include "SubFunction.h"

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
 函 数 名: void f_AddU8Data(uchar *pData)
 功能描述: 累加8位无符号型数据
 输入参数: 无
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_AddU8Data(uchar *pData)
{
    if (*pData < 0xff)
    {
		(*pData) ++;
    }
}

/*****************************************************************************
 函 数 名: void f_Dec8Data(uchar *pData)
 功能描述: 递减8位无符号型数据
 输入参数: 无
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_DecU8Data(uchar *pData)
{
    if (*pData > 0)
    {
		(*pData) --;
    }
}

/*****************************************************************************
 函 数 名: void f_AddU16Data(uint *pData)
 功能描述: 累加16位无符号型数据
 输入参数: 
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_AddU16Data(uint *pData)
{
    if (*pData < 0xffff)
    {
		(*pData) ++;
    }
}

/*****************************************************************************
 函 数 名: void f_Dec8Data(uint *pData)
 功能描述: 递减16位无符号型数据
 输入参数: 
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_DecU16Data(uint *pData)
{
    if (*pData > 0)
    {
		(*pData) --;
    }
}

/*****************************************************************************
 函 数 名: void f_AddU32Data(ulong *pData)
 功能描述: 累加32位无符号型数据
 输入参数: 
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_AddU32Data(ulong *pData)
{
    if (*pData < 0xffffffff)
    {
		(*pData) ++;
    }
}

/*****************************************************************************
 函 数 名: void f_Dec32Data(ulong *pData)
 功能描述: 递减32位无符号型数据
 输入参数: 
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_DecU32Data(ulong *pData)
{
    if (*pData > 0)
    {
		(*pData) --;
    }
}

/*****************************************************************************
 函 数 名: void f_AddRunTimerMinute(MINUTE_DEF pTime)
 功能描述: 分钟时间累加
 输入参数: 
 返 回 值: 
 注     意: 1S时基调用
 
 修改历史:
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_AddRunTimerMinute(MINUTE_DEF *pTime)
{
	pTime->second ++;
	if ((pTime->second ++) >= 60)
	{
		pTime->second = 0;
		f_AddU16Data(&(pTime->minute));
	}
}

/*****************************************************************************
 函 数 名: void f_AddRunTimerHour(HOUR_DEF *pTime)
 功能描述: 小时时间累加
 输入参数: 
 返 回 值: 
 注     意: 1S时基调用
 
 修改历史:
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_AddRunTimerHour(HOUR_DEF *pTime)
{
	pTime->second ++;
	if ((pTime->second ++) >= 60)
	{
		pTime->second = 0;
		if ((pTime->minute ++) >= 60)
		{
			f_AddU16Data(&(pTime->hour));
		}
	}
}

/*****************************************************************************
 函 数 名: f_Memset
 功能描述: 
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月13日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_Memset(void *pData, uchar setValue, uint size)
{
    uchar *pValue = (uchar *)pData;

	while (size --)
	{
		*pValue ++ = setValue;
	}
}
