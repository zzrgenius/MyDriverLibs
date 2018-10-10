#ifndef __KEY_SCAN_H
#define __KEY_SCAN_H

#ifdef  VAR_KEY_SCAN_GLOBALS
	#define  VAR_KEY_SCAN_EXT
#else
	#define  VAR_KEY_SCAN_EXT  extern
#endif

#define KEY_SIG_NUMB	16
#define KEY_COM_NUMB	0

//----------按键进程状态,最大支持8钟-----------
#define PRESSED			0x01	//按下短按
#define PRESSED_RE		0x02	//释放短按
#define PRESSED_1S		0x04	// 1S长按
#define PRESSED_1d5S	0x08	// 1.5S长按
#define PRESSED_2S		0x10	// 2S长按
#define PRESSED_3S		0x20	// 3S长按
#define PRESSED_5S		0x40	//5S长按
#define PRESSED_300mS	0x80	//300mS长按

//---------------状态时间定义,与状态一致--------------
#define KEY_DELAY_TIME			5//5*10ms
#define KEY_SHORT_TIME			90//释放有效时间 80*10ms
#define KEY_PRESS_TIME_300mS	30//30*10ms
#define KEY_PRESS_TIME_1000mS	100//100*10ms
#define KEY_PRESS_TIME_1500mS	150//150*10ms
#define KEY_PRESS_TIME_2S		50//200//200*10ms
#define KEY_PRESS_TIME_3S		300//300*10ms
#define KEY_PRESS_TIME_5S		500//500*10ms
#define KEY_PRESS_TIME_10S		1000//1000*10ms
#define KEY_PRESS_TIME_15S		1500//1000*10ms

#define MAX_STEP 	8//为Tab_KeyOutState[]长度
typedef struct
{
	unsigned int StateTm;
	unsigned char StateName;
}ST_KeyTimeState;

VAR_KEY_SCAN_EXT FLASH ST_KeyTimeState Tab_KeyOutState[]//更具需要的按键输出信息填写(所有按键信息汇总,不包括PRESSED_RE)
#ifdef VAR_KEY_SCAN_GLOBALS
=
{
	{KEY_DELAY_TIME , PRESSED},
	{KEY_PRESS_TIME_1000mS , PRESSED_1S},
	{KEY_PRESS_TIME_2S , PRESSED_2S},
	{KEY_PRESS_TIME_3S , PRESSED_3S},	
	{0,0xff}	
}
#endif
;

#define GetTime(nKey)		(Tab_KeyOutState[nKey].StateTm)//获取对应名字按键时间
#define SetTimeInf(nKey)	(Tab_KeyOutState[nKey].StateName)//对达到时间的，赋值按键状态

#define KEY_ALL		0xffffffff
#define NO_KEY 		0
#define SIG_BASE 	8
//--------------单键
#define KEY_SIG_1	0x000001
#define KEY_SIG_2	0x000002
#define KEY_SIG_3	0x000004
#define KEY_SIG_4	0x000008
#define KEY_SIG_5	0x000010
#define KEY_SIG_6	0x000020
#define KEY_SIG_7	0x000040
#define KEY_SIG_8	0x000080
#define KEY_SIG_9	0x000100
#define KEY_SIG_10	0x000200
#define KEY_SIG_11	0x000400
#define KEY_SIG_12	0x000800
#define KEY_SIG_13	0x001000
#define KEY_SIG_14	0x002000
#define KEY_SIG_15	0x004000
#define KEY_SIG_16	0x008000
#define KEY_SIG_17	0x010000
#define KEY_SIG_18	0x020000
#define KEY_SIG_19	0x040000
#define KEY_SIG_20	0x080000
#define KEY_SIG_21	0x100000
#define KEY_SIG_22	0x200000
#define KEY_SIG_23	0x400000
#define KEY_SIG_24	0x800000

//---------------组合按键键值
#define KEY_COM_1	0//(KEY_SIG_10 | KEY_SIG_12)//SIG4+SIG5
#define KEY_COM_2	0
#define KEY_COM_3	0
#define KEY_COM_4	0
#define KEY_COM_5	0
#define KEY_COM_6	0
#define KEY_COM_7	0
#define KEY_COM_8	0

#define KEY_TOTAL_COM (KEY_COM_1 | KEY_COM_2)


VAR_KEY_SCAN_EXT FLASH unsigned long nTab_KeyHexDef[]
#ifdef VAR_KEY_SCAN_GLOBALS
=
{
	KEY_COM_1,
	KEY_COM_2,
	KEY_COM_3,
	KEY_COM_4,
	KEY_COM_5,
	KEY_COM_6,
	KEY_COM_7,
	KEY_COM_8,
	
	KEY_SIG_1,
	KEY_SIG_2,
	KEY_SIG_3,
	KEY_SIG_4,
	KEY_SIG_5,
	KEY_SIG_6,
	KEY_SIG_7,
	KEY_SIG_8,
	KEY_SIG_9,
	KEY_SIG_10,
	KEY_SIG_11,
	KEY_SIG_12,
	KEY_SIG_13,
	KEY_SIG_14,
	KEY_SIG_15,
	KEY_SIG_16,
	KEY_SIG_17,
	KEY_SIG_18,
	KEY_SIG_19,
	KEY_SIG_20,
	KEY_SIG_21,
	KEY_SIG_22,
	KEY_SIG_23,
	KEY_SIG_24
}
#endif
;

typedef enum
{//按键单按\组合状态
	KEY_FREE,
	KEY_COM_PRESS_1,
	KEY_COM_PRESS_2,
	KEY_COM_PRESS_3,
	KEY_COM_PRESS_4,
	KEY_COM_PRESS_5,
	KEY_COM_PRESS_6,
	KEY_COM_PRESS_7,
	KEY_COM_PRESS_8,
	KEY_SIGNAL_PRESS_1,
	KEY_SIGNAL_PRESS_2,
	KEY_SIGNAL_PRESS_3,
	KEY_SIGNAL_PRESS_4,
	KEY_SIGNAL_PRESS_5,
	KEY_SIGNAL_PRESS_6,
	KEY_SIGNAL_PRESS_7,
	KEY_SIGNAL_PRESS_8,
	KEY_SIGNAL_PRESS_9,
	KEY_SIGNAL_PRESS_10,
	KEY_SIGNAL_PRESS_11,
	KEY_SIGNAL_PRESS_12,
	KEY_SIGNAL_PRESS_13,
	KEY_SIGNAL_PRESS_14,
	KEY_SIGNAL_PRESS_15,
	KEY_SIGNAL_PRESS_16,
	KEY_SIGNAL_PRESS_17,
	KEY_SIGNAL_PRESS_18,
	KEY_SIGNAL_PRESS_19,
	KEY_SIGNAL_PRESS_20,
	KEY_SIGNAL_PRESS_21,
	KEY_SIGNAL_PRESS_22,
	KEY_SIGNAL_PRESS_23,
	KEY_SIGNAL_PRESS_24
}KEY_PRESSED_STATE;

typedef struct
{
	unsigned long nKeyInf;	//获取过来的原始按键信息
	unsigned char nKeyResultInf; //按键键输出结果
	unsigned char bKeyUsedFlag : 1; //按键结果被使用
	unsigned char bKeyFirstRelse : 1;//按键第一次被释放
	unsigned char bKeyPressFlag : 1;	//按键被按下标志
	KEY_PRESSED_STATE KeyPressName;	//按下按键名
	unsigned int nKeyDownTm;//按键按下时间
	unsigned int nNoKeyTm;//无按键按下时间
	unsigned int nKeyRealDownTm;	//按键真实按下时间
	unsigned char nKeyStep;//扫描步骤
}KEY_SCAN_INF;
VAR_KEY_SCAN_EXT AT_NEAR KEY_SCAN_INF KeyScanInf __attribute__((at(0x1D0)));

VAR_KEY_SCAN_EXT void f_KeyScan(void);

#endif	//__KEY_SCAN_H

