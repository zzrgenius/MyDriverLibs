#ifndef STORAGE_VAULE_TABLE_H
#define STORAGE_VAULE_TABLE_H

#include "Storage.h"

typedef enum
{
    STORAGE_VALUE1 = 0,
    STORAGE_VALUE2
}storageOffset_def;//�洢�����ڴ洢���е�ƫ��ֵ

//test
int testValue;

const storageType storageValueTable[]
{
    {STORAGE_VALUE1, (void *)&testValue, VALUE_U16, 0}
};




#endif