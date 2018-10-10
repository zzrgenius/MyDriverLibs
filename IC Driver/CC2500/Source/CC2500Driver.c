/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : CC2500Driver.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��31��
  ����޸�   :
  ��������   : CC2500����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "CC2500Driver.h"
#include "CC2500Register.h"
#include "SubFunction.h"
#include "CC2500Protocol.h"
#include "IO_Define.h"


/*----------------------------------------------*
 * �ⲿ����˵��                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                                     *
 *----------------------------------------------*/
uchar f_CC2500_InitByChannel(uchar channel);

/*----------------------------------------------*
 * ȫ�ֱ���                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/
CC250_DRIVER cc2500;


/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
//CC2500_GDO0 CC2500��һЩ״̬������

/*****************************************************************************
 �� �� ��: f_CC2500_WaitIDLE
 ��������  : �ȴ�CC2500����
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��1��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_CC2500_WaitIDLE(uint tryCnt)
{
    while (tryCnt > 0)
    {
        if (false == CC2500_SDI)
        {
            break;
        }
        tryCnt--;
        f_Delay(10);
    }

    if (0 == tryCnt)//��ʱ����
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*****************************************************************************
 �� �� ��: f_CC2500_WriteReg
 ��������  : дCC2500�Ĵ���
 �������  : addr �Ĵ�����ַ
           setValue ���üĴ���ֵ
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_WriteReg(uchar addr, uchar setValue)
{
    f_SPIEnChip(cc2500.spi, STATE_ON);
    f_CC2500_WaitIDLE(1000);
    f_SPIWriteData(cc2500.spi, addr&0x7F, 8);
    f_SPIWriteData(cc2500.spi, setValue, 8);

    f_SPIEnChip(cc2500.spi, STATE_OFF);
}

/*****************************************************************************
 �� �� ��: f_CC2500_WriteBurst
 ��������  : CC2500����д�������
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_WriteBurst(uchar addr, uchar *pData, uchar len)
{
    uchar i;
    
    f_SPIEnChip(cc2500.spi, STATE_ON);
    f_CC2500_WaitIDLE(1000);
    f_SPIWriteData(cc2500.spi, addr|TI_CCxxx0_WRITE_BURST, 8);
    for (i = 0; i < len; i++)
    {
        f_SPIWriteData(cc2500.spi, pData[i], 8);
    }
    f_SPIEnChip(cc2500.spi, STATE_OFF);
}

/*****************************************************************************
 �� �� ��: f_CC2500_ReadReg
 ��������  : ��CC2500�Ĵ���
 �������  : addr �Ĵ�����ַ
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_CC2500_ReadReg(uchar addr)
{
    uchar getValue;
    
    f_SPIEnChip(cc2500.spi, STATE_ON);
    f_CC2500_WaitIDLE(1000);
    f_SPIWriteData(cc2500.spi, addr|TI_CCxxx0_READ_SINGLE, 8);
    getValue = (uchar)f_SPIReadData(cc2500.spi, 8);
    f_SPIEnChip(cc2500.spi, STATE_OFF);
    return getValue;
}

/*****************************************************************************
 �� �� ��: f_CC2500_ReadBurst
 ��������  : CC2500������ȡ
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_ReadBurst(uchar addr, uchar *pData, uchar len)
{
    uchar i;
    
    f_SPIEnChip(cc2500.spi, STATE_ON);
    f_CC2500_WaitIDLE(1000);
    f_SPIWriteData(cc2500.spi, addr|TI_CCxxx0_READ_BURST, 8);
    for (i = 0; i < len; i++)
    {
        pData[i] = (uchar)f_SPIReadData(cc2500.spi, 8);
    }
    f_SPIEnChip(cc2500.spi, STATE_OFF);
}

/*****************************************************************************
 �� �� ��: f_CC2500_WriteStrobe
 ��������  : CCC2500д״̬�Ĵ���
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_WriteStrobe(uchar strobe)
{
    f_SPIEnChip(cc2500.spi, STATE_ON);
    f_CC2500_WaitIDLE(1000);
    f_SPIWriteData(cc2500.spi, strobe, 8);
    f_SPIEnChip(cc2500.spi, STATE_OFF);
}

/*****************************************************************************
 �� �� ��: f_CC2500_ReadStrobe
 ��������  : ��CC2500״̬�Ĵ���
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_CC2500_ReadStrobe(uchar addr)
{
    uchar getValue;
    f_CC2500_ReadBurst(addr, &getValue, 1);
    return getValue;
}

/*****************************************************************************
 �� �� ��: f_CC2500_ResetAllReg
 ��������  : CC2500�����������мĴ���
 �������  : channel ��Ƶͨ����
 �������  :
 �� �� ֵ: �ɹ�:true;ʧ��:false
 ע     ��: �ٶ�250K,FIFO����256
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_CC2500_ResetAllReg(uchar channel)
{
    uchar i;

    for (i = 0; i < CC2500_REG_SIZE; i ++)
    {
        f_CC2500_WriteReg(tab_CC2500Register[i].addr, tab_CC2500Register[i].setValue);
    }
    f_CC2500_WriteReg(TI_CCxxx0_CHANNR, channel);// Channel number.
    if (0x3B != f_CC2500_ReadReg(TI_CCxxx0_MDMCFG3))
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*****************************************************************************
 �� �� ��: f_CC2500_IntoSleep
 ��������  : CC2500��������ģʽ
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_IntoSleep(void)
{
    f_CC2500_WriteStrobe(TI_CCxxx0_SIDLE);
	f_CC2500_WriteStrobe(TI_CCxxx0_SPWD);
	cc2500.bRfSleep = true;
}

/*****************************************************************************
 �� �� ��: f_CC2500_AutoSleep
 ��������  : �Զ��������ߣ����н���
 �������  : void  
 �������  :
 �� �� ֵ: 
 ע     ��: 100ms����
 
 �޸���ʷ      :
  1.��    ��   : 2018��9��19��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_AutoSleep(void)
{
    if (false == cc2500.bRfSleep
	&& 0 == cc2500.needSendCnt
	&& true == cc2500.bResetOK) //�������(�ѳɹ���ʼ��)
	{
        cc2500.autoSleepTm++;
        if (cc2500.autoSleepTm >= 20) //2s�Զ�����ģ������
        {
            cc2500.autoSleepTm = 0;
            f_CC2500_IntoSleep();    
        }
	}
	else
	{
        cc2500.autoSleepTm = 0;
	}
    
}

/*****************************************************************************
 �� �� ��: f_CC2500_SetRevMode
 ��������  : ����CC2500Ϊ����ģʽ
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_SetRevMode(void)
{
    if (false == cc2500.bResetOK)
    {
        return;
    }
    
    f_CC2500_WriteStrobe(TI_CCxxx0_SIDLE);
	f_CC2500_WriteStrobe(TI_CCxxx0_SFRX); //���FIFO
	f_CC2500_WriteStrobe(TI_CCxxx0_SRX); //ѡ�����ģʽ
}

/*****************************************************************************
 �� �� ��: f_CC2500_SendData
 ��������  : CC2500��������
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_SendData(uchar *pData, uchar len)
{
    uint waitCnt;
    
    f_CC2500_WriteStrobe(TI_CCxxx0_SIDLE);
	f_CC2500_WriteStrobe(TI_CCxxx0_SFTX);
	f_CC2500_WriteBurst(TI_CCxxx0_TXFIFO, pData, len);
	f_CC2500_WriteStrobe(TI_CCxxx0_STX);

    //�ȴ���������-��Ҫ330us ����1ms
	waitCnt = 800;
	while(waitCnt--)
	{
		if(CC2500_SDI)
		{
		    break; 
		}
	}

    //�ȴ����ͽ���-250Kbps 64Bytes*8=512Bits Լ2ms������ɣ���������3ms
	f_CC2500_WaitIDLE(2400);
	
	//������ɺ��Զ�����IDLE״̬
}

/*****************************************************************************
 �� �� ��: f_CC2500_RevData
 ��������  : CC2500��������
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_CC2500_RevData(uchar *pData, uchar *len)
{
    #define CC2500_APPEND_LEN 2
    uchar status[CC2500_APPEND_LEN];
    uchar getLen;
    uchar nTemp;

    *len = 0;
	nTemp = f_CC2500_ReadStrobe(TI_CCxxx0_RXBYTES);
	if (nTemp & TI_CCxxx0_NUM_RXBYTES)
	{
		getLen = f_CC2500_ReadReg(TI_CCxxx0_RXFIFO);//��������(�������෢�Ķ����ֽ�)
		
		if (getLen < CC2500_REV_LEN)
		{
			f_CC2500_ReadBurst(TI_CCxxx0_RXFIFO, pData, getLen); //��ȡ����,�������ֽ�Ҳ����
			f_CC2500_ReadBurst(TI_CCxxx0_RXFIFO, status, CC2500_APPEND_LEN);//read 2 appended status bytes (status[0]=RSSI,status[1]=LQI)
			f_CC2500_WriteStrobe(TI_CCxxx0_SFRX);
			if (status[TI_CCxxx0_LQI_RX] & TI_CCxxx0_CRC_OK)
			{
			    *len = getLen;
			    cc2500.bRfSleep = false; //�յ����ݻ�����������
				return true;
			}
		} 
	}
	f_CC2500_SetRevMode();
	return false;
}

/*****************************************************************************
 �� �� ��: f_CC2500_ChangeChannel
 ��������  : ����ͨ��
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: ���ݽ��յ�Ƶ���ڲ���(��Ҫʵ��)������Ҫʱ����
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_ChangeChannel(void)
{
    if (false == cc2500.bResetOK)
    {
        return;
    }
    
    if (cc2500.curChannelIndex < CC2500_MAX_CHANNEL)
    {
        cc2500.curChannelIndex++;
    }
    else
    {
        cc2500.curChannelIndex = 0;
    }
    f_CC2500_WriteStrobe(TI_CCxxx0_SIDLE);
	f_CC2500_WriteReg(TI_CCxxx0_CHANNR, cc2500.channels[cc2500.curChannelIndex]);// Channel number.
	f_CC2500_WriteStrobe(TI_CCxxx0_SCAL);//����
	f_Delay(200);
}

/*****************************************************************************
 �� �� ��: f_CC2500_StartSend
 ��������  : CC2500��������
 �������  : void  
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��1��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_StartSend(void)
{
    cc2500.needSendCnt++;
}

/*****************************************************************************
 �� �� ��: f_CC2500_SendDeal
 ��������  : CC2500���ʹ���
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: ��ѭ������
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��1��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_SendDeal(void)
{
	#define CC2500_SEND_REPET_CNT	3//�����ظ����ʹ���
	
	static uchar sendTimes = 0; //���ʹ���
	static uchar len = 0;

    if (false == cc2500.bResetOK) //��ʼ��ʧ�ܻ���δ��ɳ�ʼ��
    {
        cc2500.needSendCnt = 0;
        return;
    }

	if (cc2500.needSendCnt > 0)
	{	
		//��ȡ����(ֻ��ȡһ��)
		if (0 == sendTimes)
		{
			len = f_CC2500_GetSendBuffer(&cc2500.sendBuffer[1], sizeof(cc2500.sendBuffer) - 1);
			len ++;//�෢��һ���ֽ�,��ʾ����
			cc2500.sendBuffer[0] = len; //��һ���ֽڱ�ʾ����
			if (cc2500.bRfSleep) //���������Ȼ���
            {
                cc2500.bRfSleep = false;
			    f_CC2500_InitByChannel(cc2500.channels[cc2500.curChannelIndex]);//���³�ʼ���¼Ĵ���(���ͽ�����ģ��������)
			}
		}

		f_CC2500_SendData(cc2500.sendBuffer, len + 1); //��Ҫ�෢һ���ֽڣ�����CRCУ���������
		f_CC2500_ChangeChannel();
		
		sendTimes++;
		if (sendTimes >= (CC2500_SEND_REPET_CNT*CC2500_MAX_CHANNEL))
		{
			//���ͽ���
			sendTimes = 0;
			cc2500.needSendCnt--;	
		}
	}
}

/*****************************************************************************
 �� �� ��: f_CC2500ReciveDeal
 ��������  : CC2500���մ���
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: ��ѭ������
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��1��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_ReciveDeal(void)
{
    uchar len;
    uchar ioState;
    if (false == cc2500.bResetOK) //��ʼ��ʧ�ܻ���δ��ɳ�ʼ��
    {
        return;
    }

    ioState = CC2500_GD0;
    if (false == ioState 
    && cc2500.bLastGD0 != ioState) //�½���
    {
	    if (cc2500.needSendCnt > 0)//���������ݷ���
	    {
	        //�����������ݣ�ת����ģʽ
	        cc2500.needSendCnt = 0; 
            f_CC2500_SetRevMode();
	    }
		if(true == f_CC2500_RevData(cc2500.revBuffer, &len))
		{
		    f_CC2500_RevProtocolDeal(cc2500.revBuffer, len);
		}
    }
    cc2500.bLastGD0 = ioState;
}

/*****************************************************************************
 �� �� ��: f_CC2500_Reset
 ��������  : CC2500��λ(�ϵ�)
 �������  :
 �������  :
 �� �� ֵ: �ɹ�:true;ʧ��false
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_CC2500_Reset(void)
{
    CC2500_CLK(STATE_ON);
	CC2500_SDO(STATE_OFF);	
	f_SPIEnChip(cc2500.spi, STATE_ON);
	f_Delay(20);
	f_SPIEnChip(cc2500.spi, STATE_OFF);
	f_Delay(20000);
	f_SPIEnChip(cc2500.spi, STATE_ON);
	if (false == f_CC2500_WaitIDLE(1000))
	{
        f_SPIEnChip(cc2500.spi, STATE_OFF);
		return false;
	}
	
	f_SPIWriteData(cc2500.spi, TI_CCxxx0_SRES, 8);
	f_Delay(20000);
	if (false == f_CC2500_WaitIDLE(1000))
	{
        f_SPIEnChip(cc2500.spi, STATE_OFF);
		return false;
	}
	f_SPIEnChip(cc2500.spi, STATE_OFF);
	return true;
}

/*****************************************************************************
 �� �� ��: f_CC2500_InitByChannel
 ��������  : ͨ��ͨ����ʼ��
 �������  :
 �������  :
 �� �� ֵ: �ɹ�:true;ʧ��false
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_CC2500_InitByChannel(uchar channel)
{
    f_SPIEnChip(cc2500.spi, STATE_OFF);
    CC2500_CLK(STATE_OFF);
	CC2500_SDO(STATE_OFF);	
	
	if(false == f_CC2500_Reset())
	{
	    return false;
	}
	
	if(false == f_CC2500_ResetAllReg(channel))
	{
	    return false;
	}

	f_CC2500_WriteStrobe(TI_CCxxx0_SIDLE);
	f_CC2500_WriteStrobe(TI_CCxxx0_SCAL);//����
	cc2500.bRfSleep = false;
	return true;    
}


/*****************************************************************************
 �� �� ��: f_CC2500_Init
 ��������  : CC2500��ʼ��
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��31��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_CC2500_Init(SPI_DRIVER *spi)
{
    uchar tryCnt = 50;
    
    f_Memset(&cc2500, 0, sizeof(CC250_DRIVER));
    cc2500.spi = spi;
    cc2500.channels[0] = 6;
    cc2500.channels[1] = 66;
    cc2500.channels[2] = 126;
    cc2500.channels[3] = 186;
    
    do
    {
        if (true == f_CC2500_InitByChannel(cc2500.channels[cc2500.curChannelIndex])) //��ʼ���ɹ�
        {
            cc2500.bResetOK = true;
            break;
        }
//        f_Delay(20000);
        f_MCU_FeedDog();//ι��
    }while(tryCnt --);
}
