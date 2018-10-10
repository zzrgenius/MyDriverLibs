/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : KeyDriver.c
  版 本 号   : 初稿
  作    者   : 钱百静
  生成日期   : 2018年4月10日
  最近修改   :
  功能描述   : 通用按键处理驱动模块,统一产生按键信息用于应用层处理
  函数列表   :
  修改历史   :
  1.日    期   : 2018年4月10日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
 #include "KeyDriver.h"

/*----------------------------------------------*
 * 外部变量说明                                       *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/
 #define KEY_DRIVER_NO_KEY 0

/*****************************************************************************
 函 数 名: void f_KeyDriverTimer(   KeyDriver const *pKeyDriver)
 功能描述: 
 输入参数: 按键驱动指针
 返 回 值: 
 注     意: 系统10ms时基调用
 
 修改历史:
  1.日    期   : 2018年4月11日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_KeyDriverDeal(   KeyDriver const *pKeyDriver)
{
	uchar i;
	//按键输入获取
	if (NULL == pKeyDriver->pHardDriver)
	{
		return;	
	}
	pKeyDriver->pHardDriver(pKeyDriver);

	switch (pKeyDriver->keyDealStep)
	{
		case KEY_DEAL_IDLE://按键空闲状态
			pKeyDriver->keyData.keyPressTm = 0;
			pKeyDriver->keyData.keyName = KEY_DRIVER_NO_KEY;

			//有按键按下
			if (KEY_DRIVER_NO_KEY != pKeyDriver->keyData.newKeyName)
			{
				pKeyDriver->keyDealStep = KEY_DEAL_PRESS;
				pKeyDriver->keyData.keyState |= KEY_PRESSED;//产生按下信息
			}
			pKeyDriver->keyData.keyName = pKeyDriver->keyData.newKeyName;
			
			break;

		case KEY_DEAL_PRESS://按键按下状态
			pKeyDriver->keyFlag.bit.bHasKey = true;
			
			if (pKeyDriver->keyData.keyPressTm < 0xffff)//后续用通用函数处理
			{
				pKeyDriver->keyData.keyPressTm ++;
			}
		
			if (pKeyDriver->keyFlag.bit.bKeyDeal)//当前产生的按键信息已处理,直接等待释放
			{
				pKeyDriver->keyDealStep = KEY_DEAL_WATE_RELEASE;
			}

			//自定义状态产生
			for (i = 0; ; i++)
			{
				if (SetTimeInf(i) == 0xff)
				{
					break;
				}

				//按键状态只产生一次
				if (pKeyDriver->keyData.keyPressTm == GetTime(i))
				{
					pKeyDriver->keyData.keyState |= SetTimeInf(i);
					break;
				}
			}

			break;

		case KEY_DEAL_WATE_RELEASE://按键等待释放状态
			//等待全部按键释放,释放时产生释放状态,按键已处理不产生释放信息
			if (KEY_DRIVER_NO_KEY == pKeyDriver->keyData.newKeyName)
			{
				pKeyDriver->keyDealStep = KEY_DEAL_IDLE;

				if (!pKeyDriver->keyFlag.bit.bKeyDeal)
				{
					pKeyDriver->keyData.keyState |= KEY_RELEASE;
				}
			}
			break;

		default:
			pKeyDriver->keyData.keyName = KEY_DRIVER_NO_KEY;
			pKeyDriver->keyData.newKeyName = KEY_DRIVER_NO_KEY;
			pKeyDriver->keyDealStep = KEY_DEAL_IDLE;
			break;
	}

	//按键处理函数

	//处理后数据清除
	pKeyDriver->keyData.keyState = KEY_IDLE;
}


/*****************************************************************************
 函 数 名: f_test
 功能描述: 
 输入参数: 无
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月11日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
UINT32_T  f_test( # )
{
    #
}

