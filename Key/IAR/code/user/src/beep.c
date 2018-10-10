/*******************************************************************************
* @file    beep.c
* @author  钟昊翰
* @version V1.0.0
* @date    2017-09-25
* @brief   该文件为源文件格式模板
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"

/* 私有常量 ----------------------------------------------------------------- */
/* 歌曲 */
const uint8_t TBL_MUSIC_NORMAL[] =
{
    FREQ_E,		TIME_D,
	BEEP_STOP
};

const uint8_t TBL_MUSIC_Unuse[] =
{
    FREQ_E,		TIME_D,
	FREQ_OFF,	TIME_B,
	FREQ_E,		TIME_D,
	FREQ_OFF,	TIME_B,
	BEEP_STOP
};

const uint8_t TBL_MUSIC_Long[] =
{
    FREQ_E,		TIME_L,
	FREQ_E,		TIME_L,
	FREQ_E,		TIME_L,
	FREQ_E,		TIME_L,
	FREQ_E,		TIME_L,
	FREQ_E,		TIME_L,
	BEEP_STOP
};

/* 低温告警 */
const uint8_t TBL_MUSIC_Alarm[] =
{
    FREQ_E,		TIME_L,
	FREQ_OFF,	TIME_E,
	FREQ_E,		TIME_L,
	FREQ_OFF,	TIME_E,
	FREQ_E,		TIME_L,
	FREQ_OFF,	TIME_E,
    FREQ_E,		TIME_L,
	FREQ_OFF,	TIME_E,
    FREQ_E,		TIME_L,
	FREQ_OFF,	TIME_E,
    FREQ_E,		TIME_L,
	FREQ_OFF,	TIME_E,
    FREQ_E,		TIME_L,
	FREQ_OFF,	TIME_E,
    FREQ_E,		TIME_L,
	FREQ_OFF,	TIME_E,
    FREQ_E,		TIME_L,
	FREQ_OFF,	TIME_E,
    FREQ_E,		TIME_L,
	FREQ_OFF,	TIME_E,
	BEEP_STOP
};

/* 上电 */
const uint8_t TBL_MUSIC_POR[] = 
{
    FREQ_E,		TIME_E,
	FREQ_OFF,	TIME_E,
	FREQ_E,		TIME_E,
	FREQ_OFF,	TIME_E,
	FREQ_E,		TIME_E,
	FREQ_OFF,	TIME_E,
    BEEP_STOP
};

/* 指向歌单的数组 */
const uint8_t *const MusicSoundTab[] =
{
	TBL_MUSIC_NORMAL,   //0
	TBL_MUSIC_Unuse,    //1
	TBL_MUSIC_Long,     //2
	TBL_MUSIC_Alarm,    //3
    TBL_MUSIC_POR       //4
};

/* 私有类型 ------------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
#define MAX_BEEP_NO (sizeof(MusicSoundTab)/sizeof(uint8_t *))


/* 私有变量 ------------------------------------------------------------------*/
uint8_t musicDelayTm = 0;        /* 每个音符播放的时间 */
uint8_t const* pMusicAddr;
uint8_t musicPos = 0;            /* 指向歌单的音符 */


/* 私有函数 ------------------------------------------------------------------*/

/**
  *  功能说明:  初始化蜂鸣器参数
  */
void f_InitBuzPara(void)
{
	musicDelayTm = 0;
	musicPos = 0;
}

/*******************************************************************************
* Description  : 蜂鸣器控制
*                若当前设置频率与上一次频率相等, 则直接返回(防止蜂鸣器声音断断续续)
* Input        : None
* Output       : None
* Note         : 
* CreateDate   : 2017/10/18
* ChangeLogs   : 
*******************************************************************************/
static void f_MCU_OutMusicPWM(uint16_t SetFreqValue) 
{
    static uint16_t LastFreqValue = 0;
    
    if(SetFreqValue == LastFreqValue)
    {
        return;
    }
    else
    {
        LastFreqValue = SetFreqValue;
    }
    
	if(SetFreqValue)
	{
        TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,243, TIM2_OCPOLARITY_HIGH);
	}
	else
	{
        TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_DISABLE,243, TIM2_OCPOLARITY_HIGH);
	}
}

/**
  *  输入参数:  MusicTab_Typedef MusicNum
  *  功能说明:  选择播放歌曲
  */
void f_Beep(MusicTab_Typedef MusicNum)
{    
	pMusicAddr = MusicSoundTab[MusicNum];
 
	f_MCU_OutMusicPWM(pMusicAddr[0]);
    
	musicPos = 1;  /* 开始鸣叫 */
	musicDelayTm = 0;
}

/**
  *  功能说明:  蜂鸣器处理函数
  */
void f_BuzPro(void)
{
	if(musicPos)
	{
		if(musicDelayTm >= pMusicAddr[musicPos])
		{
			musicPos ++;
			musicDelayTm = 0;
            
			if(pMusicAddr[musicPos] == BEEP_STOP)
			{/* 结束鸣叫 */
				musicPos = 0;
                
				f_MCU_OutMusicPWM(0);
			}
			else
			{
                f_MCU_OutMusicPWM(pMusicAddr[musicPos]);
                
				musicPos ++;
				musicDelayTm = 0;
			}
		}
	}
}

/**
  *  功能说明:  检测蜂鸣器是否停止鸣叫
  *  输出参数:  true  蜂鸣器停止鸣叫
                false 蜂鸣器正在鸣叫
  */
bool f_IsBeepStop(void)
{
    if(musicPos)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
  *  功能说明:  蜂鸣器计时器
  *  注意事项:  需要 10ms 时基,用于计时每个音符的时间
  */
void f_IncBuzTm(void)
{
	f_AddUint8_t(&musicDelayTm, 1);
}