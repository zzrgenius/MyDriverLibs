/*******************************************************************************
* @file    timer.c
* @author  钟昊翰
* @version V1.0.0
* @date    2017-09-25
* @brief   该文件为计时器源文件
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"

/* 私有常量 ----------------------------------------------------------------- */
/* 私有类型 ------------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
/* 私有函数 ------------------------------------------------------------------*/
/* 全局变量 ------------------------------------------------------------------*/
TimerFlg_Typedef  sysTimerFlag = {0};  /* 系统时间标志 */
static uint16_t timerCNT_1ms = 0;    /* 计时器, 每1ms自加1 */
static uint8_t  sysPowerOnTm = 0;    /* 系统上电时间 */
static bool      tm_0D5 = false;     /* 每0.5s取反一次 */
/**
  *  功能说明:  系统时间初始化, 初始化系统时间计数器和所有时间标志
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
  *  功能说明:  系统计时
  *  注意事项:  需要 1ms 时基
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
        
        timerCNT_1ms = 0;  /* 初始化系统时间计数器 */
    }
}

/*******************************************************************************
* Description  : 系统上电时间计时
* Input        : None
* Output       : None
* Note         : 需要 1s 时基
* CreateDate   : 2017/12/12
* ChangeLogs   : 
*******************************************************************************/
void f_SysPowerOnTM(void)
{
    f_AddUint8_t(&sysPowerOnTm, 1);
}

/*******************************************************************************
* Description  : 读取系统上电时间计时
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
* Description  : 0.5s标志翻转
* Input        : None
* Output       : None
* Note         : 需要 500ms 时基
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