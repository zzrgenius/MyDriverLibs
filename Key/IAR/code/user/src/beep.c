/*******************************************************************************
* @file    beep.c
* @author  ��껺�
* @version V1.0.0
* @date    2017-09-25
* @brief   ���ļ�ΪԴ�ļ���ʽģ��
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"

/* ˽�г��� ----------------------------------------------------------------- */
/* ���� */
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

/* ���¸澯 */
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

/* �ϵ� */
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

/* ָ��赥������ */
const uint8_t *const MusicSoundTab[] =
{
	TBL_MUSIC_NORMAL,   //0
	TBL_MUSIC_Unuse,    //1
	TBL_MUSIC_Long,     //2
	TBL_MUSIC_Alarm,    //3
    TBL_MUSIC_POR       //4
};

/* ˽������ ------------------------------------------------------------------*/
/* ˽�ж��� ------------------------------------------------------------------*/
#define MAX_BEEP_NO (sizeof(MusicSoundTab)/sizeof(uint8_t *))


/* ˽�б��� ------------------------------------------------------------------*/
uint8_t musicDelayTm = 0;        /* ÿ���������ŵ�ʱ�� */
uint8_t const* pMusicAddr;
uint8_t musicPos = 0;            /* ָ��赥������ */


/* ˽�к��� ------------------------------------------------------------------*/

/**
  *  ����˵��:  ��ʼ������������
  */
void f_InitBuzPara(void)
{
	musicDelayTm = 0;
	musicPos = 0;
}

/*******************************************************************************
* Description  : ����������
*                ����ǰ����Ƶ������һ��Ƶ�����, ��ֱ�ӷ���(��ֹ�����������϶�����)
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
  *  �������:  MusicTab_Typedef MusicNum
  *  ����˵��:  ѡ�񲥷Ÿ���
  */
void f_Beep(MusicTab_Typedef MusicNum)
{    
	pMusicAddr = MusicSoundTab[MusicNum];
 
	f_MCU_OutMusicPWM(pMusicAddr[0]);
    
	musicPos = 1;  /* ��ʼ���� */
	musicDelayTm = 0;
}

/**
  *  ����˵��:  ������������
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
			{/* �������� */
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
  *  ����˵��:  ���������Ƿ�ֹͣ����
  *  �������:  true  ������ֹͣ����
                false ��������������
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
  *  ����˵��:  ��������ʱ��
  *  ע������:  ��Ҫ 10ms ʱ��,���ڼ�ʱÿ��������ʱ��
  */
void f_IncBuzTm(void)
{
	f_AddUint8_t(&musicDelayTm, 1);
}