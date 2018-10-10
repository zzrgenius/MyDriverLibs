/*******************************************************************************
* File         : key_hardware.c
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2018/4/13
* Description  : 按键硬件模糊层
* Change Logs  : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"
#include"key_hardware.h"

/* 私有类型 ------------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
/* 私有宏   ------------------------------------------------------------------*/
#define READ_KEY_S1  PC_IDR_IDR3
#define READ_KEY_S2  PC_IDR_IDR4
#define READ_KEY_S3  PC_IDR_IDR5
#define READ_KEY_S4  PC_IDR_IDR6
#define READ_KEY_S5  PC_IDR_IDR7
#define READ_KEY_S6  PD_IDR_IDR2
#define READ_KEY_S7  PD_IDR_IDR3
#define READ_KEY_S8  PA_IDR_IDR1
#define READ_KEY_S9  PA_IDR_IDR2
/* 私有函数 ------------------------------------------------------------------*/
/* 私有常量 ----------------------------------------------------------------- */
/* 私有变量 ------------------------------------------------------------------*/
/* 公有变量 ------------------------------------------------------------------*/

/*******************************************************************************
* Description  : 按键识别
* Input        : None
* Output       : None
* Note         : 
* CreateDate   : 2018/4/2
* ChangeLogs   : 
*******************************************************************************/
void f_KeyDiscern(void)
{
    // 单按键识别
    f_SingleKeyDiscern(KEY_CODE0, (KeyState_t)(!READ_KEY_S1));
    f_SingleKeyDiscern(KEY_CODE1, (KeyState_t)(!READ_KEY_S2));
    f_SingleKeyDiscern(KEY_CODE2, (KeyState_t)(!READ_KEY_S3));
    
    // 组合按键
    f_ComplexKeyDiscern(KEY_CODE3, 2, (uint8_t)KEY_CODE0, (uint8_t)KEY_CODE1);
}
