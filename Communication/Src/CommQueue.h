#ifndef __COMM_QUEUE_H__
#define __COMM_QUEUE_H__

/*----------------------------------------------*
 * ����ͷ�ļ�										  *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * �������Ͷ���										 *
 *----------------------------------------------*/
#define QUEUE_DATA_TYPE uint
#define COMM_QUEUE_LEN 10 //���д�С

typedef struct 
{
	uchar	head; //����ͷ
	uchar	tail; //����β
	QUEUE_DATA_TYPE  buf[COMM_QUEUE_LEN]; //����
	uchar	curSize; //��ǰ���д�С
} COMM_QUEUE; //ͨ�Ŷ���


/*----------------------------------------------*
 * ģ�鼶��������									  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������									  *
 *----------------------------------------------*/
void f_CommQueueInit(COMM_QUEUE *pDriver);
uchar f_CommQueueIsEmpty(COMM_QUEUE *pDriver);
uchar f_CommQueuePop(COMM_QUEUE *pDriver, QUEUE_DATA_TYPE *pData);
uchar f_CommQueuePush(COMM_QUEUE *pDriver, QUEUE_DATA_TYPE data);
uchar f_CommFindData(COMM_QUEUE *pDriver, QUEUE_DATA_TYPE data);

#endif /* __COMM_QUEUE_H__ */

