#ifndef __MUSIC_BEEP_H__
#define __MUSIC_BEEP_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
typedef struct 
{
	uint freq; //����Ƶ��
	uint keepTm; //����ʱ��
}MUSIC_BEEP_VALUE; //��������ֵ,���ڽ�������

typedef enum 
{
    MUSIC_BEEP_ERR = 0, //������           
    MUSIC_BEEP_SIT,	//������
	MUSIC_BEEP_NORMAL, //����Ӧ
	MUSIC_BEEP_NORMAL_2, //������2
	MUSIC_BEEP_FUNC_ON, //���ܿ�����
	MUSIC_BEEP_FUNC_OFF, //���ܹر���
	MUSIC_BEEP_L1, //������1
	MUSIC_BEEP_L2, //������2
	MUSIC_BEEP_L3, //������3
	MUSIC_BEEP_L4, //������4
	MUSIC_BEEP_L5, //������5
	MUSIC_BEEP_UNUSE,	//��Ч��
	MUSIC_BEEP_UNUSE_2,	//��Ч��2
	MUSIC_BEEP_POWER_ON, //������
	MUSIC_BEEP_POWER_ON_2, //������_2
	MUSIC_BEEP_POWER_OFF, //�ػ���
	MUSIC_BEEP_POWER_OFF_2 //�ػ���
}MUSIC_BEEP_TYPE;//����������pAllBeepTable��Ӧ(Լ�����ȼ�Խ�ߣ����ȼ��ߵ��ܴ�����ȼ��͵ģ���֮����)
#define BEEP_MIN_PRIORITY MUSIC_BEEP_ERR //��С���ȼ�

typedef struct 
{
	uint curBeepTm; //��ǰ����ʱ�� 
	MUSIC_BEEP_VALUE beepInfo;
	const MUSIC_BEEP_VALUE *pBeepTab; //��������
	uchar beepIndex; //����˳��
	MUSIC_BEEP_TYPE curType; //��ǰ����(�������ȼ���Ϣ)
}MUSIC_BEEP_DRIVER;//��������


/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_MusicBeep(void);
void f_SetBeep(MUSIC_BEEP_TYPE type);

#endif /* __MUSIC_BEEP_H__ */
