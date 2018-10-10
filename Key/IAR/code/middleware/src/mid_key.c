/*******************************************************************************
* File         : mid_key.c
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2018/3/12
* Description  : 中间件:按键驱动
* Change Logs  : 
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include<stdint.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>
#include<stdbool.h>

#include"parm_check.h"
#include"mid_key.h"
#include"key_cfg.h"
#include"mid_adder_subtractor.h"
/* 私有类型 ------------------------------------------------------------------*/
// 按键状态寄存器
typedef struct KeyStatusFlag_Struct
{
    KeycodeProperty_t KeycodeProperty : 1;  // 键码属性,           根据需求设置初始值
    FunctionLock_t    FuncLock        : 1;  // 功能锁,             根据需求设置初始值
    KeyState_t        LastState       : 1;  // 上次(按键)状态,     默认初始值为KEY_OFF即可
    KeyState_t        CurState        : 1;  // 当前(按键)状态,     默认初始值为KEY_OFF即可
}KeySR_t;

// 键码属性
typedef struct Key_Struct
{
    KeySR_t     SR;                   // (按键)状态寄存器
    uint16_t   KeepTMR;              // (按键状态)保持计时器,   默认初始值为0x0000即可
    uint16_t   AnotherStateKeepTMR;  // 另一种状态保持计时器,   默认初始值为0x0000即可

    RespList_t  *pRespList;     // 响应列表
    uint8_t     RespListSize;  // 响应列表长度   注意:响应列表长度必须正确,否则会发生未知的错误
}KeyProperty_t;
/* 私有定义 ------------------------------------------------------------------*/
/* 私有宏   ------------------------------------------------------------------*/
#define GET_KEYCODE    (*(uint16_t *)arg_ptr._Ap)  // 获取键码
/* 私有函数 ------------------------------------------------------------------*/
static void f_KeyFunction(KeyState_t CurKeyState,void (*pPressedCallback)(void),void (*pReleasedCallback)(void));
/* 私有常量 ----------------------------------------------------------------- */
/* 私有变量 ------------------------------------------------------------------*/
static KeyProperty_t key[KEY_CODE_NUM];
/* 公有变量 ------------------------------------------------------------------*/

/*******************************************************************************
* Description  : 按键属性恢复默认值
*                所有按键配置成如下:
*                "按钮"模式
*                解锁功能锁
*                当前按钮状态为关状态
*                计时清0
*                清除所有响应列表
* Input        : None
* Output       : None
* Note         : 
* CreateDate   : 2018/4/13
* ChangeLogs   : 
*******************************************************************************/
void f_KeyPropertyDeInit(void)
{
    memset(key, 0x00, sizeof(key));
}

/*******************************************************************************
* Description  : 按键属性初始化
* Input        : KeyCode        键码
*                *pRespList     响应列表指针
*                 RespListSize  响应列表长度
* Output       : None
* Note         : 
* CreateDate   : 2018/4/13
* ChangeLogs   : 
*******************************************************************************/
void f_KeyPropertyInit(uint8_t KeyCode,RespList_t *pRespList,  uint8_t RespListSize)
{
    USER_ASSERT_PARAM(IS_LESS_CONST(KeyCode, KEY_CODE_NUM));
    USER_ASSERT_PARAM(IS_NOT_NULL(pRespList));
    USER_ASSERT_PARAM(IS_ABOVE_CONST(RespListSize, 0));
    
    key[KeyCode].pRespList = pRespList;
    key[KeyCode].RespListSize = RespListSize;
}

/*******************************************************************************
* Description  : 配置键码属性
* Input        : KeyCode    键码
*                Property  (键码)属性
* Output       : None
* Note         : 
* CreateDate   : 2018/4/14
* ChangeLogs   : 
*******************************************************************************/
void f_CFG_KeycodeProperty(uint8_t KeyCode, KeycodeProperty_t Property)
{
    USER_ASSERT_PARAM(IS_LESS_CONST(KeyCode, KEY_CODE_NUM));
    
    key[KeyCode].SR.KeycodeProperty = Property;
}

/*******************************************************************************
* Description  : 设置键码功能
* Input        : KeyCode    键码
*                LockState  (功能)锁状态
* Output       : None
* Note         : 
* CreateDate   : 2018/4/14
* ChangeLogs   : 
*******************************************************************************/
void f_SET_KeycodeFunction(uint8_t KeyCode, FunctionLock_t LockState)
{
    USER_ASSERT_PARAM(IS_LESS_CONST(KeyCode, KEY_CODE_NUM));
    
    key[KeyCode].SR.FuncLock = LockState;
}

/*******************************************************************************
* Description  : 单按键识别
* Input        : KeyCode      键码
*                KeyCurState  按键当前状态
* Output       : None
* Note         : 
* CreateDate   : 2018/4/13
* ChangeLogs   : 
*******************************************************************************/
void f_SingleKeyDiscern(uint8_t KeyCode, KeyState_t KeyCurState)
{
    USER_ASSERT_PARAM(IS_LESS_CONST(KeyCode, KEY_CODE_NUM));
    
    key[KeyCode].SR.CurState = KeyCurState;
}

/*******************************************************************************
* Description  : 复合按键识别
* Input        : ComplexKeycode 复合按键键码
*                SingleKeyNum   单按键键码数量
*                ...            SingleKeyNum个单按键键码
* Output       : None
* Note         : 例:3个单按键组合成一个复合按键
*                当三个单按键同时按下时,则认为组合按键被按下,三个单按键被释放
*                当三个单按键非同时按下时,则组合按键被释放,三个单按键状态不变
*                f_ComplexKeyDiscern(ComplexKeycode, 3, SingleKeycode0, SingleKeycode1， SingleKeycode2);
*                调用参数说明:
*                3:组合按键状态由3个单按键的状态确定
*                ComplexKeycode:  复合按键键码
*                SingleKeycode0:  单按键键码0
*                SingleKeycode1:  单按键键码1
*                SingleKeycode2:  单按键键码2
* CreateDate   : 2018/4/2
* ChangeLogs   : 
*******************************************************************************/
void f_ComplexKeyDiscern(uint8_t ComplexKeycode, uint8_t SingleKeyNum,...)
{
    USER_ASSERT_PARAM(IS_LESS_CONST(SingleKeyNum, KEY_CODE_NUM));
    USER_ASSERT_PARAM(IS_ABOVE_CONST(SingleKeyNum, 1));
    
    // 定义一个va_list型的变量,这个变量是存储参数地址的指针
    va_list arg_ptr;
    uint8_t SingleKeyNumBuff = SingleKeyNum;  // 记录KeycodeNum的值
    
    // 然后用va_start宏初始化变量arg_ptr,这个宏的第二个参数是可变参数列表的前一个参数,即最后一个固定参数.
    va_start(arg_ptr, SingleKeyNum);
    
    while(KEY_ON == key[GET_KEYCODE].SR.CurState && SingleKeyNum)
    {
        USER_ASSERT_PARAM(IS_LESS_CONST(GET_KEYCODE, KEY_CODE_NUM));  // 不定参数有效性校验
        
        va_arg(arg_ptr, uint16_t *);
        
        SingleKeyNum --;
    }
    
    if(0 == SingleKeyNum)
    {// 所有单按键都被按下
        key[ComplexKeycode].SR.CurState = KEY_ON;  // 组合按键有效
        
        // 将所有单按键清除
        va_start(arg_ptr, SingleKeyNum);
        
        while(SingleKeyNumBuff)
        {
            key[GET_KEYCODE].SR.CurState = KEY_OFF;
            
            va_arg(arg_ptr, uint16_t *);
            
            SingleKeyNumBuff --;
        }
    }
    else
    {
        key[ComplexKeycode].SR.CurState = KEY_OFF;  // 组合按键无效
    }
    
    va_end(arg_ptr); //将指针清空
}

/*******************************************************************************
* Description  : 按键响应
*                ①轮询所有键码.
*                ②若键码处于消抖期,则相应键码的响应计时保持不变,且该键码对应的函数一律不执行.
*                ③若键码(按下/释放)的响应计时==当前的响应计时,且功能锁未上锁,则执行相应的函数.
*                  否则不动作
* Input        : *KeyDiscernCallBack  按键识别回调函数
* Output       : None
* Note         : 
* CreateDate   : 2018/04/14
* ChangeLogs   : 
*******************************************************************************/
void f_KeyResp(void (*KeyDiscernCallBack)(void))
{
    USER_ASSERT_PARAM(IS_NOT_NULL(KeyDiscernCallBack));
    
    // 按键识别
    KeyDiscernCallBack();
    
    for(uint8_t i=0;i<KEY_CODE_NUM;i++)  // 轮询所有按键
    {
        RespList_t *pNode = key[i].pRespList;  // 为了减少代码长度,方便阅读

        if(pNode != NULL)
        {
            /* 键码逻辑保持时间计时 */
            if(key[i].SR.CurState == key[i].SR.LastState)
            {
                f_AddUint16_t(&key[i].KeepTMR, ADD_TIME);
            }
            else
            {
                key[i].AnotherStateKeepTMR = key[i].KeepTMR;  // 记录另一种状态的保持计时器
                
                key[i].SR.LastState = key[i].SR.CurState;
                key[i].KeepTMR = 0;
            }
            
            /* 轮询该按键所有响应节点 */
            for(uint8_t j=0;j<key[i].RespListSize;j++)
            {
                if(key[i].SR.FuncLock == FUNC_UNLOCK)  // 功能锁未上锁
                {
                    switch(key[i].SR.KeycodeProperty)
                    {
                        case BUTTON:  // 按键属性
                        {
                            if(pNode[j].RespTM == key[i].KeepTMR)
                            {
                                if(key[i].AnotherStateKeepTMR >= DEBOUNCE_MIN_TM) // 另一种状态保持时间必须大于最小消抖时间,才能响应当前状态
                                {
                                    f_KeyFunction(key[i].SR.CurState, pNode[j].pFuncPressed, pNode[j].pFuncReleased);
                                }
                            }
                            break;
                        }
                        case SWITCH:  // 开关属性
                        {
                            if(pNode[j].RespTM >= key[i].KeepTMR)
                            {
                                f_KeyFunction(key[i].SR.CurState, pNode[j].pFuncPressed, pNode[j].pFuncReleased);
                            }
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}

/*******************************************************************************
* Description  : 按键功能
* Input        : CurKeyState  当前按键状态
* Output       : *pPressedCallback  (按键)按下回调函数
*                *pReleasedCallback (按键)释放回调函数
* Note         : 
* CreateDate   : 2018/3/13
* ChangeLogs   : 
*******************************************************************************/
static void f_KeyFunction(KeyState_t CurKeyState,void (*pPressedCallback)(void),void (*pReleasedCallback)(void))
{
    switch(CurKeyState)
    {
        case KEY_ON:
        {
            if(pPressedCallback != NULL)
            {
                pPressedCallback();
            }
            break;
        }
        case KEY_OFF:
        {
            if(pReleasedCallback != NULL)
            {
                pReleasedCallback();
            }
            break;
        }
        default:
        {
            break;
        }
    }
}
