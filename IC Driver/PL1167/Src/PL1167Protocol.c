/******************************************************************************

                  ��Ȩ���� (C), 2008-2018, �����Ŷ��������޹�˾

 ******************************************************************************
  �� �� ��   : PL1167Protocol.c
  �� �� ��   : V1.0
  ��    ��   : Ǯ�پ�
  ��������   : 2018��5��24��
  ����޸�   :
  ��������   : PL1167Э�鴦��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��24��
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
PROCOTOL_XI_MA_RC procotolXiMaRC;//����ң����Э��
uchar machineID[MACHINE_CODE_LEN];//���������

/*----------------------------------------------*
 * ģ�鼶����                                        *
 *----------------------------------------------*/
uint dealFrameCnt;


/*----------------------------------------------*
 * ��������                                         *
 *----------------------------------------------*/


/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define COMM_HEAD_LEN 10
#define FRAME_INDEX_POS 3
#define MACHINE_CODE_POS 4

//����ң�������
#define XIMA_RC_CMD_CODE 0x0f//����ң��������
#define PACKET_LEN sizeof(PROCOTOL_XI_MA_RC)//�ڲ������С(ʵ����Ҫת�����Э��)
#define XIMA_FRAME_LEN (PACKET_LEN + COMM_HEAD_LEN + 1)//��֡���ݴ�С(ͨ��ͷ����+�������+У���)

//����������
#define MATCH_CMD_CODE 0x0A//���������
#define MATCH_FRAME_LEN	XIMA_FRAME_LEN//���֡����




/*****************************************************************************
 �� �� ��: f_CompareValue
 ��������  : �Ƚ�2�������Ƿ����
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��29��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_CompareValue(uchar *pSrc, uchar *pDst, uchar len)
{
	uchar i;
	
    for (i = 0; i < len; i++)
    {
		if (*pSrc != *pDst)
		{
			return false;
		}
		pDst++;
		pSrc++;
    }
    return true;
}

/*****************************************************************************
 �� �� ��: f_IsRevMachineID
 ��������  : �ж��Ƿ�Ϊ����ID��0~10Ϊ����ID���������������ȣ���ЩID��У�鲻�洢
 �������:
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��5��3��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_IsRevMachineID(const uchar *pData, uchar len)
{
    uchar i;

    for (i = 1; i < len; i ++)
    {
		if (0 != pData[i])//ǰ������ȫΪ0
		{
			return false;
		}
    }

    if (pData[0] <= 10)
    {
		return true;
    }
    return false;
}
 
/*****************************************************************************
 �� �� ��: f_PL1167_GetSendBuffer
 ��������  : ��ȡ�������ݻ���
 �������: pBuf:����ָ��;len���泤��
 �� �� ֵ: ʵ�ʷ������ݳ���
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��23��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_PL1167_GetSendBuffer(uchar *pBuf, uint len)
{
	static uchar frameIndex = 0;//֡���,ÿ�η��ͼ�1
	/*
		����Э��
		Head + MachineID + ���Э�� + CheckSum
		0x33
		���Э�飺����
		ͷ��		������		����1	     ����2	����3  	����4	    ������
		0xEE	0x59	Data0	Data1	Data2	Data3	0x55

		����1��
		Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
		��Դ		ֹͣ		���		Ů����ϴ	�β���ϴ	��˸�	�����	��˵�

		����2��
		Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
				���¸�	  	������		���µ�				ˮ�¸�		ˮ����	ˮ�µ�

		����3��
		Bit7	Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
				��ˮ		���		�����ϴ	Һ������   	ҹ��		��Ħ		����
	*/

	f_Memset(pBuf, 0, len);
    f_Memset(&procotolXiMaRC, 0, PACKET_LEN);
    
	//====�ڲ�Э��ͷ��====
	pBuf[0] = 0x55;
	pBuf[1] = 0xaa;
	pBuf[2] = 0xf0;
	pBuf[FRAME_INDEX_POS] = frameIndex++;
	
//	pBuf[4] = functionData.machineID[0];
//	pBuf[5] = functionData.machineID[1];
//	pBuf[6] = functionData.machineID[2];

	//====����ת��====
	procotolXiMaRC.machineCode = 0x59;
	procotolXiMaRC.endCode = 0x55;
	
	//����
	
	
	//====���뻺��====
	f_MemCpy(&pBuf[COMM_HEAD_LEN], &procotolXiMaRC, PACKET_LEN);
	
	//====У���====
	pBuf[XIMA_FRAME_LEN - 1] = f_CalcAddSum(pBuf, XIMA_FRAME_LEN - 1);
	
    return XIMA_FRAME_LEN;
}

/*****************************************************************************
 �� �� ��: f_PL1167_RevProtocolDeal
 ��������  : ���յ����ݰ�����
 �������: pData���ݻ���
 		   len���泤��
 �� �� ֵ: 
 ע     ��: 
 
 �޸���ʷ:
  1.��    ��   : 2018��4��24��
    ��    ��   : Ǯ�پ�
    �޸�����    : �����ɺ���

*****************************************************************************/
uchar f_PL1167_RevProtocolDeal(uchar *pData, uchar len)
{
	static uchar frameIndex = 100;//ң������0��ʼ,��ֹһ��
	
	if (len < XIMA_FRAME_LEN)
	{
		return false;
	}

    if (len > 3 && 0x55 == pData[0] && 0xaa == pData[1])
    {
    	if (MATCH_CMD_CODE == pData[2])//���ģʽ
    	{
			if (pData[MATCH_FRAME_LEN - 1] == f_CalcAddSum(pData, MATCH_FRAME_LEN - 1))
			{
				//��ֹ��������֡�յ���Ч
				if (frameIndex != pData[FRAME_INDEX_POS])
				{
					frameIndex = pData[FRAME_INDEX_POS];
					//��ǰ�������ģʽ
					if (SYS_STATE_MATCH == systemInfo.sysState)
					{
						//��ȡң��ID
						f_MemCpy(machineID, &pData[MACHINE_CODE_POS], MACHINE_CODE_LEN);

						//�ж��Ƿ�Ϊ����ID
						if (false == f_IsRevMachineID(machineID, MACHINE_CODE_LEN))
						{
							//�洢ң��ID
							f_MCU_WriteToEEPROM(0, MACHINE_CODE_LEN, machineID);

							//���͹���ֹͣ(��Ҫ��Ϊ�˷���)
							f_IR_StartSend(&pData[COMM_HEAD_LEN], PACKET_LEN);

							//��Խ�����������������
							systemInfo.sysState = SYS_STATE_RUN;
						}
					}
				}
			}
    	}
    	else if (XIMA_RC_CMD_CODE == pData[2])//����ģʽ
    	{
			if (pData[XIMA_FRAME_LEN - 1] == f_CalcAddSum(pData, XIMA_FRAME_LEN - 1))
			{
				//��ֹ��������֡�յ���Ч
				if (frameIndex != pData[FRAME_INDEX_POS])
				{
					frameIndex = pData[FRAME_INDEX_POS];
					dealFrameCnt ++;

					//�Ƚϵ�ǰID(����IDֱ��У��ͨ��)
					if (f_IsRevMachineID(&pData[MACHINE_CODE_POS], MACHINE_CODE_LEN) 
					|| f_CompareValue(machineID, &pData[MACHINE_CODE_POS], MACHINE_CODE_LEN))
					{
						//���ⷢ����������
						f_IR_StartSend(&pData[COMM_HEAD_LEN], PACKET_LEN);
					}
					return true;
				}
			}
		}
    }
    return false;
}

