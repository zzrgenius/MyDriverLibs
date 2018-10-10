#ifndef __FIRMWAREUPDATE_H__
#define __FIRMWAREUPDATE_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"


/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
//(7+1K)+28K+28K
#define FLASH_PAGE_SIZE         1024
#define BASIC_FLASH_ADDR		0x08000000

#define OFFSET_PARA 			0x1c00 //升级参数区	偏移				  
#define OFFSET_FIRMWARE_APP		0x2000 //程序运行区 偏移
#define OFFSET_FIRMWARE_DL		0x9000 //程序下载存放区 偏移

#define PARA_ADDR				(BASIC_FLASH_ADDR + OFFSET_PARA) //升级标志参数区
#define FIREWARE_ADDR_APP 		(BASIC_FLASH_ADDR + OFFSET_FIRMWARE_APP) //程序运行区	 
#define FIREWARE_ADDR_DOWNLOAD 	(BASIC_FLASH_ADDR + OFFSET_FIRMWARE_DL) //下载数据存放区	
#define FIREWARE_ADDR_REAL      (FIREWARE_ADDR_DOWNLOAD + FLASH_PAGE_SIZE) //有效代码区(下载)

#define FIREWARE_UPDATE_FLAG	0x55555555 //升级标志

typedef struct 
{
    char head[11]; //"sinodod_V1"
    uchar crc16_L;
    uchar crc16H;

    uchar len_0;
    uchar len_1;
    uchar len_2;
    uchar len_3;
}HEAD_INFO; //升级包附带信息



/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_UpdateDeal(void);
void f_UpdateReset(void);
uchar f_UpdateWriteFlag(void);
void f_UpdateCleanFlag(void);
uchar f_UpdateRecFireware(uchar *data, uint len, uint32_t offset);
uchar f_CheckFireware(uint32_t revLen);




#endif /* __FIRMWAREUPDATE_H__ */
