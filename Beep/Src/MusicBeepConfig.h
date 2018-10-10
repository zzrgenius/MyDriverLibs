#ifndef __MUSIC_BEEP_CONFIG_H__
#define __MUSIC_BEEP_CONFIG_H__

#ifdef VAR_MUSIC_BEEP_GLOBALS
	#define VAR_MUSIC_BEEP_EXT 
#else
	#define VAR_MUSIC_BEEP_EXT extern
#endif

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
#define BEEP_VOICE	50L //声音大小 1~100

//时间,单位1ms
#define BEEP_TIME_10MS			10
#define BEEP_TIME_45MS			45
#define BEEP_TIME_50MS			50
#define BEEP_TIME_85MS			85
#define BEEP_TIME_100MS 		100
#define BEEP_TIME_120MS 		120
#define BEEP_TIME_200MS 		200
#define BEEP_TIME_300MS 		300
#define BEEP_TIME_500MS 		500
#define BEEP_TIME_765MS			765
#define BEEP_TIME_820MS			820
#define BEEP_TIME_1S			1000
#define BEEP_TIME_OFF			0


//输出频率,转定时器1000/freq
#define FREQ_1_96K				510// 1.96K
#define FREQ_2K 				500// 2K
#define FREQ_2_10K				476// 2.10K
#define FREQ_2_36K				424// 2.36K
#define FREQ_2_76K				362// 2.76
#define FREQ_2_86K				350// 2.86K
#define FREQ_3_11K				322// 3.11

#define FREQ_XIMA_DOU			488//2.0495K	
#define FREQ_XIMA_RUI			432//2.315K	
#define FREQ_XIMA_MI			388//2.578K	
#define FREQ_XIMA_FA			364//2.747K	
#define FREQ_XIMA_SOU			324//3.087K	

#define BEEP_OFF				0
/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/
//普通按键音
const MUSIC_BEEP_VALUE Tab_MUSIC_Normal[] =
{
 	{FREQ_2_76K, BEEP_TIME_200MS},
 	{BEEP_OFF, BEEP_TIME_300MS},
//	{BEEP_OFF, BEEP_TIME_1S}, //余音释放
	{BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//无效按键音(2声)
const MUSIC_BEEP_VALUE Tab_MUSIC_Unuse[] =
{
 	{FREQ_2_76K, BEEP_TIME_50MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_76K, BEEP_TIME_50MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
//	{BEEP_OFF, BEEP_TIME_1S}, //余音释放
	{BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//开机音
const MUSIC_BEEP_VALUE Tab_MUSIC_PowerOn[] =
{
 	{FREQ_1_96K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_10K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_36K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_86K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{BEEP_OFF, BEEP_TIME_1S}, //余音释放
	{BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//关机音
const MUSIC_BEEP_VALUE Tab_MUSIC_PowerOff[] =
{
 	{FREQ_2_86K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_36K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_10K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_1_96K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{BEEP_OFF, BEEP_TIME_1S}, //余音释放
	{BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};


//长鸣1S
const MUSIC_BEEP_VALUE Tab_MUSIC_Long[] =
{
	{FREQ_2_76K, BEEP_TIME_1S},
//	{BEEP_OFF, BEEP_TIME_100MS}, //余音释放
	{BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//无效按键音
const MUSIC_BEEP_VALUE Tab_MUSIC_Err[] =
{
 	{FREQ_2_76K, BEEP_TIME_10MS},
	{BEEP_OFF, BEEP_TIME_500MS}, 
	{FREQ_2_76K, BEEP_TIME_10MS},
	{BEEP_OFF, BEEP_TIME_500MS},
	{FREQ_2_76K, BEEP_TIME_10MS},
	{BEEP_OFF, BEEP_TIME_500MS},
	{FREQ_2_76K, BEEP_TIME_10MS},
	{BEEP_OFF, BEEP_TIME_500MS},
	{FREQ_2_76K, BEEP_TIME_10MS},
	{BEEP_OFF, BEEP_TIME_500MS},
//	{BEEP_OFF, BEEP_TIME_1S}, //余音释放
	{BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//阶梯等级音1
const MUSIC_BEEP_VALUE Tab_MUSIC_L1[] =
{
    {FREQ_XIMA_DOU, BEEP_TIME_200MS},
    {BEEP_OFF, BEEP_TIME_300MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//阶梯等级音2
const MUSIC_BEEP_VALUE Tab_MUSIC_L2[] =
{
    {FREQ_XIMA_RUI, BEEP_TIME_200MS},
    {BEEP_OFF, BEEP_TIME_300MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//阶梯等级音3
const MUSIC_BEEP_VALUE Tab_MUSIC_L3[] =
{
    {FREQ_XIMA_MI, BEEP_TIME_200MS},
    {BEEP_OFF, BEEP_TIME_300MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//阶梯等级音4
const MUSIC_BEEP_VALUE Tab_MUSIC_L4[] =
{
    {FREQ_XIMA_FA, BEEP_TIME_200MS},
    {BEEP_OFF, BEEP_TIME_300MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//阶梯等级音5
const MUSIC_BEEP_VALUE Tab_MUSIC_L5[] =
{
    {FREQ_XIMA_SOU, BEEP_TIME_200MS},
    {BEEP_OFF, BEEP_TIME_300MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//新开机音_2
const MUSIC_BEEP_VALUE Tab_MUSIC_PowerOn_2[] =
{
    {956, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {852, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {760, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {640, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {424, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_85MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//新开机音_2
const MUSIC_BEEP_VALUE Tab_MUSIC_PowerOff_2[] =
{
    {424, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {640, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {760, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {852, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {956, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_85MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};


//功能开启音
const MUSIC_BEEP_VALUE Tab_MUSIC_FuncOn[] =
{
    {760, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {600, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {568, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_765MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//功能关闭音
const MUSIC_BEEP_VALUE Tab_MUSIC_FuncOff[] =
{
    {508, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {672, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {760, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_765MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//test beep
const MUSIC_BEEP_VALUE Tab_MUSIC_Test4[] =
{
    {760, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {600, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_765MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//正常音_2
const MUSIC_BEEP_VALUE Tab_MUSIC_Normal_2[] =
{
    {600, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_765MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//无效音_2
const MUSIC_BEEP_VALUE Tab_MUSIC_Unuse_2[] =
{
    {904, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {904, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_765MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};

//test beep
const MUSIC_BEEP_VALUE Tab_MUSIC_Test7[] =
{
    {508, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {760, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {508, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_820MS},
    {BEEP_OFF, BEEP_TIME_OFF} //音乐结束
};



//声音表(越后面等级越高,高等级可以打断低等级)
const MUSIC_BEEP_VALUE *pAllBeepTable[] =
{
    Tab_MUSIC_Err,
    Tab_MUSIC_Long,
	Tab_MUSIC_Normal,
	Tab_MUSIC_Normal_2,
	Tab_MUSIC_FuncOn,
	Tab_MUSIC_FuncOff,
	Tab_MUSIC_L1,
	Tab_MUSIC_L2,
	Tab_MUSIC_L3,
	Tab_MUSIC_L4,
	Tab_MUSIC_L5,
	Tab_MUSIC_Unuse,
	Tab_MUSIC_Unuse_2,
	Tab_MUSIC_PowerOn,
	Tab_MUSIC_PowerOn_2,
	Tab_MUSIC_PowerOff,
	Tab_MUSIC_PowerOff_2
};

#define BEEP_TAB_SIZE (sizeof(pAllBeepTable)/(sizeof(pAllBeepTable[0])))

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/


#endif /* __MUSIC_BEEP_CONFIG_H__ */

