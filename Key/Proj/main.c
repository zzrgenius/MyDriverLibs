/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "KeyDeal.h"
#include "TimeFlag.h"
SYS_TIME_FLAG sysTimeFlag;

main()
{
	f_KeyDealInit();
	while (1)
{
	f_KeyDriverDeal(&keyDriver);
}
}