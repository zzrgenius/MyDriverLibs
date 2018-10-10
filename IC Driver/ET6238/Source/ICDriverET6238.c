/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : ICDriverET6238.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月28日 星期一
  最近修改   :
  功能描述   : ET6238驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "ICDriverET6238.h"
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
IC_DRIVER_ET6238 ic_ET6238;


/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

/*****************************************************************************
 函 数 名: f_ET6238_WriteCMD
 功能描述  : ET6238写命令
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_ET6238_WriteCMD(uchar cmd)
{

	if (false == f_I2CDriverWriteSlaveAddr(ic_ET6238.pI2CDriver, ET6238_SLAVE_ADDR)) //写器件地址
	{
        return false;
	}

	f_I2CDriverWriteByte(ic_ET6238.pI2CDriver, cmd); //写数据
	if (false == f_I2CDriverReadAck(ic_ET6238.pI2CDriver)) //等待ACK
	{
        return false;
	}

    f_I2CDriverStop(ic_ET6238.pI2CDriver);
    return true;
}

/*****************************************************************************
 函 数 名: f_ET6238_WriteByte
 功能描述  : 向ET6238写一个字节
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_ET6238_WriteByte(uchar addr, uchar data)
{
    return f_I2CDriverWriteSlaveByte(ic_ET6238.pI2CDriver, ET6238_SLAVE_ADDR, addr, data);
}

/*****************************************************************************
 函 数 名: f_ET6238_WriteBytes
 功能描述  : 向ET6238写多个数据
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_ET6238_WriteBytes(uchar addr, uchar *pData, uint len)
{
    return f_I2CDriverWriteSlaveBytes(ic_ET6238.pI2CDriver, ET6238_SLAVE_ADDR, addr, pData, len);
}

/*****************************************************************************
 函 数 名: f_ET6238_ReadByte
 功能描述  : 向ET6238读一个字节
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_ET6238_ReadByte(uchar addr, uchar *pData)
{
    return f_I2CDriverReadSlaveByte(ic_ET6238.pI2CDriver, ET6238_SLAVE_ADDR, addr, pData);
}

/*****************************************************************************
 函 数 名: f_ET6238_ReadBytes
 功能描述  : 向ET6238读多个数据
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_ET6238_ReadBytes(uchar addr, uchar *pData, uint len)
{
    return f_I2CDriverReadSlaveBytes(ic_ET6238.pI2CDriver, ET6238_SLAVE_ADDR, addr, pData, len);
}

/*****************************************************************************
 函 数 名: f_ET6238_ShowData
 功能描述  : ET6238显示数据刷新
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_ET6238_ShowData(uchar *pData, uint len)
{
    f_ET6238_WriteBytes(ET6238_COM0_ADDR, pData, len); //写入显示数据
    f_ET6238_WriteCMD(ET6238_DIS_ON); //显示开启
}

/*****************************************************************************
 函 数 名: f_ET6238_ReadAllKey
 功能描述  : 读取按键
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_ET6238_ReadAllKey(uchar *pData, uint len)
{
    f_ET6238_ReadBytes(ET6238_KEY_ADDR, pData, len); //读按键
}

/*****************************************************************************
 函 数 名: f_ET6238Init
 功能描述  : ET6238初始化
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_ET6238Init(I2C_DRIVER *pI2CDriver)
{
    f_Memset(&ic_ET6238, 0, sizeof(IC_DRIVER_ET6238));
    ic_ET6238.pI2CDriver = pI2CDriver;

    f_ET6238_WriteCMD(ET6238_SYSTEM_ON);
    f_ET6238_WriteCMD(ET6238_INT_ROW);
    f_ET6238_WriteCMD(ET6238_LIGHT_L16);
    f_ET6238_WriteCMD(ET6238_DIS_OFF);
}

