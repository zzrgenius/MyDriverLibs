#define VAR_INIT_GLOBALS
#include "Include.h"

/*=========================================================
* 功能描述: CPU时钟初始化
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void sCpuClkInit(void)
{
	CLK_ECKR &= 0xfe;			//使用内部晶振(PA1.2可用于GPIO)
	CLK_CKDIVR = 0x00;          		// 01: fHSI= fHSI RC output/1 = 16M. 
	while(!(CLK_ICKR&0x02));		//等待就绪
}

/*=========================================================
* 功能描述: CPU的IO口初始化
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void sCpuIoInit(void)
{
	CFG_GCR |= 0x01;
    /**************IO口配置**************/
    //			DDR				CR1			CR2			ADC_TDR
    //输出：	1				1				0				X				推挽输出		
    //输入：	0				0				0				X				悬浮输入		
    //AD输入：0				0				0				1				禁止施密特触发		

    /*PA0		PA1		PA2			PA3		PA4			PA5		PA6		PA7
      NC		OUT		OUT			OUT		NO	    		NO    	NO   	NO  */  
    PA_DDR = 0x0E; 
    PA_CR1 = 0xFF;          		
    PA_CR2 = 0x00; 					  		
    //SPICS = 0;
    /*PB0		PB1		PB2		PB3			PB4		PB5		PB6		PB7
    //NO		NO		NO		NO			IN		IN		NO    	NO 	*/	
    //PB_DDR = 0x00;    
    PB_DDR = 0x20; 
    PB_CR1 = 0xFF;          		
    PB_CR2 = 0x00;      
    //EXTI_CR1 |= 0x08;//PB口下降沿中断

    /*PC0		PC1		PC2		PC3		PC4		PC5		PC6		PC7
    //NO		NO   	 NO		OUT		OUT		OUT		OUT		OUT*/  
    PC_DDR = 0xF8;          		
    PC_CR1 = 0xFF;          		
    PC_CR2 = 0x00;          		

    /*PD0		PD1		PD2		PD3		PD4		PD5			PD6	     		PD7
    //NO		SWIM 	OUT		OUT		OUT		OUT(TX)		IN(RXD)		NO	*/ 
    PD_DDR = 0x3C;   
     //PD_DDR = 0x38; 
    PD_CR1 = 0xFF; 
    PD_CR2 = 0x00;   
    //RFRST = 0;
	
   // EXTI_CR1 |= 0x08;//PB口下降沿中断
}

/*=========================================================
* 功能描述: CPU看门狗初始化
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void sMcuDongInit(void)
{
	IWDG_KR = 0xcc;					//启动看门狗
	IWDG_KR = 0x55;					//看门狗寄存器去保护
	IWDG_RLR = 0xff;					//看门狗重新装载数值
	IWDG_PR = 0x06;					//64K的128分频,最长1.02S
	IWDG_KR = 0xaa;					//看门狗寄存器保护,同时启动看门狗
}

/*=========================================================
* 功能描述: CPU看门狗喂狗
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_McuFeedDog(void)
{
	IWDG_KR=0xaa;					//喂狗
}

/*=========================================================
* 功能描述: CPU定时器初始化
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void sTimeInit(void)
{
	/*定时时基100us*/	
	TIM1_PSCRH = 0;
	TIM1_PSCRL = 0x0f;	//f= fmain/(PSCR+1)=16/(15 + 1)=1M=1us
	TIM1_ARRH = 0x03;	//产生一个1mss的时基 ARR = 999
	TIM1_ARRL = 0xe7;
	TIM1_IER |= 0x01;
	TIM1_CR1  |= 0x01;	//使能定时器1
}

/*=========================================================
* 功能描述: CPU初始化
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_CpuInit(void)
{
	sCpuClkInit();
	sCpuIoInit();
	sTimeInit();
	sMcuDongInit();
}
