#ifndef __CPU_MAIN_H
#define __CPU_MAIN_H

#ifdef  VAR_MAIN_GLOBALS
	#define  CPU_MAIN_EXT
#else
	#define  CPU_MIAN_EXT  extern
#endif

#define MCU_STM8

#ifdef MCU_STM8
/* asm instruction define */
	#define NOP()		_asm("NOP")
	#define _DI()		_asm("sim")
	#define _EI()		_asm("rim")
	#define EnableInterrupts()	_EI()
	#define DisableInterrupts()	_DI()
	#define FLASH		const @near
	#define IT_HEADE	@far @interrupt @svlreg //@svlreg为了使所有寄存器压栈

	#define USE_AT_NEAR						//使用@near

	#ifdef  USE_AT_NEAR
		#define  AT_NEAR @near
	#else
		#define  AT_NEAR  
	#endif

	//#define USE_AT_FAR						//使用@far

	#ifdef  USE_AT_FAR
		#define  AT_FAR @far
	#else
		#define  AT_FAR  
	#endif
#else
	#define NOP()		__wait_nop()
	#define _DI()		__DI()
	#define _EI()		__EI()
	#define unsigned char_tinyp	unsigned char __tinyp
	#define unsigned char_tiny	unsigned char __tiny
	#define INTTERUPT_HEAD		__interrupt void
	#define FLASH		const
#endif

#define NULL		((void *)0)

#define uchar			unsigned char
#define schar			signed char
#define uint			unsigned int
#define sint			signed int
#define ulong			unsigned long
#define slong			signed long
#define byte_8		unsigned char
#define word_16		unsigned int
#define uword16 	unsigned int
#define word_32		unsigned long 		
#define vunsigned char	volatile unsigned char

//=========================逻辑值定义=======================
#define false 								0
#define true 									1
#define FALSE 	0
#define TRUE 		1

#define BEEP_TRUE 						1
#define BEEP_FALSE 						0

#define LED_ON 								1
#define LED_OFF 							0

#define SW_ON 								1
#define SW_OFF 								0

//=========================字模部分=======================
#define A			10
#define b			11
#define C			12
#define c			13
#define d			14
#define E			15
#define F			16
#define G			17
#define H			18
#define h			19
#define J			20
#define L			21
#define y			22
#define o			23
#define HG		24
#define P			25
#define N			26
#define U			27
#define u			28
#define t			29
#define r			30
#define MIE			31

//===IO状态==
#define OUT_ON							1
#define OUT_OFF							0

#define IN_ON								1
#define IN_OFF							0

#define OUT_MUSIC_ON				1
#define OUT_MUSIC_OFF				0



//===============基础数据类型定义===============
enum eDataType			//数据类型
{
	UCHAR,
	UINT,
	ULONG
};

typedef struct							/*小时,分钟,秒结构*/
{	
	unsigned char	second;
	unsigned char	minute;
	unsigned int	hour;
}hour_def;

typedef struct							/*小时,分钟结构*/
{
	unsigned char	minute;
	unsigned char	hour;
}hour_minute_def;

#define TIMER_HOUR_MIN hour_minute_def

typedef struct							/*分钟,秒结构*/
{
	unsigned int	minute;
	unsigned char	second;
}minute_def;

#define TIMER_MIN_SEC minute_def

typedef union
{
	unsigned long word;
	struct
	{
		unsigned char byte_0;
		unsigned char byte_1;
		unsigned char byte_2;
		unsigned char byte_3;
	}byte;
}long_def;

typedef union
{
	unsigned int m_word;
	struct
	{
		unsigned char high_byte;
		unsigned char low_byte;
	}m_byte;
}int_def;

//保存类型定义
typedef struct							/*分钟,秒结构*/
{
	unsigned char	DataType;			//数据类型
	unsigned char	DataNO;				//该类型数据的数目
	unsigned char	DataStartAddInEE;	//数据在存储器中的起始位置
}TYPE_DATA_SAVE;


//unsigned char字节位定义
typedef struct  					//一个字节的分解位定义
{
		unsigned char	b0 : 1;
		unsigned char	b1 : 1;
		unsigned char	b2 : 1;
		unsigned char	b3 : 1;
		unsigned char	b4 : 1;
		unsigned char	b5 : 1;
		unsigned char	b6 : 1;
		unsigned char	b7 : 1;
}bit_def;


typedef union 
{
	bit_def m_bit;
	unsigned char m_byte;
}byte_def;

#define TYPE_BYTE byte_def

//uint字节位定义
typedef struct {
	unsigned int b0:1;
	unsigned int b1:1;
	unsigned int b2:1;
	unsigned int b3:1;
	unsigned int b4:1;
	unsigned int b5:1;
	unsigned int b6:1;
	unsigned int b7:1;
	unsigned int b8:1;
	unsigned int b9:1;
	unsigned int b10:1;
	unsigned int b11:1;
	unsigned int b12:1;
	unsigned int b13:1;
	unsigned int b14:1;
	unsigned int b15:1;
}WORD_FIELD;

typedef union {
	unsigned int	word;
	unsigned char	byte[2];
	WORD_FIELD 	bit;
} TYPE_WORD;

#endif	//__CPU_MAIN_H
