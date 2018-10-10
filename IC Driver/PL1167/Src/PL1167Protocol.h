#ifndef __PL1167_PROTOCOL_H__
#define __PL1167_PROTOCOL_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
typedef struct 
{
	uchar machineCode;
	
	uchar bStrength_L:1;//强度低
	uchar bStrength_M:1;//强度中
	uchar bStrength_H:1;//强度高
	uchar bFuncHip:1;//臀部
	uchar bFuncFemal:1;//女性
	uchar bFuncDry:1;//烘干
	uchar bStop:1;//停止
	uchar bPower:1;//电源

	uchar bWaterTemp_L:1;//水温低
	uchar bWaterTemp_M:1;//水温中
	uchar bWaterTemp_H:1;//水温高
	uchar rev1:1;//保留位
	uchar bSeatTemp_L:1;//座温低
	uchar bSeatTemp_M:1;//座温中
	uchar bSeatTemp_H:1;//座温高
	uchar rev2:1;//保留位

	uchar bSave:1;//保存
	uchar bMassage:1;//按摩
	uchar bLight:1;//夜灯
	uchar bLEDLight:1;//液晶背光
	uchar bClean:1;//喷杆自洁
	uchar bWide:1;//宽幅
	uchar bRush:1;//冲水
	uchar rev3:1;//保留位

	uchar data4;

	uchar endCode;	
}PROCOTOL_XI_MA_RC;//西马遥控器协议

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
extern PROCOTOL_XI_MA_RC procotolXiMaRC;

#define MACHINE_CODE_LEN 6//配对码长度
extern uchar machineID[MACHINE_CODE_LEN];//机器配对码

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
uchar f_PL1167_GetSendBuffer(uchar *pBuf, uint len);
uchar f_PL1167_RevProtocolDeal(uchar *pData, uchar len);


#endif /* __PL1167_PROTOCOL_H__ */
