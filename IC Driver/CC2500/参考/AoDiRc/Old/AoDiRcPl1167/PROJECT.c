#define VAR_MAIN_GLOBALS
#include "HT66F018.h"
#include "Main.h"
//#include "Include.h"

void main()
{
	if(_to && _pdf)//���Ź����߸�λ
	{
		GCC_NOP();
		GCC_NOP();
	}
	else
	{
	//	f_MCU_InitSfr();
	}
	while(1)
	{
	//	f_MCU_FeedDog();//ι��
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
	if(b10msFlag)	//10ms��
	{
		b10msFlag = false;
		n50msCnt ++;
		if(n50msCnt >= 5)								//50ms meeted
		{
			n50msCnt = 0;
			b50msFlag = true;
			n1sCnt ++;
			if((n1sCnt % 2) == 0)						//100ms meeted
			{
				b100msFlag = true;
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
	}
}