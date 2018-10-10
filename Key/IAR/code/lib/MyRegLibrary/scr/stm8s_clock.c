/*******************************************************************************
* @file    stm8s_clock.c
* @author  钟昊翰
* @version V1.0.0
* @date    2017-09-25
* @brief   该文件为stm8s时钟配置文档
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"
#include"stm8s_clock.h"

/* 私有常量 ----------------------------------------------------------------- */
/* 私有类型 ------------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
const uint8_t HSIDivFactor[4] = {1, 2, 4, 8}; /*!< Holds the different HSI Divider factors */

/* 私有变量 ------------------------------------------------------------------*/
/* 私有函数 ------------------------------------------------------------------*/

/**
  *  功能说明:  时钟初始化,关闭HSE,使能HSI(16MHz)
  */
void f_ClockInit(void)
{
    /* 关闭外部晶振 */
    CLK_ECKR_bit.HSEEN = 0;
    
    /* fHSI = fHSI RC输出 */
    /* fCPU = fMASTER */
    CLK_CKDIVR = 0x00;   // 16MHz
    
    /* 等待内部高速时钟准备就绪 */
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