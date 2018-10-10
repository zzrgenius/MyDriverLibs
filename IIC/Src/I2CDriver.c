/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : I2CDriver.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年4月17日
  最近修改   :
  功能描述   : 通用I2C驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "I2CDriver.h"
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
 #define MAX_READ_ACK_CNT 20
 #define IIC_MAX_WRITE_CNT 5

/*****************************************************************************
 函 数 名: void f_I2CDriverStart(I2C_DRIVER *pDriver)
 功能描述: I2C驱动在总线产生一个开始信号
 输入参数: pDriver I2C驱动指针
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_I2CDriverStart(I2C_DRIVER *pDriver)
{
    pDriver->pHardDriver->ClockOut(true);
    pDriver->pHardDriver->DataOut(true);
    pDriver->pHardDriver->SetDataDir(IO_DIR_OUT);
    pDriver->pHardDriver->DataOut(false);
    pDriver->pHardDriver->ClockOut(false);
}

/*****************************************************************************
 函 数 名: void f_I2CDriverStop(I2C_DRIVER *pDriver)
 功能描述: I2C驱动在总线产生一个停止信号
 输入参数: pDriver I2C驱动指针
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_I2CDriverStop(I2C_DRIVER *pDriver)
{
    pDriver->pHardDriver->DataOut(false);
    pDriver->pHardDriver->SetDataDir(IO_DIR_OUT);
    pDriver->pHardDriver->ClockOut(true);
    pDriver->pHardDriver->DataOut(true);
}

/*****************************************************************************
 函 数 名: void f_I2CDriverWriteAck(I2C_DRIVER *pDriver, I2C_DRIVER_ACK_TYPE ack)
 功能描述: I2C驱动在总线产生一个应答信号
 输入参数: pDriver I2C驱动指针
 		   ack 应答信号
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_I2CDriverWriteAck(I2C_DRIVER *pDriver, I2C_DRIVER_ACK_TYPE ack)
{
	if(I2C_DRIVER_ACK == ack)//应答数据线输出低电平
	{
		pDriver->pHardDriver->DataOut(false);
	}
	else//应答非数据线输出高电平
	{
		pDriver->pHardDriver->DataOut(true);
	}
	pDriver->pHardDriver->SetDataDir(IO_DIR_OUT);
	pDriver->pHardDriver->ClockOut(true);
	pDriver->pHardDriver->ClockOut(false);
}

/*****************************************************************************
 函 数 名: void f_I2CDriverWriteByte(I2C_DRIVER *pDriver, uchar data)
 功能描述: 向I2C总线写一个字节数据
 输入参数: pDriver I2C驱动指针
 		   data 写入数据
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_I2CDriverWriteByte(I2C_DRIVER *pDriver, uchar data)
{
    uchar i;

	pDriver->pHardDriver->ClockOut(false);
	pDriver->pHardDriver->SetDataDir(IO_DIR_OUT);
	for (i = 0; i < 8; i++)
	{
		if ((data<<i)&0x80)
		{
			pDriver->pHardDriver->DataOut(true);
		}
		else
		{
			pDriver->pHardDriver->DataOut(false);
		}
		pDriver->pHardDriver->ClockOut(true);
		pDriver->pHardDriver->ClockOut(false);
	}
}

/*****************************************************************************
 函 数 名: uchar f_I2CDriverReadAck(I2C_DRIVER *pDriver)
 功能描述: I2C驱动在总线产生一个应答信号
 输入参数: pDriver I2C驱动指针
 返 回 值: true:读取到应答;false:未读取到应答信号
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_I2CDriverReadAck(I2C_DRIVER *pDriver)
{
	uchar tryCnt = 0;
	uchar ret = true;
	
	pDriver->pHardDriver->ClockOut(false);
	pDriver->pHardDriver->SetDataDir(IO_DIR_IN);
	pDriver->pHardDriver->ClockOut(true);
	while(pDriver->pHardDriver->DataIn())
	{
		pDriver->pHardDriver->Delay();
		tryCnt ++;
		if(tryCnt > MAX_READ_ACK_CNT)
		{
			ret = false;
			break;
		}
	};
	pDriver->pHardDriver->ClockOut(false);
	return ret;
}

/*****************************************************************************
 函 数 名: f_I2CDriverReadByte
 功能描述: pDriver I2C驱动指针
 输入参数: 读取数据
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_I2CDriverReadByte(I2C_DRIVER* pDriver)
{
    uchar i;
    uchar data = 0;

	pDriver->pHardDriver->ClockOut(false);
	pDriver->pHardDriver->SetDataDir(IO_DIR_IN);
	for (i = 0; i < 8; i++)
	{
		pDriver->pHardDriver->ClockOut(true);
		data <<= 1;
		data |= pDriver->pHardDriver->DataIn();
		pDriver->pHardDriver->ClockOut(false);
	}
	return data;
}

uchar f_I2CDriverWriteSlaveAddr(I2C_DRIVER* pDriver, uchar slaveAddr)
{
	uchar tryCnt = 0;
	uchar ret = true;
	do
	{
		//写器件地址
		f_I2CDriverStop(pDriver);
		f_I2CDriverStart(pDriver);
		f_I2CDriverWriteByte(pDriver, slaveAddr);

		if((++tryCnt) > IIC_MAX_WRITE_CNT)
		{
			ret = false;
			break;
		}
	}while(false == f_I2CDriverReadAck(pDriver));
	return ret;
}

/*****************************************************************************
 函 数 名: uchar f_I2CDriverWriteSlaveByte(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar data)
 功能描述: 向总线上的设备写入一个字节数据
 输入参数: pDriver I2C驱动指针
 		   slaveAddr 器件地址
 		   dataAddr 数据地址
 		   data 写入数据
 返 回 值: true:写入成功;false:写入失败
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_I2CDriverWriteSlaveByte(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar data)
{
    slaveAddr &= 0xFE;//保持为写
	f_I2CDriverWriteSlaveAddr(pDriver, slaveAddr);//写器件地址
	f_I2CDriverWriteByte(pDriver, dataAddr);//写入数据地址
	if(false == f_I2CDriverReadAck(pDriver))//判定ACK
	{
		return false;
	}
	
	f_I2CDriverWriteByte(pDriver, data);//写入数据
	if(false == f_I2CDriverReadAck(pDriver))//判定ACK
	{
		return false;
	}
	f_I2CDriverStop(pDriver);//发送停止位
	return true;
}

/*****************************************************************************
 函 数 名: uchar f_I2CDriverReadSlaveByte(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData)
 功能描述: 向总线上的设备读取一个字节数据
 输入参数: pDriver I2C驱动指针
 		   slaveAddr 器件地址
 		   dataAddr 数据地址
 		   pData 读取数据缓存指针
 返 回 值: true:读取成功;false:读取失败
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_I2CDriverReadSlaveByte(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData)
{
    slaveAddr &= 0xFE;//保持为写
	f_I2CDriverWriteSlaveAddr(pDriver, slaveAddr);//写器件地址
	f_I2CDriverWriteByte(pDriver, dataAddr);//写入数据地址
	if(false == f_I2CDriverReadAck(pDriver))//判定ACK
	{
		return false;
	}
	
	slaveAddr |= 0x01;//设置为读
	f_I2CDriverStart(pDriver);//发送一个起始位
	f_I2CDriverWriteByte(pDriver, slaveAddr);//写入读操作
	if(false == f_I2CDriverReadAck(pDriver))//判定ACK
	{
		return false;
	}
	*pData = f_I2CDriverReadByte(pDriver);
	f_I2CDriverWriteAck(pDriver, I2C_DRIVER_NO_ACK);//写应答信号
	f_I2CDriverStop(pDriver);//发送停止位
	return true;
}

/*****************************************************************************
 函 数 名: uchar f_I2CDriverWriteSlaveBytes(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData, uint length)
 功能描述: 向总线上的设备连续写入多个字节数据
 输入参数: pDriver I2C驱动指针
 		   slaveAddr 器件地址
 		   dataAddr 数据地址
 		   pData 写入数据缓存地址
 		   length 长度
 返 回 值: true:写入成功;false:写入失败
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_I2CDriverWriteSlaveBytes(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData, uint length)
{
	uint i;
	
    slaveAddr &= 0xFE;//保持为写
	f_I2CDriverWriteSlaveAddr(pDriver, slaveAddr);//写器件地址
	f_I2CDriverWriteByte(pDriver, dataAddr);//写入数据地址
	if(false == f_I2CDriverReadAck(pDriver))//判定ACK
	{
		return false;
	}

	for(i = 0; i < length; i++)
	{
		//pDriver->pHardDriver->FreeDog();
		f_I2CDriverWriteByte(pDriver, pData[i]);//写入数据
		if(false == f_I2CDriverReadAck(pDriver))//判定ACK
		{
			return false;
		}
	}
	
	f_I2CDriverStop(pDriver);//发送停止位
	return true;
}

/*****************************************************************************
 函 数 名: uchar f_I2CDriverReadSlaveBytes(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData)
 功能描述: 向总线上的设备读取一个字节数据
 输入参数: pDriver I2C驱动指针
 		   slaveAddr 器件地址
 		   dataAddr 数据地址
 		   pData 读取数据缓存指针
 返 回 值: true:读取成功;false:读取失败
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_I2CDriverReadSlaveBytes(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData, uchar length)
{
	uint i;
	
    slaveAddr &= 0xFE;//保持为写
	f_I2CDriverWriteSlaveAddr(pDriver, slaveAddr);//写器件地址
	f_I2CDriverWriteByte(pDriver, dataAddr);//写入数据地址
	if(false == f_I2CDriverReadAck(pDriver))//判定ACK
	{
		return false;
	}
	
	slaveAddr |= 0x01;//设置为读
	f_I2CDriverStart(pDriver);//发送一个起始位
	f_I2CDriverWriteByte(pDriver, slaveAddr);//写入读操作
	if(false == f_I2CDriverReadAck(pDriver))//判定ACK
	{
		return false;
	}

	for(i = 0;i < length;i ++)
	{
		//pDriver->pHardDriver->FreeDog();
		pData[i] = f_I2CDriverReadByte(pDriver);
		if (i < (length - 1))//除最后一个数据外
		{
			f_I2CDriverWriteAck(pDriver, I2C_DRIVER_ACK);//写应答信号
		}
	}
	f_I2CDriverWriteAck(pDriver, I2C_DRIVER_NO_ACK);//写应答信号
	f_I2CDriverStop(pDriver);//发送停止位
	return true;
}

/*****************************************************************************
 函 数 名: f_I2CDriverInit
 功能描述  : I2C驱动初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月17日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_I2CDriverInit(I2C_DRIVER *pDriver, const I2C_HARDWARE_DRIVER *pHardware)
{
	f_Memset(pDriver, 0, sizeof(I2C_DRIVER));
    pDriver->pHardDriver = pHardware;
}

