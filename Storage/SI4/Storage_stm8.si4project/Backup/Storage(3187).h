#ifndef STORAGE_H
#define STORAGE_H
#include "DataType.h"

typedef e_bool (*writeFunc)(uint, uchar, const uchar *);
typedef void (*readFunc)(uint, uchar, uchar *);

typedef enum
{
    VALUE_U8 = 1,
    VALUE_U16 = 2,
    VALUE_U32 = 4
}valueType_def;//存储值的字节数

typedef union
{
    uchar value8;
    uint  value16;
    ulong value32;
}initValue_def;

typedef struct
{
    uint offset;
    void *value;
    valueType_def valueType;
    initValue_def initValue;
}storageType;


#endif