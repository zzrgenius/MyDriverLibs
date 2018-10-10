#ifndef __PL1167_PROTOCOL_H__
#define __PL1167_PROTOCOL_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
typedef struct 
{
	uchar machineCode;
	
	uchar bStrength_L:1;//ǿ�ȵ�
	uchar bStrength_M:1;//ǿ����
	uchar bStrength_H:1;//ǿ�ȸ�
	uchar bFuncHip:1;//�β�
	uchar bFuncFemal:1;//Ů��
	uchar bFuncDry:1;//���
	uchar bStop:1;//ֹͣ
	uchar bPower:1;//��Դ

	uchar bWaterTemp_L:1;//ˮ�µ�
	uchar bWaterTemp_M:1;//ˮ����
	uchar bWaterTemp_H:1;//ˮ�¸�
	uchar rev1:1;//����λ
	uchar bSeatTemp_L:1;//���µ�
	uchar bSeatTemp_M:1;//������
	uchar bSeatTemp_H:1;//���¸�
	uchar rev2:1;//����λ

	uchar bSave:1;//����
	uchar bMassage:1;//��Ħ
	uchar bLight:1;//ҹ��
	uchar bLEDLight:1;//Һ������
	uchar bClean:1;//����Խ�
	uchar bWide:1;//���
	uchar bRush:1;//��ˮ
	uchar rev3:1;//����λ

	uchar data4;

	uchar endCode;	
}PROCOTOL_XI_MA_RC;//����ң����Э��

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern PROCOTOL_XI_MA_RC procotolXiMaRC;

#define MACHINE_CODE_LEN 6//����볤��
extern uchar machineID[MACHINE_CODE_LEN];//���������

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
uchar f_PL1167_GetSendBuffer(uchar *pBuf, uint len);
uchar f_PL1167_RevProtocolDeal(uchar *pData, uchar len);


#endif /* __PL1167_PROTOCOL_H__ */
