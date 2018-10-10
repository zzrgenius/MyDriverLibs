#ifndef MCU_EEROM_H
#define MCU_EEROM_H

#ifdef MCU_EEROM_TYPE_GLOBAL
	#define MCU_EEROM_TYPE
#else
	#define MCU_EEROM_TYPE	extern
#endif

#define DATA_TYPE_NO	3	//需要存储的数据类型数目

#define UCHAR_NO						3
#define UINT_NO							0
#define ULONG_NO						0

#if UCHAR_NO > 0
	MCU_EEROM_TYPE uchar * FLASH pValuAdd_uchar[]
	#ifdef MCU_EEROM_TYPE_GLOBAL
	=
	{
		&machineInf.AddressRf[0],
		&machineInf.AddressRf[1],
		&machineInf.AddressRf[2]
	}
	#endif
	;
	
	MCU_EEROM_TYPE FLASH uchar TAB_Limit_uchar[UCHAR_NO][3]
	#ifdef MCU_EEROM_TYPE_GLOBAL
	=
	{
		{0, 0xff, 0xff},
		{0, 0xff, 0xff},
		{0, 0xff, 0xff}
	}
	#endif
	;

#endif

#if UINT_NO > 0
	MCU_EEROM_TYPE uint * FLASH pValuAdd_uint[]
	#ifdef MCU_EEROM_TYPE_GLOBAL
	=
	{
	}
	#endif
	;
	
	
	MCU_EEROM_TYPE FLASH uint TAB_Limit_uint[UINT_NO][3]
	#ifdef MCU_EEROM_TYPE_GLOBAL
	=
	{
		{0, 0xffff, 0x4444},
		{0, 0xffff, 0x5555},
		{0, 0xffff, 0x6666}
	}
	#endif
	;
#endif

#if ULONG_NO > 0
	MCU_EEROM_TYPE ulong * FLASH pValuAdd_ulong[]
	#ifdef MCU_EEROM_TYPE_GLOBAL
	=
	{
	}
	#endif
	;
		
	MCU_EEROM_TYPE FLASH ulong TAB_Limit_ulong[ULONG_NO][3]
	#ifdef MCU_EEROM_TYPE_GLOBAL
	=
	{
		{0, 0xffffffff, 0x77777777},
		{0, 0xffffffff, 0x88888888},
		{0, 0xffffffff, 0x99999999}
	}
	#endif
	;
#endif

//以上类型数据可以根据实际要存储的数据多少调整
	



#define START_EEROM_ADD	0x4000
#define DATA_IN_EEROM_START_ADD		20	//数据其实地址
#define UCHAR_START_ADD					TAB_Save_Data_List[0].DataStartAddInEE
#define UINT_START_ADD						TAB_Save_Data_List[1].DataStartAddInEE
#define ULONG_START_ADD					TAB_Save_Data_List[2].DataStartAddInEE
#define FIRST_POWER_ON_FLAG				0x5161
#define FIRST_POWER_ON_FLAG_ADD			0
#define MACHINE_TYPE_ADD					2
MCU_EEROM_TYPE uchar eMachine_Type@(START_EEROM_ADD + MACHINE_TYPE_ADD);
MCU_EEROM_TYPE uint eFirstPowerON@(START_EEROM_ADD + FIRST_POWER_ON_FLAG_ADD);
MCU_EEROM_TYPE FLASH TYPE_DATA_SAVE TAB_Save_Data_List[DATA_TYPE_NO]
#ifdef MCU_EEROM_TYPE_GLOBAL
=
{
	{UCHAR,		UCHAR_NO,				DATA_IN_EEROM_START_ADD},
	{UINT,		UINT_NO,					DATA_IN_EEROM_START_ADD + UCHAR_NO},
	{ULONG,		ULONG_NO,				DATA_IN_EEROM_START_ADD + UCHAR_NO + UINT_NO*2},
}
#endif
;


MCU_EEROM_TYPE void f_WriteOneTypeData(uchar iDataType,uchar iAddInEerom);
MCU_EEROM_TYPE void f_ReadOneTypeData(uchar iDataType,uchar iAddInEerom);
MCU_EEROM_TYPE void f_ReadAllDataEeprom(void);
MCU_EEROM_TYPE void f_InitDataEeprom(void);
MCU_EEROM_TYPE void f_WriteOneDataEeprom(void);

#endif//MCU_EEROM_H