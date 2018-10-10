/*******************************************************************************
  * @file    beep.h
  * @author  钟昊翰
  * @version V1.0.0
  * @date    2017-09-25
  * @brief   该头文件为头文件格式模板
*******************************************************************************/

#ifndef __BEEP_H__
#define __BEEP_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum  /* 歌单 */
{
    NORMAL         = 0, /* 普通声音   1声 响0.2s        */
    UNUSE          = 1, /* 无效声音   2声 响0.2s 停0.5s */
    LONG_BEEP      = 2, /* 长鸣声音   1声 响6.0s        */
    ALARM          = 3, /* 报警声音  10声 响1.0s 停0.5s */
    POR            = 4  /* 上电       3声 响1.0s 停1.0s */
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

#define BEEP_STOP       0xFF  /* 音乐停止标志 */


/* Exported functions ------------------------------------------------------- */
void f_InitBuzPara(void);
void f_Beep(MusicTab_Typedef i_MusicNum);
void f_BuzPro(void);
void f_IncBuzTm(void);
bool f_IsBeepStop(void);

/* Exported variables ------------------------------------------------------- */

#endif