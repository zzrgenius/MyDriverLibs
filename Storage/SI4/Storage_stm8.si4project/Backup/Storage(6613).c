

/* =========================================================
* 函 数 名: f_ChangeKeyInf
* 功能描述: 将硬件上面获取的信息，转换为可处理信息
* 全局变量: 无
* 输    入: 按键信息变量
* 返    回: 无
* 处理过程:
* 注	意：不同按键排布，处理内容需修改
* 修改日期			修改人				修改说明
* 2014-4-12			钱百静 			完成基本功能
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

