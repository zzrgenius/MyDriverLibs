#include "Storage.h"

writeFunc storageWrite;
readFunc storageRead;

/*
���ݴ洢ʾ�⣺
ǰ3���ֽ�(byte0 - byte2)���ڶ����Ƿ��״�����,��־�ַ�XDD
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





