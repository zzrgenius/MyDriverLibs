#ifndef __KEY_DRIVER_H__
#define __KEY_DRIVER_H__



/*----------------------------------------------*
 * �������ƶ���  
 * 
 *˵����ÿ������ռ1λ��ʹ��ulong(32λ)��ʾ����0x00000001��ʼ����
 *----------------------------------------------*/
//��������
#define KEY_NAME_POWER 0x00000001//��Դ��
#define KEY_NAME_STOP  0x00000002//ֹͣ��
#define KEY_NAME_WASH  0x00000004//��ϴ��

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

#define KEY_PRESSED_1S KEY_STATE_1
#define KEY_PRESSED_3S KEY_STATE_2
#define KEY_PRESSED_5S KEY_STATE_3

/*----------------------------------------------*
 * ��������˵��                                       *
 *----------------------------------------------*/



#endif
