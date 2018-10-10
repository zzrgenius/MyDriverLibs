#define VAR_RF_GLOBALS
#include "Include.h"

byte_def tComState;
#define bReceiveOverFlag			tComState.m_bit.b0	//������ɱ�־
#define bReceiveFinishFlag			tComState.m_bit.b1	//���ճɹ���־
#define bSendFlag					tComState.m_bit.b2	//���ͱ�־
#define bWaitReceiveFlag			tComState.m_bit.b3

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
void f_MemSetData(uchar *nBuff,uchar nSetData,uchar nEndNo)
{
	uchar i;
	for(i = 0; i < nEndNo; i ++)
	{
		nBuff[i] = nSetData;
	}
}

/*=========================================================
* ��������: ��ʼ�������� ÿ��50ms����һ��ʱ�䣩����һ��
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void f_StartDataSend(void)
{	
	if(bSendFlag == true)																						//��������
	{      
		LED = 0;
	  	f_SendPacket(&ucCOMBuf[0], ucCOMBuf[0]+1);

	  	SetCC2500_ChannelNumber(Cc2500Inf.RF_Channel[Cc2500Inf.RF_Channel_Index]);
		Cc2500Inf.RF_ChNum++;
		if(Cc2500Inf.RF_ChNum > 4)
		{
			Cc2500Inf.RF_ChNum = 0;
			Cc2500Inf.RF_Channel_Index ++;
			if(Cc2500Inf.RF_Channel_Index > 3)
			{ 
				Cc2500Inf.RF_Channel_Index = 0;
				Cc2500Inf.RF_CrcNum ++;
				if(Cc2500Inf.RF_CrcNum > 2)
				{
					Cc2500Inf.RF_CrcNum = 0;
					bSendFlag = false;
   					LED = 1;
				}
			}
		}



	  	
//		Cc2500Inf.RF_Channel_Index ++;
//		if(Cc2500Inf.RF_Channel_Index > 3)
//		{
//			Cc2500Inf.RF_Channel_Index = 0;
//			Cc2500Inf.RF_ChNum++;
//			if(Cc2500Inf.RF_ChNum > 4)
//			{
//				Cc2500Inf.RF_ChNum = 0;
//				bSendFlag = false;
//   				LED = 1;
//			}
//		}
  	}
}

/*=========================================================
* �� �� ��: f_GetSendBuff()
* ��������: ��ȡ���ͻ���
* ���÷���: f_GetSendBuff()
* ���ú���: 
* ȫ�ֱ���: 
========================================================= */
void f_GetSendBuffRF(void)
{
	if(SysInf.RfSendFlag)
	{
		SysInf.RfSendFlag = false;
		bSendFlag = true;						// ʹ�ܷ��� 
		f_MemSetData(ucCOMBuf,0,TXD_TOTAL_BYTES);		
		ucCOMBuf[0] = TXD_TOTAL_BYTES;		// �����ֽ��� 
		ucCOMBuf[1] = ADDR[0];
		ucCOMBuf[2] = ADDR[1];
		ucCOMBuf[3] = ADDR[2];
		ucCOMBuf[4] = sendNum++;				//ָ��ң������
		ucCOMBuf[5] = 0X03;					//��������			
		ucCOMBuf[6] = SysInf.SeatTempGear << 4;
		ucCOMBuf[6] |= SysInf.WaterTempGear;	//��4λ���µ�4λˮ��  
		ucCOMBuf[7] = SysInf.DryTempGear;		//��4λ���¸�4λ��ʱ����
		ucCOMBuf[8] = SysInf.ValveGear<< 4;
		ucCOMBuf[8] |= SysInf.NozzleGear;
		ucCOMBuf[9] = 0x01;//ϵͳ���ػ�״̬
		ucCOMBuf[10] = SysInf.KeyNum;
		ucCOMBuf[TXD_TOTAL_BYTES - 1] = f_AddTotalNum(ucCOMBuf,(TXD_TOTAL_BYTES - 1));
		SysInf.KeyNum = 0x00;
	}
}

