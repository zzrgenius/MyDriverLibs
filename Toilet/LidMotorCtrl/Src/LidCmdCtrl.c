/******************************************************************************

                  版权所有 (C), 2008-2018, 杭州信多达电器有限公司

 ******************************************************************************
  文 件 名   : LidCmdCtrl.c
  版 本 号   : V1.0
  作    者   : 钱百静
  生成日期   : 2018年5月15日
  最近修改   :
  功能描述   : 翻盖命令处理
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月15日
    作    者   : 钱百静
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "HeadInclude.h"
#include "LidMotorHardware.h"

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
LID_CMD_CTRL AT_NEAR lidCmdCtrl;

/*----------------------------------------------*
 * 常量定义                                         *
 *----------------------------------------------*/
//速度调节顺序
schar* const tab_speedIndex[] =
{
	&lidCmdCtrl.seatLidMotor.data.fwdOffset,
	&lidCmdCtrl.seatLidMotor.data.revOffset,
	&lidCmdCtrl.topLidMotor.data.fwdOffset,
	&lidCmdCtrl.topLidMotor.data.revOffset
};

/*----------------------------------------------*
 * 宏定义                                          *
 *----------------------------------------------*/

/*****************************************************************************
 函 数 名: f_LidCmdSetCmd
 功能描述  : 设置当前命令
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月15日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
uchar f_LidCmdSetCmd(LID_CMD_CTRL *pDriver, LID_MOTOR_CMD cmd, uchar fource)
{
	uchar ret = false;
	
	pDriver->cmdRunTm = 0;
    pDriver->bCmdSeatDeal = false;
    pDriver->bCmdTopDeal = false;
    
    //强制
	if (fource || LID_RUN_CMD_NULL == cmd)
	{
		pDriver->setCMD = cmd;
	    ret = true;
	}
	else
	{
		if (STATE_ON == funcSit.sitSwitch.state
		|| SYS_STATE_STANDBY == systemInfo.sysState)//着座/关机功能无效/已插电机pDriver->bWithMotor
		{
			pDriver->setCMD = LID_RUN_CMD_NULL;
		}
		else
		{
		    pDriver->setCMD = cmd;
		    ret = true;
		    
	    }
	}
    return ret;
}

/*****************************************************************************
 函 数 名: f_LidCmdDeal
 功能描述  : 翻盖翻圈命令处理
 输入参数:
 返 回 值: 
 注     意: 10ms
 
 修改历史:
  1.日    期   : 2018年5月15日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_LidCmdDeal(LID_CMD_CTRL *pDriver)
{
	LID_MOTOR_DIR dir;

	//====手动判断(仅离座判断)====
	if (STATE_OFF == funcSit.sitSwitch.state
	&& systemInfo.powerOnTm > 1)//上电1S稳定后
	{
		pDriver->handleCheckTm++;
		if (pDriver->handleCheckTm >= 5)// 50ms检测一次
		{
			pDriver->handleCheckTm = 0;
			
			//翻圈手动判断
		    dir = f_LidMotorHandleCheck(&pDriver->seatLidMotor, pDriver->lastSeatPos);
	    	pDriver->lastSeatPos = pDriver->seatLidMotor.data.curAngle;

		    if (MOTOR_DIR_REV == dir)//反转
		    {
		    	f_LidCmdSetCmd(pDriver, LID_RUN_CMD_HANDLE, false); //手动
		    	pDriver->setSeatDir = MOTOR_DIR_REV;
		    	pDriver->bSetSeatDir = true;
		    }
		    else if (MOTOR_DIR_FWD == dir)//正转
		    {
				f_LidCmdSetCmd(pDriver, LID_RUN_CMD_ALL_OPEN, false); //全开
		    }
		   
		    //翻盖手动判断
		    dir = f_LidMotorHandleCheck(&pDriver->topLidMotor, pDriver->lastTopPos);
		    pDriver->lastTopPos = pDriver->topLidMotor.data.curAngle;
		    if (MOTOR_DIR_REV == dir)//反转
		    {
				f_LidCmdSetCmd(pDriver, LID_RUN_CMD_ALL_CLOSE, false); //全关
		    }
		    else if (MOTOR_DIR_FWD == dir)//正转
		    {
		    	f_LidCmdSetCmd(pDriver, LID_RUN_CMD_HANDLE, false); //手动
		    	pDriver->setTopDir = MOTOR_DIR_FWD;
		    	pDriver->bSetTopDir = true;
		    }
	    }
    }
    else
    {
		pDriver->lastSeatPos = pDriver->seatLidMotor.data.curAngle;
		pDriver->lastTopPos = pDriver->topLidMotor.data.curAngle;
    }

	//====命令处理====
    if (LID_RUN_CMD_ALL_OPEN == pDriver->setCMD)//全开
    {
    	MOTOR_RELAY(STATE_ON);
    	//先运行翻盖
    	if (pDriver->bCmdTopDeal == false)
    	{
    		pDriver->bCmdTopDeal = true;
    		pDriver->setTopDir = MOTOR_DIR_FWD;
    		pDriver->bSetTopDir = true;
    	}

		//上盖已运行到中位置以上,座圈启动
    	if (f_LidMotorIsOverMid(&pDriver->topLidMotor) == true)
    	{
			if (pDriver->bCmdSeatDeal == false)
	    	{
	    		pDriver->bCmdSeatDeal = true;
	    		pDriver->setSeatDir = MOTOR_DIR_FWD;
	    		pDriver->bSetSeatDir = true;
	    	}
    	}
    }
    else if (LID_RUN_CMD_ALL_CLOSE == pDriver->setCMD)//全关
    {
    	MOTOR_RELAY(STATE_ON);
    	//先运行翻圈
    	if (pDriver->bCmdSeatDeal == false)
    	{
    		pDriver->bCmdSeatDeal = true;
    		pDriver->setSeatDir = MOTOR_DIR_REV;
    		pDriver->bSetSeatDir = true;
    	}

		//座圈已运行到中位置以下,盖板启动
    	if (f_LidMotorIsOverMid(&pDriver->seatLidMotor) == false)
    	{
			if (pDriver->bCmdTopDeal == false)
	    	{
	    		pDriver->bCmdTopDeal = true;
	    		pDriver->setTopDir = MOTOR_DIR_REV;
	    		pDriver->bSetTopDir = true;
	    	}
    	}
    }
    else if (LID_RUN_CMD_HALF == pDriver->setCMD)//半开
    {
    	MOTOR_RELAY(STATE_ON);
    	//翻圈
    	if (pDriver->bCmdSeatDeal == false)
    	{
    		pDriver->bCmdSeatDeal = true;
    		pDriver->setSeatDir = MOTOR_DIR_REV;
    		pDriver->bSetSeatDir = true;
    	}

		//翻盖
		if (pDriver->bCmdTopDeal == false)
    	{
    		pDriver->bCmdTopDeal = true;
    		pDriver->setTopDir = MOTOR_DIR_FWD;
    		pDriver->bSetTopDir = true;
    	}
    }

    
    if (LID_RUN_CMD_NULL != pDriver->setCMD)//非停止
    {
    	MOTOR_RELAY(STATE_ON);
    }
    else 
    {
    	MOTOR_RELAY(STATE_OFF);
    	pDriver->setSeatDir = MOTOR_DIR_STOP;
    	pDriver->setTopDir = MOTOR_DIR_STOP;
    	pDriver->bSetSeatDir = true;
    	pDriver->bSetTopDir = true;
    }
    
    if (LID_RUN_CMD_NULL != pDriver->setCMD)//命令最大时间退出判断
	{
		f_AddU16Data(&pDriver->cmdRunTm);
	    if (pDriver->cmdRunTm >= pDriver->setMaxCmdTm)
	    {
			pDriver->setCMD = LID_RUN_CMD_NULL;
	    }
    }

    //====设置电机方向====
    if (pDriver->bSetSeatDir)
    {
    	pDriver->bSetSeatDir = false;
    	f_LidMotorSetState(&pDriver->seatLidMotor, pDriver->setSeatDir);
    }

    if (pDriver->bSetTopDir)
    {
    	pDriver->bSetTopDir = false;
    	f_LidMotorSetState(&pDriver->topLidMotor, pDriver->setTopDir);
    }

	//====实际电机控制====
	f_LidMotorCtrl(&pDriver->seatLidMotor); // 翻圈电机处理
	f_LidMotorCtrl(&pDriver->topLidMotor); // 翻盖电机处理

	//====命令结束判断=====
    if (MOTOR_DIR_STOP == pDriver->topLidMotor.data.curDir 
    && MOTOR_DIR_STOP == pDriver->seatLidMotor.data.curDir)//电机都已停止
    {
		pDriver->setCMD = LID_RUN_CMD_NULL;
    }
}

/*****************************************************************************
 函 数 名: f_LidCmdReset
 功能描述  : 复位盖板
 输入参数  :
 输出参数  :
 返 回 值: 
 注     意: 
 
 修改历史      :
  1.日    期   : 2018年6月13日
    作    者   : 钱百静
    修改内容   : 新生成函数

*****************************************************************************/
void f_LidCmdReset(void)
{
    //进行电机初始化复位(针对霍尔)
//    f_LidMotorReset(&lidCmdCtrl.seatLidMotor);
    f_LidMotorReset(&lidCmdCtrl.topLidMotor);
    f_LidCmdSetCmd(&lidCmdCtrl, LID_RUN_CMD_ALL_CLOSE, true); //强制合盖
}

/*****************************************************************************
 函 数 名: f_LidCmdCtrlInit
 功能描述  : 翻盖命令控制初始化
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月15日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_LidCmdCtrlInit(void)
{
	f_Memset(&lidCmdCtrl, 0, sizeof(LID_CMD_CTRL));
    f_LidMotorDriverInit(&lidCmdCtrl.seatLidMotor, &seatLidHardware, f_SeatLidSetFwdSpeed, f_SeatLidSetRevSpeed, 100);//周期10ms
    f_LidMotorDriverInit(&lidCmdCtrl.topLidMotor, &topLidHardware, f_TopLidSetFwdSpeed, f_TopLidSetRevSpeed, 100);//周期10ms
    lidCmdCtrl.setMaxCmdTm = 500; //单次命令最大运行时间5S

    //复位盖板
    f_LidCmdReset();

    //====速度初始化值====
    //翻圈正向
    lidCmdCtrl.seatLidMotor.data.speedFwd[0] = 100;
    lidCmdCtrl.seatLidMotor.data.speedFwd[1] = 90;
    lidCmdCtrl.seatLidMotor.data.speedFwd[2] = 80;
    lidCmdCtrl.seatLidMotor.data.speedFwd[3] = 70;
    lidCmdCtrl.seatLidMotor.data.speedFwd[4] = 60;
    lidCmdCtrl.seatLidMotor.data.speedFwd[5] = 50;
    lidCmdCtrl.seatLidMotor.data.speedFwd[6] = 30;
    lidCmdCtrl.seatLidMotor.data.speedFwd[7] = 20;
    lidCmdCtrl.seatLidMotor.data.speedFwd[8] = 10;
    lidCmdCtrl.seatLidMotor.data.speedFwd[9] = 0;
    //翻圈反向
    lidCmdCtrl.seatLidMotor.data.speedRev[0] = 10;
    lidCmdCtrl.seatLidMotor.data.speedRev[1] = 10;
    lidCmdCtrl.seatLidMotor.data.speedRev[2] = 15;
    lidCmdCtrl.seatLidMotor.data.speedRev[3] = 20;
    lidCmdCtrl.seatLidMotor.data.speedRev[4] = 25;
    lidCmdCtrl.seatLidMotor.data.speedRev[5] = 30;
    lidCmdCtrl.seatLidMotor.data.speedRev[6] = 35;
    lidCmdCtrl.seatLidMotor.data.speedRev[7] = 40;
    lidCmdCtrl.seatLidMotor.data.speedRev[8] = 45;
    lidCmdCtrl.seatLidMotor.data.speedRev[9] = 50;

    //翻盖正向
    lidCmdCtrl.topLidMotor.data.speedFwd[0] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[1] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[2] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[3] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[4] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[5] = 100;
    lidCmdCtrl.topLidMotor.data.speedFwd[6] = 80;
    lidCmdCtrl.topLidMotor.data.speedFwd[7] = 40;
    lidCmdCtrl.topLidMotor.data.speedFwd[8] = 10;
    lidCmdCtrl.topLidMotor.data.speedFwd[9] = 0;
    //翻盖反向(盖板比较重，主要靠刹车)
    lidCmdCtrl.topLidMotor.data.speedRev[0] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[1] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[2] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[3] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[4] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[5] = 0;
    lidCmdCtrl.topLidMotor.data.speedRev[6] = 10;
    lidCmdCtrl.topLidMotor.data.speedRev[7] = 30;
    lidCmdCtrl.topLidMotor.data.speedRev[8] = 60;
    lidCmdCtrl.topLidMotor.data.speedRev[9] = 90;
}

//====调节速度用====

/*****************************************************************************
 函 数 名: f_LidCmdIntoAdjust
 功能描述  : 进入盖板速度调节模式
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月23日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_LidCmdIntoAdjust(void)
{
    lidCmdCtrl.adjustIndex = SPEED_ADJUST_SEAT_FWD;
	lidCmdCtrl.badjustMode = true;
}

/*****************************************************************************
 函 数 名: f_LidCmdAddSpeed
 功能描述  : 速度增加
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月23日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_LidCmdAddSpeed(void)
{
	if (*tab_speedIndex[lidCmdCtrl.adjustIndex] < speedOffsetRange.max)
	{
	    (*tab_speedIndex[lidCmdCtrl.adjustIndex])++;
	    f_StorageWriteValues(&storageDriver, STORAGE_SEAT_FWD_OFFSET + lidCmdCtrl.adjustIndex, true);
    }
}

/*****************************************************************************
 函 数 名: f_LidCmdDecSpeed
 功能描述  : 速度减小
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月23日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_LidCmdDecSpeed(void)
{
	if (*tab_speedIndex[lidCmdCtrl.adjustIndex] > speedOffsetRange.min)
	{
	    (*tab_speedIndex[lidCmdCtrl.adjustIndex])--;
	    f_StorageWriteValues(&storageDriver, STORAGE_SEAT_FWD_OFFSET + lidCmdCtrl.adjustIndex, true);
    }
}

/*****************************************************************************
 函 数 名: f_LidCmdAddIndex
 功能描述  : 调节序号增加
 输入参数:
 返 回 值: 
 注     意: 
 
 修改历史:
  1.日    期   : 2018年5月23日
    作    者   : 钱百静
    修改内容    : 新生成函数

*****************************************************************************/
void f_LidCmdAddIndex(void)
{
    if (lidCmdCtrl.adjustIndex < SPEED_ADJUST_TOP_REV)
	{
		lidCmdCtrl.adjustIndex++;
	}
	else
	{
		lidCmdCtrl.badjustMode = false;
	}
}

