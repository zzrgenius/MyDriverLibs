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
	void (*GetKeys)(struct Key_Driver *pKeyDriver);
}KeyHardwareDriver;

//��������׶�
typedef enum 
{
	KEY_DEAL_IDLE = 0,
	KEY_DEAL_PRESS
}KeyDealStep;

//���������־
typedef union
{
	byte_8 byte;
	struct
	{
		byte_8 bKeyDeal		:1; //�����Ѵ����־
	}bit;
}KeyFlags;

//��������
typedef struct
{
	uint 	keyPressTm;
	ulong 	keyName;
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
