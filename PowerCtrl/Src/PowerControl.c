/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : PowerControl.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��4��13��
  ����޸�   :
  ��������   : ���ں��������Ŀɿع����(��MOC3063M),�ɰ�һ���벨���ȿ��ơ�Ŀǰ�Ȱ�50HZ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��4��13��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
 #include "DataType.h"
 #include "SubFunction.h"

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

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define POWER_PERIOD_TM	100 //��Դ����*0.1ms- 50HZ 
const uint setGroupPeriodTm	= POWER_CTRL_GROUP_NUM*POWER_PERIOD_TM;//ÿ��������

//����˳���
const uchar tab_PowerCalcIndex[POWER_CTRL_GROUP_NUM]
={0, 5, 2, 7, 4, 9, 1, 6, 3, 8};


/*****************************************************************************
 �� �� ��: void f_PowerCtrlOut(POWER_CTRL *pPowerCtrl)
 ��������: ���ڹ��ʿ������
 �������:
 �� �� ֵ: 
 ע     ��: 100us�жϵ���
 
 �޸���ʷ:
  1.��    ��   : 2018��4��14��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_PowerCtrlOut(POWER_CTRL *pPowerCtrl)
{
    f_AddU16Data(&(pPowerCtrl->data.periodTm));

	//����������δ��
    if (pPowerCtrl->data.periodTm <= setGroupPeriodTm)
    {
   		if (NULL != pPowerCtrl->pHardwareFunc)
		{
			//�ײ�Ӳ������
			if (pPowerCtrl->data.periodTm <= pPowerCtrl->data.periodOnTm[pPowerCtrl->data.ctrlGroupIndex])
			{
				pPowerCtrl->pHardwareFunc(pPowerCtrl, POWER_CTRL_ON);
			}
			else
			{
				pPowerCtrl->pHardwareFunc(pPowerCtrl, POWER_CTRL_OFF);
			}
		}
    }
    else
    {
    	//���������ڽ���,ת��һ������
		pPowerCtrl->data.periodTm = 0;
		pPowerCtrl->data.ctrlGroupIndex ++;
		if (pPowerCtrl->data.ctrlGroupIndex >= POWER_CTRL_GROUP_NUM)
		{
			pPowerCtrl->data.ctrlGroupIndex = 0;
		}
    }
}

/*****************************************************************************
 �� �� ��: f_PowerCtrlCalc
 ��������  : ��������Ĺ��ʰٷֱȻ�����Ҫ�����ر�ʱ��              
 �������: pPowerCtrl:���ʿ�������ָ��;
 		   percent�����ưٷֱ�
 �� �� ֵ: 
 ע     ��: ��Ҫʱ����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��14��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_PowerCtrlCalc(POWER_CTRL *pPowerCtrl, uchar percent)
{
	uchar needOnGroupNum;
	uchar needOnPartNum;
	uchar i;

    //��󲻳���100%
	if(percent > 100)
	{
		percent = 100;
	}

	needOnGroupNum = percent/POWER_CTRL_GROUP_NUM;//ÿ�鶼����ʱ�䲿��	
	needOnPartNum = percent%POWER_CTRL_GROUP_NUM;//ʣ�ಿ��

	//����ÿ�鶼�ӵİٷֱ�
	for(i = 0; i < POWER_CTRL_GROUP_NUM; i ++)
	{
		pPowerCtrl->data.periodOnTm[tab_PowerCalcIndex[i]] = (uint)(needOnGroupNum)*POWER_PERIOD_TM;
	}

    //ʣ�����ȿ��Ƶ���,ÿ���1%,�Ȱ����Ƶʱ��
    for(i = 0; i < needOnPartNum; i ++)
    {
        pPowerCtrl->data.periodOnTm[tab_PowerCalcIndex[i]] += POWER_PERIOD_TM;
    }
}

/*****************************************************************************
 �� �� ��: f_PowerCtrlInit
 ��������  : ���ʿ���������ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��14��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_PowerCtrlInit(POWER_CTRL *pPowerCtrl, const PowerCtrlHardware pFunc)
{
    f_Memset(pPowerCtrl, 0, sizeof(POWER_CTRL));
    pPowerCtrl->pHardwareFunc = pFunc;
}

