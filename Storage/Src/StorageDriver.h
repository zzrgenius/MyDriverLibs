#ifndef __STORAGE_DRIVER_H__
#define __STORAGE_DRIVER_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 前置声明                                         *
 *----------------------------------------------*/
struct storage_driver;
typedef struct storage_driver STORAGE_DRIVER;

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
typedef struct
{
    void *pValue; //数据指针
    uchar  valueSize; //数据大小
    const void * pInitValue; //初始化值指针
}STORAGE_TYPE;//存储数据结构

typedef struct 
{
	uchar (*writeFunc)(uint, uchar, const uchar *);
	void (*readFunc)(uint, uchar, uchar *);
}STORAGE_HARDWARE;//硬件驱动部分

typedef struct 
{
	uint baseAddr; //当前数据读写基值
	ulong blockWriteCnt;//当前块写次数
	uchar writeErrCnt;//写失败次数，达到一定次数，换分区
}STORAGE_DATA;

struct storage_driver
{
	STORAGE_DATA data;
	STORAGE_HARDWARE const *pHardware;
};

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern STORAGE_DRIVER storageDriver;

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
#define BASE_ADDR_OFFSET 0 //写数据偏移地址存储位置(类型uint)
#define HEAD_OFFSET (BASE_ADDR_OFFSET + sizeof(uint)) //首次上电标志偏移地址(包括强制更改数据偏移地址)
#define BASE_ADDR_VALUE (HEAD_OFFSET + STORAGE_HEAD_SIZE)//写数据偏移地址初始化值

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_StorageReadValues(STORAGE_DRIVER *PDriver, uchar index);
void f_StoragerInit(STORAGE_DRIVER *PDriver, const STORAGE_HARDWARE *pHardware);
void f_StorageWriteValues(STORAGE_DRIVER *PDriver, uchar index, uchar check);
void f_StorageGetVersion(const uchar **pData, uchar *pSize);


#endif /* __STORAGE_DRIVER_H__ */
