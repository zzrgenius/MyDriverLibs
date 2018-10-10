#define VAR_SUBFUNCTION_GLOBALS
#include "Include.h"

/*=========================================================
* 功能描述:  内存复制
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
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
* 功能描述:  校验和
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
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
* 功能描述:  异或校验和
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
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
* 功能描述: 获取传感器参数的驱动函数
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
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
* 功能描述:  清除模式运行时间小时
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_ClearRunTimeH(hour_def *nTempHourDef)
{
	nTempHourDef -> hour = 0;
	nTempHourDef -> minute = 0;
	nTempHourDef -> second = 0;
}

/*=========================================================
* 功能描述:  清除模式运行时间分钟
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void f_ClearRunTimeM(minute_def *nTempMinDef)
{
	nTempMinDef -> minute = 0;
	nTempMinDef -> second = 0;
}

/*=========================================================
* 功能描述:  计算运行时间,如果到60秒则分加1,并保存各时间最大值
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
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
* 功能描述:  计算运行时间,如果到60分则时加1,并保存各时间最大值
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
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
* 功能描述:  无符号字符自加
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void AddCharData(uchar *nTempCharBuff)
{
	(*nTempCharBuff) ++;
	if((*nTempCharBuff) > 250)
		(*nTempCharBuff) = 250;
}
/*=========================================================
* 功能描述:  无符号字符自减
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void DecCharData(uchar *nTempIntBuff)
{
	if(*nTempIntBuff)
		(*nTempIntBuff) --;
}
/*=========================================================
* 功能描述:  无符号整形自加
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void AddIntData(uint *nTempIntBuff)
{
	(*nTempIntBuff) ++;
	if((*nTempIntBuff) > 65530)
		(*nTempIntBuff) = 65530;
}
/*=========================================================
* 功能描述:  无符号整形自减
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
void DecIntData(uint *nTempIntBuff)
{
	if(*nTempIntBuff)
		(*nTempIntBuff) --;
}
/*=========================================================
* 功能描述:  将给定数组的前多少位加和去掉进位
* 修改日期	修改人		修改说明
* 2017-11-10		朱峰 			完成基本功能
=========================================================*/
uchar AddTotalNum(uchar *nBuff,uchar nEndNo)
{
	uchar i,nTotalSum;
	nTotalSum = 0;
	for(i = 0; i < nEndNo; i ++)
		nTotalSum += nBuff[i];
	return nTotalSum;
}