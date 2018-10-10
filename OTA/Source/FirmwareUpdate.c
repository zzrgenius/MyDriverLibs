/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : FirmwareUpdate.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年9月12日
  最近修改   :
  功能描述   : 固件升级控制及跳转切换
  函数列表   :
  修改历史   :
  1.日    期   : 2018年9月12日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "HeadInclude.h"

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/
uchar updateBuf[FLASH_PAGE_SIZE];

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

/*****************************************************************************
 函 数 名: f_Update_Check
 功能描述  : 检查是否有升级标志
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年9月12日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_Update_Check(void)
{
    uint32_t magic_code;
    Read_Flash((unsigned char *)&magic_code, PARA_ADDR, 4);

    return (FIREWARE_UPDATE_FLAG == magic_code)?true:false;
}

/*****************************************************************************
 函 数 名: f_UpdateFirmware
 功能描述  : 升级固件
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年9月12日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_UpdateFirmware(void)
{
    uint32_t srcAddr; //固件存放地址
    uint32_t objAddr; //运行地址
    uint32_t offset; //转移偏差

    HEAD_INFO headInfo;
    uint32_t fileSize; //固件数据包大小
    uint16_t size; //每次搬运大小
    uint8_t i;
    
    if (false == f_Update_Check()) //无升级直接运行程序
    {
        return true;
    }

    //====升级流程====
    //1、读取包长
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

    //2、数据区搬移
    srcAddr = FIREWARE_ADDR_REAL;
    objAddr = FIREWARE_ADDR_APP;
    offset = 0;
    for(i = 0; i < 27; i++) //数据最大27K
    {
        if (0 != fileSize) //搬运未完成
        {
            if (fileSize > FLASH_PAGE_SIZE)
            {
            	size = FLASH_PAGE_SIZE;
            }
            else
            {
                size = fileSize; //最后一点数据
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
        else //剩余页擦除 todo:是否可以直接结束
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
 函 数 名: f_Update_JumpApp
 功能描述  : 跳转到运行程序
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年9月12日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_Update_JumpApp(void)
{
    typedef  void (*pFunction)(void);

    uint32_t *appAddr;
    pFunction Jump_To_Application;
    uint32_t JumpAddr;
    
    appAddr = (uint32_t *)FIREWARE_ADDR_APP;

    //====判断程序是否正常====
    // See if the first location is 0xfffffffff or something that does not
    // look like a stack pointer, or if the second location is 0xffffffff or
    // something that does not look like a reset vector.
    if((appAddr[0] == 0xffffffff) || ((appAddr[0] & 0xfff00000) != 0x20000000) 
    || (appAddr[1] == 0xffffffff) || ((appAddr[1] & 0xfff00001) != 0x08000001))
    {
        return;
    }

    //====跳转程序====
    JumpAddr = *(__IO uint32_t*) (FIREWARE_ADDR_APP + 4);
    Jump_To_Application = (pFunction)(JumpAddr);

    __set_MSP(*(__IO uint32_t*) FIREWARE_ADDR_APP); //设置PC指针
    Jump_To_Application();
}

/*****************************************************************************
 函 数 名: f_CheckFireware
 功能描述  : 固件完整性检测
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年9月12日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_CheckFireware(uint32_t revLen)
{
    uint32_t offset; //转移偏差
    uint32_t addr;

    HEAD_INFO headInfo;
    uint32_t fileSize; //固件数据包大小
    uint16_t size; //每次搬运大小
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

    //1、包长校验:fileSize表示真正程序大小，revLen包括头部，大小为PAGE_SIZE
    if (revLen != (fileSize + FLASH_PAGE_SIZE))
    {
        return false;
    }

    //2、头标志校验
    if (0 != strcmp(headInfo.head, "sinodod_V1"))
    {
        return false;
    } 

    //3、CRC16校验
    addr = FIREWARE_ADDR_REAL; //真正数据位置
    f_CRC16_Init();
    offset = 0;
    for(i = 0; i < 27; i++) //数据最大27K
    {
        if (0 != fileSize) //读取
        {
            if (fileSize > FLASH_PAGE_SIZE)
            {
            	size = FLASH_PAGE_SIZE;
            }
            else
            {
                size = fileSize; //最后一点数据
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


    //校验通过
    return true;
}

/*****************************************************************************
 函 数 名: f_UpdateRecFireware
 功能描述  : 接收固件
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年9月12日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_UpdateRecFireware(uchar *data, uint len, uint32_t offset)
{
    uint32_t addr;
    //固件数据处理
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
 函 数 名: f_UpdateWriteFlag
 功能描述  : 写待升级标志
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年9月12日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
uchar f_UpdateWriteFlag(void)
{
    uint32_t updateFlag = FIREWARE_UPDATE_FLAG;

    //写入升级标志
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
 函 数 名: f_UpdateCleanFlag
 功能描述  : 清升级标志
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年9月12日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_UpdateCleanFlag(void)
{
    if (f_Update_Check()) //有升级标志
    {
        Earse_Flash(PARA_ADDR);
    }
}

/*****************************************************************************
 函 数 名: f_UpdateReset
 功能描述  : 复位
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年9月12日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_UpdateReset(void)
{
    NVIC_SystemReset();
}

/*****************************************************************************
 函 数 名: f_UpdateDeal
 功能描述  : 升级
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年9月12日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_UpdateDeal(void)
{
    if (f_UpdateFirmware()) //升级成功或无需升级则跳转运行程序
    {
        f_Update_JumpApp();
    }
    else //失败则复位
    {
        f_UpdateReset();     
    }
}

