/*******************************************************************************
* File         : mid_key.h
* Version      : v1.0.0
* Author       : 钟昊翰
* CreateDate   : 2018/3/12
* Description  : 中间件:按键驱动
* Change Logs  : 
*******************************************************************************/
#ifndef __MID_KEY_20180312_H__
#define __MID_KEY_20180312_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* 键码属性 */
typedef enum
{
    BUTTON = 0,         // 按钮
    SWITCH = (!BUTTON)  // 开关
}KeycodeProperty_t;

/* 功能锁 */
typedef enum
{
    FUNC_UNLOCK = 0,            // 按钮/开关的功能解锁
    FUNC_LOCK = (!FUNC_UNLOCK)  // 按钮/开关的功能上锁(上锁时,按钮/开关的保持计时器依旧会累加,但不会响应功能)
}FunctionLock_t;

/* 按键状态 */
typedef enum
{
    KEY_OFF = 0,         // 开关:关(按钮:释放)
    KEY_ON = (!KEY_OFF)  // 开关:开(按钮:按下)
}KeyState_t;

/* 响应列表 */
typedef struct RespList_Struct
{
    const uint16_t RespTM;      // 响应定时
    void (*pFuncPressed)(void);  // 开关(开)/按钮(按下)触发函数
    void (*pFuncReleased)(void); // 开关(关)/按钮(释放)触发函数
}RespList_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define ADD_TIME          10           // 按键保持时间累加值(要保证函数"f_KeyResp"调用周期相等)
#define DEBOUNCE_MIN_TM  (5*ADD_TIME)  // 最小消抖时间
/* Exported functions ------------------------------------------------------- */
void f_KeyPropertyDeInit(void);
void f_KeyPropertyInit(uint8_t KeyCode,RespList_t *pRespList,  uint8_t RespListSize);
void f_CFG_KeycodeProperty(uint8_t KeyCode, KeycodeProperty_t Property);

void f_SET_KeycodeFunction(uint8_t KeyCode, FunctionLock_t LockState);

void f_SingleKeyDiscern(uint8_t KeyCode, KeyState_t KeyCurState);
void f_ComplexKeyDiscern(uint8_t ComplexKeycode, uint8_t SingleKeyNum,...);

void f_KeyResp(void (*KeyDiscernCallBack)(void));
/* Exported variables ------------------------------------------------------- */


#endif
