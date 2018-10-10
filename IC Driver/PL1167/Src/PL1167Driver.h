#ifndef __PL1167_DRIVER_H__
#define __PL1167_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "SPIDriver.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
#define PL1167_SEND_LEN 20//���ͻ����С
#define PL1167_REV_LEN 20//���ջ����С
typedef struct
{
	SPI_DRIVER spi;
	uchar sendWaitTm;//�������ͺ�ȴ����ͳ�ʱʱ��
	uchar needSendCnt;//����Ҫ���͵Ĵ���
	uchar sendBuffer[PL1167_SEND_LEN]; //���ͻ���
	uchar revBuffer[PL1167_REV_LEN]; //���ջ���

	uchar bStartWait :1; //��ʼ���͵ȴ�
}PL1167_DRIVER;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
PL1167_DRIVER pl1167;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_PL1167Init(void);
void f_PL1167ChangeFreq(void);
void f_PL1167SendDeal(void);
void f_PL1167RevDeal(void);
void f_PL1167StartSend(void);
void f_PL1167InitReg(void);
void f_PL1167IntoSleep(void);

#endif /* __PL1167_DRIVER_H__ */
