/*******************************************************************************
* @file    stm8s_it.c
* @author  钟昊翰
* @version V1.0.0
* @date    2017-09-25
* @brief   该文件为中断处理函数文件
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include"main.h"
#include"drive.h"
#include"stm8s_it.h"

/* 私有常量 ----------------------------------------------------------------- */
/* 私有类型 ------------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
/* 私有变量 ------------------------------------------------------------------*/
/* 私有函数 ------------------------------------------------------------------*/

#pragma vector = TIM1_OVR_UIF_vector
__interrupt void TIM1_UPD_OVF_BRK_IRQHandler(void)
{
    if(TIM1_SR1_bit.UIF)
    {
        TIM1_SR1_bit.UIF = 0;   /* 清除溢出标志 */
    }
}

#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_UPD_OVF_BRK_IRQHandler(void)
{
    if(TIM2_SR1_bit.UIF)
    {
        TIM2_SR1_bit.UIF = 0;   /* 清除溢出标志 */
    }
}

#pragma vector = TIM4_OVR_UIF_vector
__interrupt void TIM4_UPD_OVF_IRQHandler(void)
{
    if(TIM4_SR_bit.UIF)
    {
        /* 清除溢出标志 */
        TIM4_SR_bit.UIF = 0;
        
        f_Timepiece();
        
        // 无接收数据计时
//        f_TimeNoReceiveTMR();
    }
}

/**
  *  功能说明:  AD转换中断函数
  */
#pragma vector = ADC1_EOC_vector
__interrupt void ADC1_IRQHandler(void)
{
    if(ADC_CSR_bit.EOC)
    {
        /* Clear EOC */
        ADC_CSR_bit.EOC = 0;
        
//        f_ADC_Samping_INT();
    }
}

//#pragma vector = UART1_T_TC_vector
//__interrupt void UART1_TX_IRQHandler(void)
//{
//    f_INT_UART_TX(f_MCU_UART1SendByte, f_DisableUART1TxINT);
//    
//    UART1_SR_bit.TC = 0;
//}

//#pragma vector = UART1_R_RXNE_vector
//__interrupt void UART1_RX_IRQHandler(void)
//{
//    /* Note:读UART1_DR寄存器会清除接收中断标志 */
//    f_INT_UART_RX(f_MCU_GetUART1ReceByte);
//}

//#pragma vector = UART2_T_TC_vector
//__interrupt void UART2_TX_IRQHandler(void)
//{
////    f_INT_UART_TX(f_MCU_UART2SendByte, f_DisableUART2TxINT);
//    
//    UART2_SR_bit.TC = 0;
//}
//
//#pragma vector = UART2_R_RXNE_vector
//__interrupt void UART2_RX_IRQHandler(void)
//{
//    /* Note:读UART1_DR寄存器会清除接收中断标志 */
////    f_INT_UART_RX(f_MCU_GetUART2ReceByte);
//}