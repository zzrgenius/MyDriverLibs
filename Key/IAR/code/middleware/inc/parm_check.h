/*******************************************************************************
* File         : parm_check.h
* Version      : v1.0.0
* Author       : ��껺�
* CreateDate   : 2017/10/23
* Description  : �����β�У��ͷ�ļ�
*                ��ͷ�ļ���� param.c �ļ�ʹ��. ���ں���������Ч�Լ��.
*
*                ���� USER_FULL_ASSERT �������Ƿ����������.
*                ֱ�ӵ��ö��� USER_ASSERT_PARAM �Ϳɽ��в������,
*                ����ÿ����ģ������Ҫ�Լ�����expr���жϷ�ʽ.
* Change Logs  : 
*******************************************************************************/
#ifndef __PARM_CHECK_H__
#define __PARM_CHECK_H__

/* Includes ------------------------------------------------------------------*/
#include<stdint.h>
#include<stdio.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define IS_NOT_NULL(INSTANCE)    ((INSTANCE) != NULL)
#define IS_ABOVE_CONST(INSTANCE,_CONST_)  ((INSTANCE) > _CONST_)
#define IS_LESS_CONST(INSTANCE,_CONST_)  ((INSTANCE) < (_CONST_))

#ifdef USER_FULL_ASSERT
    #define USER_ASSERT_PARAM(expr) ((expr) ? (void)0 : UserAssertFailed((uint8_t *)__FILE__, __LINE__,(uint8_t *)__FUNCTION__))
    void UserAssertFailed(uint8_t* file, uint32_t line, uint8_t *funcname);
#else
    #define USER_ASSERT_PARAM(expr) ((void)0)
#endif
/* Exported functions ------------------------------------------------------- */
/* Exported variables ------------------------------------------------------- */

#endif
