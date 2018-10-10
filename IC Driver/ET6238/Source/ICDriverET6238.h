#ifndef __IC_DRIVER_ET6238_H__
#define __IC_DRIVER_ET6238_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "I2CDriver.h"

/*----------------------------------------------*
* ǰ������                                         *
*----------------------------------------------*/
struct ic_driver_et6238;
typedef struct ic_driver_et6238 IC_DRIVER_ET6238;


/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define ET6238_SLAVE_ADDR	 0XE0 //������ַ
//====����====

#define ET6238_SYSTEM_OFF		0X20 //�����
#define ET6238_SYSTEM_ON		0X21 //����
#define ET6238_DIS_OFF			0X80 //��ʾ��
#define ET6238_DIS_ON			0X81 //��ʾ��
#define ET6238_INT_ROW		    0XA0 //����ROW15�ж�/�����
#define ET6238_INT_LOW			0XA1 //����ROW15��������жϣ�����Ч
#define ET6238_INT_HIGH 		0XA3 //����ROW15��������жϣ�����Ч
#define ET6238_LIGHT_L1 		0xE0 //��ʾ����1/16
#define ET6238_LIGHT_L2 		0xE1 //��ʾ����2/16
#define ET6238_LIGHT_L3 		0xE2 //��ʾ����3/16
#define ET6238_LIGHT_L4 		0xE3 //��ʾ����4/16
#define ET6238_LIGHT_L5 		0xE4 //��ʾ����5/16
#define ET6238_LIGHT_L6 		0xE5 //��ʾ����6/16
#define ET6238_LIGHT_L7 		0xE6 //��ʾ����7/16
#define ET6238_LIGHT_L8 		0xE7 //��ʾ����8/16
#define ET6238_LIGHT_L9 		0xE8 //��ʾ����9/16
#define ET6238_LIGHT_L10		0xE9 //��ʾ����10/16
#define ET6238_LIGHT_L11		0xEA //��ʾ����11/16
#define ET6238_LIGHT_L12		0xEB //��ʾ����12/16
#define ET6238_LIGHT_L13		0xEC //��ʾ����13/16
#define ET6238_LIGHT_L14		0xED //��ʾ����14/16
#define ET6238_LIGHT_L15		0xEE //��ʾ����15/16
#define ET6238_LIGHT_L16		0xEF //��ʾ����16/16

#define ET6238_COM0_ADDR		0X00

#define ET6238_KEY_ADDR     	0x40 //���������40��ʼ������



/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
struct ic_driver_et6238
{
	I2C_DRIVER *pI2CDriver;
};


/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_ET6238Init(I2C_DRIVER *pI2CDriver);
void f_ET6238_ReadAllKey(uchar *pData, uint len);
void f_ET6238_ShowData(uchar *pData, uint len);
uchar f_ET6238_WriteCMD(uchar cmd);


#endif /* __IC_DRIVER_ET6238_H__ */
