#ifndef HARDWAR_H
#define HARDWAR_H

/* ��ʱ��TIMER1ʱ����� */
/*#define TIMER1_COUNT_4M_H				0XEF		//0XFF EC  FF
#define TIMER1_COUNT_4M_L				0XFD		//0XE2 77  32

#define TIMER1_COUNT_32K_10S_H			0X5F		//1S EF
#define TIMER1_COUNT_32K_10S_L			0XE8		//   FD

#define TIMER1_COUNT_32K_50MS_H			0XFF		//50ms
#define TIMER1_COUNT_32K_50MS_L			0X32*/

/* ����Ϊ���ļ�ʹ�õĳ������� */
//#define ADC_AN0			0X01																		/* ͨ��0 */

//#define IS_ADC_CHANNEL(CHANNEL)		(CHANNEL == ADC_AN0)

/* ����Ϊ���ļ�ʹ�õĺ��� */
void f_NOPDelay(unsigned int i_Value);
void f_MCU_FeedDog(void);
void f_MCU_InitSfr(void);

#endif