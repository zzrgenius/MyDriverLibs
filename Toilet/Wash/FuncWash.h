#ifndef __FUN_CWASH_H__
#define __FUNC_WASH_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"
#include "Function.h"
/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
typedef enum
{
	WASH_INDEX_ORG, //��ԭ��
	WASH_INDEX_PER_WASH, //ǰ��ϴ
	WASH_INDEX_SET_POS, //�������(���λ�á����ȡ��ȴ�����)
	WASH_INDEX_SET_FLOW, //��������(����������õ�λ)
	WASH_INDEX_WASH, //������ϴ(��ϴʱ�䡢�ƶ���ϴ)
	WASH_INDEX_BACK_FLOW, //������ԭ��
	WASH_INDEX_BACK_POS, //��˻�ԭ��(��˻���,ͬʱ��ϴ)
	WASH_INDEX_BACK_WASH, //��˻��˳�ϴ
	WASH_INDEX_CLEAN, //���Խ�(��˵�λ��ˮ�رա����ô�������λ)
	WASH_INDEX_END //��ϴ����
}FUNC_WASH_INDEX; //��ϴ˳��

typedef struct 
{
	STEPMOTER_DRIVER *pNozzleSM; //��˲����������ָ��	
	STEPMOTER_DRIVER *pFlowSM; //���������������ָ��
	const sint *pTabPos; //���λ��
	const sint *pTabFlow; //����λ��
}FUNC_WASH_HARDWARE; //Ӳ������

typedef struct
{
	FUNC_WASH_INDEX index; //����
	uchar waitTm; //���̵ȴ�ʱ��
	FUNC_WASH_HARDWARE const *pHardware; //Ӳ������
	FUNC_SET_LEVEL posLevel; //��˵�λ
	FUNC_SET_LEVEL flowLevel; //������λ
	FUNC_SET_LEVEL flowLevelSave; //��������(һ��SPA��)
	uchar strongWeakTm;//ǿ��ʱ��
	FUNC_SET_LEVEL strongWeakLevel; //ǿ����ǰ��λ
	uchar coldHotTm;//����ʱ��
	uchar setPumpPercent; //�������ðٷֱ�
	
	union
	{
		struct 
		{
			uint bPosAtTag :1; //��˵����Ŀ��λ��
			uint bFlowAtTag :1; //���������Ŀ��λ��
			uint bRealStart :1; //������ϴ���̵�(WASH_INDEX_WASH)
			uint bEnStrongWeak :1; //ǿ�����水Ħ
			uint bFlowMax :1; //�����ѵ����
			uint bEnMove :1; //�ƶ���ϴ
			uint bMoveEnd :1; //�ƶ���ϴ�Ƿ񵽶�
			uint bEnColdHot :1; //���Ȱ�Ħ
			uint bPosBackReset :1; //��˻��˸�λ
			uint bResetCurPos :1; //��ǰλ������
			uint bFlowReset :1; //���������λ
			uint bEnAirPump :1; //ʹ�ܿ�����ͨ��
		}m_bits;
		uint m_byte;
	}flags;//һЩ��ʱ��־(���Զ����)

	uchar bNeedPosBack :1; //�л�ʱ�Ƿ�Ҫ��˻���
	uchar bEnHeat :1; //ʹ��ˮ�¼���
	uchar bChangePos :1; //���λ�øı�(����λ��)
	uchar bChangeFlow :1; //����λ�øı�(��������)
	uchar bEnInwaterValve :1; //ʹ�ܽ�ˮ��
}FUNC_WASH; //��ϴ����

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
extern FUNC_WASH AT_NEAR funcWashHip;//�β���ϴ
extern FUNC_WASH AT_NEAR funcWashFemale;//Ů����ϴ
extern const FUNC_WASH_HARDWARE hipWashHardware;
extern const FUNC_WASH_HARDWARE femaleWashHardware;
/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_FuncWashDeal(void);
void f_FuncWashInit(FUNC_WASH *pDriver, const FUNC_WASH_HARDWARE *pHardware);
uchar f_FuncSetWashState(FUNC_WASH *pDriver, STATE_INFO state);
void f_FuncWashNext(FUNC_WASH *pDriver, FUNC_WASH_INDEX index);
void f_FuncWashPosCtrl(FUNC_WASH *pDriver);
void f_FuncWashFlowCtrl(FUNC_WASH *pDriver);
void f_FuncWashColdHotCtrl(FUNC_WASH *pDriver);
uchar f_FuncSetStrongWeak(FUNC_WASH *pDriver, STATE_INFO state);
uchar f_FuncSetWashMove(FUNC_WASH *pDriver, STATE_INFO state);
uchar f_FuncSetColdHot(FUNC_WASH *pDriver, STATE_INFO state);
void f_FuncSetPos(FUNC_WASH *pDriver, FUNC_SET_LEVEL pos, uchar bForce);
void f_FuncSetFlow(FUNC_WASH *pDriver, FUNC_SET_LEVEL flow, uchar bForce);
uchar f_FuncSetPurge(FUNC_WASH *pDriver, STATE_INFO state);

#endif /* __FUNC_WASH_H__ */
