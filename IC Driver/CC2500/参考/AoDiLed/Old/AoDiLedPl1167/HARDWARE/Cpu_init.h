#ifndef __CPU_INIT_H
#define __CPU_INIT_H

#ifdef  VAR_INIT_GLOBALS
	#define  CPU_INIT_EXT
#else
	#define  CPU_INIT_EXT  extern
#endif

CPU_INIT_EXT void f_CpuInit(void);
CPU_INIT_EXT void f_McuFeedDog(void);

#endif	//__CPU_INIT_H