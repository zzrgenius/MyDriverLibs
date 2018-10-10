/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : PL1167.c
  �� �� ��   : V1.0
  ��    ��   : zhufeng
  ��������   : 2018��4��27��
  ����޸�   :
  ��������   : PL1167�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����   : �����ļ�

******************************************************************************/
#define VAR_PL1167_GLOBALS
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
uchar SendBuff[SEND_LEN];
//uchar RfData[11];
//uchar irData[4];

static const uchar PrfRegAddrTab[]=
{
	0x00,0x01,0x02,0x04,0x05,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,
	0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,
	0x20,0x21,0x22,0x23,
	0x28,0x29,0x2a,0x2b,
	0x24,0x25,0x26,0x27,
	0x07,0x24,0x27,
};

static const uint PrfRegTab[]=
{
	0x6fe0,0x5681,0x6617,0x9cc9,0x6637,0x0030,0x6c90,0x4800,0x7ffd,0x0008,0x0000,0x48bd,
	0x00ff,0x8005,0x0067,0x1659,0x19e0,0x1300,0x1800,
	0x5000,0x3fc7,0x2000,0x0340,
	0x4401,0xb800,0xfdc8,0x000f,
	0x7209,0x0000,0x0000,0xb057,
	0x0073,0xeede,0x11f9
};

static const uint FreqTemp[]=
{
	0x0073,0x0003,0x0063,0x0043,0x0033
};

static const uchar FreqRegAddrTab[]=	//����
{
  0x07,0x34,0x07
};
static const uint FreqRegTab[][3]=
{
	{0x0073,0x8080,0x0083},
	{0x0003,0x8080,0x00e3},
	{0x0063,0x8080,0x00c3},
	{0x0043,0x8080,0x00b3},
	{0x0033,0x8080,0x00f3}
};

/*****************************************************************************
 �� �� ��: f_pSpiWr8
 ��������  : д8λSPI
 �������: uchar dat  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pSpiWr8(uchar dat)
{
 	uchar i;
	for(i=0; i<8; i++)  
	{
		SPICLK = 1;
		if((dat&0x80)==0x80)
			SPIMOSI = 1;
		else
			SPIMOSI = 0;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		SPICLK = 0;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		dat <<= 1;
	}
	
}

/*****************************************************************************
 �� �� ��: f_pSpiRd8
 ��������  : ��8λSPI
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_pSpiRd8(void)
{
	uchar i;
	uchar dat = 0;
	for(i=0; i<8; i++)
	{
		SPICLK = 1;
		dat <<= 1;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		SPICLK = 0;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		if(SPIMISO==0)
			dat &= 0xfe;
		else
			dat |= 0x01;
	}
	return dat;
}

/*****************************************************************************
 �� �� ��: f_pSpiRd16
 ��������  : ��16λSPI
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
uint f_pSpiRd16(void)
{
	uint dat;
	uchar i;
	dat = 0;
	for(i=0; i<16; i++)  
	{
		SPICLK = 1;
		dat <<= 1;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		SPICLK = 0;
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		NOP();NOP();NOP();NOP();NOP();
		if(SPIMISO==0)
			dat &= 0xfffe;
		else
			dat |= 0x0001;
	}
	return dat;
}

/*****************************************************************************
 �� �� ��: f_pPrfWrReg16
 ��������  : д16λ�Ĵ���
 �������: uchar reg    
             uint regval  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pPrfWrReg16(uchar reg, uint regval)
{
	SPICS = 0;
	f_pSpiWr8(reg);
	f_pSpiWr8((uchar)(regval>>8));
	f_pSpiWr8((uchar)(regval&0x00FF));
	SPICS = 1;
}

/*****************************************************************************
 �� �� ��: f_pPrfRegRd16
 ��������  : ��16λ�Ĵ���
 �������: uchar addr  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
uint f_pPrfRegRd16(uchar addr)
{
	uint dat;
	
	SPICS = 0;
	f_pSpiWr8(addr|PRF_REG_RD);
	dat = f_pSpiRd16();
	SPICS = 1;
	return dat;
}

/*****************************************************************************
 �� �� ��: f_pPL1167ReInit
 ��������  : PL1167�س�ʼ��
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��21��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pPL1167ReInit(void)
{
	uchar i,j,err;
	uint regval;
	for(i=0;i<3;i++)
	{
		err = 0;
		for(j=0;j<PRF_INIT_TAB_LEN;j++)
		{
			f_pPrfWrReg16(PrfRegAddrTab[j], PrfRegTab[j]);
			regval = f_pPrfRegRd16(PrfRegAddrTab[j]);
			if(regval!=PrfRegTab[j])
			{
				err = 1;
				NOP();
			}
		}
		if(err==0)
			break;		
	}	
}

/*****************************************************************************
 �� �� ��: f_pPL1167Init
 ��������  : ��ƵоƬ��ʼ��
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pPL1167Init(void)
{
	RFRST = 0;
	SPICS = 1;
	f_NOPDelay(10000);// 10ms
	RFRST = 1;
	f_pPL1167ReInit();
}

/*****************************************************************************
 �� �� ��: f_pAddTotalNum
 ��������  : �ۼӺ�
 �������: uchar *nBuff  
             uchar nEndNo  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_pAddTotalNum(uchar *nBuff,uchar nEndNo)
{
	uchar i,nTotalSum;
	nTotalSum = 0;
	for(i = 0; i < nEndNo; i ++)
	{
		nTotalSum += nBuff[i];
	}
	return nTotalSum;
}

/*****************************************************************************
 �� �� ��: f_pSendBuffer
 ��������  : ���ʹ���
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pSendBuffer(void)
{
	static uchar sendNum = 0;
	if(SendInf.SendStart == true)
	{
		LED = 0;
		SendBuff[0] = SEND_LEN;
		SendBuff[1] = ADDR[0];
		SendBuff[2] = ADDR[1];
		SendBuff[3] = ADDR[2];
		SendBuff[4] = sendNum++;				//ָ��ң������
		SendBuff[5] = 0X03;					//��������			
		SendBuff[6] = SysInf.SeatTempGear << 4;
		SendBuff[6] |= SysInf.WaterTempGear;	//��4λ���µ�4λˮ��  
		SendBuff[7] = SysInf.DryTempGear;		//��4λ���¸�4λ��ʱ����
		SendBuff[8] = SysInf.ValveGear<< 4;
		SendBuff[8] |= SysInf.NozzleGear;
		SendBuff[9] = 0x01;//ϵͳ���ػ�״̬
		SendBuff[10] = SysInf.KeyNum;
		SendBuff[11] = f_pAddTotalNum(SendBuff,SEND_LEN-1);
		SysInf.KeyNum = 0x00;
		SendInf.SendStart = false;
		SendInf.SendFlag = true;
		f_pPL1167ReInit();
	}
}

/*****************************************************************************
 �� �� ��: f_pSendDeal
 ��������  : ���ʹ���
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_pSendDeal(void)
{
	uchar i;
	uint j;
	static uchar m=0;
	static uchar n=0;
	f_pSendBuffer();
	if(SendInf.SendFlag)
	{
		f_pPrfWrReg16(0x07, FreqTemp[n]);
		f_pPrfWrReg16(0x34, 0x8080);
		SPICS = 0;
		f_pSpiWr8(0x32);
		for(i=0;i<SEND_LEN;i++)
		{
			f_pSpiWr8(SendBuff[i]);
		}
		SPICS = 1;
		f_pPrfWrReg16(0x07, FreqTemp[n]|0x0100);
		j = 0;
		while(PKT==0)
		{
			if (j ++ > 1000)	//�˴���Ҫ��ӳ�ʱ���� 1ms
				break;			
		};
		f_pPrfWrReg16(0x07, FreqTemp[n]);
		m++;
		if(m>4)
		{
			m=0;
			n++;
			if(n>4)
			{
				n=0;
				SendInf.SendFlag = false;
			}
		}
		LED = 1;
	}
}

/*****************************************************************************
 �� �� ��: f_pRfRecDeal
 ��������  : ���մ���
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
//void f_pRfRecDeal(void)
//{
//	uchar i;
//	uchar lenght;
//	static uchar tempData1,tempData2;
//	if(_pb2==1)
//	{
//		NOP();NOP();NOP();NOP();
//		NOP();NOP();NOP();NOP();
//		NOP();NOP();NOP();NOP();
//		NOP();NOP();NOP();NOP();
//		if(_pb2==1)		
//		{
//			SPICS = 0;
//			f_pSpiWr8(0x32|PRF_REG_RD);
//			lenght = f_pSpiRd8();
//			if(lenght > 11)
//			{
//				lenght = 11;
//			}
//			for(i=0;i<lenght;i++)
//			{
//				RfData[i] = f_pSpiRd8();
//			}
//			SPICS = 1;
//			
//			f_pPrfWrReg16(0x34, 0x8080);
//			f_pPrfWrReg16(0x07, 0x00f3);
//			//�����ж�
//			if(RfData[0] == 0x55 && RfData[1] == 0xaa && RfData[2] == 0xf0)
//			{
//				if((tempData1 != RfData[3]) && (tempData2 != RfData[10]) )
//				{
//					tempData1 = RfData[3];
//					tempData2 = RfData[10];
//					if(RfData[7] == (RfData[4] + RfData[5] + RfData[6]))
//					{	
//							irData[0] = RfData[4];
//							irData[1] = RfData[5];
//							irData[2] = RfData[6];
//							irData[3] = RfData[7];
//					}
//				}
//			}
//			for(i=0;i<11;i++)
//			{
//				RfData[i] = 0x00;
//			}
//		}
//	}
//}

/*****************************************************************************
 �� �� ��: f_pFreqDeal
 ��������  : ��Ƶ����
 �������: void  
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��27��
    ��    ��   : zhufeng
    �޸�����    : �����ɺ���

*****************************************************************************/
//void f_pFreqDeal(void)
//{
//	static uchar freqTemp = 0;
//	uchar i;
//	i=0;
//	for(i=0;i<3;i++)
//	{
//		f_pPrfWrReg16(FreqRegAddrTab[i], FreqRegTab[freqTemp][i]);
//	}
//	freqTemp++;	
//	if(freqTemp > 4)
//	{
//		freqTemp =0;
//	}
//}
