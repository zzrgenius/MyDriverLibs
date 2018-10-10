/*******************************************************************************
* File         : mid_key.h
* Version      : v1.0.0
* Author       : ��껺�
* CreateDate   : 2018/3/12
* Description  : �м��:��������
* Change Logs  : 
*******************************************************************************/
#ifndef __MID_KEY_20180312_H__
#define __MID_KEY_20180312_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* �������� */
typedef enum
{
    BUTTON = 0,         // ��ť
    SWITCH = (!BUTTON)  // ����
}KeycodeProperty_t;

/* ������ */
typedef enum
{
    FUNC_UNLOCK = 0,            // ��ť/���صĹ��ܽ���
    FUNC_LOCK = (!FUNC_UNLOCK)  // ��ť/���صĹ�������(����ʱ,��ť/���صı��ּ�ʱ�����ɻ��ۼ�,��������Ӧ����)
}FunctionLock_t;

/* ����״̬ */
typedef enum
{
    KEY_OFF = 0,         // ����:��(��ť:�ͷ�)
    KEY_ON = (!KEY_OFF)  // ����:��(��ť:����)
}KeyState_t;

/* ��Ӧ�б� */
typedef struct RespList_Struct
{
    const uint16_t RespTM;      // ��Ӧ��ʱ
    void (*pFuncPressed)(void);  // ����(��)/��ť(����)��������
    void (*pFuncReleased)(void); // ����(��)/��ť(�ͷ�)��������
}RespList_t;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define ADD_TIME          10           // ��������ʱ���ۼ�ֵ(Ҫ��֤����"f_KeyResp"�����������)
#define DEBOUNCE_MIN_TM  (5*ADD_TIME)  // ��С����ʱ��
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
