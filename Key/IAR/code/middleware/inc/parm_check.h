/*******************************************************************************
* File         : parm_check.h
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2017/10/23
* Description  : 函数形参校验头文件
*                该头文件配合 param.c 文件使用. 用于函数参数有效性检查.
*
*                可用 USER_FULL_ASSERT 来决定是否做参数检查.
*                直接调用定义 USER_ASSERT_PARAM 就可进行参数检查,
*                但在每个子模块中需要自己定义expr的判断方式.
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
