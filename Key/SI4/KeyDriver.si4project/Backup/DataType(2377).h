

#ifndef DATA_TYPE_H
#define DATA_TYPE_H

//avr-size $(OutputPath)$(TargetSName).elf
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
	#define uchar_tinyp	unsigned char __tinyp
	#define uchar_tiny	unsigned char __tiny
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
#define byte_8			unsigned char
#define word_16			unsigned int
#define uword16 		unsigned int
#define word_32			unsigned long
#define vuchar			volatile unsigned char

//uchar8分解位定义
typedef struct
{
    unsigned char	b0 : 1;
    unsigned char	b1 : 1;
    unsigned char	b2 : 1;
    unsigned char	b3 : 1;
    unsigned char	b4 : 1;
    unsigned char	b5 : 1;
    unsigned char	b6 : 1;
    unsigned char	b7 : 1;
}s_byte_def;

typedef union
{
	s_byte_def    m_bit;
	unsigned char m_byte;
}u_u8_def;

//uint字节位定义
typedef struct
{
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
}s_word_def;

typedef union {
	unsigned int	word;
	unsigned char	byte[2];
	s_word_def 	bit;
} u_u16_def;

typedef enum
{
    BOOL_FALSE = 0,
    BOOL_TRUE
} e_bool;

#define true 1
#define false 0

#endif
