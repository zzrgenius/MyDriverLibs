#define VAR_SUBFUNCTION_GLOBALS
#include "Include.h"

/*=========================================================
* ��������:  �ڴ渴��
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void *f_Memcpy(void *dest,const void *src, uint nSize)
{
	uchar *mov = src;
	uchar *mov_to = dest;

	if(src == NULL || dest == NULL)
	{
		return NULL;
	}
	
	while(nSize --)
	{
		*mov_to++ = *mov++;
	}

	return(mov_to);
}

/*=========================================================
* ��������:  У���
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
uint f_CheckSum(uchar *nBuff,uchar nStartNo,uchar nEndNo)
{
	uchar i;
	uint nTotalSum;
	nTotalSum = 0;
	for(i = nStartNo; i < nEndNo; i ++)
	{
		nTotalSum += nBuff[i];
	}
	return nTotalSum;
}

/*=========================================================
* ��������:  ���У���
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
uint f_XorSum(uchar *nBuff,uchar nStartNo,uchar nEndNo)
{
	uchar i;
	uint nTotalSum;
	nTotalSum = nStartNo;
	for(i = (nStartNo+1); i < nEndNo; i ++)
	{
		nTotalSum ^= nBuff[i];
	}
	return nTotalSum;
}

/*=========================================================
* ��������: ��ȡ��������������������
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void f_GetSWState(uchar bIOstate, LEVEL_SWITCH_INF *pSwInf, uint needOnTm, uint needOffTm)
{
	if(bIOstate)
	{
		AddIntData(&(pSwInf->nKeepOnTm));
		pSwInf->nKeepOffTm = 0;
		if(pSwInf->nKeepOnTm >= needOnTm)
		{
			pSwInf->bSwitchState = SW_ON;
		}
	}
	else
	{
		AddIntData(&(pSwInf->nKeepOffTm));
		pSwInf->nKeepOnTm = 0;
		if(pSwInf->nKeepOffTm >= needOffTm)
		{
			pSwInf->bSwitchState = SW_OFF;
		}
	}
}

/*=========================================================
* ��������:  ���ģʽ����ʱ��Сʱ
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void f_ClearRunTimeH(hour_def *nTempHourDef)
{
	nTempHourDef -> hour = 0;
	nTempHourDef -> minute = 0;
	nTempHourDef -> second = 0;
}

/*=========================================================
* ��������:  ���ģʽ����ʱ�����
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void f_ClearRunTimeM(minute_def *nTempMinDef)
{
	nTempMinDef -> minute = 0;
	nTempMinDef -> second = 0;
}

/*=========================================================
* ��������:  ��������ʱ��,�����60����ּ�1,�������ʱ�����ֵ
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void f_AddRunTimerM(minute_def *nTempMinDef)
{
	if(nReducedTime)
		nTempMinDef -> second += 10;
	else
		nTempMinDef -> second ++;
	if((nTempMinDef -> second >= 60))
	{
		nTempMinDef -> second = 0;
		nTempMinDef -> minute ++;
		if(nTempMinDef -> minute >= 65530)
			nTempMinDef -> minute = 65530;
	}
}
/*=========================================================
* ��������:  ��������ʱ��,�����60����ʱ��1,�������ʱ�����ֵ
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void f_AddRunTimerH(hour_def *nTempHourDef)
{
	if(nReducedTime)
		nTempHourDef->second += 10;
	else
		nTempHourDef->second ++;
	if(nTempHourDef->second >= 60)
	{
		nTempHourDef->second = 0;
		nTempHourDef->minute ++;
		if(nTempHourDef->minute >= 60)
		{
			nTempHourDef->minute = 0;
			nTempHourDef->hour++;
			if(nTempHourDef->hour > 65530)
			{
				nTempHourDef->hour = 65530;
			}
		}
	}
}

/*=========================================================
* ��������:  �޷����ַ��Լ�
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void AddCharData(uchar *nTempCharBuff)
{
	(*nTempCharBuff) ++;
	if((*nTempCharBuff) > 250)
		(*nTempCharBuff) = 250;
}
/*=========================================================
* ��������:  �޷����ַ��Լ�
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void DecCharData(uchar *nTempIntBuff)
{
	if(*nTempIntBuff)
		(*nTempIntBuff) --;
}
/*=========================================================
* ��������:  �޷��������Լ�
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void AddIntData(uint *nTempIntBuff)
{
	(*nTempIntBuff) ++;
	if((*nTempIntBuff) > 65530)
		(*nTempIntBuff) = 65530;
}
/*=========================================================
* ��������:  �޷��������Լ�
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
void DecIntData(uint *nTempIntBuff)
{
	if(*nTempIntBuff)
		(*nTempIntBuff) --;
}
/*=========================================================
* ��������:  �����������ǰ����λ�Ӻ�ȥ����λ
* �޸�����	�޸���		�޸�˵��
* 2017-11-10		��� 			��ɻ�������
=========================================================*/
uchar AddTotalNum(uchar *nBuff,uchar nEndNo)
{
	uchar i,nTotalSum;
	nTotalSum = 0;
	for(i = 0; i < nEndNo; i ++)
		nTotalSum += nBuff[i];
	return nTotalSum;
}