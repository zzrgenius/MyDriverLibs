/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : ICDriverET6226.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月18日
  最近修改   :
  功能描述   : 芯片ET6226驱动，支持写入和读取
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "ICDriverET6226.h"
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
IC_DRIVER_ET6226 icDriverET6226;

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

/*****************************************************************************
 函 数 名: f_ICDriverET6226WriteCMD
 功能描述  : 向ET6226写命令
 输入参数: pDriver: 驱动指针
 		   cmd :下发命令
 返 回 值: true:成功l;false失败
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_ICDriverET6226WriteCMD(uint cmd)
{
	f_I2CDriverStop(icDriverET6226.pI2CDriver);
	f_I2CDriverStart(icDriverET6226.pI2CDriver);
	f_I2CDriverWriteByte(icDriverET6226.pI2CDriver, (uchar)(cmd>>8));
	if(false == f_I2CDriverReadAck(icDriverET6226.pI2CDriver))//判定ACK
	{
		return false;
	}
	
	f_I2CDriverWriteByte(icDriverET6226.pI2CDriver, (uchar)(cmd));
 	if(false == f_I2CDriverReadAck(icDriverET6226.pI2CDriver))//判定ACK
	{
		return false;
	}
 	f_I2CDriverStop(icDriverET6226.pI2CDriver);
	return true;
}

/*****************************************************************************
 函 数 名: f_ICDriverET6226ReadKey
 功能描述  : 读取ET6226按键值
 输入参数: pDriver: 驱动指针
 		   pKey :按键缓存指针
 返 回 值: true:成功l;false失败
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_ICDriverET6226ReadKey(uchar *pKey)
{
    f_I2CDriverStop(icDriverET6226.pI2CDriver);
	f_I2CDriverStart(icDriverET6226.pI2CDriver);
	f_I2CDriverWriteByte(icDriverET6226.pI2CDriver, (uchar)(ET6226_CMD_GET_KEY>>8));
	if(false == f_I2CDriverReadAck(icDriverET6226.pI2CDriver))//判定ACK
	{
		return false;
	}

	*pKey = f_I2CDriverReadByte(icDriverET6226.pI2CDriver);
	return true;
}

/*****************************************************************************
 函 数 名: f_ICDriverET6226Init
 功能描述  : ET6226驱动初始化
 输入参数: pI2CDriver:i2c驱动指针
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月18日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_ICDriverET6226Init(I2C_DRIVER *pI2CDriver)
{
    f_Memset(&icDriverET6226, 0, sizeof(IC_DRIVER_ET6226));
    icDriverET6226.pI2CDriver = pI2CDriver;
    f_ICDriverET6226WriteCMD(ET6226_CMD_8_SEG);//8段码,亮度等级,开启显示,键盘
}
