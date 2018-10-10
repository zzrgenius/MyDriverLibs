#ifndef __IC_DRIVER_ET6238_H__
#define __IC_DRIVER_ET6238_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "I2CDriver.h"

/*----------------------------------------------*
* 前置声明                                         *
*----------------------------------------------*/
struct ic_driver_et6238;
typedef struct ic_driver_et6238 IC_DRIVER_ET6238;


/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
#define ET6238_SLAVE_ADDR	 0XE0 //器件地址
//====命令====

#define ET6238_SYSTEM_OFF		0X20 //晶振关
#define ET6238_SYSTEM_ON		0X21 //晶振开
#define ET6238_DIS_OFF			0X80 //显示关
#define ET6238_DIS_ON			0X81 //显示开
#define ET6238_INT_ROW		    0XA0 //设置ROW15中断/行输出
#define ET6238_INT_LOW			0XA1 //设置ROW15按键输出中断，低有效
#define ET6238_INT_HIGH 		0XA3 //设置ROW15按键输出中断，高有效
#define ET6238_LIGHT_L1 		0xE0 //显示亮度1/16
#define ET6238_LIGHT_L2 		0xE1 //显示亮度2/16
#define ET6238_LIGHT_L3 		0xE2 //显示亮度3/16
#define ET6238_LIGHT_L4 		0xE3 //显示亮度4/16
#define ET6238_LIGHT_L5 		0xE4 //显示亮度5/16
#define ET6238_LIGHT_L6 		0xE5 //显示亮度6/16
#define ET6238_LIGHT_L7 		0xE6 //显示亮度7/16
#define ET6238_LIGHT_L8 		0xE7 //显示亮度8/16
#define ET6238_LIGHT_L9 		0xE8 //显示亮度9/16
#define ET6238_LIGHT_L10		0xE9 //显示亮度10/16
#define ET6238_LIGHT_L11		0xEA //显示亮度11/16
#define ET6238_LIGHT_L12		0xEB //显示亮度12/16
#define ET6238_LIGHT_L13		0xEC //显示亮度13/16
#define ET6238_LIGHT_L14		0xED //显示亮度14/16
#define ET6238_LIGHT_L15		0xEE //显示亮度15/16
#define ET6238_LIGHT_L16		0xEF //显示亮度16/16

#define ET6238_COM0_ADDR		0X00

#define ET6238_KEY_ADDR     	0x40 //按键必须从40开始连续读



/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
struct ic_driver_et6238
{
	I2C_DRIVER *pI2CDriver;
};


/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_ET6238Init(I2C_DRIVER *pI2CDriver);
void f_ET6238_ReadAllKey(uchar *pData, uint len);
void f_ET6238_ShowData(uchar *pData, uint len);
uchar f_ET6238_WriteCMD(uchar cmd);


#endif /* __IC_DRIVER_ET6238_H__ */
