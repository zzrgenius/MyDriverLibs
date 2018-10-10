/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : MusicBeep.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月7日
  最近修改   :
  功能描述   : 音乐蜂鸣器驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月7日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/
#define  VAR_MUSIC_BEEP_GLOBALS
/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "MusicBeep.h"
#include "MusicBeepConfig.h"
#include "IO_Define.h"
#include "SubFunction.h"

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/
MUSIC_BEEP_DRIVER musicBeep;

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

/*****************************************************************************
 函 数 名: f_BeepPWMOut
 功能描述  : 蜂鸣器PWM输出
 输入参数: uint freq  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月7日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_BeepPWMOut(uint setFreq)
{
	if(setFreq)
	{
		TIM2_ARRH = setFreq>>8;
		TIM2_ARRL = (uchar)setFreq;	
		setFreq = setFreq*BEEP_VOICE/100;
		TIM2_CCR1H = (setFreq>>8);
		TIM2_CCR1L = ((uchar)setFreq);
		TIM2_CCMR1=0x68;//通道1 开启预装载， PWM模式1 向上计数时 <CCR 有效电平
		MUSIC_BEEP_POWER(true);
	}
	else
	{
		TIM2_CCMR1 = 0x48;//强制输出无效电平 低电平
		MUSIC_BEEP_POWER(false);
	}
}

/*****************************************************************************
 函 数 名: f_SetBeep
 功能描述  : 设置蜂鸣组，用于选择声音
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月7日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_SetBeep(MUSIC_BEEP_TYPE type)
{
	if (type >= BEEP_TAB_SIZE)
	{
		return;
	}

	if (type >= musicBeep.curType)
	{
        musicBeep.beepIndex = 0;
        musicBeep.curBeepTm = 0;
        musicBeep.pBeepTab = pAllBeepTable[type];
        musicBeep.beepInfo = musicBeep.pBeepTab[musicBeep.beepIndex];
        f_BeepPWMOut(musicBeep.beepInfo.freq);//设置第一个蜂鸣频率
    }
}

/*****************************************************************************
 函 数 名: f_MusicBeep
 功能描述  : 音乐蜂鸣器流程控制
 输入参数:
 返 回 值: 
 注     意: 10ms调用
 
 修改历史:
  1.日    期   : 2018年5月7日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_MusicBeep(void)
{
    if (NULL != musicBeep.pBeepTab)
    {
    	f_AddU16Data(&musicBeep.curBeepTm);
		if (musicBeep.curBeepTm >= musicBeep.beepInfo.keepTm)
		{
			musicBeep.curBeepTm = 0;
			musicBeep.beepIndex++;
			musicBeep.beepInfo = musicBeep.pBeepTab[musicBeep.beepIndex];
			if (BEEP_TIME_OFF == musicBeep.beepInfo.keepTm)//音乐结束
			{
				musicBeep.pBeepTab = NULL;
				musicBeep.curType = BEEP_MIN_PRIORITY; //设置为最小优先级,让其他音乐可以响
				f_BeepPWMOut(0);
			}
			else
			{
				if (BEEP_OFF == musicBeep.beepInfo.freq)
				{
					MUSIC_BEEP_POWER(false);
				}
				else
				{
					f_BeepPWMOut(musicBeep.beepInfo.freq);
				}
			}
		}
    }
}

