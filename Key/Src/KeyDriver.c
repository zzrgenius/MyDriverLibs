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

  2.日    期   : 2018年4月16日
    作    者   : 钱百静
    修改内容   : 1、增加按键卡住剔除处理
    		  2、增加强制独立按键处理支持

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
 #include "KeyDriver.h"
 #include "SubFunction.h"
 #include "TimeFlag.h"

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
//独立处理按键
#if (KEY_DRIVER_INDE_KEY_NUM > 0)
	KEY_DRIVER_INDE_KEY keyDriverIndeKey[KEY_DRIVER_INDE_KEY_NUM];
#endif

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

/*****************************************************************************
 函 数 名: uchar f_IsSingleKey(ulong KeyName)
 功能描述: 判断当前按键是否为单键
 输入参数:
 返 回 值: 
 注     意: 目前强制为32位数据
 
 修改历史:
  1.日    期   : 2018年4月14日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_IsSingleKey(ulong KeyName)
{
	uchar i;
	uchar enKeyCnt = 0;
	for (i = 0; i < 32; i++)
	{
	    if ((KeyName>>i) & 0x01)
	    {
			if ( ++enKeyCnt >= 2)
			{
				return false;
			}
	    }
    }

    return true;
}

/*****************************************************************************
 函 数 名: f_IndependentKeyDeal
 功能描述  : 独立处理按键，即使多个按键按下，需要分别产生不同独立按键响应。
 			多个独立按键同时产生状态时依次外发(间隔10ms)
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年4月14日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
#if (KEY_DRIVER_INDE_KEY_NUM > 0)
void f_IndependentKeyDeal(KEY_DRIVER        *pKeyDriver)
{
	uchar i;
	uchar stateIndex;

	//独立按键处理
	for (i = 0; i < KEY_DRIVER_INDE_KEY_NUM; i++)
	{
		keyDriverIndeKey[i].newName = pKeyDriver->data.newName & Tab_IndeKeyValue[i];
		f_AddU16Data(&(keyDriverIndeKey[i].pressTm));//按下时间累加
	
		switch (keyDriverIndeKey[i].dealStep)
		{
			case KEY_DEAL_IDLE://按键空闲状态
				keyDriverIndeKey[i].pressTm = 0;

				//有按键按下
				if (KEY_DRIVER_NO_KEY != keyDriverIndeKey[i].newName)
				{
					keyDriverIndeKey[i].dealStep = KEY_DEAL_PRESS;
					keyDriverIndeKey[i].state |= KEY_PRESSED;//产生按下信息
				}
				keyDriverIndeKey[i].name = keyDriverIndeKey[i].newName;
				break;

			case KEY_DEAL_PRESS://按键按下状态
				#ifdef KEY_DONE_OVER
					//按键释放或者已经处理
					if (KEY_DRIVER_NO_KEY == keyDriverIndeKey[i].newName || f_GetKeyDealDone(keyDriverIndeKey[i].name))
					{
						keyDriverIndeKey[i].pressTm = 0;
						keyDriverIndeKey[i].dealStep = KEY_DEAL_WATE_RELEASE;
					}
				#else
					//按键释放
					if (KEY_DRIVER_NO_KEY == keyDriverIndeKey[i].newName)
					{
						keyDriverIndeKey[i].pressTm = 0;
						keyDriverIndeKey[i].dealStep = KEY_DEAL_WATE_RELEASE;
					}
					#endif
				break;

			case KEY_DEAL_WATE_RELEASE://按键等待释放状态
				if (KEY_DRIVER_NO_KEY == keyDriverIndeKey[i].newName)
				{
					keyDriverIndeKey[i].dealStep = KEY_DEAL_IDLE;
					if (!f_GetKeyDealDone(keyDriverIndeKey[i].name))
					{
						keyDriverIndeKey[i].state = 0; //清除所有状态
						keyDriverIndeKey[i].state |= KEY_RELEASE;
					}
				}
				break;

			default:
				keyDriverIndeKey[i].name = KEY_DRIVER_NO_KEY;
				keyDriverIndeKey[i].newName = KEY_DRIVER_NO_KEY;
				keyDriverIndeKey[i].dealStep = KEY_DEAL_IDLE;
				break;
		}

		//自定义状态产生
		for (stateIndex = 0; (keyDriverIndeKey[i].pressTm > 0) && (f_SetKeyTimeState(stateIndex) != KEY_STATE_RESERVE); stateIndex++)
		{
			//按键状态只产生一次
			if (keyDriverIndeKey[i].pressTm == f_GetKeyStateTime(stateIndex))
			{
				//等待释放时，只产生卡死状态
				if (KEY_DEAL_WATE_RELEASE ==keyDriverIndeKey[i].dealStep
				&& KEY_LOCKED != f_SetKeyTimeState(stateIndex))
				{
					break;
				}

				keyDriverIndeKey[i].state |= f_SetKeyTimeState(stateIndex);
				break;
			}
		}

		//当前按键有新状态产生-按倒序发送
		if (KEY_STATE_IDLE != keyDriverIndeKey[i].state)
		{
			//通过通用的数据接口向外提供信息
			pKeyDriver->data.name = keyDriverIndeKey[i].name;
			pKeyDriver->data.state = keyDriverIndeKey[i].state;

			keyDriverIndeKey[i].state = KEY_STATE_IDLE;
		}
	}			
}
#endif
 
/*****************************************************************************
 函 数 名: void f_KeyDriverTimer(KeyDriver const *pKeyDriver)
 功能描述: 
 输入参数: pKeyDriver：按键驱动指针
 返 回 值: 
 注     意: 系统10ms时基调用
 
 修改历史:
  1.日    期   : 2018年4月11日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_KeyDriverDeal(KEY_DRIVER       *pKeyDriver)
{
	uchar i;

	//系统10ms判断

	//指针有效性判断，判断是否成功注册
	if (NULL == pKeyDriver->pHardDriver || NULL == pKeyDriver->dealCallback)
	{
		return;	
	}

	//按键输入获取
	pKeyDriver->pHardDriver->GetKeys(pKeyDriver);
	
	//按键掩码处理，防止卡按键影响
	pKeyDriver->data.mask |= ~(pKeyDriver->data.getKeys);//一旦对应的按键释放,该位mask恢复
	pKeyDriver->data.newName = pKeyDriver->data.getKeys & pKeyDriver->data.mask;

	f_AddU16Data(&(pKeyDriver->data.pressTm));//按下时间累加
	switch (pKeyDriver->dealStep)
	{
		case KEY_DEAL_IDLE://按键空闲状态
			pKeyDriver->data.pressTm = 0;
			pKeyDriver->data.keyDone = 0;
			pKeyDriver->data.state = KEY_STATE_IDLE;
			pKeyDriver->flag.byte = 0;

			//有按键按下
			if (KEY_DRIVER_NO_KEY != pKeyDriver->data.newName)
			{
				pKeyDriver->dealStep = KEY_DEAL_PRESS;
				pKeyDriver->data.state |= KEY_PRESSED;//产生按下信息
			}
			pKeyDriver->data.name = pKeyDriver->data.newName;
			break;

		case KEY_DEAL_PRESS://按键按下状态
			pKeyDriver->flag.bits.bHasKey = true;
			
			//按键变化则重新检测按键
			if (pKeyDriver->data.name != pKeyDriver->data.newName)
			{
				if (f_IsSingleKey(pKeyDriver->data.name) 
				&& KEY_DRIVER_NO_KEY != pKeyDriver->data.newName)
				{
					//单键变化则重新检测(新的组合)
					pKeyDriver->dealStep = KEY_DEAL_IDLE;
				}
				else
				{
					//组合键则先等待释放/直接释放
					pKeyDriver->dealStep = KEY_DEAL_WATE_RELEASE;
				}
			}

			#ifdef KEY_DONE_OVER
				//按键已处理则等待释放,不产生有用状态
				if (f_GetKeyDealDone(pKeyDriver->data.name))
				{
					pKeyDriver->dealStep = KEY_DEAL_WATE_RELEASE;
				}
			#endif
			break;

		case KEY_DEAL_WATE_RELEASE://按键等待释放状态
			//等待全部按键释放,释放时产生释放状态,按键已处理不产生释放信息
			if (KEY_DRIVER_NO_KEY == pKeyDriver->data.newName)
			{
				pKeyDriver->dealStep = KEY_DEAL_IDLE;

				if (!f_GetKeyDealDone(pKeyDriver->data.name))
				{
					pKeyDriver->data.state = 0; //清除所有状态
					pKeyDriver->data.state |= KEY_RELEASE;
				}
			}
			else
			{
				//为按键变化时，重新检测新按键是否可能卡死
				if (pKeyDriver->data.name != pKeyDriver->data.newName)
				{
					pKeyDriver->data.pressTm = 0;
					pKeyDriver->data.name = pKeyDriver->data.newName;
				}
			}
			break;

		default:
			pKeyDriver->data.name = KEY_DRIVER_NO_KEY;
			pKeyDriver->data.newName = KEY_DRIVER_NO_KEY;
			pKeyDriver->dealStep = KEY_DEAL_IDLE;
			break;
	}

	//自定义状态产生
	for (i = 0; (pKeyDriver->data.pressTm > 0) && (f_SetKeyTimeState(i) != KEY_STATE_RESERVE); i++)
	{
		//按键状态只产生一次
		if (pKeyDriver->data.pressTm == f_GetKeyStateTime(i))
		{
			//等待释放时，只产生卡死状态
			if (KEY_DEAL_WATE_RELEASE == pKeyDriver->dealStep
			&& KEY_LOCKED != f_SetKeyTimeState(i))
			{
				break;
			}
			
			pKeyDriver->data.state |= f_SetKeyTimeState(i);
			break;
		}
	}
	
	//独立按键获取
	#if (KEY_DRIVER_INDE_KEY_NUM > 0)
		f_IndependentKeyDeal(pKeyDriver);
	#endif

	//按键卡死状态处理
	if (f_IsKeyState(KEY_LOCKED))
	{
		//认为卡住，将按键移除检测，当按键恢复时会自动重新添加进入检测
		f_RemoveKey(pKeyDriver->data.getKeys);
		f_SetKeyDealDone();
	}
	
	//按键处理函数
	pKeyDriver->dealCallback(pKeyDriver);

	//处理后数据清除
	if (f_GetKeyDealDone(pKeyDriver->data.name))
	{
		pKeyDriver->data.state = KEY_STATE_IDLE;
	}
}

/*****************************************************************************
 函 数 名: void f_KeyDriverInit( KeyDriver const *pKeyDriver,
							KeyHardwareDriver const *pKeyDriverHardware, 
							KeyDriverCallback const pKeyDealFunc)
 功能描述: 
 输入参数: pKeyDriver:按键驱动指针; 
 		   pKeyDriverHardware：按键驱动硬件层指针; 
 		   pKeyDealFunc:按键处理回调函数
 返 回 值: 
 注     意: 初始化注册调用一次
 
 修改历史:
  1.日    期   : 2018年4月11日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_KeyDriverInit( KEY_DRIVER *pKeyDriver,
							const KEY_HARDWARE_DRIVER *pKeyDriverHardware, 
							const KeyDriverCallback pKeyDealFunc)
{
	f_Memset(pKeyDriver, 0, sizeof(KEY_DRIVER));
	pKeyDriver->data.mask = KEY_DRIVER_ALL_KEY;
	pKeyDriver->pHardDriver = pKeyDriverHardware;
	pKeyDriver->dealCallback = pKeyDealFunc;
}


