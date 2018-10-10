/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : KeyDriver.c
  版 本 号   : 初稿
  作    者   : 钱百静
  生成日期   : 2018年4月10日
  最近修改   :
  功能描述   : 通用按键处理驱动模块,统一产生按键信息用于应用层处理
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月10日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/

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

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
 #define KEY_SHAKE_TM 5//50ms


/*****************************************************************************
 函 数 名  : f_KeyDriverTimer(KeyDriver const *pKeyDriver)
 功能描述      : 按键处理10ms时基
 输入参数      : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年4月11日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_KeyDriverTimer(   KeyDriver const *pKeyDriver)
{
	pKeyDriver->keyData.keyPressTm ++;
}


/*****************************************************************************
 函 数 名: f_test
 功能描述: 
 输入参数: 无
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月11日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
UINT32_T  f_test( # )
{
    #
}

