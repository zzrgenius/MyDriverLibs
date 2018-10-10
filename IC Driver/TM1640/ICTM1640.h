#ifndef __ICTM1640_H__
#define __ICTM1640_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "I2CDriver.h"


/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define TM1640_DATA_AUTO_ADD  0x40 //���������Զ���ַģʽ
#define TM1640_DATA_STABLE_ADD  0x44 //��������̶���ַģʽ

#define TM1640_START_ADDR 0x00 //��ַ������ʼ��ַ(��Χ 00~0F)
#define TM1640_LED_LEVEL_1 0x88 //��ʾ���ȵȼ�1
#define TM1640_LED_LEVEL_2 0x89
#define TM1640_LED_LEVEL_4 0x8A
#define TM1640_LED_LEVEL_10 0x8B
#define TM1640_LED_LEVEL_11 0x8C
#define TM1640_LED_LEVEL_12 0x8D
#define TM1640_LED_LEVEL_13 0x8E
#define TM1640_LED_LEVEL_14 0x8F

#define TM1640_LED_LEVEL_OFF 0x80 //��ʾ�ر�

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
 
typedef struct 
{
	I2C_DRIVER *pI2CDriver;
}IC_DRIVER_TM1640;

extern IC_DRIVER_TM1640 tm1640;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_TM1640_Init(I2C_DRIVER *pDriver);
void f_TM1640DisplayAuto(uchar startAddr, uchar *data, uchar len, uchar degree);



#endif /* __ICTM1640_H__ */
