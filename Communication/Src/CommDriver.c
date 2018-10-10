/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : CommDriver.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��8��
  ����޸�   :
  ��������   : ͨ�������������շ����ݹ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��8��
    ��    ��   : Ǯ�پ�
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "CommDriver.h"
#include "SubFunction.h"
#include "CommProtocol.h"

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

/*****************************************************************************
 �� �� ��: f_FindNextSendCMD
 ��������  : Ѱ����һ����������
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��8��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_FindNextSendCMD(COMM_DRIVER *pDriver)
{
    if (COMM_CMD_NULL != pDriver->sendData.curSendCMD)
	{
		//���ط����
		if (pDriver->sendData.CMDSendCnt > COMM_GET_RETRY_CNT(pDriver->sendData.curSendCMD))
		{
			//�Ƿ���Ҫѭ������
			if (COMM_IS_NEED_SYC(pDriver->sendData.curSendCMD))
			{
				//��ǰ����û����ͬ����
				if (false == f_CommFindData(&(pDriver->sendData.queue), pDriver->sendData.curSendCMD))
				{
				
					 f_CommQueuePush(&(pDriver->sendData.queue), pDriver->sendData.curSendCMD);
				}
			}
		}
		else
		{
			return true;//������ǰ����
		}
    }
    return f_CommQueuePop(&(pDriver->sendData.queue), &(pDriver->sendData.curSendCMD));
}

/*****************************************************************************
 �� �� ��: f_CommSendCMD
 ��������  : ��������(�ڲ�����)
 �������: pDriver����ָ��
 		   cmd��Ҫ��������
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��8��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_CommSendCMD(COMM_DRIVER *pDriver, QUEUE_DATA_TYPE cmd)
{
    return f_CommQueuePush(&(pDriver->sendData.queue), cmd);
}

/*****************************************************************************
 �� �� ��: void f_CommDriverDeal(COMM_DRIVER *pDriver)
 ��������  : ͨ�Ŵ���
 �������: pDriver����ָ��
 �� �� ֵ: 
 ע     ��: 1ms����
 
 �޸���ʷ:
  1.��    ��   : 2018��4��19��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_CommDriverDeal(COMM_DRIVER *pDriver)
{
	COMM_FUNC_TAB const *pFuncTab = NULL;

	//���Ͳ���
    f_AddU16Data(&(pDriver->sendData.noSendTm));
    switch(pDriver->sendData.sendState)
    {
		case COMM_SEND_STATE_IDLE://����	
			if (pDriver->sendData.noSendTm >= pDriver->pHardware->sendFrameItv)
			{
				//��������Ҫ����(�����ط��ж�)
				if (f_FindNextSendCMD(pDriver))
				{
					pDriver->sendData.sendState = COMM_SEND_STATE_GET_BUFFER;
				}
			}
			break;

		case COMM_SEND_STATE_GET_BUFFER:
			//��������õ�ӳ���
			pFuncTab = f_CommFindFuncTable(pDriver->sendData.curSendCMD);
			if (pFuncTab && pFuncTab->GetSendBuf)
			{
			    if (0 != pFuncTab->baudRate)//��Ҫ���ò�����
			    {
                    if (pDriver->pHardware->ChangeBaudRate) //Ӳ����������
                    {
                        pDriver->pHardware->ChangeBaudRate(pFuncTab->baudRate);
                    }
			    }
			    
				pFuncTab->GetSendBuf(pDriver);
				pDriver->sendData.sendState = COMM_SEND_STATE_START;
			}
			else
			{
				pDriver->sendData.sendState = COMM_SEND_STATE_IDLE;
			}
			break;

		case COMM_SEND_STATE_START:
			pDriver->sendData.noSendTm = 0;
			pDriver->sendData.CMDSendCnt ++;
			pDriver->sendData.sendState = COMM_SEND_STATE_SENDING;//��ֹ�������ж�ʱ״̬���ԣ��ȸ�ֵ
			pDriver->pHardware->StartSend(pDriver);
			break;

		case COMM_SEND_STATE_SENDING:
			if (pDriver->sendData.noSendTm >= pDriver->pHardware->sendErrTm)
			{
				//���ͳ�ʱ,ֹͣ����
				if (pDriver->pHardware->SetSendInterrupt)
				{
					pDriver->pHardware->SetSendInterrupt(false);
				}

				pDriver->sendData.sendState = COMM_SEND_STATE_OVER;
			}
			break;

		case COMM_SEND_STATE_OVER:
			if (pDriver->sendData.noSendTm >= pDriver->pHardware->waitReplyTm)
			{
				//�ȴ�Ӧ��ʱ
				pFuncTab = f_CommFindFuncTable(pDriver->sendData.curSendCMD);
				if (pFuncTab && pFuncTab->NoReplyDeal)
				{
					pFuncTab->NoReplyDeal(pDriver);
				}
				pDriver->sendData.sendState = COMM_SEND_STATE_IDLE;
			}
			break;
			
		case COMM_SEND_STATE_REPLY://��״̬�ڽ��մ�����������
			pDriver->sendData.sendState = COMM_SEND_STATE_IDLE;
			pDriver->sendData.curSendCMD = COMM_CMD_NULL;
			pDriver->sendData.CMDSendCnt = 0;
			f_Memset(pDriver->sendData.pBuffer->pBuffer, 0, pDriver->sendData.pBuffer->size);//���ͻ�������
			break;

		default:
			break;
    }

    //���մ���
    f_AddU16Data(&(pDriver->revData.noRevTm));
    switch(pDriver->revData.revState)
    {
		case COMM_REV_STATE_WAIT://�ȴ�����	
			if ( pDriver->revData.noRevTm > 0
			&& (pDriver->revData.noRevTm % pDriver->pHardware->frameRevOverItv == 0))//֡�������ʱ�䵽
			{
				if (pDriver->revData.curRevNum > 0)
				{
					pDriver->revData.noRevTm = 0;
					pDriver->revData.revState = COMM_REV_STATE_OVER;
					if (pDriver->pHardware->SetRecInterrupt)
					{
						//��������,�ʴ����ʱ����չر�
						pDriver->pHardware->SetRecInterrupt(false);
					}
				}
			}
			break;

		case COMM_REV_STATE_OVER:
			if (f_CommRevDeal(pDriver))
			{
				//��������õ�ӳ���
				pFuncTab = f_CommFindFuncTable(pDriver->revData.curRevCMD);
				//��ǰ���յ���������Ӧ��
				if (pDriver->revData.curRevCMD == pDriver->sendData.curSendCMD)
				{
					pDriver->sendData.sendState = COMM_SEND_STATE_REPLY;
				}
				
				if (pFuncTab && pFuncTab->RevDataDeal)
				{
					//�������ݴ���
					pFuncTab->RevDataDeal(pDriver);
				}
			}

			pDriver->revData.revState = COMM_REV_STATE_WAIT;
			pDriver->revData.noRevTm = 0;
			pDriver->revData.curRevNum = 0;
			if (pDriver->pHardware->SetRecInterrupt)
			{
				pDriver->pHardware->SetRecInterrupt(true);
			}
			//���ջ�������
			f_Memset(pDriver->revData.pBuffer->pBuffer, 0, pDriver->revData.pBuffer->size);
			break;

		
		default:
			break;
    }
}

/*****************************************************************************
 �� �� ��: f_CommDriverInit
 ��������: ͨ��������ʼ��
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��8��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
void f_CommDriverInit(COMM_DRIVER *pDriver, 
							const COMM_HARDWARE *pHardware, 
							const COMM_FRAME_BUFFER *pSendBuf, 
							const COMM_FRAME_BUFFER *pRevBuf)
{
    f_Memset(pDriver, 0, sizeof(COMM_DRIVER));
    pDriver->pHardware = pHardware;
    pDriver->sendData.pBuffer = pSendBuf;
    pDriver->revData.pBuffer = pRevBuf;
    f_CommQueueInit(&(pDriver->sendData.queue));
}