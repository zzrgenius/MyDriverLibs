/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : I2CDriver.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��17��
  ����޸�   :
  ��������   : ͨ��I2C����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "I2CDriver.h"
#include "SubFunction.h"

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
 #define MAX_READ_ACK_CNT 20
 #define IIC_MAX_WRITE_CNT 5

/*****************************************************************************
 �� �� ��: void f_I2CDriverStart(I2C_DRIVER *pDriver)
 ��������: I2C���������߲���һ����ʼ�ź�
 �������: pDriver I2C����ָ��
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_I2CDriverStart(I2C_DRIVER *pDriver)
{
    pDriver->pHardDriver->ClockOut(true);
    pDriver->pHardDriver->DataOut(true);
    pDriver->pHardDriver->SetDataDir(IO_DIR_OUT);
    pDriver->pHardDriver->DataOut(false);
    pDriver->pHardDriver->ClockOut(false);
}

/*****************************************************************************
 �� �� ��: void f_I2CDriverStop(I2C_DRIVER *pDriver)
 ��������: I2C���������߲���һ��ֹͣ�ź�
 �������: pDriver I2C����ָ��
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_I2CDriverStop(I2C_DRIVER *pDriver)
{
    pDriver->pHardDriver->DataOut(false);
    pDriver->pHardDriver->SetDataDir(IO_DIR_OUT);
    pDriver->pHardDriver->ClockOut(true);
    pDriver->pHardDriver->DataOut(true);
}

/*****************************************************************************
 �� �� ��: void f_I2CDriverWriteAck(I2C_DRIVER *pDriver, I2C_DRIVER_ACK_TYPE ack)
 ��������: I2C���������߲���һ��Ӧ���ź�
 �������: pDriver I2C����ָ��
 		   ack Ӧ���ź�
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_I2CDriverWriteAck(I2C_DRIVER *pDriver, I2C_DRIVER_ACK_TYPE ack)
{
	if(I2C_DRIVER_ACK == ack)//Ӧ������������͵�ƽ
	{
		pDriver->pHardDriver->DataOut(false);
	}
	else//Ӧ�������������ߵ�ƽ
	{
		pDriver->pHardDriver->DataOut(true);
	}
	pDriver->pHardDriver->SetDataDir(IO_DIR_OUT);
	pDriver->pHardDriver->ClockOut(true);
	pDriver->pHardDriver->ClockOut(false);
}

/*****************************************************************************
 �� �� ��: void f_I2CDriverWriteByte(I2C_DRIVER *pDriver, uchar data)
 ��������: ��I2C����дһ���ֽ�����
 �������: pDriver I2C����ָ��
 		   data д������
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_I2CDriverWriteByte(I2C_DRIVER *pDriver, uchar data)
{
    uchar i;

	pDriver->pHardDriver->ClockOut(false);
	pDriver->pHardDriver->SetDataDir(IO_DIR_OUT);
	for (i = 0; i < 8; i++)
	{
		if ((data<<i)&0x80)
		{
			pDriver->pHardDriver->DataOut(true);
		}
		else
		{
			pDriver->pHardDriver->DataOut(false);
		}
		pDriver->pHardDriver->ClockOut(true);
		pDriver->pHardDriver->ClockOut(false);
	}
}

/*****************************************************************************
 �� �� ��: uchar f_I2CDriverReadAck(I2C_DRIVER *pDriver)
 ��������: I2C���������߲���һ��Ӧ���ź�
 �������: pDriver I2C����ָ��
 �� �� ֵ: true:��ȡ��Ӧ��;false:δ��ȡ��Ӧ���ź�
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_I2CDriverReadAck(I2C_DRIVER *pDriver)
{
	uchar tryCnt = 0;
	uchar ret = true;
	
	pDriver->pHardDriver->ClockOut(false);
	pDriver->pHardDriver->SetDataDir(IO_DIR_IN);
	pDriver->pHardDriver->ClockOut(true);
	while(pDriver->pHardDriver->DataIn())
	{
		pDriver->pHardDriver->Delay();
		tryCnt ++;
		if(tryCnt > MAX_READ_ACK_CNT)
		{
			ret = false;
			break;
		}
	};
	pDriver->pHardDriver->ClockOut(false);
	return ret;
}

/*****************************************************************************
 �� �� ��: f_I2CDriverReadByte
 ��������: pDriver I2C����ָ��
 �������: ��ȡ����
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_I2CDriverReadByte(I2C_DRIVER* pDriver)
{
    uchar i;
    uchar data = 0;

	pDriver->pHardDriver->ClockOut(false);
	pDriver->pHardDriver->SetDataDir(IO_DIR_IN);
	for (i = 0; i < 8; i++)
	{
		pDriver->pHardDriver->ClockOut(true);
		data <<= 1;
		data |= pDriver->pHardDriver->DataIn();
		pDriver->pHardDriver->ClockOut(false);
	}
	return data;
}

uchar f_I2CDriverWriteSlaveAddr(I2C_DRIVER* pDriver, uchar slaveAddr)
{
	uchar tryCnt = 0;
	uchar ret = true;
	do
	{
		//д������ַ
		f_I2CDriverStop(pDriver);
		f_I2CDriverStart(pDriver);
		f_I2CDriverWriteByte(pDriver, slaveAddr);

		if((++tryCnt) > IIC_MAX_WRITE_CNT)
		{
			ret = false;
			break;
		}
	}while(false == f_I2CDriverReadAck(pDriver));
	return ret;
}

/*****************************************************************************
 �� �� ��: uchar f_I2CDriverWriteSlaveByte(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar data)
 ��������: �������ϵ��豸д��һ���ֽ�����
 �������: pDriver I2C����ָ��
 		   slaveAddr ������ַ
 		   dataAddr ���ݵ�ַ
 		   data д������
 �� �� ֵ: true:д��ɹ�;false:д��ʧ��
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_I2CDriverWriteSlaveByte(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar data)
{
    slaveAddr &= 0xFE;//����Ϊд
	f_I2CDriverWriteSlaveAddr(pDriver, slaveAddr);//д������ַ
	f_I2CDriverWriteByte(pDriver, dataAddr);//д�����ݵ�ַ
	if(false == f_I2CDriverReadAck(pDriver))//�ж�ACK
	{
		return false;
	}
	
	f_I2CDriverWriteByte(pDriver, data);//д������
	if(false == f_I2CDriverReadAck(pDriver))//�ж�ACK
	{
		return false;
	}
	f_I2CDriverStop(pDriver);//����ֹͣλ
	return true;
}

/*****************************************************************************
 �� �� ��: uchar f_I2CDriverReadSlaveByte(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData)
 ��������: �������ϵ��豸��ȡһ���ֽ�����
 �������: pDriver I2C����ָ��
 		   slaveAddr ������ַ
 		   dataAddr ���ݵ�ַ
 		   pData ��ȡ���ݻ���ָ��
 �� �� ֵ: true:��ȡ�ɹ�;false:��ȡʧ��
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_I2CDriverReadSlaveByte(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData)
{
    slaveAddr &= 0xFE;//����Ϊд
	f_I2CDriverWriteSlaveAddr(pDriver, slaveAddr);//д������ַ
	f_I2CDriverWriteByte(pDriver, dataAddr);//д�����ݵ�ַ
	if(false == f_I2CDriverReadAck(pDriver))//�ж�ACK
	{
		return false;
	}
	
	slaveAddr |= 0x01;//����Ϊ��
	f_I2CDriverStart(pDriver);//����һ����ʼλ
	f_I2CDriverWriteByte(pDriver, slaveAddr);//д�������
	if(false == f_I2CDriverReadAck(pDriver))//�ж�ACK
	{
		return false;
	}
	*pData = f_I2CDriverReadByte(pDriver);
	f_I2CDriverWriteAck(pDriver, I2C_DRIVER_NO_ACK);//дӦ���ź�
	f_I2CDriverStop(pDriver);//����ֹͣλ
	return true;
}

/*****************************************************************************
 �� �� ��: uchar f_I2CDriverWriteSlaveBytes(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData, uint length)
 ��������: �������ϵ��豸����д�����ֽ�����
 �������: pDriver I2C����ָ��
 		   slaveAddr ������ַ
 		   dataAddr ���ݵ�ַ
 		   pData д�����ݻ����ַ
 		   length ����
 �� �� ֵ: true:д��ɹ�;false:д��ʧ��
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_I2CDriverWriteSlaveBytes(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData, uint length)
{
	uint i;
	
    slaveAddr &= 0xFE;//����Ϊд
	f_I2CDriverWriteSlaveAddr(pDriver, slaveAddr);//д������ַ
	f_I2CDriverWriteByte(pDriver, dataAddr);//д�����ݵ�ַ
	if(false == f_I2CDriverReadAck(pDriver))//�ж�ACK
	{
		return false;
	}

	for(i = 0; i < length; i++)
	{
		//pDriver->pHardDriver->FreeDog();
		f_I2CDriverWriteByte(pDriver, pData[i]);//д������
		if(false == f_I2CDriverReadAck(pDriver))//�ж�ACK
		{
			return false;
		}
	}
	
	f_I2CDriverStop(pDriver);//����ֹͣλ
	return true;
}

/*****************************************************************************
 �� �� ��: uchar f_I2CDriverReadSlaveBytes(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData)
 ��������: �������ϵ��豸��ȡһ���ֽ�����
 �������: pDriver I2C����ָ��
 		   slaveAddr ������ַ
 		   dataAddr ���ݵ�ַ
 		   pData ��ȡ���ݻ���ָ��
 �� �� ֵ: true:��ȡ�ɹ�;false:��ȡʧ��
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_I2CDriverReadSlaveBytes(I2C_DRIVER *pDriver, uchar slaveAddr, uchar dataAddr, uchar *pData, uchar length)
{
	uint i;
	
    slaveAddr &= 0xFE;//����Ϊд
	f_I2CDriverWriteSlaveAddr(pDriver, slaveAddr);//д������ַ
	f_I2CDriverWriteByte(pDriver, dataAddr);//д�����ݵ�ַ
	if(false == f_I2CDriverReadAck(pDriver))//�ж�ACK
	{
		return false;
	}
	
	slaveAddr |= 0x01;//����Ϊ��
	f_I2CDriverStart(pDriver);//����һ����ʼλ
	f_I2CDriverWriteByte(pDriver, slaveAddr);//д�������
	if(false == f_I2CDriverReadAck(pDriver))//�ж�ACK
	{
		return false;
	}

	for(i = 0;i < length;i ++)
	{
		//pDriver->pHardDriver->FreeDog();
		pData[i] = f_I2CDriverReadByte(pDriver);
		if (i < (length - 1))//�����һ��������
		{
			f_I2CDriverWriteAck(pDriver, I2C_DRIVER_ACK);//дӦ���ź�
		}
	}
	f_I2CDriverWriteAck(pDriver, I2C_DRIVER_NO_ACK);//дӦ���ź�
	f_I2CDriverStop(pDriver);//����ֹͣλ
	return true;
}

/*****************************************************************************
 �� �� ��: f_I2CDriverInit
 ��������  : I2C������ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��17��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_I2CDriverInit(I2C_DRIVER *pDriver, const I2C_HARDWARE_DRIVER *pHardware)
{
	f_Memset(pDriver, 0, sizeof(I2C_DRIVER));
    pDriver->pHardDriver = pHardware;
}

