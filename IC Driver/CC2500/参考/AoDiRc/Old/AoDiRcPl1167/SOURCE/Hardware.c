#include "Include.h"
/*=========================================================
* 函 数 名：f_NOPDelay()
* 功能描述：延时程序
* 调用方法：f_NOPDelay();
* 全局变量：
* 处理过程：
* 输		入：延时时间：i_Value
* 返		回：无
==========================================================*/
void f_NOPDelay(unsigned int i_Value)
{
	while(--i_Value)
	{
		GCC_CLRWDT();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
		GCC_NOP();
	}
}

/*=========================================================
* 函 数 名：f_MCU_FeedDog()
* 功能描述：喂狗
* 调用方法：f_MCU_FeedDog();
* 全局变量：
* 处理过程：
* 输		入：无
* 返		回：无
==========================================================*/
void f_MCU_FeedDog(void)
{
	GCC_CLRWDT();
}

/**********************************************
*Name	:RAMClr_Init
*Function: 清内存
*Input  :
*Output	:
*Register Used:	system init
***********************************************/
void RAMClr_Init(void)			//RAM0 全部清零
{
	_bp=0;
	for(_mp1=0xff;_mp1>=0xa0;_mp1--)
	{
		_iar1=0;
	} 
	_bp=1;
	for(_mp1=0xff;_mp1>=0xa0;_mp1--)
	{
		_iar1=0;
	} 
} 

/*=========================================================
* 函 数 名：f_MCU_InitSfrt()
* 功能描述：初始化寄存器
* 调用方法：f_MCU_InitSfr();
* 全局变量：
* 处理过程：
* 输		入：无
* 返		回：无
==========================================================*/
void f_MCU_InitSfr(void)
{ 
	//快速唤醒
	_smod = 0x03 ;//fsystem=fh= 16M

	f_NOPDelay(600);
	
	_eec=0x00;	//内部eeprom初始化-不使能	

	//PA,PB默认模拟,需设置
	_acerl=0x00;//做数字口

	//比较输出关闭
	_cpc = 0x08;

	_integ =0;
	
	/* 设置端口方向：1：输入，0：输出;上拉：1：使能 */
	/*	PA			PA7		PA6		PA5		PA4		PA3		PA2		PA1		PA0			
		Dir			in		in		in		out		in		in		in		in
					1		1		1		0		1		1		1		1
		Fun			seg3		seg1	       seg4	       RST	       seg5	       DEBUG 	seg2	       DEBUG
	*/
	/*_pa = 0xff;//数据
	_pac = 0xff;//方向
	_papu = 0xff;//上拉//悬空/烧录口输入上拉高
	_pawu = 0x7a;//唤醒		1,3,4,5,6*/
	_pa = 0xef;//数据
	_pac = 0xef;//方向
	_papu = 0xff;//上拉//悬空/烧录口输入上拉高
	_pawu = 0xea;//唤醒		1,3,5,6,7

	/* 设置端口方向：1：输入，0：输出;上拉：1：使能 */
	/*	PB			PB7		PB6		PB5		PB4		PB3		PB2		PB1		PB0			
		Dir			NC		OUT		OUT		OUT		OUT		out		OUT		in
					1		0		0		0		0		0		0		1
		Fun			NC		COM1	COM3	COM2	COM4	RF_SI	RF_CLK	IN
	*/
	_pb=0xff;
	_pbc=0x81;//方向
	_pbpu=0xff;//上拉//悬空/烧录口输入上拉高

	
	/* 设置端口方向：1：输入，0：输出;上拉：1：使能 */
	/*	PC			PC7		PC6		PC5		PC4		PC3		PC2		PC1		PC0			
		Dir			in		in		in		in		in		OUT		in		OUT
					1		1		1		1		1		0		1		0
		Fun			NU		NU		NU		NU		NU		RF_CS	RF_SO	LED
	*/
	_pc=0xff;
	_pcc=0xfa;//方向
	_pcpu=0xff;//上拉//悬空/烧录口输入上拉高

	RAMClr_Init();


	//看门狗
	_wdtc=0x57;			//看门狗使能看门狗溢出周期   (2^18 /32k) =8.192 s
	//_wdtc=0xA0;				//关闭看门狗

	//低电压检测
	//_lvden = true;
	_lvden = false;
	_vlvd0 = 0;		//2.4V
	_vlvd1 = 1;
	_vlvd2 = 0;
	

	_tbc=0xc7;			//TBC寄存器设置

	
	//STM
	_tm0c0=0x20;  //fh/16= 1M	
	_tm0c1=0xc1;  //定时模式
	
	_tm0al=1000 % 256;  //1ms
	_tm0ah=1000 / 256;
	
	_mf0e=1;
	_t0ae=1;
	
	_t0on=1;
	
	//f_ISM_TimerInit();
	
	_emi = 1;		//总中断

		
}