/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : Hardware.c
  版 本 号   : V1.0
  作    者   : zhufeng
  生成日期   : 2018年4月21日
  最近修改   :
  功能描述   : CPU初始化文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月21日
    作    者   : zhufeng
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
  #define VAR_CPUINITHT66F018_GLOBALS
 #include "Include.h"
 
/*****************************************************************************
 函 数 名: f_NOPDelay
 功能描述  : 延时函数
 输入参数: unsigned int i_Value  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月21日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_NOPDelay(uint i_Value)
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

/*****************************************************************************
 函 数 名: f_pFeedDog
 功能描述  : 看门狗喂狗
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月21日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pFeedDog(void)
{
	GCC_CLRWDT();
}

/*****************************************************************************
 函 数 名: f_pClrRam
 功能描述  : 清楚内存函数
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月21日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pClrRam(void)			//RAM0 全部清零
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

/*****************************************************************************
 函 数 名: f_pSfrInit
 功能描述  : 初始化寄存器
 输入参数: void  
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月27日
    作    者   : zhufeng
    修改内容    : 新生成函数

*****************************************************************************/
void f_pSfrInit(void)
{ 
	//快速唤醒
	_smod = 0x01 ;//fsystem=fh= 16M
	f_NOPDelay(600);
	_eec=0x00;	//内部eeprom初始化-不使能	
	//PA,PB默认模拟,需设置
	_acerl=0x00;//做数字口
	//比较输出关闭
	_cpc = 0x08;
	_integ =0;

	_pa = 0xef;//数据
	_pac = 0xef;//方向
	_papu = 0xff;//上拉//悬空/烧录口输入上拉高
	_pawu = 0xea;//唤醒		1,3,5,6,7

	_pb=0xff;
	_pbc=0x81;//方向
	_pbpu=0xff;//上拉//悬空/烧录口输入上拉高

	_pc=0xff;
	_pcc=0xfa;//方向
	_pcpu=0xff;//上拉//悬空/烧录口输入上拉高

	f_pClrRam();

	//看门狗
	//_wdtc=0x57;			//看门狗使能看门狗溢出周期   (2^18 /32k) =8.192 s
	_wdtc=0x54;			//看门狗使能看门狗溢出周期   (2^15 /32k) =1.024 s
	
	//低电压检测
	_lvrc = 0x55;		//  2.1v
	_lvdc=0x10;			//低电压使能
	//_tbc=0xc7;			//TBC寄存器设置
	//STM
	_tm0c0=0x20;  //fh/16= 1M	
	_tm0c1=0xc1;  //定时模式
	_tm0al=1000 % 256;  //1ms
	_tm0ah=1000 / 256;
	_mf0e=1;
	_t0ae=1;
	_t0on=1;
	_emi = 1;		//总中断	
}