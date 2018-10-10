#ifndef __IR_CONTROL_H__
#define __IR_CONTROL_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * �������Ͷ���                                       *
 *----------------------------------------------*/
typedef enum
{
	IR_STEP_IDLE,
	IR_STEP_HEAD,
	IR_STEP_DATA,
	IR_STEP_END
}IR_COMMI_STEP;

typedef enum
{
	IR_READ_NULL = 0,
	IR_READ_HEAD,//������
	IR_READ_END,//������
	IR_READ_BIT_0,//����λ0
	IR_READ_BIT_1//����λ1
}IR_READ_BIT_INFO;

#define IR_REV_BUF_NUM 10
#define IR_SEND_BUF_NUM 10
typedef struct
{
	IR_COMMI_STEP revStep;
	uchar revBitPos;//��ǰ��ȡλλ��
	uchar revByteCnt;//��ȡ�ֽ���
	uint  revLowTm; //���յ͵�ƽʱ��
	uint  revPeriodTm; //���ոߵ�ƽʱ��
	uint  revLowTmBuf; //���յ͵�ƽʱ�仺��
	uint  revPeriodTmBuf; //���ոߵ�ƽʱ�仺��
	uchar revNULLCnt; //���մ������ݴ���
	uchar revBuf[IR_REV_BUF_NUM];
	
	uchar bRevOneBitOVer :1; //����һ���ֽ����
	uchar bLastRevLevelState :1; //�ϴν��յ�ƽ״̬
	uchar bNeedDeal :1;
	
	IR_COMMI_STEP sendStep;//���Ͳ���
	uchar sendBitPos;//��ǰ����λλ��
	uchar sendByteCnt; //��ǰ�����ֽ���
	uchar needSendByte; //��Ҫ�����ֽ���
	uint sendTm; //��ǰ����ʱ��
	uint setLowTm; //���õ͵�ƽʱ��
	uint setPeriodTm; //��������ʱ��
	uchar sendBuf[IR_SEND_BUF_NUM];

	uchar bSendOneBitOver :1;//λ���ݷ������
	uchar bSendSpecialCode :1;//����������(ͷ��/β��)
	uchar bSendOneByteOver :1;//��ǰһ���ֽڷ������
	
}IR_CONTROL_DRIVER;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern IR_CONTROL_DRIVER irControlDriver;

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_IR_ControlDeal(void);
void f_IR_StartSend(uchar *pBuf, uchar len);
void f_IRControlInit(void);


#endif /* __IRCONTROL_H__ */
