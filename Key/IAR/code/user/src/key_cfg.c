/*******************************************************************************
* File         : key_cfg.c
* Version      : v1.0.0
* Author       : ��껺�
* CreateDate   : 2018/4/13
* Description  : �������ò�
* Change Logs  : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"
#include"key_cfg.h"

/* ˽������ ------------------------------------------------------------------*/
/* ˽�ж��� ------------------------------------------------------------------*/
/* ˽�к�   ------------------------------------------------------------------*/
#define KEY_RESP(_RESP_ROOT_)   _RESP_ROOT_,(sizeof(_RESP_ROOT_)/sizeof(_RESP_ROOT_[0]))

#define DBMTM     DEBOUNCE_MIN_TM  // ������Сʱ��
#define K1STM     (1000u)          // ������Ӧʱ��(��λ:ms)
#define K2STM     (2000u)
#define K3STM     (3000u)
#define K4STM     (4000u)
#define K5STM     (5000u)
#define K6STM     (6000u)
#define K7STM     (7000u)
/* ˽�к��� ------------------------------------------------------------------*/
/* ˽�г��� ----------------------------------------------------------------- */
RespList_t keycode0[] = 
{
/*   ��Ӧʱ��  ������Ӧ      �ͷ���Ӧ   */
    {DBMTM,    f_Key0_P_0,   f_Key0_R_0},
    {K3STM,    f_Key0_P_1,   NULL      },
    {K5STM,    f_Key0_P_2,   NULL      },
    
    /* ��һ�������ж����Ӧʱ��,ֱ������Ӧ�б������Ԫ�ؼ���(��ͬ) */
//    {K7STM,    f_Key0_P_1,   f_Key0_R_0},
};

RespList_t keycode1[] = 
{
/*   ��Ӧʱ��  ������Ӧ      �ͷ���Ӧ   */
    {DBMTM,    f_Key1_P_0,   f_Key1_R_0},
    {K3STM,    f_Key1_P_1,   NULL,     },
};

RespList_t keycode2[] = 
{
/*   ��Ӧʱ��  ������Ӧ      �ͷ���Ӧ   */
    {DBMTM,    f_Key2_P_0,   f_Key2_R_0},
    {K3STM,    f_Key2_P_1,   NULL,     },
};

RespList_t keycode3[] = 
{
/*   ��Ӧʱ��  ������Ӧ      �ͷ���Ӧ   */
    {DBMTM,    f_Key3_P_0,   f_Key3_R_0},
    {K3STM,    f_Key3_P_1,   NULL,     },
};
/* ˽�б��� ------------------------------------------------------------------*/
/* ���б��� ------------------------------------------------------------------*/

/*******************************************************************************
* Description  : ��������
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


