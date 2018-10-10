/*******************************************************************************
  * @file    stm8s_flash.h
  * @author  钟昊翰
  * @version V1.0.0
  * @date    2017-09-26
  * @brief   该头文件为flash文件
*******************************************************************************/

#ifndef __STM8S_FLASH_H__
#define __STM8S_FLASH_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/**
  * @brief  FLASH fixed programming time
  */
typedef enum
{
    FLASH_PROGRAMTIME_STANDARD = (uint8_t)0x00, /*!< Standard programming time fixed at 1/2 tprog */
    FLASH_PROGRAMTIME_TPROG    = (uint8_t)0x01  /*!< Programming time fixed at tprog */
} FLASH_ProgramTime_TypeDef;

/**
  * @brief  FLASH Memory types
  */
typedef enum {
    FLASH_MEMTYPE_PROG      = (uint8_t)0xFD, /*!< Program memory */
    FLASH_MEMTYPE_DATA      = (uint8_t)0xF7  /*!< Data EEPROM memory */
} FLASH_MemType_TypeDef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define FLASH_PROG_START_PHYSICAL_ADDRESS ((uint32_t)0x008000) /*!< Program memory: start address */

#if defined (STM8S208) || defined(STM8S207) || defined(STM8S007) || defined (STM8AF52Ax) || defined (STM8AF62Ax)
 #define FLASH_PROG_END_PHYSICAL_ADDRESS   ((uint32_t)0x027FFF) /*!< Program memory: end address */
 #define FLASH_PROG_BLOCKS_NUMBER          ((uint16_t)1024)     /*!< Program memory: total number of blocks */
 #define FLASH_DATA_START_PHYSICAL_ADDRESS ((uint32_t)0x004000) /*!< Data EEPROM memory: start address */
 #define FLASH_DATA_END_PHYSICAL_ADDRESS   ((uint32_t)0x0047FF) /*!< Data EEPROM memory: end address */
 #define FLASH_DATA_BLOCKS_NUMBER          ((uint16_t)16)       /*!< Data EEPROM memory: total number of blocks */
 #define FLASH_BLOCK_SIZE                  ((uint8_t)128)       /*!< Number of bytes in a block (common for Program and Data memories) */
#endif /* STM8S208, STM8S207, STM8S007, STM8AF52Ax, STM8AF62Ax */

#if defined(STM8S105) || defined(STM8S005) || defined(STM8AF626x)
 #define FLASH_PROG_END_PHYSICAL_ADDRESS   ((uint32_t)0xFFFF)   /*!< Program memory: end address */
 #define FLASH_PROG_BLOCKS_NUMBER          ((uint16_t)256)      /*!< Program memory: total number of blocks */
 #define FLASH_DATA_START_PHYSICAL_ADDRESS ((uint32_t)0x004000) /*!< Data EEPROM memory: start address */
 #define FLASH_DATA_END_PHYSICAL_ADDRESS   ((uint32_t)0x0043FF) /*!< Data EEPROM memory: end address */
 #define FLASH_DATA_BLOCKS_NUMBER          ((uint16_t)8)        /*!< Data EEPROM memory: total number of blocks */
 #define FLASH_BLOCK_SIZE                  ((uint8_t)128)       /*!< Number of bytes in a block (common for Program and Data memories) */
#endif /* STM8S105 or STM8AF626x */

#if defined(STM8S103) || defined(STM8S003) || defined(STM8S903) || defined(STM8AF622x)
 #define FLASH_PROG_END_PHYSICAL_ADDRESS   ((uint32_t)0x9FFF)   /*!< Program memory: end address */
 #define FLASH_PROG_BLOCKS_NUMBER          ((uint16_t)128)      /*!< Program memory: total number of blocks */
 #define FLASH_DATA_START_PHYSICAL_ADDRESS ((uint32_t)0x004000) /*!< Data EEPROM memory: start address */
 #define FLASH_DATA_END_PHYSICAL_ADDRESS   ((uint32_t)0x00427F) /*!< Data EEPROM memory: end address */
 #define FLASH_DATA_BLOCKS_NUMBER          ((uint16_t)10)       /*!< Data EEPROM memory: total number of blocks */
 #define FLASH_BLOCK_SIZE                  ((uint8_t)64)        /*!< Number of bytes in a block (common for Program and Data memories) */
#endif /* STM8S103 or STM8S003 or STM8S903 or STM8AF622x*/
/* Exported functions ------------------------------------------------------- */
/* Exported variables ------------------------------------------------------- */
void FLASH_SetProgrammingTime(FLASH_ProgramTime_TypeDef FLASH_ProgTime);
void FLASH_Unlock(FLASH_MemType_TypeDef FLASH_MemType);
void FLASH_Lock(FLASH_MemType_TypeDef FLASH_MemType);
void FLASH_ProgramByte(uint32_t Address, uint8_t Data);
uint8_t FLASH_ReadByte(uint32_t Address);
void FLASH_EraseByte(uint32_t Address);
void FLASH_ProgramWord(uint32_t Address, uint32_t Data);

#endif