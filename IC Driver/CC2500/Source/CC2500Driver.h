#ifndef __CC2500_DRIVER_H__
#define __CC2500_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "SPIDriver.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
#define CC2500_SEND_LEN 32//���ͻ����С
#define CC2500_REV_LEN 64//���ջ����С
#define CC2500_MAX_CHANNEL 4 //�����Ƶͨ������

typedef struct
{
	SPI_DRIVER *spi;
	uchar channels[CC2500_MAX_CHANNEL]; //��Ƶ�л�ͨ����
	uchar curChannelIndex; //��ǰͨ�����
	
	uchar needSendCnt;//����Ҫ���͵Ĵ���
	uchar sendBuffer[CC2500_SEND_LEN]; //���ͻ���
	uchar revBuffer[CC2500_REV_LEN]; //���ջ���

	uchar autoSleepTm; //�Զ���������ʱ��

	uchar bResetOK :1; //������λ���
	uchar bLastGD0 :1; //�ϴ�״̬��
	uchar bRfSleep :1; //��������
}CC250_DRIVER;


/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern CC250_DRIVER cc2500;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_CC2500_ChangeChannel(void);
void f_CC2500_Init(SPI_DRIVER *spi);
void f_CC2500_IntoSleep(void);
void f_CC2500_AutoSleep(void);
void f_CC2500_ReciveDeal(void);
void f_CC2500_SendDeal(void);
void f_CC2500_StartSend(void);
void f_CC2500_SetRevMode(void);




#endif /* __CC2500_DRIVER_H__ */
