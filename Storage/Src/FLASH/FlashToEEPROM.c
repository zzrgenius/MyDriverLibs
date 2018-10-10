/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : FlashToEEPROM.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��28�� ����һ
  ����޸�   :
  ��������   : flashģ��eeprom��д,ע���������ݳ��Ȳ��ó���һҳ��С(256)
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��28�� ����һ
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "FlashToEEPROM.h"
#include "SubFunction.h"
#include "StorageConfig.h"


/*----------------------------------------------*
 * �ⲿ����˵��                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                                     *
 *----------------------------------------------*/
uchar f_MCU_WriteToFlash(uint offset, uchar numb, const uchar *pData);
void f_MCU_ReadFromFlash(uint offset, uchar numb, uchar *pData);



/*----------------------------------------------*
 * ȫ�ֱ���                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/
typedef struct
{
    word_32 curPageAddr; //��ǰҳ��ַ
    word_32 curWriteAddr; //��ǰҳд���ַ(���Ե�ַ)
    uchar pageNo; //��ǰ��Чҳ��
    uint useableLen; //ʣ���д�ֳ�
}FLASH_STORAGE_INFO;

FLASH_STORAGE_INFO flashInfo;



/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/
const STORAGE_HARDWARE storageHardware =
{
	f_MCU_WriteToFlash,
	f_MCU_ReadFromFlash
};


/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define PAGE_START_ADDR 0x0800F000 //flash�洢��ʼ��ַ(0x08000000 + 1024*60)
#define USE_PAGE_NUMB 4u //2ҳ����ѭ����д(����2ҳ)
#define PAGE_SIZE 1024u //ҳ��С1K

#define ERASED                ((word_32)0xFFFFFFFF) //��ǰҳΪ�գ��ɽ���д����
#define VALID_PAGE            ((word_32)0x00000000) //��ǰҳ����ʹ��

/*****************************************************************************
 �� �� ��  : f_FlashReadWordData
 ��������  : ���ݵ�ַ��ȡflash��һ��������
 �������  : word_32 addr  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��28�� ����һ
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
word_32 f_FlashReadWordData(word_32 addr)
{
    return *((__IO word_32*)(addr));
}

/*****************************************************************************
 �� �� ��: f_FlashWriteValue
 ��������  : ��flashд����
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: �ڲ���
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��29��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_FlashWriteValue(word_32 *pWriteAddr, uchar size, uint offset, const uchar *pData)
{
    word_32 data;
    while (size--)
	{
        data = offset;
        data <<= 16; //��ַ�Ÿ��ֽ�λ��
        data += *pData;
        fmc_word_program(*pWriteAddr, data);
        pData++;
        offset++;
        *pWriteAddr += 4u;
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    };
}

/*****************************************************************************
 �� �� ��: f_FlashFindWritePlace
 ��������  : �ҵ���һ������д��λ��
 �������  : uchar pageNo  
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��29��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_FlashFindWritePlace(FLASH_STORAGE_INFO *pInfo)
{
    word_32 realAddr;
    word_32 writePos;
    word_32 data;
    uchar ret = false;
    
    realAddr = PAGE_START_ADDR + (word_32)(pInfo->pageNo)*PAGE_SIZE;
    for (writePos = realAddr + 4u; writePos < realAddr + PAGE_SIZE; writePos+= 4u)//�ҵ���ǰдλ��
    {
        data = f_FlashReadWordData(writePos);
        if (ERASED == data) //�ҵ��׸�ȫ��λ��
        {
            pInfo->curWriteAddr = writePos;
            pInfo->useableLen = (PAGE_SIZE - (writePos - realAddr))/4;
            ret = true;
            break;
        }
    }
    return ret;
}


/*****************************************************************************
 �� �� ��: f_FlashChangePage
 ��������  : flash��ҳ
 �������  : void  
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��28�� ����һ
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_FlashChangePage(void)
{
    uchar i;
    FLASH_STORAGE_INFO info; //Ŀ����ҳ��Ϣ
    word_32 data;
    uint realOffset;
    uchar index;
    uchar size;
    uchar *pData;
    const uchar *pVersion;

    info.pageNo = flashInfo.pageNo;

     fmc_unlock(); //����
     
    //====�ҵ���һҳ====
    info.pageNo ++;
    if (info.pageNo >= USE_PAGE_NUMB)
    {
        info.pageNo = 0;    
    }

    info.curPageAddr = PAGE_START_ADDR + (word_32)(info.pageNo)*PAGE_SIZE;
    data = f_FlashReadWordData(info.curPageAddr);
    if(ERASED != data)//��ǰҳ�ǿ�
    {
        //���³�ʼ����ǰҳ
        fmc_page_erase(info.curPageAddr);
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);   
    }
    
    //====д�������ݵ��µ�ҳ====
    
    //�ҵ���дλ��(�����ϴε���ûд�꣬���ǲ����в���)
    if (false == f_FlashFindWritePlace(&info)) //�ҵ���дλ��
    {
        fmc_page_erase(info.curPageAddr);
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
        f_FlashFindWritePlace(&info); //���ҿ���λ��
    }
    
    //д������ַ
    f_FlashWriteValue(&info.curWriteAddr, sizeof(storageDriver.data.baseAddr), BASE_ADDR_OFFSET, (const uchar *)(&storageDriver.data.baseAddr));

    //д�״ο�����־(�汾��Ϣ)
    f_StorageGetVersion(&pVersion, &size);
    f_FlashWriteValue(&info.curWriteAddr, size, HEAD_OFFSET, pVersion);

    //ϵͳ����
    for (index = 0; index < TOTAL_STORAGE_SIZE; index++)
    {
        realOffset = storageDriver.data.baseAddr;
        for (i = 0; i < index; i++)
        {
            realOffset += tab_StorageValue[i].valueSize;
        }
        size = tab_StorageValue[index].valueSize;
        pData = (uchar *)(tab_StorageValue[index].pValue);
        f_FlashWriteValue(&info.curWriteAddr, size, realOffset, pData);
    }

    //====Ŀ��ҳ����Ϊ��Чҳ====
    fmc_word_program(info.curPageAddr, VALID_PAGE); //��ǰҳд����״̬
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);

    //====�����ǰҳ����====
    fmc_page_erase(flashInfo.curPageAddr);
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);

    fmc_lock(); //����

    //====������Чҳ����====
    info.useableLen = (PAGE_SIZE - info.curWriteAddr)/4; //������ó���
    flashInfo = info;
}

/*****************************************************************************
 �� �� ��  : f_FlashCheckWrite
 ��������  : У�鲢��ȡд��Ϣ
 �������  : writeNumb д���ݸ���
 �������  : 
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��28�� ����һ
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_FlashCheckWrite(uchar writeNumb)
{
    if (flashInfo.useableLen < writeNumb)//��ǰҳ�Ѿ�����д
    {
        f_FlashChangePage();
    }
}

/*****************************************************************************
 �� �� ��: f_FlashGetPosByOffset
 ��������  : ����ģ��EEPROM��ַ����ȡʵ�ʵ�ַ
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��28�� ����һ
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_FlashGetAddrByOffset(uint offset, word_32 *pAddr)
{
    word_32 addr;
    word_32 data;
    //�ӵ�ǰд��ַ��ǰ��
    for (addr = flashInfo.curWriteAddr; addr > flashInfo.curPageAddr; addr -= 4u)
    {
        data = f_FlashReadWordData(addr);
        if ((uint)(data >> 16) == offset) //ƥ�䵽��ǰ��ַ
        {
            *pAddr = addr;
            return true;
        }
    }
    return false;
}

/*****************************************************************************
 �� �� ��  : f_MCU_WriteToFlash
 ��������  : ��Flash�洢ϣд������
 �������  : uint offset         
             uchar numb          
             const uchar *pData  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��28�� ����һ
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_MCU_WriteToFlash(uint offset, uchar numb, const uchar *pData)
{
    word_32 data; //д�������,����ģ��eeprom��ַ��Ϣ�Ͱ�������
    fmc_state_enum ret;
    
    if (numb == 0)
	{
        return false;
	}

	//��鵱ǰҳ�Ƿ�д
	f_FlashCheckWrite(numb);
    fmc_unlock();
    while (numb--)
	{
        data = offset;
        data <<= 16; //��ַ�Ÿ��ֽ�λ��
        data += *pData;
        ret = fmc_word_program(flashInfo.curWriteAddr, data);
        pData++;
        offset++;
        flashInfo.curWriteAddr += 4u;
        f_DecU16Data(&flashInfo.useableLen);
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    };
    fmc_lock();

    return FMC_READY == ret?true:false;
}

/*****************************************************************************
 �� �� ��  : f_MCU_ReadFromFlash
 ��������  : ��flash�ж�ȡ����
 �������  : uint offset   
             uchar numb    
             uchar *pData  
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��28�� ����һ
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_MCU_ReadFromFlash(uint offset, uchar numb, uchar *pData)
{
    word_32 realAddr; //����offset�ҵ�ʵ�ʴ洢flash��ַ
    word_32 data;

    if (f_FlashGetAddrByOffset(offset, &realAddr))
    {
    	while (numb --)
        {
            //����ƫ�ƻ�ȡ����
            data = f_FlashReadWordData(realAddr);
            *pData = (uchar)(data&0xff); //���ݷ��ڵ�8λ
            pData++;
            realAddr += 4u;
        };
    }
    else
    {
        while (numb --)
        {
            *pData = 0xff; //����Ĭ��ֵ
            pData++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : f_FlashToEEPROMInit
 ��������  : flashģ��eeprom��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��28�� ����һ
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
void f_FlashToEEPROMInit(void)
{
    word_32 i;
    word_32 data;
    word_32 realAddr;
    
    for (i = 0; i < USE_PAGE_NUMB; i++)
    {
        realAddr = PAGE_START_ADDR + i*PAGE_SIZE;
        data = f_FlashReadWordData(realAddr);
        if (VALID_PAGE == data)
        {
            flashInfo.curPageAddr = realAddr;
            flashInfo.pageNo = (uchar)i;
            f_FlashFindWritePlace(&flashInfo); //�ҵ���дλ��
            break;
        }
    }

    if (0 == flashInfo.curPageAddr) //δ�ҵ���Чҳ,Ĭ�ϳ�ʼ��
    {
        flashInfo.curPageAddr = PAGE_START_ADDR;
        flashInfo.pageNo = 0;
        flashInfo.curWriteAddr = PAGE_START_ADDR + 4u;
        flashInfo.useableLen = PAGE_SIZE/4 - 1;
        fmc_unlock();
        fmc_word_program(PAGE_START_ADDR, VALID_PAGE); //��ǰҳд����״̬
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
        fmc_lock();
    }
}
