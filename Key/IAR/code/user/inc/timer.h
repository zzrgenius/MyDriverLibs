/*******************************************************************************
  * @file    timer.h
  * @author  ��껺�
  * @version V1.0.0
  * @date    2017-09-25
  * @brief   ��ͷ�ļ�Ϊ��ʱ�������ļ�
*******************************************************************************/

#ifndef __TIMER_H__
#define __TIMER_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct TIMER_FLG
{
//    uint8_t  TKS_2MSF    : 1;   /* ʱ���־ */
//    uint8_t  TKS_5MSF    : 1;
    uint8_t  TKS_10MSF   : 1;
//    uint8_t  TKS_50MSF   : 1;
    uint8_t  TKS_100MSF  : 1;
//    uint8_t  TKS_250MSF  : 1;
    uint8_t  TKS_500MSF  : 1;
    uint8_t  TKS_1SF     : 1;
}TimerFlg_Typedef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void f_SysTimer_Init(void);
void f_Timepiece(void);

void f_SysPowerOnTM(void);
uint8_t f_ReadSysPowerOnTM(void);

void f_Overturn500msFlag(void);
bool f_Read500msFlag(void);

/* Exported variables ------------------------------------------------------- */
extern TimerFlg_Typedef  sysTimerFlag;
#endif