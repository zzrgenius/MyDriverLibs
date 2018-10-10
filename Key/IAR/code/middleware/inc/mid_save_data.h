/*******************************************************************************
* File         : mid_save_data.h
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2018/4/6
* Description  : 中间件:保存数据
* Change Logs  : 
*******************************************************************************/
#ifndef __MID_SAVE_DATA_20180406_H__
#define __MID_SAVE_DATA_20180406_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
#define SVAE_CONST_VALUE  0x55  // 保存的常量值,用于数据校验

// 保存数据的数据结构,根据项目不同,可以进行相应更改,但首字节(constValue)和最后的字节(checkSum),必须保留
// 注意在修改该数据结构时,需要注意默认值是否同步修改
typedef struct SaveData_Struct
{
    uint8_t  constValue; // 常量,用于校验
    uint16_t motorStepRO;  // 电机运行步数----RO阀步进电机
    uint16_t motorStepCW;  // 电机运行步数----净水阀步进电机
    uint8_t  checkSum;   // 校验和
}SaveData_t;
#define SAVE_DATA_SIZE   sizeof(SaveData_t)

// eeprom起始地址
#define EERPEOM_START_ADDR   0x4000
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void f_ReadEEPROM(SaveData_t *pSaveData, const SaveData_t DefaultSaveData, uint8_t (*pf_ReadByte)(uint32_t));

void f_EnableWriteEEPROM(void);
void f_WriteEEPROM(SaveData_t *pSaveData, void (*pf_SaveDataCallback)(uint32_t, uint8_t *, uint8_t));
/* Exported variables ------------------------------------------------------- */



#endif
