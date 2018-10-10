#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "KeyDriverConfig.h"

/*----------------------------------------------*
 * ǰ������                                         *
 *----------------------------------------------*/
struct Key_Driver;

/*----------------------------------------------*
 * �������Ͷ���                                       *
 *----------------------------------------------*/
 
//����Ӳ������
typedef struct
{
	uchar keyShakeCnt;
	void (*GetKeys)(struct Key_Driver *);
}KEY_HARDWARE_DRIVER;

//��������׶�
typedef enum 
{
	KEY_DEAL_INIT = 0,
	KEY_DEAL_IDLE,
	KEY_DEAL_PRESS,
	KEY_DEAL_WATE_RELEASE//�ȴ��ͷ�
}KEY_DEAL_STEP;

//���������־
typedef union
{
	byte_8 byte;
	struct
	{
		byte_8 bDealDone	:1; //�����Ѵ����־
		byte_8 bHasKey		:1; //�а�������
	}bit;
}KEY_FLAG;

//��������
typedef struct
{
	uint 		pressTm;//��������ʱ��
	ulong 		name;
	ulong 		newName;
	ulong 		getKeys; //ֱ�ӻ�ȡ�İ�����Ϣ
	ulong 		mask;	//�������룬����һЩ������ס����һֱ��������Ӧ�ò���������޳�����ֹ����������Ӱ��
	ulong		keyDone; //�����Ѵ����־,�Ͱ�����ͬ��
	KEY_STATE 	state;
}KEY_DRIVER_DATA;

//������������
typedef struct
{
	uint			pressTm; //��������ʱ��
	ulong			name;
	ulong 			newName;
	KEY_DEAL_STEP	dealStep; //����������
	KEY_STATE		state;
}KEY_DRIVER_INDE_KEY;

//�ص�����ָ��
typedef void (*KeyDriverCallback)(struct Key_Driver *);
 
//��������
typedef struct Key_Driver
{
	KEY_DRIVER_DATA	data;		//������������
	KEY_DEAL_STEP	dealStep;	//����������
	KEY_FLAG		flag;		//������ر�־λ
	KEY_HARDWARE_DRIVER const *pHardDriver;//����Ӳ������ָ��
	KeyDriverCallback dealCallback;//��������ص�����ָ��
}KEY_DRIVER;
 

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_KeyDriverInit(KEY_DRIVER       *pKeyDriver,
							KEY_HARDWARE_DRIVER const *pKeyDriverHardware, 
							KeyDriverCallback const pKeyDealFunc);
void f_KeyDriverDeal(KEY_DRIVER *pKeyDriver);


#endif /* __KEYDRIVER_H__ */
