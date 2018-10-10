#include "Storage.h"
#include "StorageValueTable.h"

#define HEAD_OFFSET 0
#define BASE_ADDR_OFFSET 3
#define BASE_ADDR_VALUE 9
#define WRITE_TIMES_OFFSET 5
#define CHANGE_BLOCK_ERROR_CNT 20//累积写失败次数，换分区

#define MAX_WRITE_TIMES 450000//芯片读写次数*1.5
#define BLOCK_RAMGE 1024

/*
数据存储示意：
前3个字节(byte0 - byte2):
用于定义是否首次启动,标志字符XDD
byte3-4:
baseAddr存储存储基值,首次启动为3，后面每次到达写次数极限时,往后偏移存储字节数+1,因为可能相邻的一个字节也会坏
byte 5-8 ：
writeTimes写次数，达到上限值，则往后偏移
 0 1 2 3 4 5 6 7 8 9 10 11 12 13
|X|D|D|BA |WC     |KWC        |value ....

*/

uint baseAddr; //当前数据读写基值
ulong blockWriteCnt;//当前块写次数
uchar writeErrCnt;//写失败次数，达到一定次数，换分区
writeFunc storageWrite;
readFunc storageRead;


/* =========================================================
* 功能描述: 判断当前存储区块是否适合存储，如果存储满，则换区块存储
* 输     入:
* 返     回:
* 修改历史:
1、2018-3-25 	钱百静 			完成基本功能
=========================================================*/
void judgeStorageBlock(void)
{
    int valueOffset;
    int i;

    blockWriteCnt ++;

    //超过块写次数或者分区写错误次数太多则换分区
    if (blockWriteCnt >= MAX_WRITE_TIMES || writeErrCnt > CHANGE_BLOCK_ERROR_CNT)
    {
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            valueOffset += (uint)storageValueTable[i].valueType;
        }
        valueOffset += 1;

        blockWriteCnt = 0;
        writeErrCnt = 0;

        //可正常切换存储区块,如果满了则一直写最后一个区块
        if (baseAddr + valueOffset < BLOCK_RAMGE)
        {
            baseAddr += valueOffset;
            //存储数据迁移到新区块
            for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
            {
                writeValues(i);
            }
        }
        storageWrite(BASE_ADDR_OFFSET, VALUE_U16, (uchar *)&baseAddr);
    }

    //防止写入太频繁,累积50次写入
    if (blockWriteCnt % 50)
    {
        writeValues(STORAGE_WriteCnt);
    }
}

/* =========================================================
* 功能描述: 写数据到当前的存储区
* 输     入: index:数据在存储表中的序号
* 返     回:
* 修改历史:
1、2018-3-25 	钱百静 			完成基本功能
=========================================================*/
void writeValues(uint index)
{
    uint realOffset;
    int i;

    judgeStorageBlock();

    realOffset = baseAddr;
    if (index > 0)
    {
        for (i = 0; i < index; i++)
        {
            realOffset += (uint)storageValueTable[i].valueType;
        }
    }

    if (BOOL_FALSE == storageWrite(realOffset, storageValueTable[index].valueType, (uchar *)storageValueTable[index].pValue))
    {
        writeErrCnt ++;
    }
}

/* =========================================================
* 功能描述: 从当前的存储区读取数据
* 输     入: index:数据在存储表中的序号
* 返     回:
* 修改历史:
1、2018-3-25 	钱百静 			完成基本功能
=========================================================*/
void readValues(uint index)
{
    uint realOffset = baseAddr;
    int i;

    if (index > 0)
    {
        for (i = 0; i < index; i++)
        {
            //计算当前变量的实际存储偏移量
            realOffset += (uint)storageValueTable[i].valueType;
        }
    }
    storageRead(realOffset, storageValueTable[index].valueType, (uchar *)storageValueTable[index].pValue);
}

/* =========================================================
* 功能描述: 存储初始化，包括读写函数注册,首次启动数据初始化及写入数据存储区
* 输     入: write：底层写数据函数
            read:底层度数据函数
* 返     回:
* 修改历史:
1、2018-3-25 	钱百静 			完成基本功能
=========================================================*/
void storageInit(writeFunc write, readFunc read)
{
    char head[3];
    uint i;

    //注册读写函数
    storageWrite = write;
    storageRead = read;

    //读出头，判断是否为首次启动
    storageRead(HEAD_OFFSET, 3, (uchar *)&head);
    if ('X' == head[0] && 'D' == head[1] && 'D' == head[2])
    {

        storageRead(BASE_ADDR_OFFSET, VALUE_U16, (uchar *)&baseAddr);

        //已初始化过，读出数据
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            readValues(i);
        }
    }
    else
    {
        baseAddr = BASE_ADDR_VALUE;
        storageWrite(BASE_ADDR_OFFSET, VALUE_U16, (uchar *)&baseAddr);

        //初始化数据并写入存储区
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            if (VALUE_U8 == storageValueTable[i].valueType)
            {
                *(uchar *)storageValueTable[i].pValue = *(uchar *)storageValueTable[i].pInitValue;
            }
            else if (VALUE_U16 == storageValueTable[i].valueType)
            {
                *(uint *)storageValueTable[i].pValue = *(uint *)storageValueTable[i].pInitValue;
            }
            else if (VALUE_U32 == storageValueTable[i].valueType)
            {
                *(ulong *)storageValueTable[i].pValue = *(ulong *)storageValueTable[i].pInitValue;
            }
            writeValues(i);
        }

        head[0] = 'X';
        head[1] = 'D';
        head[2] = 'D';
        storageWrite(HEAD_OFFSET, 3, (uchar *)&head);
    }

}

