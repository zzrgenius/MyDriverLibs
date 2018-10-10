/*******************************************************************************
  * @file    beep.h
  * @author  ��껺�
  * @version V1.0.0
  * @date    2017-09-25
  * @brief   ��ͷ�ļ�Ϊͷ�ļ���ʽģ��
*******************************************************************************/

#ifndef __BEEP_H__
#define __BEEP_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum  /* �赥 */
{
    NORMAL         = 0, /* ��ͨ����   1�� ��0.2s        */
    UNUSE          = 1, /* ��Ч����   2�� ��0.2s ͣ0.5s */
    LONG_BEEP      = 2, /* ��������   1�� ��6.0s        */
    ALARM          = 3, /* ��������  10�� ��1.0s ͣ0.5s */
    POR            = 4  /* �ϵ�       3�� ��1.0s ͣ1.0s */
}MusicTab_Typedef;


/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define TIME_A      3   /* *10ms */
#define TIME_B      5   /* *10ms */
#define TIME_C      10  /* *10ms */
#define TIME_D      20  /* *10ms */
#define TIME_E      50  /* *10ms */
#define TIME_L      100 /* *10ms */
#define TIME_M      6000 /* *10ms */

//#define FREQ_A      200
//#define FREQ_B      210
//#define FREQ_C      220
//#define FREQ_D      230
#define FREQ_E      244  /* 2048 Hz */
//#define FREQ_F      254
#define FREQ_OFF    0

#define BEEP_STOP       0xFF  /* ����ֹͣ��־ */


/* Exported functions ------------------------------------------------------- */
void f_InitBuzPara(void);
void f_Beep(MusicTab_Typedef i_MusicNum);
void f_BuzPro(void);
void f_IncBuzTm(void);
bool f_IsBeepStop(void);

/* Exported variables ------------------------------------------------------- */

#endif