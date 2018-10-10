/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : CommHardware.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��8��
  ����޸�   :
  ��������   : ͨ��Ӳ�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��8��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "CommHardware.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                       *
 *----------------------------------------------*/


/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                                     *
 *----------------------------------------------*/
void f_UART1_SatrtSend(COMM_DRIVER *pDriver);
void f_UART1_SetRevInterrupt(uchar en);
void f_UART1_SetSendInterrupt(uchar en);
void f_UART1_ChangeBaudRate(word_32 baudRate);


void f_UART2_SatrtSend(COMM_DRIVER *pDriver);
void f_UART2_SetRevInterrupt(uchar en);
void f_UART2_SetSendInterrupt(uchar en);
void f_UART2_ChangeBaudRate(word_32 baudRate);

/*----------------------------------------------*
 * ȫ�ֱ���                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/
//����0Ӳ����Ϣ(wifi)
const COMM_HARDWARE uart1Hardware =
{
	15, //��֡�������,��λ1ms
	20, //֡���ͼ��,��λ1ms
	5, //���ֽڷ��ͳ�ʱʱ��,��λ1ms
	100, //�ȴ�Ӧ��ʱʱ��,��λ1ms
	f_UART1_SetSendInterrupt,
	f_UART1_SetRevInterrupt,
	f_UART1_SatrtSend,
	f_UART1_ChangeBaudRate //�޸ù��ܻ����趯̬�޸Ŀ�����ΪNULL(���ϲ�������С����������)
};

//����1Ӳ����Ϣ(����ģ��\ת��)
const COMM_HARDWARE uart2Hardware =
{
	15, //��֡�������,��λ1ms
	20, //֡���ͼ��,��λ1ms
	10, //���ֽڷ��ͳ�ʱʱ��,��λ1ms
	50, //�ȴ�Ӧ��ʱʱ��,��λ1ms
	f_UART2_SetSendInterrupt,
	f_UART2_SetRevInterrupt,
	f_UART2_SatrtSend,
	f_UART2_ChangeBaudRate //�޸ù��ܻ����趯̬�޸Ŀ�����ΪNULL(���ϲ�������С����������)
};

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/

//====UART1====

//�������ͺ���
void f_UART1_SatrtSend(COMM_DRIVER *pDriver)
{
	pDriver->sendData.curSendNum = 0;
	usart_data_transmit(USART0, pDriver->sendData.pBuffer->pBuffer[pDriver->sendData.curSendNum]); //���͵�һ������
	if (pDriver->pHardware->SetSendInterrupt)
	{
		pDriver->pHardware->SetSendInterrupt(true); //ʹ�ܷ���
	}
}

//��������
void f_UART1_SendData(COMM_DRIVER *pDriver)
{
	if (COMM_SEND_STATE_SENDING == pDriver->sendData.sendState)
	{
		pDriver->sendData.curSendNum ++;
		if (pDriver->sendData.curSendNum >= pDriver->sendData.needSendNum)
		{
			pDriver->sendData.curSendNum = 0;
			pDriver->sendData.sendState = COMM_SEND_STATE_OVER;
			if (pDriver->pHardware->SetSendInterrupt)
			{
				pDriver->pHardware->SetSendInterrupt(false); 
			}
		}
		else
		{
			usart_data_transmit(USART0, pDriver->sendData.pBuffer->pBuffer[pDriver->sendData.curSendNum]);
		}
	}
	else 
	{
        if (pDriver->pHardware->SetSendInterrupt)
    	{
    		pDriver->pHardware->SetSendInterrupt(false); 
    	}
	}
	pDriver->sendData.noSendTm = 0;
}

//��������
uchar f_UART1_ReceByte(void)
{
	return (uchar)usart_data_receive(USART0);
}

void f_UART1_RevData(COMM_DRIVER *pDriver)
{
	uchar iTempRceData;
	iTempRceData = f_UART1_ReceByte();
	if (pDriver->revData.curRevNum < pDriver->revData.pBuffer->size)
	{
		pDriver->revData.pBuffer->pBuffer[pDriver->revData.curRevNum] = iTempRceData;
		pDriver->revData.curRevNum ++;
	}
	else
	{
		pDriver->revData.revState = COMM_REV_STATE_OVER;
		if (pDriver->pHardware->SetRecInterrupt)
		{
			//��������,�ʴ����ʱ����չر�
			pDriver->pHardware->SetRecInterrupt(false);
		}
	}
	pDriver->revData.noRevTm = 0;
}

//����������
void f_UART1_ChangeBaudRate(word_32 baudRate)
{
    //����˳�������ע��
    usart_interrupt_disable(USART0, USART_INT_TC); //�����жϹر�
    usart_interrupt_disable(USART0, USART_INT_RBNE); //�����жϹر�
    usart_disable(USART0); //�رմ���
    usart_baudrate_set(USART0, baudRate); //����������
    usart_enable(USART0); //�򿪴���
    usart_interrupt_enable(USART0, USART_INT_RBNE); //���ջ���ǿ��ж�
    usart_interrupt_enable(USART0, USART_INT_TC); //�������ʹ��
}


//�ж�����
void f_UART1_SetSendInterrupt(uchar en)
{
    if (en)
    {
        usart_interrupt_enable(USART0, USART_INT_TC); //��������ж�
    }
    else
    {
        usart_interrupt_disable(USART0, USART_INT_TC); //��������ж�
    }
}

void f_UART1_SetRevInterrupt(uchar en)
{
    if (en)
    {
        usart_interrupt_enable(USART0, USART_INT_RBNE); //���շǿ��ж�
    }
    else
    {
        usart_interrupt_disable(USART0, USART_INT_RBNE); //���շǿ��ж�
    }
}



//====UART2====

//�������ͺ���
void f_UART2_SatrtSend(COMM_DRIVER *pDriver)
{
	pDriver->sendData.curSendNum = 0;
	usart_data_transmit(USART1, pDriver->sendData.pBuffer->pBuffer[pDriver->sendData.curSendNum]); //���͵�һ������
	if (pDriver->pHardware->SetSendInterrupt)
	{
		pDriver->pHardware->SetSendInterrupt(true); //ʹ�ܷ���
	}
}

//��������
void f_UART2_SendData(COMM_DRIVER *pDriver)
{
	if (COMM_SEND_STATE_SENDING == pDriver->sendData.sendState)
	{
		pDriver->sendData.curSendNum ++;
		if (pDriver->sendData.curSendNum >= pDriver->sendData.needSendNum)
		{
			pDriver->sendData.curSendNum = 0;
			pDriver->sendData.sendState = COMM_SEND_STATE_OVER;
			if (pDriver->pHardware->SetSendInterrupt)
			{
				pDriver->pHardware->SetSendInterrupt(false); 
			}
		}
		else
		{
			usart_data_transmit(USART1, pDriver->sendData.pBuffer->pBuffer[pDriver->sendData.curSendNum]);
		}
	}
	else
	{
        if (pDriver->pHardware->SetSendInterrupt)
		{
			pDriver->pHardware->SetSendInterrupt(false); 
		}
	}
	pDriver->sendData.noSendTm = 0;
}

//��������
uchar f_UART2_ReceByte(void)
{
	return (uchar)usart_data_receive(USART1);
}

void f_UART2_RevData(COMM_DRIVER *pDriver)
{
	uchar iTempRceData;
	iTempRceData = f_UART2_ReceByte();
	if (pDriver->revData.curRevNum < pDriver->revData.pBuffer->size)
	{
		pDriver->revData.pBuffer->pBuffer[pDriver->revData.curRevNum] = iTempRceData;
		pDriver->revData.curRevNum ++;
	}
	else
	{
		pDriver->revData.revState = COMM_REV_STATE_OVER;
		if (pDriver->pHardware->SetRecInterrupt)
		{
			//��������,�ʴ����ʱ����չر�
			pDriver->pHardware->SetRecInterrupt(false);
		}
	}
	pDriver->revData.noRevTm = 0;
}

//����������
void f_UART2_ChangeBaudRate(word_32 baudRate)
{
    //����˳�������ע��
    usart_interrupt_disable(USART1, USART_INT_TC); //�����жϹر�
    usart_interrupt_disable(USART1, USART_INT_RBNE); //�����жϹر�
    usart_disable(USART1); //�رմ���
    usart_baudrate_set(USART1, baudRate); //����������
    usart_enable(USART1); //�򿪴���
    usart_interrupt_enable(USART1, USART_INT_RBNE); //���ջ���ǿ��ж�
    usart_interrupt_enable(USART1, USART_INT_TC); //�������ʹ��
    
}


//�ж�����
void f_UART2_SetSendInterrupt(uchar en)
{
    if (en)
    {
        usart_interrupt_enable(USART1, USART_INT_TC); //��������ж�
    }
    else
    {
        usart_interrupt_disable(USART1, USART_INT_TC); //��������ж�
    }
}

void f_UART2_SetRevInterrupt(uchar en)
{
    if (en)
    {
        usart_interrupt_enable(USART1, USART_INT_RBNE); //���շǿ��ж�
    }
    else
    {
        usart_interrupt_disable(USART1, USART_INT_RBNE); //���շǿ��ж�
    }
}




