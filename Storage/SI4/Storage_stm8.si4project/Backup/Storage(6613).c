

/* =========================================================
* �� �� ��: f_ChangeKeyInf
* ��������: ��Ӳ�������ȡ����Ϣ��ת��Ϊ�ɴ�����Ϣ
* ȫ�ֱ���: ��
* ��    ��: ������Ϣ����
* ��    ��: ��
* �������:
* ע	�⣺��ͬ�����Ų��������������޸�
* �޸�����			�޸���				�޸�˵��
* 2014-4-12			Ǯ�پ� 			��ɻ�������
 =========================================================*/
 uchar f_MCU_UnLock_EEROM(void)
{
	uint iCnt;
	iCnt = 0;
	FLASH_CR1 |= 0x01;
	if(FLASH_IAPSR & 0x08)return true;
	else
	{
		FLASH_DUKR = 0xAE;
		FLASH_DUKR = 0x56;
	}
	while(!(FLASH_IAPSR & 0x08))
	{
		iCnt ++;
		if(iCnt >= 5000)
		{
//			bEERomUnLockErr = 1;
			return false;
		}
	}
	return true;
}

