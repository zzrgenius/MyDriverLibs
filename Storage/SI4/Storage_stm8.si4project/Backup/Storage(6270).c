#include "Storage.h"

writeFunc storageWrite;
readFunc storageRead;

/*
数据存储示意：
前3个字节(byte0 - byte2)用于定义是否首次启动,标志字符XDD
byte

|X|D|D|B A|

*/

uint baseAddr; //
ulong writeTimes;


void storageInit(writeFunc write, readFunc read)
{
    storageWrite = write;
    storageRead = read;


}





