#define VAR_MAIN_GLOBALS
#include "Include.h"

uchar f_MCU_HT_ReadMore(uchar nReadAdd)
{
	uchar ReadData;

	_eea = nReadAdd;//����EE��ַ
	_mp1 = 0x40;//����EEָ��
	__eec.bits.__rden = 1;//����RDEN
	__eec.bits.__rd = 1;//����������
	while(__eec.bits.__rd);//�ж϶�����
	NOP();
	NOP();
	NOP();
	_eec = 0;//��Ĵ���EEC
	ReadData = _eed;//������
	
	_mp1 = 0x00;//����ָ��
	_eea = 0;
	_eed = 0;
	return ReadData;
}

void main(void)
{
	if(_to && _pdf)//���Ź����߸�λ
	{
		GCC_NOP();
		GCC_NOP();
	}
	else
	{
		f_pSfrInit();
		PL1167_Init();
		ADDR[0] = f_MCU_HT_ReadMore(0);					//��ַ��1
		ADDR[1] = f_MCU_HT_ReadMore(1);					//��ַ��2		
		ADDR[2] = f_MCU_HT_ReadMore(2);					//��ַ��3
	}
	while(1)
	{
		f_pFeedDog();//ι��
		f_SendBuffer();
		f_SendDeal();
		f_RfRecDeal();
		f_CalTm();
	}

}

/* =========================================================
* �� �� ��: void f_CalTm()
* ��������: ��������ʱ��,�����60����ּ�1,�������ʱ�����ֵ
* ���÷���: f_CalTm();
* ���ú���: ��
* ȫ�ֱ���: 
========================================================= */
void f_CalTm(void)
{
	//static unsigned char temp=0;
	if(b5msFlag)
	{
		b5msFlag = false;
	}
	if(b10msFlag)	//10ms��
	{
		b10msFlag = false;
		f_KeyScan();//����ɨ��
		f_KeyDeal();//��������
		n50msCnt ++;
		if(n50msCnt >= 5)								//50ms meeted
		{
			n50msCnt = 0;
			b50msFlag = true;
			n1sCnt ++;
			if((n1sCnt % 2) == 0)						//100ms meeted
			{
				b100msFlag = true;
				f_Go_To_Halt();
			}
			if((n1sCnt % 5) == 0)						//250ms meeted 
			{
				b250msFlag = true;
			}		
			if((n1sCnt % 10) == 0)						//500ms meeted 
			{
				b500msFlag = true;
				b1HzFlag ^= true;
			}
				
			if(n1sCnt >= 20)							//1s meeted
			{
				n1sCnt = 0;
				b1sFlag = true;
				b0d5HzFlag ^= true;
			}
		}
	}
	if(b100msFlag)	//100ms meeted
	{
		b100msFlag = false;
	}
	if(b250msFlag)
	{
		b250msFlag = false;
	}
	if(b500msFlag)
	{
		b500msFlag = false;
	}
	if(b1sFlag)	//1S meeted
	{
		b1sFlag = false;
		f_FreqDeal();
		/*if(temp == 0)
		{
			temp = 1;
			LED = 0;
		}
		else
		{
			temp = 0;
			LED = 1;
		}*/
	}
}

/*=========================================================
* �� �� ����f_Go_To_Halt()
* ������������CC1101����Ϊ˯��ģʽ������ֹͣģʽ 
* ���÷�����
* ȫ�ֱ�����
* ������̣�
* ��		�룺��
* ��		�أ���
==========================================================*/
void f_Go_To_Halt(void)
{	
	if(nKeyWakeTm < 250)//��������ʱ��
		nKeyWakeTm ++;
	if (!bInSleepFlag)
	{
		if(nKeyWakeTm >= 30)		/* ����������3s�����sleepģʽ */
		{
			bInSleepFlag = true;
		}
		return;
	}
	//_t0on = 0;		//��ʱ��0�ر�																					//�رն�ʱ��
	_adoff = 1;		//ad�ر�
	KEY_COM1 = false;
	KEY_COM2 = false;
	KEY_COM3 = false;
	KEY_COM4 = false;
	_idlen = 0;			//����ģʽ1->���Ź������Զ���0,ʱ����ʱ����ر�
														
	GCC_HALT();
	GCC_NOP();
	GCC_NOP();
	GCC_NOP();
	GCC_NOP();
	GCC_NOP();
}