#ifndef __KEYDRIVER_H__
#define __KEYDRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

struct Key_Driver;

/*----------------------------------------------*
 * �������Ͷ���                                       *
 *----------------------------------------------*/
 
//����Ӳ������
typedef struct
{
	void (*GetKeys)(struct Key_Driver *pKeyDriver);
}KeyHardwareDriver;

//��������
typedef struct
{
	uint keyPressTm;
}KeyDriverData;
 
//��������
typedef struct Key_Driver
{

	KeyHardwareDriver const *pHardDriver;
}KeyDriver;
 

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/




/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

//����������ʼ��ע�ắ��
void f_KeyDriverInit();
 


#endif /* __KEYDRIVER_H__ */
