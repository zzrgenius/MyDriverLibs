#ifndef __CPUINITHT66F018_H__
#define __CPUINITHT66F018_H__

#ifdef  VAR_CPUINITHT66F018_GLOBALS
	#define  VAR_CPUINITHT66F018_EXT
#else
	#define  VAR_CPUINITHT66F018_EXT  extern
#endif

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 数据类型定义                                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
 
VAR_CPUINITHT66F018_EXT void f_NOPDelay(uint i_Value);
VAR_CPUINITHT66F018_EXT void f_pFeedDog(void);
VAR_CPUINITHT66F018_EXT void f_pSfrInit(void);

#endif /* __CPUINITHT66F018_H__ */
