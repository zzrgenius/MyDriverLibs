#ifndef __SUBDEFINE_H
#define __SUBDEFINE_H

//avr-size $(OutputPath)$(TargetSName).elf
//#define MCU_STM8

#ifdef MCU_STM8
/* asm instruction define */
	#define NOP()		_asm("NOP")
	#define _DI()		_asm("sim")
	#define _EI()		_asm("rim")
	#define EnableInterrupts()	_EI()
	#define DisableInterrupts()	_DI()
	#define FLASH		const @near
	#define IT_HEADE	@far @interrupt @svlreg //@svlregΪ��ʹ���мĴ���ѹջ

	//#define USE_AT_NEAR						//ʹ��@near

	#ifdef  USE_AT_NEAR
		#define  AT_NEAR @near
	#else
		#define  AT_NEAR  volatile
	#endif

	//#define USE_AT_FAR						//ʹ��@far

	#ifdef  USE_AT_FAR
		#define  AT_FAR @far
	#else
		#define  AT_FAR  volatile
	#endif
#else
	#define NOP()		GCC_NOP()
	#define _DI()		__DI()
	#define _EI()		__EI()
	#define uchar_tinyp	unsigned char __tinyp
	#define uchar_tiny	unsigned char __tiny
	#define INTTERUPT_HEAD		__interrupt void
	#define FLASH		const
#endif

#define NULL		((void *)0)
#define TEMPERROR_OPEN	-120
#define TEMPERROR_SHORT	-121


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

//=========================�߼�ֵ����=======================
#define false 								0
#define true 								1

#define BEEP_TRUE 							1
#define BEEP_FALSE 							0

#define LED_ON 								1
#define LED_OFF 							0

#define SW_ON 								1
#define SW_OFF 								0

//=========================��ģ����=======================
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
#define HG			24
#define P			25
#define N			26
#define U			27
#define u			28
#define t			29
#define r			30
#define MIE			31

//===============speed===============
#define SPEED_INIT          0x7FFE



//===============ENUM===============
//ͨѶ״̬
typedef enum
{
	COMMUNICATIONSTATE_IDLE,
	COMMUNICATIONSTATE_SENDING,
	COMMUNICATIONSTATE_RECEIVING,
	COMMUNICATIONSTATE_DEALING
}enumCommunicationState;

enum eDataType			//��������
{
	UCHAR,
	SCHAR,
	UINT,
	SINT,
	ULONG,
	SLONG,
	UFLOAT,
	SFLOAT,
	REAL_TIMER,
	SET_TIMER,
	RUN_TIME
};

//=================STRUCT/UNION=====================
typedef struct							/*Сʱ,����,��ṹ*/
{	
	unsigned char	second;
	unsigned char	minute;
	unsigned int	hour;
}hour_def;

typedef struct							/*Сʱ,���ӽṹ*/
{
	unsigned char	minute;
	unsigned char	hour;
}hour_minute_def;

#define TIMER_HOUR_MIN hour_minute_def

typedef struct							/*����,��ṹ*/
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

//�������Ͷ���
typedef struct							/*����,��ṹ*/
{
	unsigned char	DataType;			//��������
	unsigned char	DataNO;				//���������ݵ���Ŀ
	unsigned char	DataStartAddInEE;	//�����ڴ洢���е���ʼλ��
}TYPE_DATA_SAVE;


//uchar�ֽ�λ����
typedef struct  					//һ���ֽڵķֽ�λ����
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

//uint�ֽ�λ����
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
	WORD_FIELD 	m_bit;
} TYPE_WORD;


typedef struct
{
	schar setTemp;			//�����¶�	
	schar showTemp;			//��ʾ�¶�
	schar sensorTemp;		//�������¶�	
	schar lastSensorTemp;	//�������¶Ȼ���	
	
	uchar bShortFlag : 1;	//��·���ϱ�־	
	uchar bOpenFlag	 : 1;	//��·��־	
}SENSOR_INF;				//��������Ϣ

typedef struct
{
	uchar bSwitchState : 1;		//����״̬
	uchar bLastSwitchState : 1;	//����״̬
	
	uint nKeepOnTm;		//ά��ʱ��X100ms
	uint nKeepOffTm;	//ά��ʱ��X100ms
}LEVEL_SWITCH_INF;	//ˮλ������Ϣ

#endif	//__SUBDEFINE_H
