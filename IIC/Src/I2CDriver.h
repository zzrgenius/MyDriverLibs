#ifndef __I2C_DRIVER_H__
#define __I2C_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * ǰ������                                         *
 *----------------------------------------------*/
struct i2c_driver;
typedef struct i2c_driver I2C_DRIVER;

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
typedef enum
{
	IO_DIR_IN = 0,
	IO_DIR_OUT
}IO_DIR_STATE;
typedef enum
{
	I2C_DRIVER_ACK = 0,
	I2C_DRIVER_NO_ACK
}I2C_DRIVER_ACK_TYPE;
 
typedef struct 
{
	void (*ClockOut)(uchar);
	uchar (*DataIn)(void);
	void (*DataOut)(uchar);
	void (*SetDataDir)(IO_DIR_STATE);
	void (*Delay)(void);
}I2C_HARDWARE_DRIVER;//I2CӲ����������

struct i2c_driver 
{
	I2C_HARDWARE_DRIVER const *pHardDriver;
};



/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void  f_I2CDriverInit(I2C_DRIVER *pDriver, const I2C_HARDWARE_DRIVER *pHardware);
uchar f_I2CDriverReadAck(I2C_DRIVER *pDriver);
uchar f_I2CDriverReadByte(I2C_DRIVER* pDriver);
uchar f_I2CDriverReadSlaveByte(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData);
uchar f_I2CDriverReadSlaveBytes(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData, uchar length);
void  f_I2CDriverStart(I2C_DRIVER *pDriver);
void  f_I2CDriverStop(I2C_DRIVER *pDriver);
void  f_I2CDriverWriteAck(I2C_DRIVER *pDriver, I2C_DRIVER_ACK_TYPE ack);
void  f_I2CDriverWriteByte(I2C_DRIVER *pDriver, uchar data);
uchar f_I2CDriverWriteSlaveAddr(I2C_DRIVER* pDriver, uchar slaveAddr);
uchar f_I2CDriverWriteSlaveByte(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar data);
uchar f_I2CDriverWriteSlaveBytes(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData, uint length);

#endif /* __I2C_DRIVER_H__ */

