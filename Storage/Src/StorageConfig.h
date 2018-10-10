#ifndef __STORAGE_CONFIG_H__
#define __STORAGE_CONFIG_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "StorageDriver.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
//====˳�����ȷ���޸�====
enum storage_index
{
    STORAGE_INDEX_WRITE_CNT = 0,//��д����
    STORAGE_SYS_STATE, //ϵͳ״̬
    STORAGE_SYS_FLAGS, //�洢ҹ���Զ���ˮ�ȱ�־
    STORAGE_ROUND_1_TM, //ϴˢʱ��
    STORAGE_BOTTOM_TM, //����ʱ��
    STORAGE_ROUND_2_TM //��ˮʱ��
};//�洢�����ڴ洢�������к�(��StorageConfig.c�еı��Ӧ)
/////////////////////////////////////////////////////////

typedef struct
{
    uchar min; //��Сֵ
    uchar max; //���ֵ
}RANGE_UCHAR_TYPE; //uchar���ݴ洢��Χ

typedef struct
{
    uint min; //��Сֵ
    uint max; //���ֵ
}RANGE_UINT_TYPE; //uint���ݴ洢��Χ

typedef struct
{
    ulong min; //��Сֵ
    ulong max; //���ֵ
}RANGE_ULONG_TYPE; //ulong���ݴ洢��Χ


/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

#define TOTAL_STORAGE_SIZE storageTableSize //�洢���С
extern const uint storageTableSize;
extern const STORAGE_TYPE tab_StorageValue[]; //�洢��

//��Χ����
extern const RANGE_UINT_TYPE flushTmRange;



/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_StorageRangeCheck(void);



#endif /* __STORAGE_CONFIG_H__ */
