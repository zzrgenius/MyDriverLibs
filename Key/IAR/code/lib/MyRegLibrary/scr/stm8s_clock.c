/*******************************************************************************
* @file    stm8s_clock.c
* @author  ��껺�
* @version V1.0.0
* @date    2017-09-25
* @brief   ���ļ�Ϊstm8sʱ�������ĵ�
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"
#include"stm8s_clock.h"

/* ˽�г��� ----------------------------------------------------------------- */
/* ˽������ ------------------------------------------------------------------*/
/* ˽�ж��� ------------------------------------------------------------------*/
const uint8_t HSIDivFactor[4] = {1, 2, 4, 8}; /*!< Holds the different HSI Divider factors */

/* ˽�б��� ------------------------------------------------------------------*/
/* ˽�к��� ------------------------------------------------------------------*/

/**
  *  ����˵��:  ʱ�ӳ�ʼ��,�ر�HSE,ʹ��HSI(16MHz)
  */
void f_ClockInit(void)
{
    /* �ر��ⲿ���� */
    CLK_ECKR_bit.HSEEN = 0;
    
    /* fHSI = fHSI RC��� */
    /* fCPU = fMASTER */
    CLK_CKDIVR = 0x00;   // 16MHz
    
    /* �ȴ��ڲ�����ʱ��׼������ */
    while(!(CLK_ICKR_bit.HSIRDY));
}

/**
  * @brief  This function returns the frequencies of different on chip clocks.
  * @param  None
  * @retval the master clock frequency
  */
uint32_t f_CLK_GetClockFreq(void)
{
    uint32_t clockfrequency = 0;
    CLK_Source_TypeDef clocksource = CLK_SOURCE_HSI;
    uint8_t presc = 0;
    
    /* Get CLK source. */
    clocksource = (CLK_Source_TypeDef)CLK_CMSR;
    
    if (clocksource == CLK_SOURCE_HSI)
    {
        presc = HSIDivFactor[CLK_CKDIVR_bit.HSIDIV];
        clockfrequency = HSI_VALUE / presc;
    }
    else if ( clocksource == CLK_SOURCE_LSI)
    {
        clockfrequency = LSI_VALUE;
    }
    else
    {
        clockfrequency = HSE_VALUE;
    }
    
    return((uint32_t)clockfrequency);
}