#ifndef __COMM_PROTOCOL_H__
#define __COMM_PROTOCOL_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "CommDriver.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
//====即热模块====
typedef struct 
{
	uchar headCode;//头码0x32
	uchar add;//地址码0xf0
	uchar mode;//模式0x81
	
	uchar bOnOff:1; //0关闭;1开启
	uchar bRevBits:7;
	
	uchar setTempMSB;//温度设置高8位(实际温度*10)
	uchar setTempLSB;//温度设置低8位
	uchar revData[5];//保留字节
	uchar xorValue; //异或校验(add~revData[4])
	uchar endCode; //尾码0x34
}PROTOCOL_IHEAT_SEND;//即热模块发送数据

typedef struct 
{
	uchar headCode;//头码0x32
	uchar add;//地址码0x0f
	uchar mode;//模式0x01
	
	uchar bOnOff:1; //0关闭;1开启
	uchar bRevBits:7;
	
	uchar bErrorZero:1;//过零错误
	uchar bErrorInTempOpen:1;//进水温度传感器开路
	uchar bErrorInTempShort:1;//进水温度传感器短路
	uchar bErrorOutTempOpen:1;//进水温度传感器开路
	uchar bErrorOutTempShort:1;//进水温度传感器短路
	uchar bErrorOverHeat:1;//过热
	uchar bRevBits1:2;
	
	uchar InTempMSB;//进水温度高8位(实际温度*10)
	uchar InTempLSB;//进水温度低8位
	uchar OutTempMSB;//出水温度高8位(实际温度*10)
	uchar OutTempLSB;//出水温度低8位
	uchar flowMSB;//流量高8位(cc/min)
	uchar flowLSB;//流量低8位
	uchar xorValue; //异或校验(add~revData[4])
	uchar endCode; //尾码0x34
}PROTOCOL_IHEAT_REV;//即热模块接收数据

//====转接板协议====
typedef struct 
{
	uchar headCode;//头码0x55
	uchar mode;//模式 1普通模式 2：调试模式
	
	uchar sysState; //系统状态
	uchar curFunc; //当前功能	
	uchar lidCMD; //翻盖翻圈命令
	uchar keyCode; //回发按键码
	uchar adjustIndex; //冲水阀调节顺序

	uchar bFlushState :1; //冲水状态
	uchar bWashMove: 1; //移动按摩
	uchar bStrongWeak: 1; //强弱按摩
	uchar bColdHot: 1; //冷热按摩
	uchar bErrNoWater: 1; //无水故障
	uchar bKeyDryIO :1; //烘干按键IO状态
	uchar bFlushAdjust :1; //冲洗时间调整
	uchar bFourceSit: 1; //强制模拟着座
	
	uchar xorValue; //异或校验
}PROTOCOL_CHANGE_SEND;//转接板发送数据

typedef struct 
{
	uchar headCode;//头码0x55
	uchar mode;//模式0x01

	uchar keyCode; //键值
	sint seatTemp; //坐温
	uchar lidCmd; //翻圈命令回传
	
	uchar seatLidRange :4; //座圈位置
	uchar topLidRange :4; //上盖位置
	
	uchar waterLevel :4; //水温档位
	uchar seatLevel :4;  //坐温档位

	uchar dryLevel :4; //烘干档位
	uchar nozzlePos :4; //喷杆位置
	
	uchar flowPos :4; //流量档位
	uchar bRevBits:4; 

	uchar bErrSeatTempOpen :1;
	uchar bErrSeatTempShort :1;
	uchar bSitState :1; //着座状态
	uchar bHasPerson :1; //微波感应
	uchar bKeyPressed :1; //扶手板有按键按下
	uchar bRevBits_1 :3; //冲洗时间调整
	
	uchar xorValue; //异或校验
}PROTOCOL_CHANGE_REV;//转接板接收数据

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
//====协议相关====
//即热
#define FRAME_IHEAT_HEAD 0x32
#define FRAME_IHEAT_ADD 0x0f
#define PFRAME_IHEAT_ADD_POS 1
#define PFRAME_IHEAT_REV_LEN sizeof(PROTOCOL_IHEAT_REV)

//转接板
#define FRAME_CHANGE_HEAD 0x55
#define PFRAME_CHANGE_REV_LEN sizeof(PROTOCOL_CHANGE_REV)

 


//====内部命令定义====
#define COMM_CMD_IHEAT COMM_SET_CMD(0, 0, 1)//即热通信,非循环,不重发,内部序号1
#define COMM_CMD_CHANGE COMM_SET_CMD(0, 0, 2)//转换板通信,非循环,不重发,内部序号2

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
COMM_FUNC_TAB const * f_CommFindFuncTable(QUEUE_DATA_TYPE cmd);
uchar f_CommRevDeal(COMM_DRIVER *pDriver);


#endif /* __COMM_PROTOCOL_H__ */
