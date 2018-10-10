#ifndef __COMM_DRIVER_H__
#define __COMM_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "CommQueue.h"

/*----------------------------------------------*
 * ǰ������ 										*
 *----------------------------------------------*/
struct comm_driver;
typedef struct comm_driver COMM_DRIVER;

/*----------------------------------------------*
 * �������Ͷ���                                       *
 *----------------------------------------------*/
typedef struct
{
	uchar frameRevOverItv;//֡�������ʱ��,����ʱ������Ϊ�Ѿ�֡���ս���,��λ1ms
	uchar sendFrameItv;//֡���ͼ��
	uchar sendErrTm; //֡����ʧ��ʱ��
	uint  waitReplyTm; //�ȴ�Ӧ��ʱʱ��
	
	void (*SetSendInterrupt)(uchar);//�����ж����ô򿪻�ر�
	void (*SetRecInterrupt)(uchar);//�����ж����ô򿪻�ر�
	void (*StartSend)(COMM_DRIVER*);//��������
	void (*ChangeBaudRate)(word_32); //���Ĳ�����
}COMM_HARDWARE;//ͨ��Ӳ������

typedef enum
{
	COMM_SEND_STATE_IDLE = 0,//���Ϳ���״̬
	COMM_SEND_STATE_GET_BUFFER,//��ȡ����״̬
	COMM_SEND_STATE_START,//��������
	COMM_SEND_STATE_SENDING,//���ڷ���
	COMM_SEND_STATE_OVER,//���ͽ���
	COMM_SEND_STATE_REPLY//�õ�Ӧ��
}COMM_SEND_STATE;//ͨ�ŷ���״̬

typedef enum
{
	COMM_REV_STATE_WAIT = 0,//�ȴ�����
	COMM_REV_STATE_OVER//���ս���
}COMM_REV_STATE;//����״̬

typedef struct
{
	uchar *pBuffer;//�����ַ
	const uint size;//�����С
}COMM_FRAME_BUFFER;//������Ϣ

typedef struct
{
	COMM_SEND_STATE sendState;//��ǰ����״̬
	COMM_FRAME_BUFFER const *pBuffer;
	uint noSendTm;//�޷���ʱ��
	uint needSendNum;//��Ҫ�����ֽ���
	uint curSendNum;//�ѷ����ֽ���
	QUEUE_DATA_TYPE curSendCMD;//��ǰ��������(�ڲ�����)
	uchar CMDSendCnt;//����ͼ���
	COMM_QUEUE queue;//�����������
}COMM_SEND_DATA;//����������

typedef struct
{
	COMM_REV_STATE revState;//��ǰ����״̬
	COMM_FRAME_BUFFER const *pBuffer;
	uint noRevTm;//�޽���ʱ��
	uint curRevNum;//��ǰ���յ��ֽ���
	QUEUE_DATA_TYPE curRevCMD;//����������(�ڲ�����)
}COMM_REV_DATA;//�������ݽṹ

typedef struct
{
    word_32 baudRate; //������
	uint internalCMD;//�ڲ�����
	void (*RevDataDeal)(COMM_DRIVER *);//������ȷ������
	void (*GetSendBuf)(COMM_DRIVER *);//��ȡ���ͻ���
	void (*NoReplyDeal)(COMM_DRIVER *);//��Ӧ������
}COMM_FUNC_TAB; //���ܴ������ṹ

struct comm_driver
{
	COMM_SEND_DATA sendData;//�����������
	COMM_REV_DATA revData;//�����������
	COMM_HARDWARE const *pHardware;//Ӳ�����
};

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define COMM_CMD_NULL 0
//====�ڲ������====
//bit15��ʾ�Ƿ�ѭ���ط�
//bit12~15 ����
//bit8~11 �ط�����
//bit0~7 �ڲ��������(��1��ʼ)
#define COMM_SET_CMD(syc, retryCnt, index) (((syc&(0x0001))<<15)|((retryCnt&(0x000f))<<8)|(index&0x000f))//�������
#define COMM_GET_RETRY_CNT(cmd) ((cmd>>8)&0x000f)//�����ط�����
#define COMM_IS_NEED_SYC(cmd) ((cmd>>15)&0x0001)//�����Ƿ��ط�


/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_CommDriverInit(COMM_DRIVER *pDriver, 
							const COMM_HARDWARE *pHardware, 
							const COMM_FRAME_BUFFER *pSendBuf, 
							const COMM_FRAME_BUFFER *pRevBuf);
void f_CommDriverDeal(COMM_DRIVER *pDriver);
uchar f_CommSendCMD(COMM_DRIVER *pDriver, QUEUE_DATA_TYPE cmd);

#endif /* __COMM_DRIVER_H__ */
