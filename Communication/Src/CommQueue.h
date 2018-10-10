#ifndef __COMM_QUEUE_H__
#define __COMM_QUEUE_H__

/*----------------------------------------------*
 * 包含头文件										  *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 数据类型定义										 *
 *----------------------------------------------*/
#define QUEUE_DATA_TYPE uint
#define COMM_QUEUE_LEN 10 //队列大小

typedef struct 
{
	uchar	head; //队列头
	uchar	tail; //队列尾
	QUEUE_DATA_TYPE  buf[COMM_QUEUE_LEN]; //缓存
	uchar	curSize; //当前队列大小
} COMM_QUEUE; //通信队列


/*----------------------------------------------*
 * 模块级变量声明									  *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明									  *
 *----------------------------------------------*/
void f_CommQueueInit(COMM_QUEUE *pDriver);
uchar f_CommQueueIsEmpty(COMM_QUEUE *pDriver);
uchar f_CommQueuePop(COMM_QUEUE *pDriver, QUEUE_DATA_TYPE *pData);
uchar f_CommQueuePush(COMM_QUEUE *pDriver, QUEUE_DATA_TYPE data);
uchar f_CommFindData(COMM_QUEUE *pDriver, QUEUE_DATA_TYPE data);

#endif /* __COMM_QUEUE_H__ */

