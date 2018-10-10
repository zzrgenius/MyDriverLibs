#include "Storage.h"
#include "StorageValueTable.h"

#define HEAD_OFFSET 0
#define BASE_ADDR_OFFSET 3
#define BASE_ADDR_VALUE 9
#define WRITE_TIMES_OFFSET 5
#define CHANGE_BLOCK_ERROR_CNT 20//�ۻ�дʧ�ܴ�����������

#define MAX_WRITE_TIMES 450000//оƬ��д����*1.5
#define BLOCK_RAMGE 1024

/*
���ݴ洢ʾ�⣺
ǰ3���ֽ�(byte0 - byte2):
���ڶ����Ƿ��״�����,��־�ַ�XDD
byte3-4:
baseAddr�洢�洢��ֵ,�״�����Ϊ3������ÿ�ε���д��������ʱ,����ƫ�ƴ洢�ֽ���+1,��Ϊ�������ڵ�һ���ֽ�Ҳ�ỵ
byte 5-8 ��
writeTimesд�������ﵽ����ֵ��������ƫ��
 0 1 2 3 4 5 6 7 8 9 10 11 12 13
|X|D|D|BA |WC     |KWC        |value ....

*/

uint baseAddr; //��ǰ���ݶ�д��ֵ
ulong blockWriteCnt;//��ǰ��д����
uchar writeErrCnt;//дʧ�ܴ������ﵽһ��������������
writeFunc storageWrite;
readFunc storageRead;


/* =========================================================
* ��������: �жϵ�ǰ�洢�����Ƿ��ʺϴ洢������洢����������洢
* ��     ��:
* ��     ��:
* �޸���ʷ:
1��2018-3-25 	Ǯ�پ� 			��ɻ�������
=========================================================*/
void judgeStorageBlock(void)
{
    int valueOffset;
    int i;

    blockWriteCnt ++;

    //������д�������߷���д�������̫���򻻷���
    if (blockWriteCnt >= MAX_WRITE_TIMES || writeErrCnt > CHANGE_BLOCK_ERROR_CNT)
    {
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            valueOffset += (uint)storageValueTable[i].valueType;
        }
        valueOffset += 1;

        blockWriteCnt = 0;
        writeErrCnt = 0;

        //�������л��洢����,���������һֱд���һ������
        if (baseAddr + valueOffset < BLOCK_RAMGE)
        {
            baseAddr += valueOffset;
            //�洢����Ǩ�Ƶ�������
            for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
            {
                writeValues(i);
            }
        }
        storageWrite(BASE_ADDR_OFFSET, VALUE_U16, (uchar *)&baseAddr);
    }

    //��ֹд��̫Ƶ��,�ۻ�50��д��
    if (blockWriteCnt % 50)
    {
        writeValues(STORAGE_WriteCnt);
    }
}

/* =========================================================
* ��������: д���ݵ���ǰ�Ĵ洢��
* ��     ��: index:�����ڴ洢���е����
* ��     ��:
* �޸���ʷ:
1��2018-3-25 	Ǯ�پ� 			��ɻ�������
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
* ��������: �ӵ�ǰ�Ĵ洢����ȡ����
* ��     ��: index:�����ڴ洢���е����
* ��     ��:
* �޸���ʷ:
1��2018-3-25 	Ǯ�پ� 			��ɻ�������
=========================================================*/
void readValues(uint index)
{
    uint realOffset = baseAddr;
    int i;

    if (index > 0)
    {
        for (i = 0; i < index; i++)
        {
            //���㵱ǰ������ʵ�ʴ洢ƫ����
            realOffset += (uint)storageValueTable[i].valueType;
        }
    }
    storageRead(realOffset, storageValueTable[index].valueType, (uchar *)storageValueTable[index].pValue);
}

/* =========================================================
* ��������: �洢��ʼ����������д����ע��,�״��������ݳ�ʼ����д�����ݴ洢��
* ��     ��: write���ײ�д���ݺ���
            read:�ײ�����ݺ���
* ��     ��:
* �޸���ʷ:
1��2018-3-25 	Ǯ�پ� 			��ɻ�������
=========================================================*/
void storageInit(writeFunc write, readFunc read)
{
    char head[3];
    uint i;

    //ע���д����
    storageWrite = write;
    storageRead = read;

    //����ͷ���ж��Ƿ�Ϊ�״�����
    storageRead(HEAD_OFFSET, 3, (uchar *)&head);
    if ('X' == head[0] && 'D' == head[1] && 'D' == head[2])
    {

        storageRead(BASE_ADDR_OFFSET, VALUE_U16, (uchar *)&baseAddr);

        //�ѳ�ʼ��������������
        for (i = 0; i < TOTAL_STORAGE_SIZE; i++)
        {
            readValues(i);
        }
    }
    else
    {
        baseAddr = BASE_ADDR_VALUE;
        storageWrite(BASE_ADDR_OFFSET, VALUE_U16, (uchar *)&baseAddr);

        //��ʼ�����ݲ�д��洢��
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

