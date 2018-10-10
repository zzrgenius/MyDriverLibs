/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : FirmwareUpdate.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��9��12��
  ����޸�   :
  ��������   : �̼��������Ƽ���ת�л�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��9��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "HeadInclude.h"

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
uchar updateBuf[FLASH_PAGE_SIZE];

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/

/*****************************************************************************
 �� �� ��: f_Update_Check
 ��������  : ����Ƿ���������־
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��9��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_Update_Check(void)
{
    uint32_t magic_code;
    Read_Flash((unsigned char *)&magic_code, PARA_ADDR, 4);

    return (FIREWARE_UPDATE_FLAG == magic_code)?true:false;
}

/*****************************************************************************
 �� �� ��: f_UpdateFirmware
 ��������  : �����̼�
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��9��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_UpdateFirmware(void)
{
    uint32_t srcAddr; //�̼���ŵ�ַ
    uint32_t objAddr; //���е�ַ
    uint32_t offset; //ת��ƫ��

    HEAD_INFO headInfo;
    uint32_t fileSize; //�̼����ݰ���С
    uint16_t size; //ÿ�ΰ��˴�С
    uint8_t i;
    
    if (false == f_Update_Check()) //������ֱ�����г���
    {
        return true;
    }

    //====��������====
    //1����ȡ����
    if (ERROR == Read_Flash(updateBuf, FIREWARE_ADDR_DOWNLOAD, 1024))
    {
        return false;
    }
    memcpy(&headInfo, updateBuf, sizeof(headInfo));
    fileSize = headInfo.len_3;
    fileSize <<= 8;
    fileSize += headInfo.len_2;
    fileSize <<= 8;
    fileSize += headInfo.len_1;
    fileSize <<= 8;
    fileSize += headInfo.len_0;

    //2������������
    srcAddr = FIREWARE_ADDR_REAL;
    objAddr = FIREWARE_ADDR_APP;
    offset = 0;
    for(i = 0; i < 27; i++) //�������27K
    {
        if (0 != fileSize) //����δ���
        {
            if (fileSize > FLASH_PAGE_SIZE)
            {
            	size = FLASH_PAGE_SIZE;
            }
            else
            {
                size = fileSize; //���һ������
            }

            if (Read_Flash(updateBuf, srcAddr + offset, size) == ERROR)
            {
            	return false;
            }

            if (Earse_Flash(objAddr + offset) == ERROR)
            {
            	return false;
            }

            if (Write_Flash(objAddr + offset, updateBuf, size) == ERROR)
            {
            	return false;
            }

            fileSize -= size;
        }
        else //ʣ��ҳ���� todo:�Ƿ����ֱ�ӽ���
        {
            if (Earse_Flash(objAddr + offset) == ERROR)
            {
            	return false;
            }
        }
        offset += FLASH_PAGE_SIZE;
    }

    return true;
}

/*****************************************************************************
 �� �� ��: f_Update_JumpApp
 ��������  : ��ת�����г���
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��9��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_Update_JumpApp(void)
{
    typedef  void (*pFunction)(void);

    uint32_t *appAddr;
    pFunction Jump_To_Application;
    uint32_t JumpAddr;
    
    appAddr = (uint32_t *)FIREWARE_ADDR_APP;

    //====�жϳ����Ƿ�����====
    // See if the first location is 0xfffffffff or something that does not
    // look like a stack pointer, or if the second location is 0xffffffff or
    // something that does not look like a reset vector.
    if((appAddr[0] == 0xffffffff) || ((appAddr[0] & 0xfff00000) != 0x20000000) 
    || (appAddr[1] == 0xffffffff) || ((appAddr[1] & 0xfff00001) != 0x08000001))
    {
        return;
    }

    //====��ת����====
    JumpAddr = *(__IO uint32_t*) (FIREWARE_ADDR_APP + 4);
    Jump_To_Application = (pFunction)(JumpAddr);

    __set_MSP(*(__IO uint32_t*) FIREWARE_ADDR_APP); //����PCָ��
    Jump_To_Application();
}

/*****************************************************************************
 �� �� ��: f_CheckFireware
 ��������  : �̼������Լ��
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��9��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_CheckFireware(uint32_t revLen)
{
    uint32_t offset; //ת��ƫ��
    uint32_t addr;

    HEAD_INFO headInfo;
    uint32_t fileSize; //�̼����ݰ���С
    uint16_t size; //ÿ�ΰ��˴�С
    uint16_t dataCRC;
    uint8_t i;

    addr = FIREWARE_ADDR_DOWNLOAD;
    
    if (ERROR == Read_Flash(updateBuf, addr, 1024))
    {
       return false;
    }
    memcpy(&headInfo, updateBuf, sizeof(headInfo));
    fileSize = headInfo.len_3;
    fileSize <<= 8;
    fileSize += headInfo.len_2;
    fileSize <<= 8;
    fileSize += headInfo.len_1;
    fileSize <<= 8;
    fileSize += headInfo.len_0;

    dataCRC = headInfo.crc16H;
    dataCRC <<= 8;
    dataCRC += headInfo.crc16_L;

    //1������У��:fileSize��ʾ���������С��revLen����ͷ������СΪPAGE_SIZE
    if (revLen != (fileSize + FLASH_PAGE_SIZE))
    {
        return false;
    }

    //2��ͷ��־У��
    if (0 != strcmp(headInfo.head, "sinodod_V1"))
    {
        return false;
    } 

    //3��CRC16У��
    addr = FIREWARE_ADDR_REAL; //��������λ��
    f_CRC16_Init();
    offset = 0;
    for(i = 0; i < 27; i++) //�������27K
    {
        if (0 != fileSize) //��ȡ
        {
            if (fileSize > FLASH_PAGE_SIZE)
            {
            	size = FLASH_PAGE_SIZE;
            }
            else
            {
                size = fileSize; //���һ������
            }

            if (Read_Flash(updateBuf, addr + offset, size) == ERROR)
            {
            	return false;
            }
            f_CRC16_Update(updateBuf, size);

            fileSize -= size;
            offset += size;
        }
        else 
        {
            break;
        }
    }

    if (dataCRC != f_CRC16_Final())
    {
        return false;
    }


    //У��ͨ��
    return true;
}

/*****************************************************************************
 �� �� ��: f_UpdateRecFireware
 ��������  : ���չ̼�
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��9��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_UpdateRecFireware(uchar *data, uint len, uint32_t offset)
{
    uint32_t addr;
    //�̼����ݴ���
    addr = FIREWARE_ADDR_DOWNLOAD;

    if(offset % 1024 == 0)
    {
        if(Earse_Flash(addr + offset) == ERROR)
        {
            return false;
        }
    }

    if(Write_Flash(addr + offset, data, len) == ERROR)
    {
        return false;
    }

    return true;
}

/*****************************************************************************
 �� �� ��: f_UpdateWriteFlag
 ��������  : д��������־
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��9��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_UpdateWriteFlag(void)
{
    uint32_t updateFlag = FIREWARE_UPDATE_FLAG;

    //д��������־
    if(Earse_Flash(PARA_ADDR) == ERROR)
    {
        return false;
    }
    
    if(Write_Flash(PARA_ADDR, (uchar *)&updateFlag, sizeof(updateFlag)) == ERROR)
    {
        return false;
    }
    return true;
}

/*****************************************************************************
 �� �� ��: f_UpdateCleanFlag
 ��������  : ��������־
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��9��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_UpdateCleanFlag(void)
{
    if (f_Update_Check()) //��������־
    {
        Earse_Flash(PARA_ADDR);
    }
}

/*****************************************************************************
 �� �� ��: f_UpdateReset
 ��������  : ��λ
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��9��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_UpdateReset(void)
{
    NVIC_SystemReset();
}

/*****************************************************************************
 �� �� ��: f_UpdateDeal
 ��������  : ����
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��9��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_UpdateDeal(void)
{
    if (f_UpdateFirmware()) //�����ɹ���������������ת���г���
    {
        f_Update_JumpApp();
    }
    else //ʧ����λ
    {
        f_UpdateReset();     
    }
}

