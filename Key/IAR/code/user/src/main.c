/*******************************************************************************
* File         : main.c
* Version      : v1.0.0
* Author       : ��껺�
* CreateDate   : 2017/10/7
* Description  : ���ļ�
* Change Logs  : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"

/* ˽������ ------------------------------------------------------------------*/
/* ˽�ж��� ------------------------------------------------------------------*/
/* ˽�к�   ------------------------------------------------------------------*/
/* ˽�к��� ------------------------------------------------------------------*/
static void f_SoftwareInit(void);
/* ˽�г��� ----------------------------------------------------------------- */
/* ˽�б��� ------------------------------------------------------------------*/
/* ���б��� ------------------------------------------------------------------*/
#include "KeyDeal.h"
#include"TimeFlag.h"
SYS_TIME_FLAG sysTimeFlag;

void main(void)
{
    __asm("sim");     // ��ֹ�ж�
    
    f_BspInit();
    f_SoftwareInit();

    __asm("rim");     // ʹ���ж�
    
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
  *����˵��:  ������ݳ�ʼ��
  */
static void f_SoftwareInit(void)
{
    f_KeyCfg();  // ��������
}
