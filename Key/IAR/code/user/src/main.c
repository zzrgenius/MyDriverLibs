/*******************************************************************************
* File         : main.c
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2017/10/7
* Description  : 主文件
* Change Logs  : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"

/* 私有类型 ------------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
/* 私有宏   ------------------------------------------------------------------*/
/* 私有函数 ------------------------------------------------------------------*/
static void f_SoftwareInit(void);
/* 私有常量 ----------------------------------------------------------------- */
/* 私有变量 ------------------------------------------------------------------*/
/* 公有变量 ------------------------------------------------------------------*/
#include "KeyDeal.h"
#include"TimeFlag.h"
SYS_TIME_FLAG sysTimeFlag;

void main(void)
{
    __asm("sim");     // 禁止中断
    
    f_BspInit();
    f_SoftwareInit();

    __asm("rim");     // 使能中断
    
    f_KeyDealInit();
    
    while(1)
    {
        REFRESH_IWG;
        
        if(sysTimerFlag.TKS_10MSF)
        {
            sysTimerFlag.TKS_10MSF = 0;
            
           f_KeyResp(f_KeyDiscern);
            
            sysTimeFlag.baseTimeFlag.bits.bSys10MsFlag = true;
           f_KeyDriverDeal(&keyDriver);
            sysTimeFlag.baseTimeFlag.bits.bSys10MsFlag = false;
        }
        
       
    }
}


/**
  *功能说明:  软件数据初始化
  */
static void f_SoftwareInit(void)
{
    f_KeyCfg();  // 按键配置
}
