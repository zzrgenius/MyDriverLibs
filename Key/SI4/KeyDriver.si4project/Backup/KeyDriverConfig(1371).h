#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__

/*----------------------------------------------*
 * �������ƶ���  
 * 
 *˵����ÿ������ռ1λ��ʹ��ulong(32λ)��ʾ����0x00000001��ʼ����
 *----------------------------------------------*/
//��������
#define KEY_SIGLE_POWER 0x00000001//��Դ��
#define KEY_SIGLE_STOP  0x00000002//ֹͣ��
#define KEY_SIGLE_WASH  0x00000004//��ϴ��

//��ϼ�����
#define KEY_COMM_RESER (KEY_SIGLE_POWER | KEY_SIGLE_STOP)//��ϼ���λ

/*----------------------------------------------*
 * ����״̬����                                       *
 *----------------------------------------------*/
typedef enum 
{
	KEY_IDLE = 0,
	KEY_PRESSED = 0x01,
	KEY_RELEASE = 0x02,
	KEY_STATE_1 = 0x04,//����״̬�����Զ���
	KEY_STATE_2 = 0x08,
	KEY_STATE_3 = 0x10,
	KEY_STATE_4 = 0x20,
	KEY_STATE_5 = 0x40,
	KEY_STATE_5 = 0x80
}KeyState;

#define KEY_PRESS_1S KEY_STATE_1
#define KEY_PRESS_1S_TM 100//*10ms

#define KEY_PRESS_3S KEY_STATE_2
#define KEY_PRESS_3S_TM 300//*10ms

#define KEY_PRESS_5S KEY_STATE_3
#define KEY_PRESS_5S_TM 500//*10ms

typedef struct
{
	unsigned int stateTime;
	KeyState selfState;
}KeySelfState;//�Զ��尴��״̬

#define GetTime(nKey)		(Tab_KeySelfState[nKey].stateTime)//��ȡ��Ӧ���ְ���ʱ��
#define SetTimeInf(nKey)	(Tab_KeySelfState[nKey].selfState)//�Դﵽʱ��ģ���ֵ����״̬

/*----------------------------------------------*
 * ��������˵��                                       *
 *----------------------------------------------*/
extern const KeySelfState Tab_KeySelfState[];


#endif
