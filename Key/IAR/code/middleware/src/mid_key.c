/*******************************************************************************
* File         : mid_key.c
* Version      : v1.0.0
* Author       : ��껺�
* CreateDate   : 2018/3/12
* Description  : �м��:��������
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
/* ˽������ ------------------------------------------------------------------*/
// ����״̬�Ĵ���
typedef struct KeyStatusFlag_Struct
{
    KeycodeProperty_t KeycodeProperty : 1;  // ��������,           �����������ó�ʼֵ
    FunctionLock_t    FuncLock        : 1;  // ������,             �����������ó�ʼֵ
    KeyState_t        LastState       : 1;  // �ϴ�(����)״̬,     Ĭ�ϳ�ʼֵΪKEY_OFF����
    KeyState_t        CurState        : 1;  // ��ǰ(����)״̬,     Ĭ�ϳ�ʼֵΪKEY_OFF����
}KeySR_t;

// ��������
typedef struct Key_Struct
{
    KeySR_t     SR;                   // (����)״̬�Ĵ���
    uint16_t   KeepTMR;              // (����״̬)���ּ�ʱ��,   Ĭ�ϳ�ʼֵΪ0x0000����
    uint16_t   AnotherStateKeepTMR;  // ��һ��״̬���ּ�ʱ��,   Ĭ�ϳ�ʼֵΪ0x0000����

    RespList_t  *pRespList;     // ��Ӧ�б�
    uint8_t     RespListSize;  // ��Ӧ�б���   ע��:��Ӧ�б��ȱ�����ȷ,����ᷢ��δ֪�Ĵ���
}KeyProperty_t;
/* ˽�ж��� ------------------------------------------------------------------*/
/* ˽�к�   ------------------------------------------------------------------*/
#define GET_KEYCODE    (*(uint16_t *)arg_ptr._Ap)  // ��ȡ����
/* ˽�к��� ------------------------------------------------------------------*/
static void f_KeyFunction(KeyState_t CurKeyState,void (*pPressedCallback)(void),void (*pReleasedCallback)(void));
/* ˽�г��� ----------------------------------------------------------------- */
/* ˽�б��� ------------------------------------------------------------------*/
static KeyProperty_t key[KEY_CODE_NUM];
/* ���б��� ------------------------------------------------------------------*/

/*******************************************************************************
* Description  : �������Իָ�Ĭ��ֵ
*                ���а������ó�����:
*                "��ť"ģʽ
*                ����������
*                ��ǰ��ť״̬Ϊ��״̬
*                ��ʱ��0
*                ���������Ӧ�б�
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
* Description  : �������Գ�ʼ��
* Input        : KeyCode        ����
*                *pRespList     ��Ӧ�б�ָ��
*                 RespListSize  ��Ӧ�б���
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
* Description  : ���ü�������
* Input        : KeyCode    ����
*                Property  (����)����
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
* Description  : ���ü��빦��
* Input        : KeyCode    ����
*                LockState  (����)��״̬
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
* Description  : ������ʶ��
* Input        : KeyCode      ����
*                KeyCurState  ������ǰ״̬
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
* Description  : ���ϰ���ʶ��
* Input        : ComplexKeycode ���ϰ�������
*                SingleKeyNum   ��������������
*                ...            SingleKeyNum������������
* Output       : None
* Note         : ��:3����������ϳ�һ�����ϰ���
*                ������������ͬʱ����ʱ,����Ϊ��ϰ���������,�������������ͷ�
*                ��������������ͬʱ����ʱ,����ϰ������ͷ�,����������״̬����
*                f_ComplexKeyDiscern(ComplexKeycode, 3, SingleKeycode0, SingleKeycode1�� SingleKeycode2);
*                ���ò���˵��:
*                3:��ϰ���״̬��3����������״̬ȷ��
*                ComplexKeycode:  ���ϰ�������
*                SingleKeycode0:  ����������0
*                SingleKeycode1:  ����������1
*                SingleKeycode2:  ����������2
* CreateDate   : 2018/4/2
* ChangeLogs   : 
*******************************************************************************/
void f_ComplexKeyDiscern(uint8_t ComplexKeycode, uint8_t SingleKeyNum,...)
{
    USER_ASSERT_PARAM(IS_LESS_CONST(SingleKeyNum, KEY_CODE_NUM));
    USER_ASSERT_PARAM(IS_ABOVE_CONST(SingleKeyNum, 1));
    
    // ����һ��va_list�͵ı���,��������Ǵ洢������ַ��ָ��
    va_list arg_ptr;
    uint8_t SingleKeyNumBuff = SingleKeyNum;  // ��¼KeycodeNum��ֵ
    
    // Ȼ����va_start���ʼ������arg_ptr,�����ĵڶ��������ǿɱ�����б��ǰһ������,�����һ���̶�����.
    va_start(arg_ptr, SingleKeyNum);
    
    while(KEY_ON == key[GET_KEYCODE].SR.CurState && SingleKeyNum)
    {
        USER_ASSERT_PARAM(IS_LESS_CONST(GET_KEYCODE, KEY_CODE_NUM));  // ����������Ч��У��
        
        va_arg(arg_ptr, uint16_t *);
        
        SingleKeyNum --;
    }
    
    if(0 == SingleKeyNum)
    {// ���е�������������
        key[ComplexKeycode].SR.CurState = KEY_ON;  // ��ϰ�����Ч
        
        // �����е��������
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
        key[ComplexKeycode].SR.CurState = KEY_OFF;  // ��ϰ�����Ч
    }
    
    va_end(arg_ptr); //��ָ�����
}

/*******************************************************************************
* Description  : ������Ӧ
*                ����ѯ���м���.
*                �������봦��������,����Ӧ�������Ӧ��ʱ���ֲ���,�Ҹü����Ӧ�ĺ���һ�ɲ�ִ��.
*                ��������(����/�ͷ�)����Ӧ��ʱ==��ǰ����Ӧ��ʱ,�ҹ�����δ����,��ִ����Ӧ�ĺ���.
*                  ���򲻶���
* Input        : *KeyDiscernCallBack  ����ʶ��ص�����
* Output       : None
* Note         : 
* CreateDate   : 2018/04/14
* ChangeLogs   : 
*******************************************************************************/
void f_KeyResp(void (*KeyDiscernCallBack)(void))
{
    USER_ASSERT_PARAM(IS_NOT_NULL(KeyDiscernCallBack));
    
    // ����ʶ��
    KeyDiscernCallBack();
    
    for(uint8_t i=0;i<KEY_CODE_NUM;i++)  // ��ѯ���а���
    {
        RespList_t *pNode = key[i].pRespList;  // Ϊ�˼��ٴ��볤��,�����Ķ�

        if(pNode != NULL)
        {
            /* �����߼�����ʱ���ʱ */
            if(key[i].SR.CurState == key[i].SR.LastState)
            {
                f_AddUint16_t(&key[i].KeepTMR, ADD_TIME);
            }
            else
            {
                key[i].AnotherStateKeepTMR = key[i].KeepTMR;  // ��¼��һ��״̬�ı��ּ�ʱ��
                
                key[i].SR.LastState = key[i].SR.CurState;
                key[i].KeepTMR = 0;
            }
            
            /* ��ѯ�ð���������Ӧ�ڵ� */
            for(uint8_t j=0;j<key[i].RespListSize;j++)
            {
                if(key[i].SR.FuncLock == FUNC_UNLOCK)  // ������δ����
                {
                    switch(key[i].SR.KeycodeProperty)
                    {
                        case BUTTON:  // ��������
                        {
                            if(pNode[j].RespTM == key[i].KeepTMR)
                            {
                                if(key[i].AnotherStateKeepTMR >= DEBOUNCE_MIN_TM) // ��һ��״̬����ʱ����������С����ʱ��,������Ӧ��ǰ״̬
                                {
                                    f_KeyFunction(key[i].SR.CurState, pNode[j].pFuncPressed, pNode[j].pFuncReleased);
                                }
                            }
                            break;
                        }
                        case SWITCH:  // ��������
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
* Description  : ��������
* Input        : CurKeyState  ��ǰ����״̬
* Output       : *pPressedCallback  (����)���»ص�����
*                *pReleasedCallback (����)�ͷŻص�����
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
