/*******************************************************************************
  * @file    main.h
  * @author  钟昊翰
  * @version V1.0.0
  * @date    2017-xx-xx
  * @brief   该头文件包含公共头文件,以及难以归类的定义
*******************************************************************************/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/
#include<stdint.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#ifdef _COSMIC_
 #define FAR  @far
 #define NEAR @near
 #define TINY @tiny
 #define EEPROM @eeprom
 #define CONST  const
#elif defined (_RAISONANCE_) /* __RCST7__ */
 #define FAR  far
 #define NEAR data
 #define TINY page0
 #define EEPROM eeprom
 #define CONST  code
 #if defined (STM8S208) || defined (STM8S207) || defined (STM8S007) || defined (STM8AF52Ax) || \
     defined (STM8AF62Ax)
   /*!< Used with memory Models for code higher than 64K */
  #define MEMCPY fmemcpy
 #else /* STM8S903, STM8S103, STM8S003, STM8S105, STM8AF626x, STM8AF622x */
  /*!< Used with memory Models for code less than 64K */
  #define MEMCPY memcpy
 #endif /* STM8S208 or STM8S207 or STM8S007 or STM8AF62Ax or STM8AF52Ax */ 
#else /*_IAR_*/
 #define FAR  __far
 #define NEAR __near
 #define TINY __tiny
 #define EEPROM __eeprom
 #define CONST  const
#endif /* __CSMC__ */

#if defined (STM8S105) || defined (STM8S005) || defined (STM8S103) || defined (STM8S003) || \
    defined (STM8S903) || defined (STM8AF626x) || defined (STM8AF622x)
/*!< Used with memory Models for code smaller than 64K */
 #define PointerAttr NEAR
 #define MemoryAddressCast uint16_t
#else /* STM8S208 or STM8S207 or STM8AF62Ax or STM8AF52Ax */
/*!< Used with memory Models for code higher than 64K */
 #define PointerAttr FAR
 #define MemoryAddressCast uint32_t
#endif /* STM8S105 or STM8S103 or STM8S003 or STM8S903 or STM8AF626x or STM8AF622x */
/* Exported functions ------------------------------------------------------- */
/* Exported variables ------------------------------------------------------- */
#endif
