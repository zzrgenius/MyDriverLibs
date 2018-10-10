/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : KeyDriverConfig.h
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��12��
  ����޸�   :
  ��������   : �������ã���Ҫ���ݾ�����Ŀ�޸ġ�
  			�޸Ĳ��裺
  			1���޸İ������ƶ����еĵ�������ϼ�(�޸İ�������)
  			2��������Ŀ��Ҫ�޸ĳ������Զ���״̬��ʱ�䣬��1S��(�޸��Զ���״̬�����״̬���㣬���Բ��޸�)
  			3����дKeyDriverConfig.c��Tab_KeySelfState
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __KEY_DRIVER_CONFIG_H__
#define __KEY_DRIVER_CONFIG_H__

#include "DataType.h"

/*----------------------------------------------*
 * �������ƶ���  
 * 
 *˵����ÿ������ռ1λ��ʹ��ulong(32λ)��ʾ����0x00000001��ʼ����
 *----------------------------------------------*/
#define KEY_DRIVER_NO_KEY 0	//�ް���״̬
#define KEY_DRIVER_ALL_KEY 0xffffffff

//��������----�޸İ�������----��������
//��������
#define KEY_SIGLE_FLUSH 0x00000001//��ˮ��


//��ϼ�����
//#define KEY_COMM_RESER (KEY_SIGLE_POWER | KEY_SIGLE_STOP)//��ϼ���λ

//��������������
#define KEY_DRIVER_INDE_KEY_NUM	0//��������������
#define KEY_INDE_HOT			0x00000008//��ˮ��
#define KEY_INDE_COLD			0x00000010//��ˮ��
//��������-----------------------��������

/*----------------------------------------------*
 * ����״̬����                                       *
 *----------------------------------------------*/
typedef enum 
{
	KEY_STATE_IDLE = 0,
	KEY_PRESSED = 0x01,//��������״̬
	KEY_RELEASE = 0x02,//�����ͷ�״̬
	KEY_LOCKED  = 0x04,//������ס״̬(��״̬�����ڲ�ʹ��)
	KEY_STATE_1 = 0x08,//����״̬�����Զ���
	KEY_STATE_2 = 0x10,
	KEY_STATE_3 = 0x20,
	KEY_STATE_4 = 0x40,
	KEY_STATE_5 = 0x80,
	KEY_STATE_RESERVE = 0xff
}KEY_STATE;

#define f_GetKeyName()		(pKeyDriver->data.name)		
#define f_IsKeyState(State) (pKeyDriver->data.state & State)
#define f_ClrKeyState(State) (pKeyDriver->data.state &= (~State)) //�����ǰ����״̬
#define f_SetKeyDealDone()	(pKeyDriver->data.keyDone |= pKeyDriver->data.name) //�����Ѵ�����������ͷ���Ϣ
#define f_GetKeyDealDone(name)	((pKeyDriver->data.keyDone&name) != KEY_DRIVER_NO_KEY?true:false)
#define f_RemoveKey(key)	(pKeyDriver->data.mask &= ~(key))

//#define KEY_DONE_OVER	//��������󣬾Ͳ������µ�״̬(�ɸ���ʵ��ʹ�ô򿪻�ر�)


//��������----�޸��Զ���״̬----��������
#define KEY_LOCK_TM 2000//����������סʱ�� 20S����������סʱ��Ӱ����������

#define KEY_PRESS_1S KEY_STATE_1 //�Զ��峤��״̬1S
#define KEY_PRESS_1S_TM 100//*10ms

#define KEY_PRESS_3S KEY_STATE_2
#define KEY_PRESS_3S_TM 300//*10ms

#define KEY_PRESS_5S KEY_STATE_3
#define KEY_PRESS_5S_TM 500//*10ms
//��������-----------------------��������

typedef struct
{
	unsigned int stateTime;
	KEY_STATE selfState;
}KEY_SELF_STATE;//�Զ��尴��״̬

#define f_GetKeyStateTime(index)		(Tab_KeySelfState[index].stateTime)//��ȡ��Ӧ���ְ���ʱ��
#define f_SetKeyTimeState(index)		(Tab_KeySelfState[index].selfState)//�Դﵽʱ��ģ���ֵ����״̬

/*----------------------------------------------*
 * ��������˵��                                       *
 *----------------------------------------------*/
extern const KEY_SELF_STATE Tab_KeySelfState[];
#if (KEY_DRIVER_INDE_KEY_NUM > 0)
	extern const ulong Tab_IndeKeyValue[];
#endif

#endif

