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
struct Key_driver;
typedef struct Key_driver KEY_DRIVER;

/*----------------------------------------------*
 * �������Ͷ���                                       *
 *----------------------------------------------*/
 
//����Ӳ������
typedef struct
{
	uchar keyShakeCnt;
	void (*GetKeys)(KEY_DRIVER *);
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
	}bits;
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
typedef void (*KeyDriverCallback)(KEY_DRIVER *);
 
//��������
struct Key_driver
{
	KEY_DRIVER_DATA	data;		//������������
	KEY_DEAL_STEP	dealStep;	//����������
	KEY_FLAG		flag;		//������ر�־λ
	KEY_HARDWARE_DRIVER const *pHardDriver;//����Ӳ������ָ��
	KeyDriverCallback dealCallback;//��������ص�����ָ��
};
 

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_KeyDriverInit(KEY_DRIVER       *pKeyDriver,
							const KEY_HARDWARE_DRIVER *pKeyDriverHardware, 
							const KeyDriverCallback pKeyDealFunc);
void f_KeyDriverDeal(KEY_DRIVER *pKeyDriver);


#endif /* __KEYDRIVER_H__ */
