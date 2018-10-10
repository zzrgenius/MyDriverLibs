#ifndef __IC_DRIVER_ET6226_H__
#define __IC_DRIVER_ET6226_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "I2CDriver.h"

 /*----------------------------------------------*
 * ǰ������                                         *
 *----------------------------------------------*/
struct ic_driver_et6226;
typedef struct ic_driver_et6226 IC_DRIVER_ET6226;

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define ET6226_CMD_OFF			0x4800
#define ET6226_CMD_8_SEG		0x4801
#define ET6226_CMD_7_SEG		0x4809
#define ET6226_CMD_LEVEL_1		0x4811
#define ET6226_CMD_LEVEL_2		0x4821
#define ET6226_CMD_LEVEL_3		0x4831
#define ET6226_CMD_LEVEL_4		0x4841
#define ET6226_CMD_LEVEL_5		0x4851
#define ET6226_CMD_LEVEL_6		0x4861
#define ET6226_CMD_COM_0		0x6800
#define ET6226_CMD_COM_1		0x6A00
#define ET6226_CMD_COM_2		0x6C00
#define ET6226_CMD_COM_3		0x6E00
#define ET6226_CMD_GET_KEY		0x4F00

/*----------------------------------------------*
 * �������Ͷ���                                       *
 *----------------------------------------------*/
struct ic_driver_et6226
{
	I2C_DRIVER *pI2CDriver;
};

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern IC_DRIVER_ET6226 icDriverET6226;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
uchar f_ICDriverET6226ReadKey(uchar *pKey);
uchar f_ICDriverET6226WriteCMD(uint cmd);
void f_ICDriverET6226Init(I2C_DRIVER *pI2CDriver);

#endif /* __IC_DRIVER_ET6226_H__ */
