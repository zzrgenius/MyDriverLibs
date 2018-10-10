/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : FlashToEEPROM.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月28日 星期一
  最近修改   :
  功能描述   : flash模仿eeprom读写,注意整体数据长度不得超过一页大小(256)
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "FlashToEEPROM.h"
#include "SubFunction.h"
#include "StorageConfig.h"


/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/
uchar f_MCU_WriteToFlash(uint offset, uchar numb, const uchar *pData);
void f_MCU_ReadFromFlash(uint offset, uchar numb, uchar *pData);



/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/
typedef struct
{
    word_32 curPageAddr; //当前页地址
    word_32 curWriteAddr; //当前页写入地址(绝对地址)
    uchar pageNo; //当前有效页号
    uint useableLen; //剩余可写字长
}FLASH_STORAGE_INFO;

FLASH_STORAGE_INFO flashInfo;



/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/
const STORAGE_HARDWARE storageHardware =
{
	f_MCU_WriteToFlash,
	f_MCU_ReadFromFlash
};


/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
#define PAGE_START_ADDR 0x0800F000 //flash存储起始地址(0x08000000 + 1024*60)
#define USE_PAGE_NUMB 4u //2页用于循环读写(至少2页)
#define PAGE_SIZE 1024u //页大小1K

#define ERASED                ((word_32)0xFFFFFFFF) //当前页为空，可进行写操作
#define VALID_PAGE            ((word_32)0x00000000) //当前页正在使用

/*****************************************************************************
 函 数 名  : f_FlashReadWordData
 功能描述  : 根据地址读取flash内一个字数据
 输入参数  : word_32 addr  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
word_32 f_FlashReadWordData(word_32 addr)
{
    return *((__IO word_32*)(addr));
}

/*****************************************************************************
 函 数 名: f_FlashWriteValue
 功能描述  : 向flash写数据
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 内部用
 
 修改历史      :
  1.日    期   : 2018年5月29日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_FlashWriteValue(word_32 *pWriteAddr, uchar size, uint offset, const uchar *pData)
{
    word_32 data;
    while (size--)
	{
        data = offset;
        data <<= 16; //地址放高字节位置
        data += *pData;
        fmc_word_program(*pWriteAddr, data);
        pData++;
        offset++;
        *pWriteAddr += 4u;
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
    };
}

/*****************************************************************************
 函 数 名: f_FlashFindWritePlace
 功能描述  : 找到第一个可以写的位置
 输入参数  : uchar pageNo  
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月29日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_FlashFindWritePlace(FLASH_STORAGE_INFO *pInfo)
{
    word_32 realAddr;
    word_32 writePos;
    word_32 data;
    uchar ret = false;
    
    realAddr = PAGE_START_ADDR + (word_32)(pInfo->pageNo)*PAGE_SIZE;
    for (writePos = realAddr + 4u; writePos < realAddr + PAGE_SIZE; writePos+= 4u)//找到当前写位置
    {
        data = f_FlashReadWordData(writePos);
        if (ERASED == data) //找到首个全空位置
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
 函 数 名: f_FlashChangePage
 功能描述  : flash换页
 输入参数  : void  
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_FlashChangePage(void)
{
    uchar i;
    FLASH_STORAGE_INFO info; //目标新页信息
    word_32 data;
    uint realOffset;
    uchar index;
    uchar size;
    uchar *pData;
    const uchar *pVersion;

    info.pageNo = flashInfo.pageNo;

     fmc_unlock(); //解锁
     
    //====找到下一页====
    info.pageNo ++;
    if (info.pageNo >= USE_PAGE_NUMB)
    {
        info.pageNo = 0;    
    }

    info.curPageAddr = PAGE_START_ADDR + (word_32)(info.pageNo)*PAGE_SIZE;
    data = f_FlashReadWordData(info.curPageAddr);
    if(ERASED != data)//当前页非空
    {
        //重新初始化当前页
        fmc_page_erase(info.curPageAddr);
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);   
    }
    
    //====写所有数据到新的页====
    
    //找到可写位置(以免上次掉电没写完，但是不进行擦除)
    if (false == f_FlashFindWritePlace(&info)) //找到可写位置
    {
        fmc_page_erase(info.curPageAddr);
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
        f_FlashFindWritePlace(&info); //重找可用位置
    }
    
    //写基础地址
    f_FlashWriteValue(&info.curWriteAddr, sizeof(storageDriver.data.baseAddr), BASE_ADDR_OFFSET, (const uchar *)(&storageDriver.data.baseAddr));

    //写首次开机标志(版本信息)
    f_StorageGetVersion(&pVersion, &size);
    f_FlashWriteValue(&info.curWriteAddr, size, HEAD_OFFSET, pVersion);

    //系统数据
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

    //====目标页设置为有效页====
    fmc_word_program(info.curPageAddr, VALID_PAGE); //当前页写可用状态
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);

    //====清除当前页数据====
    fmc_page_erase(flashInfo.curPageAddr);
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);

    fmc_lock(); //上锁

    //====设置有效页参数====
    info.useableLen = (PAGE_SIZE - info.curWriteAddr)/4; //重设可用长度
    flashInfo = info;
}

/*****************************************************************************
 函 数 名  : f_FlashCheckWrite
 功能描述  : 校验并获取写信息
 输入参数  : writeNumb 写数据个数
 输出参数  : 
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_FlashCheckWrite(uchar writeNumb)
{
    if (flashInfo.useableLen < writeNumb)//当前页已经不够写
    {
        f_FlashChangePage();
    }
}

/*****************************************************************************
 函 数 名: f_FlashGetPosByOffset
 功能描述  : 根据模拟EEPROM地址，获取实际地址
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_FlashGetAddrByOffset(uint offset, word_32 *pAddr)
{
    word_32 addr;
    word_32 data;
    //从当前写地址往前找
    for (addr = flashInfo.curWriteAddr; addr > flashInfo.curPageAddr; addr -= 4u)
    {
        data = f_FlashReadWordData(addr);
        if ((uint)(data >> 16) == offset) //匹配到当前地址
        {
            *pAddr = addr;
            return true;
        }
    }
    return false;
}

/*****************************************************************************
 函 数 名  : f_MCU_WriteToFlash
 功能描述  : 向Flash存储希写入数据
 输入参数  : uint offset         
             uchar numb          
             const uchar *pData  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_MCU_WriteToFlash(uint offset, uchar numb, const uchar *pData)
{
    word_32 data; //写入的数据,包含模拟eeprom地址信息和半字数据
    fmc_state_enum ret;
    
    if (numb == 0)
	{
        return false;
	}

	//检查当前页是否够写
	f_FlashCheckWrite(numb);
    fmc_unlock();
    while (numb--)
	{
        data = offset;
        data <<= 16; //地址放高字节位置
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
 函 数 名  : f_MCU_ReadFromFlash
 功能描述  : 从flash中读取数据
 输入参数  : uint offset   
             uchar numb    
             uchar *pData  
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_MCU_ReadFromFlash(uint offset, uchar numb, uchar *pData)
{
    word_32 realAddr; //根据offset找到实际存储flash地址
    word_32 data;

    if (f_FlashGetAddrByOffset(offset, &realAddr))
    {
    	while (numb --)
        {
            //根据偏移获取数据
            data = f_FlashReadWordData(realAddr);
            *pData = (uchar)(data&0xff); //数据放在低8位
            pData++;
            realAddr += 4u;
        };
    }
    else
    {
        while (numb --)
        {
            *pData = 0xff; //返回默认值
            pData++;
        }
    }
}

/*****************************************************************************
 函 数 名  : f_FlashToEEPROMInit
 功能描述  : flash模拟eeprom初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月28日 星期一
    作    者   : 钱百静
    修改内容   : 新生成函数

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
            f_FlashFindWritePlace(&flashInfo); //找到可写位置
            break;
        }
    }

    if (0 == flashInfo.curPageAddr) //未找到有效页,默认初始化
    {
        flashInfo.curPageAddr = PAGE_START_ADDR;
        flashInfo.pageNo = 0;
        flashInfo.curWriteAddr = PAGE_START_ADDR + 4u;
        flashInfo.useableLen = PAGE_SIZE/4 - 1;
        fmc_unlock();
        fmc_word_program(PAGE_START_ADDR, VALID_PAGE); //当前页写可用状态
        fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_WPERR | FMC_FLAG_PGERR);
        fmc_lock();
    }
}
