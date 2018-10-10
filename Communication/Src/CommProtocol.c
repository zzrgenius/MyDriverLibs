/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : CommProtocol.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��8��
  ����޸�   :
  ��������   : ͨ��Э��������ݣ���Ҫ���ڴ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��8��
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
void f_CommFuncIheatGetBuf(COMM_DRIVER *pDriver);
void f_CommFuncIheatRevDeal(COMM_DRIVER *pDriver);
void f_CommFuncChangeGetBuf(COMM_DRIVER *pDriver);
void f_CommFuncChangeRevDeal(COMM_DRIVER *pDriver);

/*----------------------------------------------*
 * ȫ�ֱ���                                         *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/
//====���ܻص���====
#define COMM_FUC_TAB_SIZE (sizeof(tab_commFunc)/sizeof(COMM_FUNC_TAB))
const COMM_FUNC_TAB tab_commFunc[] =
{
	//����ͨ��
	{
	    2400u,//���ͬһ�����ڲ���Ҫ�޸Ŀ�����Ϊ0,ͬʱ��Ӳ�������Ĳ������޸ĺ�����ΪNULL
		COMM_CMD_IHEAT, //�ڲ�����
		f_CommFuncIheatRevDeal,//���մ�����
		f_CommFuncIheatGetBuf,//���ʹ�����
		f_CheckIheatCommErr//��Ӧ������
	},

	//ת�Ӱ�ͨ��
	{
	    9600u,
		COMM_CMD_CHANGE, //�ڲ�����
		f_CommFuncChangeRevDeal,//���մ�����
		f_CommFuncChangeGetBuf,//���ʹ�����
		f_CheckChangeCommErr//��Ӧ������
	}
};

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
//====Э�鷢�͡����մ�����====
//���ȷ���Э��
void f_CommFuncIheatGetBuf(COMM_DRIVER *pDriver)
{
	PROTOCOL_IHEAT_SEND sendData;
	f_Memset(&sendData, 0, sizeof(PROTOCOL_IHEAT_SEND));
	//����ת��
	sendData.headCode = FRAME_IHEAT_HEAD;
	sendData.add = 0xf0;
	sendData.mode = 0x81;
	sendData.endCode = 0x34;
	sendData.setTempLSB = (uchar)(functionInfo.outTempInfo.setTemp * 10);
	sendData.setTempMSB = (uchar)((functionInfo.outTempInfo.setTemp * 10) >> 8);
	sendData.bOnOff = functionInfo.bEnHeat;
	sendData.xorValue = f_CalcXOR((uchar *)&(sendData.add), sizeof(PROTOCOL_IHEAT_SEND) - 3);//У������
	
	//���ػ���
	f_Memset(pDriver->sendData.pBuffer->pBuffer, 0, pDriver->sendData.pBuffer->size);
	f_MemCpy(pDriver->sendData.pBuffer->pBuffer, &sendData, sizeof(PROTOCOL_IHEAT_SEND));
	pDriver->sendData.needSendNum = sizeof(PROTOCOL_IHEAT_SEND);//���ͳ���
}

//���Ƚ���Э��
void f_CommFuncIheatRevDeal(COMM_DRIVER *pDriver)
{
	PROTOCOL_IHEAT_REV revData;
	f_Memset(&revData, 0, sizeof(PROTOCOL_IHEAT_REV));
	f_MemCpy(&revData, pDriver->revData.pBuffer->pBuffer, sizeof(PROTOCOL_IHEAT_REV));
	funcError.iheatNoReplyCnt = 0;
	
	//����ת��
	functionInfo.curWaterFlow = revData.flowMSB;
	functionInfo.curWaterFlow <<= 8;
	functionInfo.curWaterFlow += revData.flowLSB;

	functionInfo.outTempInfo.sensorTemp = revData.OutTempMSB;
	functionInfo.outTempInfo.sensorTemp <<= 8;
	functionInfo.outTempInfo.sensorTemp += revData.OutTempLSB;
	functionInfo.outTempInfo.sensorTemp /= 10; //�������¶ȷŴ���10��
	functionInfo.outTempInfo.bOpenFlag = revData.bErrorOutTempOpen;
	functionInfo.outTempInfo.bShortFlag = revData.bErrorOutTempShort;

	functionInfo.inTempInfo.sensorTemp = revData.InTempMSB;
	functionInfo.inTempInfo.sensorTemp <<= 8;
	functionInfo.inTempInfo.sensorTemp += revData.InTempLSB;
	functionInfo.inTempInfo.sensorTemp /= 10; //�������¶ȷŴ���10��
	functionInfo.inTempInfo.bOpenFlag = revData.bErrorInTempOpen;
	functionInfo.inTempInfo.bShortFlag = revData.bErrorInTempShort;
}

//ת�Ӱ巢��Э��
void f_CommFuncChangeGetBuf(COMM_DRIVER *pDriver)
{
	PROTOCOL_CHANGE_SEND sendData;
	f_Memset(&sendData, 0, sizeof(PROTOCOL_CHANGE_SEND));
	//����ת��
	sendData.headCode = 0x55;
	sendData.mode = 1;
	sendData.sysState = (uchar)(systemInfo.sysState);
	sendData.curFunc = (uchar)(functionInfo.curFunction);
	sendData.lidCMD = (uchar)(functionInfo.sendLidCmd);
	sendData.keyCode = functionInfo.reSendKey; //����ֵ�ش�
	sendData.adjustIndex = (uchar)funcFlush.adjustIndex;
	
	sendData.bFlushState = funcFlush.curStep == FLUSH_SREQ_STOP?false:true;
	sendData.bWashMove = (funcWashHip.flags.m_bits.bEnMove || funcWashFemale.flags.m_bits.bEnMove);
	sendData.bStrongWeak = (funcWashHip.flags.m_bits.bEnStrongWeak || funcWashFemale.flags.m_bits.bEnStrongWeak);
	sendData.bColdHot = (funcWashHip.flags.m_bits.bEnColdHot || funcWashFemale.flags.m_bits.bEnColdHot);
	sendData.bErrNoWater = funcError.bErrNoWater;
	sendData.bKeyDryIO = FLUSH_KEY;
	sendData.bFlushAdjust = funcFlush.bAdjust;
	sendData.bFourceSit = funcSit.bFourceSit;

	sendData.xorValue = f_CalcXOR((uchar *)&(sendData.headCode), sizeof(PROTOCOL_CHANGE_SEND) - 1);//У������
	
	//���ػ���
	f_Memset(pDriver->sendData.pBuffer->pBuffer, 0, pDriver->sendData.pBuffer->size);
	f_MemCpy(pDriver->sendData.pBuffer->pBuffer, &sendData, sizeof(PROTOCOL_CHANGE_SEND));
	pDriver->sendData.needSendNum = sizeof(PROTOCOL_CHANGE_SEND);//���ͳ���
}

//ת�Ӱ����Э��
void f_CommFuncChangeRevDeal(COMM_DRIVER *pDriver)
{
	PROTOCOL_CHANGE_REV revData;
	f_Memset(&revData, 0, sizeof(PROTOCOL_CHANGE_REV));
	f_MemCpy(&revData, pDriver->revData.pBuffer->pBuffer, sizeof(PROTOCOL_CHANGE_REV));
	funcError.changeNoReplyCnt = 0;
	
	//����ת��
	functionInfo.getKeyCode = revData.keyCode;
	functionInfo.reSendKey = revData.keyCode;
	funcSeatHeat.sensorInfo.sensorTemp = revData.seatTemp;
	funcSeatHeat.sensorInfo.bOpenFlag = revData.bErrSeatTempOpen;
	funcSeatHeat.sensorInfo.bShortFlag = revData.bErrSeatTempShort;

	if (functionInfo.sendLidCmd == revData.lidCmd)//ת�Ӱ����յ�����
	{
		functionInfo.sendLidCmd = LID_RUN_CMD_NULL;
	}
	functionInfo.lidCmd = (LID_MOTOR_CMD)(revData.lidCmd);
	
	functionInfo.waterTempLevel = (FUNC_SET_LEVEL)(revData.waterLevel);//ˮ�µ�λ
	funcSeatHeat.level = (FUNC_SET_LEVEL)(revData.seatLevel);//���µ�λ
	funcDry.level = (FUNC_SET_LEVEL)(revData.dryLevel);//�����µ�λ
	functionInfo.setPos = (FUNC_SET_LEVEL)(revData.nozzlePos);//��λ
	functionInfo.setFlow = (FUNC_SET_LEVEL)(revData.flowPos);//����
	functionInfo.topLidRange = (LID_MOTOR_RANGE)(revData.topLidRange); //�ϸ�λ��
	functionInfo.seatLidRange = (LID_MOTOR_RANGE)(revData.seatLidRange); //��Ȧλ��
	
	funcSit.state = (STATE_INFO)(revData.bSitState || funcSit.bFourceSit);
	functionInfo.bHasPerson = revData.bHasPerson;
	functionInfo.bChangeBoardKey = revData.bKeyPressed;
}

//====�ӿڹ��ܺ���====

/*****************************************************************************
 �� �� ��: f_CommFindFuncTable
 ��������  : �������������ش�����
 �������:
 �� �� ֵ: 
 ע     ��: ���޸�
 
 �޸���ʷ:
  1.��    ��   : 2018��5��8��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
COMM_FUNC_TAB const * f_CommFindFuncTable(QUEUE_DATA_TYPE cmd)
{
	uchar i;
	COMM_FUNC_TAB const * pTable = NULL;
    for (i = 0; i < COMM_FUC_TAB_SIZE; i++)
    {
		if (tab_commFunc[i].internalCMD == cmd)
		{
			pTable = &tab_commFunc[i];
			break;
		}
    }
    return pTable;
}

/*****************************************************************************
 �� �� ��: f_CommRevDeal
 ��������  : ���մ�����
 �������:
 �� �� ֵ: 
 ע     ��: ���������޸�
 
 �޸���ʷ:
  1.��    ��   : 2018��5��8��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_CommRevDeal(COMM_DRIVER *pDriver)
{
    if (pDriver->revData.pBuffer->pBuffer[0] == FRAME_IHEAT_HEAD 
     && pDriver->revData.pBuffer->pBuffer[1] == FRAME_IHEAT_ADD)
    {
		if (pDriver->revData.pBuffer->pBuffer[PFRAME_IHEAT_REV_LEN - 2] == f_CalcXOR(&pDriver->revData.pBuffer->pBuffer[PFRAME_IHEAT_ADD_POS], PFRAME_IHEAT_REV_LEN - 3))
		{
			//���Ƚ����ж�
			pDriver->revData.curRevCMD = COMM_CMD_IHEAT;
			return true;
		}
    }
    else if (pDriver->revData.pBuffer->pBuffer[0] == FRAME_CHANGE_HEAD)
    {
		if (pDriver->revData.pBuffer->pBuffer[PFRAME_CHANGE_REV_LEN - 1] == f_CalcXOR(pDriver->revData.pBuffer->pBuffer, PFRAME_CHANGE_REV_LEN - 1))
		{
			//ת�Ӱ�����ж�
			pDriver->revData.curRevCMD = COMM_CMD_CHANGE;
			return true;
		}
		else
		{
			pDriver->revData.curRevCMD = 0;
		}
    }
    return false;
}
