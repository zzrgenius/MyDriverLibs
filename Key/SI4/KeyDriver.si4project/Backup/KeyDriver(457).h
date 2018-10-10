#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "KeyDriverConfig.h"

struct Key_Driver;

/*----------------------------------------------*
 * �������Ͷ���                                       *
 *----------------------------------------------*/
 
//����Ӳ������
typedef struct
{
	uchar keyShakeCnt;
	void (*GetKeys)(struct Key_Driver *pKeyDriver);
}KeyHardwareDriver;

//��������׶�
typedef enum 
{
	KEY_DEAL_INIT = 0,
	KEY_DEAL_IDLE,
	KEY_DEAL_PRESS,
	KEY_DEAL_WATE_RELEASE//�ȴ��ͷ�
}KeyDealStep;

//���������־
typedef union
{
	byte_8 byte;
	struct
	{
		byte_8 bKeyDeal		:1; //�����Ѵ����־
		byte_8 bHasKey		:1; //�а�������
	}bit;
}KeyFlags;

//��������
typedef struct
{
	uint 	keyPressTm;//��������ʱ��
	ulong 	keyName;
	ulong 	newKeyName;
	KeyState keyState;
}KeyDriverData;
 
//��������
typedef struct Key_Driver
{
	KeyDriverData	keyData;
	KeyDealStep		keyDealStep;
	KeyFlags		keyFlag;
	KeyHardwareDriver const *pHardDriver;
}KeyDriver;
 

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/




/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

//����������ʼ��ע�ắ��
void f_KeyDriverInit(KeyDriver const *pKeyDriver);
 


#endif /* __KEYDRIVER_H__ */
