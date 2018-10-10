#ifndef __STORAGE_CONFIG_H__
#define __STORAGE_CONFIG_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "StorageDriver.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
//====顺序务必确认修改====
enum storage_index
{
    STORAGE_INDEX_WRITE_CNT = 0,//块写次数
    STORAGE_SYS_STATE, //系统状态
    STORAGE_SYS_FLAGS, //存储夜灯自动冲水等标志
    STORAGE_ROUND_1_TM, //洗刷时间
    STORAGE_BOTTOM_TM, //排污时间
    STORAGE_ROUND_2_TM //回水时间
};//存储数据在存储区的序列号(与StorageConfig.c中的表对应)
/////////////////////////////////////////////////////////

typedef struct
{
    uchar min; //最小值
    uchar max; //最大值
}RANGE_UCHAR_TYPE; //uchar数据存储范围

typedef struct
{
    uint min; //最小值
    uint max; //最大值
}RANGE_UINT_TYPE; //uint数据存储范围

typedef struct
{
    ulong min; //最小值
    ulong max; //最大值
}RANGE_ULONG_TYPE; //ulong数据存储范围


/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

#define TOTAL_STORAGE_SIZE storageTableSize //存储表大小
extern const uint storageTableSize;
extern const STORAGE_TYPE tab_StorageValue[]; //存储表

//范围数据
extern const RANGE_UINT_TYPE flushTmRange;



/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_StorageRangeCheck(void);



#endif /* __STORAGE_CONFIG_H__ */
