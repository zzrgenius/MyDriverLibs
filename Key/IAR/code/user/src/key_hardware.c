/*******************************************************************************
* File         : key_hardware.c
* Version      : v1.0.0
* Author       : ��껺�
* CreateDate   : 2018/4/13
* Description  : ����Ӳ��ģ����
* Change Logs  : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"
#include"key_hardware.h"

/* ˽������ ------------------------------------------------------------------*/
/* ˽�ж��� ------------------------------------------------------------------*/
/* ˽�к�   ------------------------------------------------------------------*/
#define READ_KEY_S1  PC_IDR_IDR3
#define READ_KEY_S2  PC_IDR_IDR4
#define READ_KEY_S3  PC_IDR_IDR5
#define READ_KEY_S4  PC_IDR_IDR6
#define READ_KEY_S5  PC_IDR_IDR7
#define READ_KEY_S6  PD_IDR_IDR2
#define READ_KEY_S7  PD_IDR_IDR3
#define READ_KEY_S8  PA_IDR_IDR1
#define READ_KEY_S9  PA_IDR_IDR2
/* ˽�к��� ------------------------------------------------------------------*/
/* ˽�г��� ----------------------------------------------------------------- */
/* ˽�б��� ------------------------------------------------------------------*/
/* ���б��� ------------------------------------------------------------------*/

/*******************************************************************************
* Description  : ����ʶ��
* Input        : None
* Output       : None
* Note         : 
* CreateDate   : 2018/4/2
* ChangeLogs   : 
*******************************************************************************/
void f_KeyDiscern(void)
{
    // ������ʶ��
    f_SingleKeyDiscern(KEY_CODE0, (KeyState_t)(!READ_KEY_S1));
    f_SingleKeyDiscern(KEY_CODE1, (KeyState_t)(!READ_KEY_S2));
    f_SingleKeyDiscern(KEY_CODE2, (KeyState_t)(!READ_KEY_S3));
    
    // ��ϰ���
    f_ComplexKeyDiscern(KEY_CODE3, 2, (uint8_t)KEY_CODE0, (uint8_t)KEY_CODE1);
}
