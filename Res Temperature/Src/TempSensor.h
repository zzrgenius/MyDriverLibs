#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__

/*----------------------------------------------*
 * 包含头文件                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * 数据类型定义                                        *
 *----------------------------------------------*/
struct temp_sensor_driver;
typedef struct temp_sensor_driver TEMP_SENSOR_DRIVER;
 
//温度传感器
typedef struct
{
	sint setTemp;			//设置温度	
	sint sensorTemp;		//传感器温度	
	sint lastSensorTemp;	//传感器温度缓存	
	
	uchar bShortFlag : 1;	//短路故障标志	
	uchar bOpenFlag	 : 1;	//开路标志	
}TEMP_SENSOR_INF;	

typedef enum
{
    DEGREE_TEMP_1 = 1, //温度分辨率1度
    DEGREE_TEMP_0d5 = 2, //温度分辨率0.5度
    DEGREE_TEMP_0d1 = 10 //温度分辨率0.1度
}TEMP_DEGREE;

typedef uint (*TempSonsorHardware)(uchar);
typedef struct 
{
	uchar channel;//通道
	uchar needFilterCnt;//需要滤波次数
	const uint *pTab_NTC;//阻值表
	uint size;
	sint baseTemp;//基础温度
	uchar isUp;//是否上拉
	TempSonsorHardware getAD;//AD获取函数	
	TEMP_DEGREE degree; //需要的分辨率(实际会放大对应倍数，如0.5度放大2倍， 0.1度放大10倍)
}TEMP_SENSOR_HARDWARE;

struct temp_sensor_driver
{
	TEMP_SENSOR_INF sensorInf;//传感器信息
	uchar filterCnt;//过滤次数
	TEMP_SENSOR_HARDWARE const *pHardware;//硬件信息
};

/*----------------------------------------------*
 * 模块级变量声明                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级函数声明                                      *
 *----------------------------------------------*/
void f_GetSensorTemp(TEMP_SENSOR_DRIVER *pDriver);
void f_TempSensorInit(TEMP_SENSOR_DRIVER *pDriver, const TEMP_SENSOR_HARDWARE *pHardware);

#endif /* __TEMP_SENSOR_H__ */
