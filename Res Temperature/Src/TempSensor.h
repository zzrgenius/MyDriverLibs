#ifndef __TEMP_SENSOR_H__
#define __TEMP_SENSOR_H__

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/
#include "DataType.h"

/*----------------------------------------------*
 * �������Ͷ���                                        *
 *----------------------------------------------*/
struct temp_sensor_driver;
typedef struct temp_sensor_driver TEMP_SENSOR_DRIVER;
 
//�¶ȴ�����
typedef struct
{
	sint setTemp;			//�����¶�	
	sint sensorTemp;		//�������¶�	
	sint lastSensorTemp;	//�������¶Ȼ���	
	
	uchar bShortFlag : 1;	//��·���ϱ�־	
	uchar bOpenFlag	 : 1;	//��·��־	
}TEMP_SENSOR_INF;	

typedef enum
{
    DEGREE_TEMP_1 = 1, //�¶ȷֱ���1��
    DEGREE_TEMP_0d5 = 2, //�¶ȷֱ���0.5��
    DEGREE_TEMP_0d1 = 10 //�¶ȷֱ���0.1��
}TEMP_DEGREE;

typedef uint (*TempSonsorHardware)(uchar);
typedef struct 
{
	uchar channel;//ͨ��
	uchar needFilterCnt;//��Ҫ�˲�����
	const uint *pTab_NTC;//��ֵ��
	uint size;
	sint baseTemp;//�����¶�
	uchar isUp;//�Ƿ�����
	TempSonsorHardware getAD;//AD��ȡ����	
	TEMP_DEGREE degree; //��Ҫ�ķֱ���(ʵ�ʻ�Ŵ��Ӧ��������0.5�ȷŴ�2���� 0.1�ȷŴ�10��)
}TEMP_SENSOR_HARDWARE;

struct temp_sensor_driver
{
	TEMP_SENSOR_INF sensorInf;//��������Ϣ
	uchar filterCnt;//���˴���
	TEMP_SENSOR_HARDWARE const *pHardware;//Ӳ����Ϣ
};

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
void f_GetSensorTemp(TEMP_SENSOR_DRIVER *pDriver);
void f_TempSensorInit(TEMP_SENSOR_DRIVER *pDriver, const TEMP_SENSOR_HARDWARE *pHardware);

#endif /* __TEMP_SENSOR_H__ */
