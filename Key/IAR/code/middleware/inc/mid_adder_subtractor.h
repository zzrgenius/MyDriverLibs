/*******************************************************************************
* File         : mid_adder_subtractor.h
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2018/3/13
* Description  : 中间件:通用加减器
* Change Logs  : 
*******************************************************************************/
#ifndef __MID_ADDER_SUBTRACTOR_20180313_H__
#define __MID_ADDER_SUBTRACTOR_20180313_H__

/* Includes ------------------------------------------------------------------*/
#include<stdint.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void f_AddUint8_t(uint8_t *pData, const uint8_t Constant);
void f_DecUint8_t(uint8_t *pData, const uint8_t Constant);

void f_AddUint16_t(uint16_t *pData, const uint16_t Constant);
void f_DecUint16_t(uint16_t *pData, const uint16_t Constant);

void f_AddUint32_t(uint32_t *pData, const uint32_t Constant);
void f_DecUint32_t(uint32_t *pData, const uint32_t Constant);
/* Exported variables ------------------------------------------------------- */



#endif
