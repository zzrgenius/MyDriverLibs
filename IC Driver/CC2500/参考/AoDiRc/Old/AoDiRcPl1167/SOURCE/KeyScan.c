#define VAR_KEY_SCAN_GLOBALS
#include "Include.h"

void f_KeayDelay(void)
{
	uchar i;
	for(i = 0; i < 15; i ++)
	{
		NOP();
	}
}

/*=========================================================
* �� �� ��: void f_ChangeKeyInf(unsigned long *KeyInfDeal)
* ��������: ��ȡ����������Ϣ
* ���÷���: f_ChangeKeyInf(&KeyInfDeal);
* ���ú���: ��
* ȫ�ֱ���: 
* ��    ��: KeyInfDeal ������Ϣ
* ��    ��: ��
* �������:
*  ע   �⣺
* �޸�����	�޸���		�޸�˵��
* 2017-08-26		��� 			��ɻ�������
=========================================================*/
void f_ChangeKeyInf(unsigned long *KeyInfDeal)
{
	(*KeyInfDeal) = NO_KEY;
	
	KEY_COM1 = false;
	KEY_COM2 = true;
	KEY_COM3 = true;
	KEY_COM4 = true;
	f_KeayDelay();
	if(!KEY_SEG1)
	{
		(*KeyInfDeal) |= KEY_SIG_1; // s20
	}
	
	KEY_COM1 = true;
	KEY_COM2 = false;
	KEY_COM3 = true;
	KEY_COM4 = true;
	f_KeayDelay();
	if(!KEY_SEG1)
	{
		(*KeyInfDeal) |= KEY_SIG_2; // s15
	}
	if(!KEY_SEG2)
	{
		(*KeyInfDeal) |= KEY_SIG_3; // s16
	}
	if(!KEY_SEG3)
	{
		(*KeyInfDeal) |= KEY_SIG_4; // s17
	}
	if(!KEY_SEG4)
	{
		(*KeyInfDeal) |= KEY_SIG_5; // s18
	}
	if(!KEY_SEG5)
	{
		(*KeyInfDeal) |= KEY_SIG_6; // s19
	}

	KEY_COM1 = true;
	KEY_COM2 = true;
	KEY_COM3 = false;
	KEY_COM4 = true;
	f_KeayDelay();
	if(!KEY_SEG1)
	{
		(*KeyInfDeal) |= KEY_SIG_7; // s10
	}
	if(!KEY_SEG2)
	{
		(*KeyInfDeal) |= KEY_SIG_8; // s11
	}
	if(!KEY_SEG3)
	{
		(*KeyInfDeal) |= KEY_SIG_9; // s12
	}
	if(!KEY_SEG4)
	{
		(*KeyInfDeal) |= KEY_SIG_10; // s13
	}
	if(!KEY_SEG5)
	{
		(*KeyInfDeal) |= KEY_SIG_11; // s14
	}

	KEY_COM1 = true;
	KEY_COM2 = true;
	KEY_COM3 = true;
	KEY_COM4 = false;
	f_KeayDelay();
	if(!KEY_SEG1)
	{
		(*KeyInfDeal) |= KEY_SIG_12; // s5
	}
	if(!KEY_SEG2)
	{
		(*KeyInfDeal) |= KEY_SIG_13; // s6
	}
	if(!KEY_SEG3)
	{
		(*KeyInfDeal) |= KEY_SIG_14; // s7
	}
	if(!KEY_SEG4)
	{
		(*KeyInfDeal) |= KEY_SIG_15; // s8
	}
	if(!KEY_SEG5)
	{
		(*KeyInfDeal) |= KEY_SIG_16; // s9
	}
	f_KeayDelay();
}

/*=========================================================
* �� �� ��: void f_ChangeKeyInf(unsigned long *KeyInfDeal)
* ��������: ��ȡ����������Ϣ
* ���÷���: f_ChangeKeyInf(&KeyInfDeal);
* ���ú���: ��
* ȫ�ֱ���: 
* ��    ��: KeyInfDeal ������Ϣ
* ��    ��: ��
* �������:
*  ע   �⣺
* �޸�����	�޸���		�޸�˵��
* 2017-08-26		��� 			��ɻ�������
=========================================================*/
void ReadKey(unsigned char *GetKeyState,unsigned char *ScanStep,unsigned int *KeyDelayTime,KEY_PRESSED_STATE Key_Get)
{	
	switch(*ScanStep)
	{
		case 0: 
		{
			*KeyDelayTime = 0;
			KeyScanInf.nKeyRealDownTm = 0;
			*GetKeyState = NO_KEY;
			(*ScanStep) = 1;
			break;
		}	
		case MAX_STEP://�ȴ����� 
		{
			;
			break;
		}	
		default: 
		{	
			if(*KeyDelayTime >= GetTime((*ScanStep) - 1))
			{
				if(SetTimeInf((*ScanStep) - 1) != 0xff)
				{
					(*GetKeyState) |= SetTimeInf((*ScanStep) - 1);
					KeyScanInf.KeyPressName = Key_Get;
					KeyScanInf.bKeyPressFlag = true; //�������±�־
					(*ScanStep) ++;
				}
				else
				{
					(*ScanStep) = MAX_STEP;
				}		
			}
			break;
		}
	}
}

/*=========================================================
* �� �� ��: void f_KeyScan(void)
* ��������: ����ɨ��
* ���÷���: f_KeyScan();
* ���ú���: ��
* ȫ�ֱ���: 
* ��    ��: ��
* ��    ��: ��
* �������:
*  ע   �⣺
* �޸�����	�޸���		�޸�˵��
* 2017-08-26		��� 			��ɻ�������
=========================================================*/
void f_KeyScan(void)
{
	#define SIG_FUNCTION 0
	#define COM_FUNCTION 1
	unsigned char 	keyName;
	unsigned char 	U8Tmp;
	unsigned int	U16Tmp;
	static unsigned char nLastScanInf = 0;

	if(KeyScanInf.nKeyDownTm <= 65530)
	{
		KeyScanInf.nKeyDownTm++;
	}
	if(KeyScanInf.nNoKeyTm <= 65530)
	{
		KeyScanInf.nNoKeyTm++;
	}
	f_ChangeKeyInf(&KeyScanInf.nKeyInf);
	if((KeyScanInf.nKeyInf & KEY_ALL) == NO_KEY)//�����ͷ�
	{
		if(KeyScanInf.nNoKeyTm >= KEY_DELAY_TIME)//�ͷ�ȥ��
		{
			//������Ϣ���
			KeyScanInf.nKeyResultInf = NO_KEY;

			if(KeyScanInf.bKeyUsedFlag == false
			&& KeyScanInf.bKeyFirstRelse == false)//�ͷŶ̰��ж�(ǰ��������ʹ��)
			{
				KeyScanInf.nKeyResultInf |= PRESSED_RE;//�̰��ͷ�
				KeyScanInf.bKeyFirstRelse = true;
			}
			//������������
			if(KeyScanInf.nKeyResultInf == NO_KEY)//�ͷ���Ϣ�ѱ����
			{
				KeyScanInf.KeyPressName = KEY_FREE;
				KeyScanInf.nKeyStep = 0;
				KeyScanInf.bKeyPressFlag = false;
				KeyScanInf.bKeyUsedFlag = false;
				nLastScanInf = SIG_FUNCTION;
			}
		}
	}
	else 
	{
		bInSleepFlag = false;
		nKeyWakeTm = 0;	//������ʱ�����
		
		KeyScanInf.nNoKeyTm = 0;
		KeyScanInf.bKeyFirstRelse = false;
		if(KeyScanInf.bKeyUsedFlag)//�Ѿ��а�����Ӧ
		{
			KeyScanInf.nKeyStep = MAX_STEP;//ֱ�ӵȴ��ͷ�
			return;
		}
		
		for(keyName = 0; keyName < KEY_COM_NUMB; keyName ++)//��ϰ���ɨ�账��
		{
			if(((KeyScanInf.nKeyInf & KEY_ALL) == nTab_KeyHexDef[keyName])
			&& KeyScanInf.bKeyUsedFlag == false)
			{
				if(KeyScanInf.bKeyUsedFlag == false && nLastScanInf == SIG_FUNCTION)//�ɵ���ת���
				{
					nLastScanInf = COM_FUNCTION;
					KeyScanInf.nKeyStep = 0;
				}
				
				ReadKey(
						&KeyScanInf.nKeyResultInf,
						&KeyScanInf.nKeyStep,
						&KeyScanInf.nKeyDownTm,
						keyName + 1
						);
				return;
			}
		}

		for(keyName  = SIG_BASE; keyName < SIG_BASE + KEY_SIG_NUMB; keyName ++)//������ɨ�账��
		{
			if(((KeyScanInf.nKeyInf & KEY_ALL) == nTab_KeyHexDef[keyName])
			&& KeyScanInf.bKeyUsedFlag == false)
			{
				if(KeyScanInf.bKeyUsedFlag == false && nLastScanInf == COM_FUNCTION)//�����ת����
				{
					KeyScanInf.bKeyUsedFlag = true;//ֱ�ӵȴ��ͷ�
					KeyScanInf.nKeyStep = MAX_STEP;//ֱ�ӵȴ��ͷ�
				}
				nLastScanInf = SIG_FUNCTION;
				
				ReadKey(
						&KeyScanInf.nKeyResultInf,
						&KeyScanInf.nKeyStep,
						&KeyScanInf.nKeyDownTm,
						keyName + 1
						);
				return;
			}
		}

		/*if(KeyScanInf.nKeyInf && (~(KEY_TOTAL_COM)))//������Ч���
		{
			KeyScanInf.bKeyFirstRelse = true;//���ͷ���Ϣ
		}*/

		//�������
		KeyScanInf.nKeyStep = MAX_STEP;//ֱ�ӵȴ��ͷ�
	}
}
