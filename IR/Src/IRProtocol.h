#ifndef __IR_PROTOCOL_H__
#define __IR_PROTOCOL_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
typedef struct 
{	
	//数据1
	uchar keyCode; //按键码
	//数据2
	uchar waterLevel:4; //水温档
	uchar seatLevel:4; //座温档
	//数据3
	uchar dryLevel:4; //烘干风温档
	uchar flowLevel:4; //流量档位
	//数据4
	uchar nozzlePos; //喷杆管位
}REMOTER_PROTOCOL;//遥控器协议

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_IRRevDataDeal(uchar *pData, uchar len);

#endif /* __IR_PROTOCOL_H__ */
