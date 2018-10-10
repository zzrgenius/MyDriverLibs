#ifndef __STORAGE_DRIVER_H__
#define __STORAGE_DRIVER_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * ǰ������                                         *
 *----------------------------------------------*/
struct storage_driver;
typedef struct storage_driver STORAGE_DRIVER;

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
typedef struct
{
    void *pValue; //����ָ��
    uchar  valueSize; //���ݴ�С
    const void * pInitValue; //��ʼ��ֵָ��
}STORAGE_TYPE;//�洢���ݽṹ

typedef struct 
{
	uchar (*writeFunc)(uint, uchar, const uchar *);
	void (*readFunc)(uint, uchar, uchar *);
}STORAGE_HARDWARE;//Ӳ����������

typedef struct 
{
	uint baseAddr; //��ǰ���ݶ�д��ֵ
	ulong blockWriteCnt;//��ǰ��д����
	uchar writeErrCnt;//дʧ�ܴ������ﵽһ��������������
}STORAGE_DATA;

struct storage_driver
{
	STORAGE_DATA data;
	STORAGE_HARDWARE const *pHardware;
};

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern STORAGE_DRIVER storageDriver;

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define BASE_ADDR_OFFSET 0 //д����ƫ�Ƶ�ַ�洢λ��(����uint)
#define HEAD_OFFSET (BASE_ADDR_OFFSET + sizeof(uint)) //�״��ϵ��־ƫ�Ƶ�ַ(����ǿ�Ƹ�������ƫ�Ƶ�ַ)
#define BASE_ADDR_VALUE (HEAD_OFFSET + STORAGE_HEAD_SIZE)//д����ƫ�Ƶ�ַ��ʼ��ֵ

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_StorageReadValues(STORAGE_DRIVER *PDriver, uchar index);
void f_StoragerInit(STORAGE_DRIVER *PDriver, const STORAGE_HARDWARE *pHardware);
void f_StorageWriteValues(STORAGE_DRIVER *PDriver, uchar index, uchar check);
void f_StorageGetVersion(const uchar **pData, uchar *pSize);


#endif /* __STORAGE_DRIVER_H__ */
