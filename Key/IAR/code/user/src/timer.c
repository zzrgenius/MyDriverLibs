/*******************************************************************************
* @file    timer.c
* @author  ��껺�
* @version V1.0.0
* @date    2017-09-25
* @brief   ���ļ�Ϊ��ʱ��Դ�ļ�
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"

/* ˽�г��� ----------------------------------------------------------------- */
/* ˽������ ------------------------------------------------------------------*/
/* ˽�ж��� ------------------------------------------------------------------*/
/* ˽�б��� ------------------------------------------------------------------*/
/* ˽�к��� ------------------------------------------------------------------*/
/* ȫ�ֱ��� ------------------------------------------------------------------*/
TimerFlg_Typedef  sysTimerFlag = {0};  /* ϵͳʱ���־ */
static uint16_t timerCNT_1ms = 0;    /* ��ʱ��, ÿ1ms�Լ�1 */
static uint8_t  sysPowerOnTm = 0;    /* ϵͳ�ϵ�ʱ�� */
static bool      tm_0D5 = false;     /* ÿ0.5sȡ��һ�� */
/**
  *  ����˵��:  ϵͳʱ���ʼ��, ��ʼ��ϵͳʱ�������������ʱ���־
  */
void f_SysTimer_Init(void)
{
    timerCNT_1ms = 0;
    
//    sysTimerFlag.TKS_2MSF   = 0;
//    sysTimerFlag.TKS_5MSF   = 0;
    sysTimerFlag.TKS_10MSF  = 0;
//    sysTimerFlag.TKS_50MSF  = 0;
    sysTimerFlag.TKS_100MSF = 0;
//    sysTimerFlag.TKS_250MSF = 0;
    sysTimerFlag.TKS_500MSF = 0;
    sysTimerFlag.TKS_1SF    = 0;
}

/**
  *  ����˵��:  ϵͳ��ʱ
  *  ע������:  ��Ҫ 1ms ʱ��
  */
void f_Timepiece(void)
{
    timerCNT_1ms ++;
    
//    if(!(timerCNT_1ms % 2))
//    {
//        sysTimerFlag.TKS_2MSF = 1;
//    }
//    if(!(timerCNT_1ms % 5))
//    {
//        sysTimerFlag.TKS_5MSF = 1;
//    }
    if(!(timerCNT_1ms % 10))
    {
        sysTimerFlag.TKS_10MSF = 1;
    }
    
//    if(!(timerCNT_1ms % 50))
//    {
//        sysTimerFlag.TKS_50MSF = 1;
//    }
    
    if(!(timerCNT_1ms % 100))
    {
        sysTimerFlag.TKS_100MSF = 1;
    }
    
//    if(!(timerCNT_1ms % 250))
//    {
//        sysTimerFlag.TKS_250MSF = 1;
//    }
    
    if(!(timerCNT_1ms % 500))
    {
        sysTimerFlag.TKS_500MSF = 1;
    }
    
    if(!(timerCNT_1ms % 1000))
    {
        sysTimerFlag.TKS_1SF = 1;
        
        timerCNT_1ms = 0;  /* ��ʼ��ϵͳʱ������� */
    }
}

/*******************************************************************************
* Description  : ϵͳ�ϵ�ʱ���ʱ
* Input        : None
* Output       : None
* Note         : ��Ҫ 1s ʱ��
* CreateDate   : 2017/12/12
* ChangeLogs   : 
*******************************************************************************/
void f_SysPowerOnTM(void)
{
    f_AddUint8_t(&sysPowerOnTm, 1);
}

/*******************************************************************************
* Description  : ��ȡϵͳ�ϵ�ʱ���ʱ
* Input        : None
* Output       : ture/false
* Note         : 
* CreateDate   : 2017/12/12
* ChangeLogs   : 
*******************************************************************************/
uint8_t f_ReadSysPowerOnTM(void)
{
    return (sysPowerOnTm);
}

/*******************************************************************************
* Description  : 0.5s��־��ת
* Input        : None
* Output       : None
* Note         : ��Ҫ 500ms ʱ��
* CreateDate   : 2017/12/12
* ChangeLogs   : 
*******************************************************************************/
void f_Overturn500msFlag(void)
{
    tm_0D5 = !tm_0D5;
}

/*******************************************************************************
* Description  : 
* Input        : None
* Output       : None
* Note         : 
* CreateDate   : 2017/12/12
* ChangeLogs   : 
*******************************************************************************/
bool f_Read500msFlag(void)
{
    return (tm_0D5);
}