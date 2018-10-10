/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : Uart1.c
  �� �� ��   : V1.0
  ��    ��   : zhufeng
  ��������   : 2018��5��1��
  ����޸�   :
  ��������   : ����1�����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����   : �����ļ�

******************************************************************************/
#define VAR_UART1_GLOBALS
#include "Include.h"
/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����˵��                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/

/*****************************************************************************
 �� �� ��: f_pUart1SendByte
 ��������  : ����һ���ֽ�,�����ݷ��͵�Ӳ������
 �������: uchar nByte  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pUart1SendByte(uchar nByte)
{
	UART1_DATA_DR = nByte;  
}

/*****************************************************************************
 �� �� ��: f_pUart1ReceByte
 ��������  : ����һ���ֽ�,��Ӳ�������ȡһ���ֽ�
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_pUart1ReceByte(void)
{
	uchar nTemp = 0;
	volatile uchar nError = 0;

	nError = UART1_DATA_SR;//�ȶ�һ��SR���ٶ�DR��������ϱ�־
	nError = 0;
	while(!(UART1_DATA_SR&0x20))//�ȴ����ݽ���,RXNE
	{
		nError ++;
		if(nError >= 30)
			break;
	}
	nTemp = UART1_DATA_DR;	//���Ĵ����������־(�������)
	return nTemp;
}

/*****************************************************************************
 �� �� ��: f_pUart1BufAddJudge
 ��������  : ���ͻ�������ж�
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_pUart1BufAddJudge(void)
{
	if(Uart1Tx.rUart1UseLine < UART1_MAX_LINE)
	{
		Uart1Tx.rUart1UseLine ++;
		return true;
	}
	else
	{
		return false;
	}
}

/*****************************************************************************
 �� �� ��: UART1_TX_Interrupt
 ��������  : �����жϺ���
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
IT_HEADE void UART1_TX_Interrupt(void)
{	
	Uart1Tx.rUart1NoComCnt = 0;
	if(Uart1ComFlag.rUart1EnSendFlag)//��Ҫ���͵Ļ���
	{
		if(Uart1Tx.rUart1ComPos <= Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][0])
		{
			f_pUart1SendByte(Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][Uart1Tx.rUart1ComPos]);
			Uart1Tx.rUart1ComPos ++;
		}
		else
		{
			if(Uart1Tx.rUart1ComPos < UART1_MAX_BYTE - 1)//��Ҫ�ж����һ���������
			{
				Uart1Tx.rUart1ComPos ++;	
			}	
		}
	}
	UART1_DATA_SR &= (~0xC0);//TIEN,TICEN
}

/*****************************************************************************
 �� �� ��: UART1_RX_Interrupt
 ��������  : �����жϺ���
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
IT_HEADE void UART1_RX_Interrupt(void)
{
	Uart1Rx.rUart1NoComCnt = 0;
	Uart1ComFlag.rUart1EnAddLine = true;
	//��֡���й�����0��ʼ���¸���(����Ч)
	if(Uart1Rx.rUart1ComPos >= UART1_MAX_BYTE)
	{
		Uart1Rx.rUart1ComPos = UART1_MAX_BYTE - 1;
	}
	Uart1Rx.Uart1ComBuff[Uart1Rx.rUart1BuffLine][Uart1Rx.rUart1ComPos] = f_pUart1ReceByte();
	Uart1Rx.rUart1ComPos++;
}

/*****************************************************************************
 �� �� ��: f_pUart1TimeCnt
 ��������  : ����ʱ�䴦��
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pUart1TimeCnt(void)
{
	//�޽��ռ�ʱ
	AddIntData(&Uart1Rx.rUart1NoComCnt);
	//ʱ����������
	if(Uart1ComFlag.rUart1EnAddLine)
	{
		if(Uart1Rx.rUart1NoComCnt >=UART1_RX_GAP_TM)//�������յ�2���ֽڼ�϶ʱ��,��Ϊ�Ѿ���֡
		{
			Uart1ComFlag.rUart1EnAddLine = false;
			if(Uart1Rx.rUart1UseLine < UART1_MAX_LINE)//��������ۼ�
			{
				Uart1Rx.rUart1UseLine++;	
				//����
				if(Uart1Rx.rUart1BuffLine < (UART1_MAX_LINE - 1))
				{
					Uart1Rx.rUart1BuffLine++;	
				}
				else
				{
					Uart1Rx.rUart1BuffLine = 0;
				}
				Uart1Rx.rUart1ComPos = 0;
			}
		}
	}
	//�����ж�
	if(Uart1Rx.rUart1NoComCnt >= 200) // 2 s
	{
		Uart1ComFlag.rUart1CommErrFlag = true;	
	}
	else
	{
		Uart1ComFlag.rUart1CommErrFlag = false;	
	}
	//���ͼ�ʱ
	AddIntData(&Uart1Tx.rUart1NoComCnt);
}

/*****************************************************************************
 �� �� ��: f_pUart1Init
 ��������  : ���ں�����ʼ��
 �������: uint baudRate  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pUart1Init(uint baudRate)
{
	uint nRate;
	UART1_DATA_CR1 = 0X00;
	UART1_DATA_CR2 = 0X00;
	UART1_DATA_CR3 = 0X00;
	UART1_DATA_SR = 0X00;
	// ������дBRR2  
	// ������ڲ�����λ115200ʱ����Ƶϵ��=16000000/115200=139  
	// ��Ӧ��ʮ��������Ϊ008B��BBR1=08,BBR2=0B
	nRate = SYS_CLOCK/baudRate;
	UART1_DATA_BR2 = (uchar)((nRate&0x000f) +( (nRate>>8)&0xf0));
	UART1_DATA_BR1 = (uchar)(nRate>>4);
	UART1_CR2_REN_TRUE;	//�����жϿ���
	UART1_CR2_RIEN_TRUE;	 
	UART1_CR2_TEN_TRUE;	 
	UART1_CR2_TIEN_TRUE;	//�����жϿ��� 
}

/*****************************************************************************
 �� �� ��: f_pUart1GetSendData
 ��������  : �����Ҫ���͵�����
 �������: BIG_STRUCT *pFuctionData  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pUart1GetSendData(BIG_STRUCT *pFuctionData)
{
	static uint i=0;
	if(f_pUart1BufAddJudge() == false)//�޷��������
	{
		return;
	}
	NeedSendInf.NeedSendFlag = false;	
	
	TxComBuff.jHead = 0x31;
	TxComBuff.jCheck = f_CheckSum((unsigned char *)&TxComBuff, 0,sizeof(UART1_COM_TX) - 1);
	//TxComBuff.jCheck = f_XorSum((unsigned char *)&TxComBuff, 0,sizeof(UART1_COM_TX) - 2);
	Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1BuffLine][0] = sizeof(UART1_COM_TX);
	f_Memcpy(&Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1BuffLine][1], &TxComBuff, sizeof(UART1_COM_TX));
	TxComBuff.jFunCmd = 0x00;
	//���¶��е���һ��
	if(Uart1Tx.rUart1BuffLine< (UART1_MAX_LINE - 1))
	{
		Uart1Tx.rUart1BuffLine ++;
	}
	else
	{
		Uart1Tx.rUart1BuffLine = 0;
	}
}

/*****************************************************************************
 �� �� ��: f_pUart1SendDeal
 ��������  : ���ͺ�������
 �������: BIG_STRUCT *pFuctionData  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pUart1SendDeal(BIG_STRUCT *pFuctionData)
{
	if(NeedSendInf.NeedSendFlag)	//���	��Ҫ���͵�����
	{
		f_pUart1GetSendData(pFuctionData);
	}
	if(Uart1Tx.rUart1UseLine > 0)//��Ҫ���͵Ļ���
	{
		Uart1ComFlag.rUart1EnSendFlag = true;	//������
		if(Uart1Tx.rUart1NoComCnt >= 50)//500ms�޷��ͣ�������,�ط���ǰ֡
		{
			Uart1ComFlag.rUart1StartSend = true;//��������
			Uart1Tx.rUart1ComPos = 0;
		}
		if(Uart1Tx.rUart1ComPos > Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][0])//��ǰ֡����
		{
			Uart1Tx.rUart1UseLine--;	
			Uart1Tx.rUart1ComPos = 0;
			if(Uart1Tx.rUart1ComLine < (UART1_MAX_LINE - 1))
			{
				Uart1Tx.rUart1ComLine++;	
			}
			else
			{
				Uart1Tx.rUart1ComLine = 0;
			}
			if(Uart1Tx.rUart1UseLine > 0)//��ǰ���껹����Ҫ����
			{
				Uart1ComFlag.rUart1StartSend = true;//��������	
			}
		}
		if(Uart1ComFlag.rUart1StartSend)//��������
		{
			Uart1ComFlag.rUart1StartSend = false;	
			Uart1Tx.rUart1ComPos = 2;
			f_pUart1SendByte(Uart1Tx.Uart1ComBuff[Uart1Tx.rUart1ComLine][1]);//���͵�1������
		}
	}
	else
	{
		Uart1ComFlag.rUart1EnSendFlag = false;
		Uart1ComFlag.rUart1StartSend = true;
		Uart1Tx.rUart1NoComCnt = 0;
	}
}

/*****************************************************************************
 �� �� ��: f_pUart1ReceDeal
 ��������  : ���մ���
 �������: BIG_STRUCT *pFuctionData  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��1��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pUart1ReceDeal(BIG_STRUCT *pFuctionData)
{
	uchar j;
	uint nCRCbuf = 0;

	if(Uart1Rx.rUart1UseLine > 0)//����Ҫ��������
	{
		if(Uart1Rx.Uart1ComBuff[Uart1Rx.rUart1ComLine][0] == 0x31)
		{
			f_Memcpy(&RxComBuff, &Uart1Rx.Uart1ComBuff[Uart1Rx.rUart1ComLine][0], sizeof(UART1_COM_RX));	
			NeedSendInf.NeedSendFlag = 1;
			pFuctionData->bInitInf = RxComBuff.nInitInf;
			pFuctionData->SystemCurState = RxComBuff.nSystemCurState;
			pFuctionData->curFunInf.curFunc = RxComBuff.nCurFunc;
			pFuctionData->WashInf.bTempChange = RxComBuff.nTempChange;
			pFuctionData->seatInf.seatSensorState.bSwitchState = RxComBuff.nSwitchState;
			pFuctionData->systemErrInf.byte = RxComBuff.nSystemErrInf;
			pFuctionData->seatInf.SeatOffTm.hour = RxComBuff.nSeatOffHour;
			pFuctionData->seatInf.SwitchSeatEn = RxComBuff.nSeatEn;
			pFuctionData->curFunInf.posState = RxComBuff.nPosState;
			pFuctionData->curFunInf.levelState = RxComBuff.nLevelState;
			if(pFuctionData->addrInf.addrFlag == 0x00)
			{
				pFuctionData->addrInf.addrFlag = RxComBuff.nAddrFlag;//������ַ��
			}
			pFuctionData->flushTimeState = RxComBuff.nFlushTimeState;
			pFuctionData->heatInf.waterHeat.setWaterLevel = RxComBuff.nSetWaterLevel;
			pFuctionData->heatInf.seatHeat.setSeatLevel = RxComBuff.nSetSeatLevel;
			pFuctionData->heatInf.dryHeat.setDryLevel = RxComBuff.nSetDryLevel;

			if(TxComBuff.jSetSeatLevel == RxComBuff.nSetSeatLevel)
			{
				if(LedInf.delaySeatDis)
				{
					LedInf.delaySeatDis = false;
					LedInf.DryDisCnt = 0;// ��ʱ10S
				}
			}
			if(TxComBuff.jSetDryLevel == RxComBuff.nSetDryLevel)
			{
				if(LedInf.delayDrytDis)
				{
					LedInf.delayDrytDis = false;
					LedInf.DryDisCnt = 11;// ��ʱ10S
				}
			}
		}
		//��ǰ֡�������
		Uart1Rx.rUart1UseLine  --;
		if(Uart1Rx.rUart1ComLine < (UART1_MAX_LINE - 1))
		{
			Uart1Rx.rUart1ComLine ++;
		}
		else
		{
			Uart1Rx.rUart1ComLine = 0;
		}
	}
}