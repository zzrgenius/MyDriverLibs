/*******************************************************************************
* File         : key_cfg.c
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2018/4/13
* Description  : 按键配置层
* Change Logs  : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"
#include"key_cfg.h"

/* 私有类型 ------------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
/* 私有宏   ------------------------------------------------------------------*/
#define KEY_RESP(_RESP_ROOT_)   _RESP_ROOT_,(sizeof(_RESP_ROOT_)/sizeof(_RESP_ROOT_[0]))

#define DBMTM     DEBOUNCE_MIN_TM  // 消抖最小时间
#define K1STM     (1000u)          // 长按响应时间(单位:ms)
#define K2STM     (2000u)
#define K3STM     (3000u)
#define K4STM     (4000u)
#define K5STM     (5000u)
#define K6STM     (6000u)
#define K7STM     (7000u)
/* 私有函数 ------------------------------------------------------------------*/
/* 私有常量 ----------------------------------------------------------------- */
RespList_t keycode0[] = 
{
/*   响应时间  按下响应      释放响应   */
    {DBMTM,    f_Key0_P_0,   f_Key0_R_0},
    {K3STM,    f_Key0_P_1,   NULL      },
    {K5STM,    f_Key0_P_2,   NULL      },
    
    /* 若一个按键有多个响应时间,直接在响应列表中添加元素即可(下同) */
//    {K7STM,    f_Key0_P_1,   f_Key0_R_0},
};

RespList_t keycode1[] = 
{
/*   响应时间  按下响应      释放响应   */
    {DBMTM,    f_Key1_P_0,   f_Key1_R_0},
    {K3STM,    f_Key1_P_1,   NULL,     },
};

RespList_t keycode2[] = 
{
/*   响应时间  按下响应      释放响应   */
    {DBMTM,    f_Key2_P_0,   f_Key2_R_0},
    {K3STM,    f_Key2_P_1,   NULL,     },
};

RespList_t keycode3[] = 
{
/*   响应时间  按下响应      释放响应   */
    {DBMTM,    f_Key3_P_0,   f_Key3_R_0},
    {K3STM,    f_Key3_P_1,   NULL,     },
};
/* 私有变量 ------------------------------------------------------------------*/
/* 公有变量 ------------------------------------------------------------------*/

/*******************************************************************************
* Description  : 按键配置
* Input        : None
* Output       : None
* Note         : 
* CreateDate   : 2018/4/13
* ChangeLogs   : 
*******************************************************************************/
void f_KeyCfg(void)
{
    f_KeyPropertyDeInit();
    
    f_KeyPropertyInit(KEY_CODE0, KEY_RESP(keycode0));
    f_KeyPropertyInit(KEY_CODE1, KEY_RESP(keycode1));
    f_KeyPropertyInit(KEY_CODE2, KEY_RESP(keycode2));
    f_KeyPropertyInit(KEY_CODE3, KEY_RESP(keycode3));
}


