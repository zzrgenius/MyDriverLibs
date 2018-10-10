#include "Include.h"
/*=========================================================
* �� �� ����f_NOPDelay()
* ������������ʱ����
* ���÷�����f_NOPDelay();
* ȫ�ֱ�����
* ������̣�
* ��		�룺��ʱʱ�䣺i_Value
* ��		�أ���
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
* �� �� ����f_MCU_FeedDog()
* ����������ι��
* ���÷�����f_MCU_FeedDog();
* ȫ�ֱ�����
* ������̣�
* ��		�룺��
* ��		�أ���
==========================================================*/
void f_MCU_FeedDog(void)
{
	GCC_CLRWDT();
}

/**********************************************
*Name	:RAMClr_Init
*Function: ���ڴ�
*Input  :
*Output	:
*Register Used:	system init
***********************************************/
void RAMClr_Init(void)			//RAM0 ȫ������
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
* �� �� ����f_MCU_InitSfrt()
* ������������ʼ���Ĵ���
* ���÷�����f_MCU_InitSfr();
* ȫ�ֱ�����
* ������̣�
* ��		�룺��
* ��		�أ���
==========================================================*/
void f_MCU_InitSfr(void)
{ 
	//���ٻ���
	_smod = 0x03 ;//fsystem=fh= 16M

	f_NOPDelay(600);
	
	_eec=0x00;	//�ڲ�eeprom��ʼ��-��ʹ��	

	//PA,PBĬ��ģ��,������
	_acerl=0x00;//�����ֿ�

	//�Ƚ�����ر�
	_cpc = 0x08;

	_integ =0;
	
	/* ���ö˿ڷ���1�����룬0�����;������1��ʹ�� */
	/*	PA			PA7		PA6		PA5		PA4		PA3		PA2		PA1		PA0			
		Dir			in		in		in		out		in		in		in		in
					1		1		1		0		1		1		1		1
		Fun			seg3		seg1	       seg4	       RST	       seg5	       DEBUG 	seg2	       DEBUG
	*/
	/*_pa = 0xff;//����
	_pac = 0xff;//����
	_papu = 0xff;//����//����/��¼������������
	_pawu = 0x7a;//����		1,3,4,5,6*/
	_pa = 0xef;//����
	_pac = 0xef;//����
	_papu = 0xff;//����//����/��¼������������
	_pawu = 0xea;//����		1,3,5,6,7

	/* ���ö˿ڷ���1�����룬0�����;������1��ʹ�� */
	/*	PB			PB7		PB6		PB5		PB4		PB3		PB2		PB1		PB0			
		Dir			NC		OUT		OUT		OUT		OUT		out		OUT		in
					1		0		0		0		0		0		0		1
		Fun			NC		COM1	COM3	COM2	COM4	RF_SI	RF_CLK	IN
	*/
	_pb=0xff;
	_pbc=0x81;//����
	_pbpu=0xff;//����//����/��¼������������

	
	/* ���ö˿ڷ���1�����룬0�����;������1��ʹ�� */
	/*	PC			PC7		PC6		PC5		PC4		PC3		PC2		PC1		PC0			
		Dir			in		in		in		in		in		OUT		in		OUT
					1		1		1		1		1		0		1		0
		Fun			NU		NU		NU		NU		NU		RF_CS	RF_SO	LED
	*/
	_pc=0xff;
	_pcc=0xfa;//����
	_pcpu=0xff;//����//����/��¼������������

	RAMClr_Init();


	//���Ź�
	_wdtc=0x57;			//���Ź�ʹ�ܿ��Ź��������   (2^18 /32k) =8.192 s
	//_wdtc=0xA0;				//�رտ��Ź�

	//�͵�ѹ���
	//_lvden = true;
	_lvden = false;
	_vlvd0 = 0;		//2.4V
	_vlvd1 = 1;
	_vlvd2 = 0;
	

	_tbc=0xc7;			//TBC�Ĵ�������

	
	//STM
	_tm0c0=0x20;  //fh/16= 1M	
	_tm0c1=0xc1;  //��ʱģʽ
	
	_tm0al=1000 % 256;  //1ms
	_tm0ah=1000 / 256;
	
	_mf0e=1;
	_t0ae=1;
	
	_t0on=1;
	
	//f_ISM_TimerInit();
	
	_emi = 1;		//���ж�

		
}