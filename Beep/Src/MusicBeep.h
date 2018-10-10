#ifndef __MUSIC_BEEP_H__
#define __MUSIC_BEEP_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
typedef struct 
{
	uint freq; //蜂鸣频率
	uint keepTm; //保持时间
}MUSIC_BEEP_VALUE; //蜂鸣音乐值,用于建蜂鸣表

typedef enum 
{
    MUSIC_BEEP_ERR = 0, //故障音           
    MUSIC_BEEP_SIT,	//着座音
	MUSIC_BEEP_NORMAL, //正常应
	MUSIC_BEEP_NORMAL_2, //正常音2
	MUSIC_BEEP_FUNC_ON, //功能开启音
	MUSIC_BEEP_FUNC_OFF, //功能关闭音
	MUSIC_BEEP_L1, //阶梯音1
	MUSIC_BEEP_L2, //阶梯音2
	MUSIC_BEEP_L3, //阶梯音3
	MUSIC_BEEP_L4, //阶梯音4
	MUSIC_BEEP_L5, //阶梯音5
	MUSIC_BEEP_UNUSE,	//无效音
	MUSIC_BEEP_UNUSE_2,	//无效音2
	MUSIC_BEEP_POWER_ON, //开机音
	MUSIC_BEEP_POWER_ON_2, //开机音_2
	MUSIC_BEEP_POWER_OFF, //关机音
	MUSIC_BEEP_POWER_OFF_2 //关机音
}MUSIC_BEEP_TYPE;//声音类型与pAllBeepTable对应(约大优先级越高，优先级高的能打断优先级低的，反之不能)
#define BEEP_MIN_PRIORITY MUSIC_BEEP_ERR //最小优先级

typedef struct 
{
	uint curBeepTm; //当前蜂鸣时间 
	MUSIC_BEEP_VALUE beepInfo;
	const MUSIC_BEEP_VALUE *pBeepTab; //蜂鸣的组
	uchar beepIndex; //蜂鸣顺序
	MUSIC_BEEP_TYPE curType; //当前类型(包含优先级信息)
}MUSIC_BEEP_DRIVER;//蜂鸣驱动


/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_MusicBeep(void);
void f_SetBeep(MUSIC_BEEP_TYPE type);

#endif /* __MUSIC_BEEP_H__ */
