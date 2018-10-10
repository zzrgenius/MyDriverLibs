#ifndef __COMM_PROTOCOL_H__
#define __COMM_PROTOCOL_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "CommDriver.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
//====����ģ��====
typedef struct 
{
	uchar headCode;//ͷ��0x32
	uchar add;//��ַ��0xf0
	uchar mode;//ģʽ0x81
	
	uchar bOnOff:1; //0�ر�;1����
	uchar bRevBits:7;
	
	uchar setTempMSB;//�¶����ø�8λ(ʵ���¶�*10)
	uchar setTempLSB;//�¶����õ�8λ
	uchar revData[5];//�����ֽ�
	uchar xorValue; //���У��(add~revData[4])
	uchar endCode; //β��0x34
}PROTOCOL_IHEAT_SEND;//����ģ�鷢������

typedef struct 
{
	uchar headCode;//ͷ��0x32
	uchar add;//��ַ��0x0f
	uchar mode;//ģʽ0x01
	
	uchar bOnOff:1; //0�ر�;1����
	uchar bRevBits:7;
	
	uchar bErrorZero:1;//�������
	uchar bErrorInTempOpen:1;//��ˮ�¶ȴ�������·
	uchar bErrorInTempShort:1;//��ˮ�¶ȴ�������·
	uchar bErrorOutTempOpen:1;//��ˮ�¶ȴ�������·
	uchar bErrorOutTempShort:1;//��ˮ�¶ȴ�������·
	uchar bErrorOverHeat:1;//����
	uchar bRevBits1:2;
	
	uchar InTempMSB;//��ˮ�¶ȸ�8λ(ʵ���¶�*10)
	uchar InTempLSB;//��ˮ�¶ȵ�8λ
	uchar OutTempMSB;//��ˮ�¶ȸ�8λ(ʵ���¶�*10)
	uchar OutTempLSB;//��ˮ�¶ȵ�8λ
	uchar flowMSB;//������8λ(cc/min)
	uchar flowLSB;//������8λ
	uchar xorValue; //���У��(add~revData[4])
	uchar endCode; //β��0x34
}PROTOCOL_IHEAT_REV;//����ģ���������

//====ת�Ӱ�Э��====
typedef struct 
{
	uchar headCode;//ͷ��0x55
	uchar mode;//ģʽ 1��ͨģʽ 2������ģʽ
	
	uchar sysState; //ϵͳ״̬
	uchar curFunc; //��ǰ����	
	uchar lidCMD; //���Ƿ�Ȧ����
	uchar keyCode; //�ط�������
	uchar adjustIndex; //��ˮ������˳��

	uchar bFlushState :1; //��ˮ״̬
	uchar bWashMove: 1; //�ƶ���Ħ
	uchar bStrongWeak: 1; //ǿ����Ħ
	uchar bColdHot: 1; //���Ȱ�Ħ
	uchar bErrNoWater: 1; //��ˮ����
	uchar bKeyDryIO :1; //��ɰ���IO״̬
	uchar bFlushAdjust :1; //��ϴʱ�����
	uchar bFourceSit: 1; //ǿ��ģ������
	
	uchar xorValue; //���У��
}PROTOCOL_CHANGE_SEND;//ת�Ӱ巢������

typedef struct 
{
	uchar headCode;//ͷ��0x55
	uchar mode;//ģʽ0x01

	uchar keyCode; //��ֵ
	sint seatTemp; //����
	uchar lidCmd; //��Ȧ����ش�
	
	uchar seatLidRange :4; //��Ȧλ��
	uchar topLidRange :4; //�ϸ�λ��
	
	uchar waterLevel :4; //ˮ�µ�λ
	uchar seatLevel :4;  //���µ�λ

	uchar dryLevel :4; //��ɵ�λ
	uchar nozzlePos :4; //���λ��
	
	uchar flowPos :4; //������λ
	uchar bRevBits:4; 

	uchar bErrSeatTempOpen :1;
	uchar bErrSeatTempShort :1;
	uchar bSitState :1; //����״̬
	uchar bHasPerson :1; //΢����Ӧ
	uchar bKeyPressed :1; //���ְ��а�������
	uchar bRevBits_1 :3; //��ϴʱ�����
	
	uchar xorValue; //���У��
}PROTOCOL_CHANGE_REV;//ת�Ӱ��������

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
//====Э�����====
//����
#define FRAME_IHEAT_HEAD 0x32
#define FRAME_IHEAT_ADD 0x0f
#define PFRAME_IHEAT_ADD_POS 1
#define PFRAME_IHEAT_REV_LEN sizeof(PROTOCOL_IHEAT_REV)

//ת�Ӱ�
#define FRAME_CHANGE_HEAD 0x55
#define PFRAME_CHANGE_REV_LEN sizeof(PROTOCOL_CHANGE_REV)

 


//====�ڲ������====
#define COMM_CMD_IHEAT COMM_SET_CMD(0, 0, 1)//����ͨ��,��ѭ��,���ط�,�ڲ����1
#define COMM_CMD_CHANGE COMM_SET_CMD(0, 0, 2)//ת����ͨ��,��ѭ��,���ط�,�ڲ����2

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
COMM_FUNC_TAB const * f_CommFindFuncTable(QUEUE_DATA_TYPE cmd);
uchar f_CommRevDeal(COMM_DRIVER *pDriver);


#endif /* __COMM_PROTOCOL_H__ */
