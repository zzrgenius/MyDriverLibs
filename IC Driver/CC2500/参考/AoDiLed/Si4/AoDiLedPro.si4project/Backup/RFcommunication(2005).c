#include "Include.h"

byte_def tComState;
#define bReceiveOverFlag			tComState.m_bit.b0	//������ɱ�־
#define bReceiveFinishFlag			tComState.m_bit.b1	//���ճɹ���־
#define bSendFlag					tComState.m_bit.b2	//���ͱ�־
#define bWaitReceiveFlag			tComState.m_bit.b3

uchar ucCOMBuf[64];		//RXD_TOTAL_BYTES		// ����,���ͻ��� 

uchar sendNum;
/*=========================================================
* ��������: �ۼӺ�
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
uchar f_AddTotalNum(uchar *nBuff,uchar nEndNo)
{
	uchar i,nTotalSum;
	nTotalSum = 0;
	for(i = 0; i < nEndNo; i ++)
	{
		nTotalSum += nBuff[i];
	}
	return nTotalSum;
}

/*=========================================================
* ��������: ���鸳ֵ
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
/*void f_MemSetData(uchar *nBuff,uchar nSetData,uchar nEndNo)
{
	uchar i;
	for(i = 0; i < nEndNo; i ++)
	{
		nBuff[i] = nSetData;
	}
}*/

/*=========================================================
* ��������: ��ʼ�������� ÿ��50ms����һ��ʱ�䣩����һ��
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void f_StartDataSend(void)
{
	uchar j;
	uchar nCC2500State;
	if(!bSendFlag)																						//�޷������ݷ���
		return;
	j = TXD_TOTAL_BYTES - 1;
	ucCOMBuf[j] = f_AddTotalNum(ucCOMBuf,j);
	if (bSendFlag)																						//��������
	{      
	  	//f_SendPacket(&ucCOMBuf[0], ucCOMBuf[0]+1);
  	}
}

/*=========================================================
* ��������: ����ͨ�Ž��յ����ź�
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void f_DealRXD(void)
{
	uchar i,j;
	if (!bReceiveOverFlag)			/* ����δ��ɣ����� */
		return;
	bReceiveOverFlag = 0;
	/* �ж�У���� */
	j = RXD_TOTAL_BYTES - 1;
	if(ucCOMBuf[j] != f_AddTotalNum(ucCOMBuf,j))
	{
		f_RxCC2500();
		return;
	}
	if(machineInf.addrInf.addrFlag == 0)
	{
		if( ucCOMBuf[1] == machineInf.AddressRf[0]
		&& ucCOMBuf[2] == machineInf.AddressRf[1]
		&& ucCOMBuf[3] == machineInf.AddressRf[2])
		{
			if(ucCOMBuf[4] != sendNum)	//����ң���������ʶ����
			{
				sendNum = ucCOMBuf[4];
				if(ucCOMBuf[5] == 0x03)	//֡�������ڿ�������
				{
					TxComBuff.jSetSeatLevel = ucCOMBuf[6]>>4;
					TxComBuff.jSetWaterLevel = ucCOMBuf[6]&0x0f; 
					TxComBuff.jSetDryLevel = ucCOMBuf[7]&0x0f; 
					TxComBuff.jLevelState = ucCOMBuf[8]>>4;
					TxComBuff.jPosState = ucCOMBuf[8]&0x0f; 
					TxComBuff.jFunCmd = ucCOMBuf[10];
					if(TxComBuff.jFunCmd == 0x08)
					{
						LedInf.delayDrytDis = true;
						//LedInf.DryDisCnt = 3;
						//LedInf.DryDisCnt = 11;// ��ʱ10S
					}
				}
			}
		}		
	}
	else
	{
		machineInf.AddressRf[0] = ucCOMBuf[1];
		machineInf.AddressRf[1] = ucCOMBuf[2];
		machineInf.AddressRf[2] = ucCOMBuf[3];
		machineInf.addrInf.addrFlag = 0;
	}
	f_RxCC2500();
}

/*=========================================================
* ��������: �ⲿ�ж�0�жϣ��½��ش���
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
IT_HEADE void PBExtInterrupt(void)
{
	if((EXTI_CR1  & 0x08) == 0x08)//�½�����Ч
	{
		if(PBI_5==0)
		{
			NOP();NOP();NOP();NOP();
			if(PBI_5==0)
			{
				if (bSendFlag)	
				{
					bSendFlag = 0;	
					f_RxCC2500(); 	
				}
				else
				{
					if(halRfReceivePacket(&ucCOMBuf[1], &ucCOMBuf[0]) == 1)
					{   
						bReceiveOverFlag = 1;  
						Cc2500Inf.nCC2500Time1 = 0;
						Cc2500Inf.nCC2500Time2 = 0;
					}
				}
			}
		}
	}
}

