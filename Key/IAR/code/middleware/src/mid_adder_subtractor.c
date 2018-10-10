/*******************************************************************************
* File         : mid_adder_subtractor.c
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2018/3/13
* Description  : 中间件:通用加减器
* Change Logs  : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include"mid_adder_subtractor.h"

/* 私有类型 ------------------------------------------------------------------*/
/* 私有定义 ------------------------------------------------------------------*/
/* 私有宏   ------------------------------------------------------------------*/
/* 私有函数 ------------------------------------------------------------------*/
/* 私有常量 ----------------------------------------------------------------- */
/* 私有变量 ------------------------------------------------------------------*/
/* 公有变量 ------------------------------------------------------------------*/

void f_AddUint8_t(uint8_t *pData, const uint8_t Constant)
{
	if((*pData) <= UINT8_MAX - Constant)
    {
		(*pData) += Constant;
    }
    else
    {
        (*pData) = UINT8_MAX;
    }
}

void f_DecUint8_t(uint8_t *pData, const uint8_t Constant)
{
	if(*pData >= Constant)
    {
		(*pData) -= Constant;
    }
    else
    {
        (*pData) = 0;
    }
}

void f_AddUint16_t(uint16_t *pData, const uint16_t Constant)
{
	if((*pData) <= UINT16_MAX - Constant)
    {
		(*pData) += Constant;
    }
    else
    {
        (*pData) = UINT16_MAX;
    }
}

void f_DecUint16_t(uint16_t *pData, const uint16_t Constant)
{
	if(*pData >= Constant)
    {
		(*pData) -= Constant;
    }
    else
    {
        (*pData) = 0;
    }
}

void f_AddUint32_t(uint32_t *pData, const uint32_t Constant)
{
	if((*pData) <= UINT32_MAX - Constant)
    {
		(*pData) += Constant;
    }
    else
    {
        (*pData) = UINT32_MAX;
    }
}

void f_DecUint32_t(uint32_t *pData, const uint32_t Constant)
{
	if(*pData >= Constant)
    {
		(*pData) -= Constant;
    }
    else
    {
        (*pData) = 0;
    }
}