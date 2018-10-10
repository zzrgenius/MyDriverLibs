/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : FuncWash.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��10��
  ����޸�   :
  ��������   : ��ϴ���̴���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��10��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "HeadInclude.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                         *
 *----------------------------------------------*/
FUNC_WASH AT_NEAR funcWashHip;//�β���ϴ
FUNC_WASH AT_NEAR funcWashFemale;//Ů����ϴ
/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/
//====����ˮ��====
const sint realWatHeatTemp[] =
{
	0, 35, 38, 41
};

//====�β���ϴ����====
//�β������ϴλ��
const sint tab_HipWashNozzle[] =
{
	1700,
	1700, //L1
	2100, //L2
	2500, //L3
	2900, //L4
	2900  //L5
};

//�β�������ϴλ��
const sint tab_HipWashFlow[] =
{
	-1600,
	-1600, //L1
	-1600, //L2
	-1600  //L3
};

const FUNC_WASH_HARDWARE hipWashHardware =
{
	&nozzleStepmotor,
	&flowStepmotor,
	tab_HipWashNozzle,
	tab_HipWashFlow
};

//====Ů����ϴ����====
//Ů�������ϴλ��
const sint tab_FemaleWashNozzle[] =
{
	1800,
	1800, //L1
	2200, //L2
	2600, //L3
	3000, //L4
	3000  //L5
};

//Ů��������ϴλ��
const sint tab_FemaleWashFlow[] =
{
	1600,
	1600, //L1
	1600, //L2
	1600  //L3
};

const FUNC_WASH_HARDWARE femaleWashHardware =
{
	&nozzleStepmotor,
	&flowStepmotor,
	tab_FemaleWashNozzle,
	tab_FemaleWashFlow
};

//====��ϴ��������ռ�ձ�====
const uchar tab_WashPumpPercent[] =
{
	0,
	50, //L1
	75, //L2
	100 //L3
};

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/

#define MOVE_WASH_OFFSET 150 //�ƶ���ϴǰ��ƫ��
#define WASH_STRONG_WEAK_GAP_TM 20 //ǿ����ϴ���ʱ��,��λ100ms
#define WASH_COLD_TM 50 //���Ȱ�Ħ��ˮʱ��,��λ100ms
#define WASH_HOT_TM 100 //���Ȱ�Ħ��ˮʱ��,��λ100ms

/*****************************************************************************
 �� �� ��: f_FuncWashNext
 ��������  : ������һ������
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncWashNext(FUNC_WASH *pDriver, FUNC_WASH_INDEX index)
{
    pDriver->index = index;
	pDriver->waitTm = 0;
	pDriver->flags.m_byte = 0;
	pDriver->bNeedPosBack = true; //Ĭ���ջ�
}

/*****************************************************************************
 �� �� ��: f_FuncSetWashState
 ��������  : ������ϴ
 �������: pDriver����ָ��
 		   state ����״̬
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_FuncSetWashState(FUNC_WASH *pDriver, STATE_INFO state)
{
    if (STATE_OFF == state)
    {
    	if (pDriver->index <= WASH_INDEX_WASH)
    	{
			f_FuncWashNext(pDriver, WASH_INDEX_BACK_FLOW);//��������
		}
		return true;
    }
    else
    {
		if (funcError.bModleWashErr 
		|| STATE_OFF == funcSit.state 
//		|| f_StepmotorResetIsOver(&nozzleStepmotor) == false
		|| f_StepmotorResetIsOver(&flowStepmotor) == false)//���ϻ����������ڸ�λ(������)
		{
			if (pDriver->index <= WASH_INDEX_WASH)//��ǰ������ϴ
	    	{
				f_FuncWashNext(pDriver, WASH_INDEX_BACK_FLOW);//��������
			}
		}
		else
		{
		    f_FuncWashNext(pDriver, WASH_INDEX_ORG);//��������
            pDriver->bNeedPosBack = false; //������˲���λ��������ϴ(������ϴ)
            funcWashHip.bNeedPosBack = false;//�����������(������˲���λ��������ϴ,������ϴ)������f_FuncWashNext���ʼ����־,������Ҫ�ڵ���֮��
            if (false == pDriver->bNeedPosBack) //������˻أ������ֹͣ
            {
                f_StepmotorStop(pDriver->pHardware->pNozzleSM);
            }
			return true;
		}
    }
    return false;
}

/*****************************************************************************
 �� �� ��: f_FuncWashChangePos
 ��������  : ��ϴ�ı�λ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncWashChangePos(FUNC_WASH *pDriver, sint tag)
{
    if(!f_StepmotorIsAtPos(pDriver->pHardware->pNozzleSM, tag))
	{
		//δ���ﵱǰλ�ã�ǿ�Ƽ������е�Ŀ��λ��
		f_StepmotorSetTarget(pDriver->pHardware->pNozzleSM, tag, true);
		pDriver->flags.m_bits.bPosAtTag = false;
	}
	else 
	{
		pDriver->flags.m_bits.bPosAtTag = true;
	}
}

/*****************************************************************************
 �� �� ��: f_FuncWashChangeFlow
 ��������  : ��ϴ�ı�����λ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncWashChangeFlow(FUNC_WASH *pDriver, sint tag)
{
    if(!f_StepmotorIsAtPos(pDriver->pHardware->pFlowSM, tag))
	{
		//δ���ﵱǰλ�ã�ǿ�Ƽ������е�Ŀ��λ��
		f_StepmotorSetTarget(pDriver->pHardware->pFlowSM, tag, true);
		pDriver->flags.m_bits.bFlowAtTag = false;
	}
	else 
	{
		pDriver->flags.m_bits.bFlowAtTag = true;
	}
}

/*****************************************************************************
 �� �� ��: f_FuncWashPosCtrl
 ��������  : ���λ�ÿ���
 �������:
 �� �� ֵ: 
 ע     ��: ��������Ҫ�ȵ�����pDriver->bChangePos = true,ʹ����˹�λ������λ��
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncWashPosCtrl(FUNC_WASH *pDriver)
{
	sint tag = 0;
	
    if (WASH_INDEX_WASH == pDriver->index)//��ǰ������ϴ
    {
		if (pDriver->flags.m_bits.bEnMove)
		{
			if (pDriver->flags.m_bits.bMoveEnd)
			{
				tag = pDriver->pHardware->pTabPos[pDriver->posLevel] + MOVE_WASH_OFFSET;
			}
			else
			{
				tag = pDriver->pHardware->pTabPos[pDriver->posLevel] - MOVE_WASH_OFFSET;
			}
			
			if(!f_StepmotorIsAtPos(pDriver->pHardware->pNozzleSM, tag))
			{
				f_StepmotorSetTarget(pDriver->pHardware->pNozzleSM, tag, false);//��ǿ�Ƶ�λ
			}
			else 
			{
				pDriver->flags.m_bits.bMoveEnd ^= true;
			}
		}
    }
    
	if (pDriver->index >= WASH_INDEX_SET_POS 
	&& pDriver->index <= WASH_INDEX_WASH)//����������ϴ֮���ܵ���
	{
	    if (pDriver->bChangePos)
	    {
	        pDriver->bChangePos = false;
	    	tag = pDriver->pHardware->pTabPos[pDriver->posLevel];
			if(!f_StepmotorIsAtPos(pDriver->pHardware->pNozzleSM, tag))
			{
				f_StepmotorSetTarget(pDriver->pHardware->pNozzleSM, tag, true);//ǿ�Ƶ�λ
			}
	    }
    }
}

/*****************************************************************************
 �� �� ��: f_FuncSetPos
 ��������  : ���ù�λ
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��12��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncSetPos(FUNC_WASH *pDriver, FUNC_SET_LEVEL pos, uchar bForce)
{
    if (bForce 
    || (false == bForce && pos != pDriver->posLevel)) //��ֹ����λ�÷�������
    {
        pDriver->posLevel = pos;
        pDriver->bChangePos = true;
    }
}

/*****************************************************************************
 �� �� ��: f_FuncSetWashMove
 ��������  : �����ƶ���ϴ
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_FuncSetWashMove(FUNC_WASH *pDriver, STATE_INFO state)
{
	if (WASH_INDEX_WASH == pDriver->index)//��ǰ������ϴ
	{
	    if (state != pDriver->flags.m_bits.bEnMove) //�͵�ǰ����״̬��ͬ
	    {
    		if (STATE_ON == state)
    		{
    			pDriver->flags.m_bits.bEnMove = true;	
    			pDriver->flags.m_bits.bMoveEnd = false; //����ǰ�ƶ�
    		}
    		else
    		{
    			pDriver->flags.m_bits.bEnMove = false;
    			pDriver->bChangePos = true; //��ֹ�ر�ʱ���λ�ò���ȷ
    		}
    		return true;
		}
	}
	return false;
}

/*****************************************************************************
 �� �� ��: f_FuncWashColdHeatCtrl
 ��������  : ���Ȱ�Ħ����
 �������:
 �� �� ֵ: 
 ע     ��: 100ms����
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncWashColdHotCtrl(FUNC_WASH *pDriver)
{
    if (WASH_INDEX_WASH == pDriver->index)//��ǰ������ϴ
    {
		if (pDriver->flags.m_bits.bEnColdHot)
		{
			f_AddU8Data(&(pDriver->coldHotTm));

			if (pDriver->bEnHeat)
			{
				if (pDriver->coldHotTm >= WASH_HOT_TM)
				{
					pDriver->coldHotTm = 0;
					pDriver->bEnHeat = false;
				}
			}
			else
			{
				if (pDriver->coldHotTm >= WASH_COLD_TM)
				{
					pDriver->coldHotTm = 0;
					pDriver->bEnHeat = true;
				}
			}
		}
		else 
		{
			pDriver->bEnHeat = true;
		}
    }
}

/*****************************************************************************
 �� �� ��: f_FuncSetColdHeat
 ��������  : ����������ϴ
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_FuncSetColdHot(FUNC_WASH *pDriver, STATE_INFO state)
{
    if (WASH_INDEX_WASH == pDriver->index)//��ǰ������ϴ
	{
	    if (state != pDriver->flags.m_bits.bEnColdHot) //�͵�ǰ����״̬��ͬ
	    {
    		if (STATE_ON == state)
    		{
    			pDriver->flags.m_bits.bEnColdHot = true;		
    		}
    		else
    		{
    			pDriver->flags.m_bits.bEnColdHot = false;
    		}
    		pDriver->coldHotTm = WASH_HOT_TM; //���������������ϴ
    		return true;
		}
	}
	return false;
}

/*****************************************************************************
 �� �� ��: f_FuncWashFlowCtrl
 ��������  : ��ϴ��������
 �������:
 �� �� ֵ: 
 ע     ��: 100ms����
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncWashFlowCtrl(FUNC_WASH *pDriver)
{
    sint tag = 0;
    
    if (WASH_INDEX_WASH == pDriver->index)//��ǰ������ϴ
    {
		if (pDriver->flags.m_bits.bEnStrongWeak)
		{
			f_AddU8Data(&(pDriver->strongWeakTm));
			if (pDriver->strongWeakTm >= WASH_STRONG_WEAK_GAP_TM)
			{
				pDriver->strongWeakTm = 0;
				if (pDriver->flags.m_bits.bFlowMax)//�Ӹߵ���
				{
					if (pDriver->strongWeakLevel > FUNC_SET_LEVEL_NULL)
					{
						pDriver->strongWeakLevel--;
					}
					else
					{
						pDriver->flags.m_bits.bFlowMax = false;
					}
				}
				else//�ӵ׵���
				{
					if (pDriver->strongWeakLevel < FUNC_SET_LEVEL_3)
					{
						pDriver->strongWeakLevel++;
					}
					else
					{
						pDriver->flags.m_bits.bFlowMax = true;
					}
				}
			}
			pDriver->setPumpPercent = tab_WashPumpPercent[pDriver->strongWeakLevel];
		}
		else 
		{
            //��������
//			pDriver->setPumpPercent = tab_WashPumpPercent[pDriver->flowLevel];
            if (pDriver->flags.m_bits.bEnAirPump)
            {
                pDriver->setPumpPercent = 100;
            }
            else
            {
                pDriver->setPumpPercent = 0;
            }
		}
    }

    if (pDriver->index >= WASH_INDEX_SET_FLOW 
	&& pDriver->index <= WASH_INDEX_WASH)//������������ϴ֮���ܵ���
	{
	    if (pDriver->bChangeFlow)
	    {
	        pDriver->bChangeFlow = false;
	    	tag = pDriver->pHardware->pTabFlow[pDriver->flowLevel];
			if(!f_StepmotorIsAtPos(pDriver->pHardware->pFlowSM, tag))
			{
				f_StepmotorSetTarget(pDriver->pHardware->pFlowSM, tag, true);//ǿ�Ƶ�λ
			}
	    }
    }
}

/*****************************************************************************
 �� �� ��: f_FuncSetFlow
 ��������  : ��������
 �������:    
               
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��12��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncSetFlow(FUNC_WASH *pDriver, FUNC_SET_LEVEL flow, uchar bForce)
{
    if (bForce 
    || (false == bForce && flow != pDriver->flowLevel)) //��ֹ����λ�÷�������
    {
        pDriver->flowLevel = flow;
        pDriver->bChangeFlow = true;
    }
}

/*****************************************************************************
 �� �� ��: f_FuncSetPurge
 ��������  : ��������ͨ�㹦��
 �������  :
 �������  :
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ      :
  1.��    ��   : 2018��6��12��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ɺ���

*****************************************************************************/
uchar f_FuncSetPurge(FUNC_WASH *pDriver, STATE_INFO state)
{   
    uchar ret = false;
    if (WASH_INDEX_WASH == pDriver->index)//��ǰ������ϴ
    {
        pDriver->flags.m_bits.bEnAirPump = state;
        ret = true;
    }
    return ret;
}

/*****************************************************************************
 �� �� ��: f_FuncSetStrongWeak
 ��������  : ǿ����Ħ����
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_FuncSetStrongWeak(FUNC_WASH *pDriver, STATE_INFO state)
{
    if (WASH_INDEX_WASH == pDriver->index)
    {
        if (state != pDriver->flags.m_bits.bEnStrongWeak) //�͵�ǰ����״̬��ͬ
        {
    		if (STATE_ON == state)
    		{
    			pDriver->flags.m_bits.bEnStrongWeak = true;
    			pDriver->strongWeakLevel = pDriver->flowLevel;
    			pDriver->strongWeakTm = 0;
    			pDriver->flags.m_bits.bFlowMax = false;
    		}
    		else
    		{
    			pDriver->flags.m_bits.bEnStrongWeak = false;
    		}
    		return true;
		}
    }
    
    return false;
}

/*****************************************************************************
 �� �� ��: f_FuncWashDeal
 ��������  : ��ϴ���̴���
 �������:
 �� �� ֵ: 
 ע     ��: 100ms����
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncWashStep(FUNC_WASH *pDriver)
{
	f_AddU8Data(&(pDriver->waitTm));
    switch (pDriver->index)
    {
		case WASH_INDEX_ORG://��ԭ��
			//��ˮ���رա����ùر�
			pDriver->bEnInwaterValve = false;
			pDriver->setPumpPercent = 0;
		
			//��˵����ԭ��
			if (pDriver->bNeedPosBack)//�Ƿ�ǿ����Ҫ��
			{
				f_FuncWashChangePos(pDriver, SM_ORG_POS);
			}
			else
			{
				pDriver->flags.m_bits.bPosAtTag = true;
			}

			//���������ԭ��
			f_FuncWashChangeFlow(pDriver, SM_ORG_POS);

			//ˮ�¼��ȹر�
			pDriver->bEnHeat = false;

			//��ǰ���̽����ж�
			if (pDriver->flags.m_bits.bPosAtTag && pDriver->flags.m_bits.bFlowAtTag)
			{
				f_FuncWashNext(pDriver, WASH_INDEX_PER_WASH);
			}
			break;

		case WASH_INDEX_PER_WASH:
			//��ˮ������, ���ùر�
			pDriver->bEnInwaterValve = true;
			pDriver->setPumpPercent = 0;

			//���ȿ���
			pDriver->bEnHeat = true;
			
			//��ǰ���̽����ж�
			if (pDriver->waitTm >= 30)//ǿ��ǰ��ϴ3S��������
			{
				f_FuncWashNext(pDriver, WASH_INDEX_SET_POS);
			}
			break;

		case WASH_INDEX_SET_POS:
			//��ˮ������, ���ùر�
			pDriver->bEnInwaterValve = true;
			pDriver->setPumpPercent = 0;

			//���ȿ���
			pDriver->bEnHeat = true;

			//�������λ��
			f_FuncWashChangePos(pDriver, pDriver->pHardware->pTabPos[pDriver->posLevel]);
			
			//��ǰ���̽����ж�
			if (pDriver->flags.m_bits.bPosAtTag)
			{
				f_FuncWashNext(pDriver, WASH_INDEX_SET_FLOW);
			}
			break;

		case WASH_INDEX_SET_FLOW:
			//��ˮ������, ���ùر�
			pDriver->bEnInwaterValve = true;
			pDriver->setPumpPercent = 0;

			//���ȿ���
			pDriver->bEnHeat = true;

			//TUDO qbj 
//			if (pDriver->waitTm >= 70 
//			|| pDriver)//�ȴ���ʱ ���� ���������¶ȸ���
			{
				//��������λ��
				f_FuncWashChangeFlow(pDriver, pDriver->pHardware->pTabFlow[pDriver->flowLevel]);
			}
			
			//��ǰ���̽����ж�
			if (pDriver->flags.m_bits.bFlowAtTag)
			{
				f_FuncWashNext(pDriver, WASH_INDEX_WASH);

				//������ֵ��Ҫ��f_FuncWashNext����Ϊf_FuncWashNext���������
				pDriver->flags.m_bits.bRealStart = true; //��ʼ������ϴ
			}
			break;
			
		case WASH_INDEX_WASH:
			//��ˮ������, ���ÿ���(��f_FuncWashFlowCtrl����)
			pDriver->bEnInwaterValve = true;

			//���á�������f_FuncWashFlowCtrl��f_FuncWashColdHotCtrl
			
			//�������ⲿ����
			break;

		case WASH_INDEX_BACK_FLOW:
            //��ˮ���ر�, ���ùر�
            pDriver->bEnInwaterValve = false;
            pDriver->setPumpPercent = 0;

            //ˮ�¼��ȹر�
            pDriver->bEnHeat = false;

			//���������ԭ��
			f_FuncWashChangeFlow(pDriver, SM_ORG_POS);
			
			//��ǰ���̽����ж�
			if (pDriver->flags.m_bits.bFlowAtTag)//������λ
			{
				f_FuncWashNext(pDriver, WASH_INDEX_BACK_POS);
			}
			break;
			
		case WASH_INDEX_BACK_POS:
			//��ˮ������, ���ùر�
			pDriver->bEnInwaterValve = true;
			pDriver->setPumpPercent = 0;

			//ˮ�¼��ȹر�
			pDriver->bEnHeat = false;

			if (false == pDriver->flags.m_bits.bPosBackReset)
			{
				//����Ȼ�����λ(�����λ�ø�λ)
				if (false == pDriver->flags.m_bits.bResetCurPos)
				{
				    //���赵λλ��Ϊ�����ǰOFFSETλ�ã������Ḵλ����߻�
				    pDriver->flags.m_bits.bResetCurPos = true;
    				f_StepmotorOffsetCurPos(pDriver->pHardware->pNozzleSM, SM_NOZZLE_MORE_OFFSET);
				}
				f_FuncWashChangePos(pDriver, SM_NOZZLE_MIN_POS);
				
				if (pDriver->flags.m_bits.bPosAtTag)
				{
					pDriver->flags.m_bits.bPosBackReset = true;
					pDriver->flags.m_bits.bPosAtTag = false;
				}
			}
			else
			{
				//��˵����ԭ��
				f_FuncWashChangePos(pDriver, SM_ORG_POS); //��ϴ��ԭ�㣬����ǰ��������ֹ�������
			}

			//��ǰ���̽����ж�
			if (pDriver->flags.m_bits.bPosBackReset 
			&& pDriver->flags.m_bits.bPosAtTag)//��˵�λ
			{
				f_FuncWashNext(pDriver, WASH_INDEX_BACK_WASH);
			}
			break;
			
		case WASH_INDEX_BACK_WASH:
			//��ˮ������, ���ùر�
			pDriver->bEnInwaterValve = true;
			pDriver->setPumpPercent = 0;

			//ˮ�¼��ȹر�
			pDriver->bEnHeat = false;

			//��ǰ���̽����ж�
			if (pDriver->waitTm >= 30)//ǿ�ƺ���ϴ3S�����
			{
				f_FuncWashNext(pDriver, WASH_INDEX_CLEAN);
			}
			break;

		case WASH_INDEX_CLEAN:
			//��ˮ���ر�, ���ô�
			pDriver->bEnInwaterValve = false;
			pDriver->setPumpPercent = 100;

			//ˮ�¼��ȹر�
			pDriver->bEnHeat = false;
			
			//���������λ
			if (pDriver->flags.m_bits.bFlowReset == false)
			{
				pDriver->flags.m_bits.bFlowReset = true;
				f_StepmotorReset(pDriver->pHardware->pFlowSM);
			}

			//��ǰ���̽����ж�
			if (f_StepmotorResetIsOver(pDriver->pHardware->pFlowSM))//���������λ���
			{
				f_FuncWashNext(pDriver, WASH_INDEX_END);
			}
			break;

		case WASH_INDEX_END://��ϴ����
			//��ˮ���ر�, ���ùر�
			pDriver->bEnInwaterValve = false;
			pDriver->setPumpPercent = 0;
		
			//ˮ�¼��ȹر�
			pDriver->bEnHeat = false;
			
			pDriver->flags.m_byte = 0;
			pDriver->bNeedPosBack = true;
			pDriver->bChangeFlow = false;
			pDriver->bChangePos = false;
			break;

		default:
			break;
    }
}

/*****************************************************************************
 �� �� ��: f_FuncWashDeal
 ��������  : ��ϴ��ش���
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��19��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncWashDeal(void)
{
	uchar percent;
	
    f_FuncWashStep(&funcWashHip);//�β���ϴ����
	f_FuncWashPosCtrl(&funcWashHip);
	f_FuncWashFlowCtrl(&funcWashHip);
	f_FuncWashColdHotCtrl(&funcWashHip);	

	f_FuncWashStep(&funcWashFemale);//Ů����ϴ����
	f_FuncWashPosCtrl(&funcWashFemale);
	f_FuncWashFlowCtrl(&funcWashFemale);
	f_FuncWashColdHotCtrl(&funcWashFemale);

	//====���ؿ���====
	//����Խ����
	if (functionInfo.bCleanPosCtrl)
	{
	    functionInfo.bCleanPosCtrl = false;
    	if(functionInfo.bSelfClean)
    	{
    		f_StepmotorSetTarget(&nozzleStepmotor, SM_NOZZLE_MAX_POS, true);//ǿ�Ƶ����
    	}
    	else
    	{
    		f_StepmotorSetTarget(&nozzleStepmotor, SM_ORG_POS, true);//ǿ�ƻָ�
    	}
	}
	
	//��ˮ������
	if (funcWashHip.bEnInwaterValve 
	|| funcWashFemale.bEnInwaterValve 
	|| functionInfo.bSelfClean 
	|| funcSit.bClean)
	{
		f_FuncSetInwaterValve(STATE_ON);	
//		f_FuncSetUV(STATE_ON);
	}
	else
	{
		f_FuncSetInwaterValve(STATE_OFF);
//		f_FuncSetUV(STATE_OFF);
	}

	//���ÿ���
	percent = funcWashHip.setPumpPercent > funcWashFemale.setPumpPercent? funcWashHip.setPumpPercent:funcWashFemale.setPumpPercent;
	f_FuncSetAirPump(percent);

	//====ˮ�´���====
    if ((funcWashHip.bEnHeat || funcWashFemale.bEnHeat) && functionInfo.waterTempLevel > FUNC_SET_LEVEL_NULL)
    {
		functionInfo.bEnHeat = true;
		functionInfo.outTempInfo.setTemp = realWatHeatTemp[functionInfo.waterTempLevel];
    }
    else
    {
		functionInfo.bEnHeat = false;
		functionInfo.outTempInfo.setTemp = 0;
    }
}

/*****************************************************************************
 �� �� ��: f_FuncWashInit
 ��������: ��ϴ������ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��11��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_FuncWashInit(FUNC_WASH *pDriver, const FUNC_WASH_HARDWARE *pHardware)
{
    f_Memset(pDriver, 0, sizeof(FUNC_WASH));
    pDriver->pHardware = pHardware;
    pDriver->index = WASH_INDEX_END;
    pDriver->bNeedPosBack = true;
}

