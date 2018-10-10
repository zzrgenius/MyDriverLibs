#ifndef __FIRMWAREUPDATE_H__
#define __FIRMWAREUPDATE_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"


/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
//(7+1K)+28K+28K
#define FLASH_PAGE_SIZE         1024
#define BASIC_FLASH_ADDR		0x08000000

#define OFFSET_PARA 			0x1c00 //����������	ƫ��				  
#define OFFSET_FIRMWARE_APP		0x2000 //���������� ƫ��
#define OFFSET_FIRMWARE_DL		0x9000 //�������ش���� ƫ��

#define PARA_ADDR				(BASIC_FLASH_ADDR + OFFSET_PARA) //������־������
#define FIREWARE_ADDR_APP 		(BASIC_FLASH_ADDR + OFFSET_FIRMWARE_APP) //����������	 
#define FIREWARE_ADDR_DOWNLOAD 	(BASIC_FLASH_ADDR + OFFSET_FIRMWARE_DL) //�������ݴ����	
#define FIREWARE_ADDR_REAL      (FIREWARE_ADDR_DOWNLOAD + FLASH_PAGE_SIZE) //��Ч������(����)

#define FIREWARE_UPDATE_FLAG	0x55555555 //������־

typedef struct 
{
    char head[11]; //"sinodod_V1"
    uchar crc16_L;
    uchar crc16H;

    uchar len_0;
    uchar len_1;
    uchar len_2;
    uchar len_3;
}HEAD_INFO; //������������Ϣ



/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_UpdateDeal(void);
void f_UpdateReset(void);
uchar f_UpdateWriteFlag(void);
void f_UpdateCleanFlag(void);
uchar f_UpdateRecFireware(uchar *data, uint len, uint32_t offset);
uchar f_CheckFireware(uint32_t revLen);




#endif /* __FIRMWAREUPDATE_H__ */
