#ifndef __MUSIC_BEEP_CONFIG_H__
#define __MUSIC_BEEP_CONFIG_H__

#ifdef VAR_MUSIC_BEEP_GLOBALS
	#define VAR_MUSIC_BEEP_EXT 
#else
	#define VAR_MUSIC_BEEP_EXT extern
#endif

/*----------------------------------------------*
 * ����ͷ�ļ�                                        *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                          *
 *----------------------------------------------*/
#define BEEP_VOICE	50L //������С 1~100

//ʱ��,��λ1ms
#define BEEP_TIME_10MS			10
#define BEEP_TIME_45MS			45
#define BEEP_TIME_50MS			50
#define BEEP_TIME_85MS			85
#define BEEP_TIME_100MS 		100
#define BEEP_TIME_120MS 		120
#define BEEP_TIME_200MS 		200
#define BEEP_TIME_300MS 		300
#define BEEP_TIME_500MS 		500
#define BEEP_TIME_765MS			765
#define BEEP_TIME_820MS			820
#define BEEP_TIME_1S			1000
#define BEEP_TIME_OFF			0


//���Ƶ��,ת��ʱ��1000/freq
#define FREQ_1_96K				510// 1.96K
#define FREQ_2K 				500// 2K
#define FREQ_2_10K				476// 2.10K
#define FREQ_2_36K				424// 2.36K
#define FREQ_2_76K				362// 2.76
#define FREQ_2_86K				350// 2.86K
#define FREQ_3_11K				322// 3.11

#define FREQ_XIMA_DOU			488//2.0495K	
#define FREQ_XIMA_RUI			432//2.315K	
#define FREQ_XIMA_MI			388//2.578K	
#define FREQ_XIMA_FA			364//2.747K	
#define FREQ_XIMA_SOU			324//3.087K	

#define BEEP_OFF				0
/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/
//��ͨ������
const MUSIC_BEEP_VALUE Tab_MUSIC_Normal[] =
{
 	{FREQ_2_76K, BEEP_TIME_200MS},
 	{BEEP_OFF, BEEP_TIME_300MS},
//	{BEEP_OFF, BEEP_TIME_1S}, //�����ͷ�
	{BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//��Ч������(2��)
const MUSIC_BEEP_VALUE Tab_MUSIC_Unuse[] =
{
 	{FREQ_2_76K, BEEP_TIME_50MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_76K, BEEP_TIME_50MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
//	{BEEP_OFF, BEEP_TIME_1S}, //�����ͷ�
	{BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//������
const MUSIC_BEEP_VALUE Tab_MUSIC_PowerOn[] =
{
 	{FREQ_1_96K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_10K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_36K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_86K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{BEEP_OFF, BEEP_TIME_1S}, //�����ͷ�
	{BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//�ػ���
const MUSIC_BEEP_VALUE Tab_MUSIC_PowerOff[] =
{
 	{FREQ_2_86K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_36K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_2_10K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{FREQ_1_96K, BEEP_TIME_100MS},
	{BEEP_OFF, BEEP_TIME_100MS}, 
	{BEEP_OFF, BEEP_TIME_1S}, //�����ͷ�
	{BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};


//����1S
const MUSIC_BEEP_VALUE Tab_MUSIC_Long[] =
{
	{FREQ_2_76K, BEEP_TIME_1S},
//	{BEEP_OFF, BEEP_TIME_100MS}, //�����ͷ�
	{BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//��Ч������
const MUSIC_BEEP_VALUE Tab_MUSIC_Err[] =
{
 	{FREQ_2_76K, BEEP_TIME_10MS},
	{BEEP_OFF, BEEP_TIME_500MS}, 
	{FREQ_2_76K, BEEP_TIME_10MS},
	{BEEP_OFF, BEEP_TIME_500MS},
	{FREQ_2_76K, BEEP_TIME_10MS},
	{BEEP_OFF, BEEP_TIME_500MS},
	{FREQ_2_76K, BEEP_TIME_10MS},
	{BEEP_OFF, BEEP_TIME_500MS},
	{FREQ_2_76K, BEEP_TIME_10MS},
	{BEEP_OFF, BEEP_TIME_500MS},
//	{BEEP_OFF, BEEP_TIME_1S}, //�����ͷ�
	{BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//���ݵȼ���1
const MUSIC_BEEP_VALUE Tab_MUSIC_L1[] =
{
    {FREQ_XIMA_DOU, BEEP_TIME_200MS},
    {BEEP_OFF, BEEP_TIME_300MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//���ݵȼ���2
const MUSIC_BEEP_VALUE Tab_MUSIC_L2[] =
{
    {FREQ_XIMA_RUI, BEEP_TIME_200MS},
    {BEEP_OFF, BEEP_TIME_300MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//���ݵȼ���3
const MUSIC_BEEP_VALUE Tab_MUSIC_L3[] =
{
    {FREQ_XIMA_MI, BEEP_TIME_200MS},
    {BEEP_OFF, BEEP_TIME_300MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//���ݵȼ���4
const MUSIC_BEEP_VALUE Tab_MUSIC_L4[] =
{
    {FREQ_XIMA_FA, BEEP_TIME_200MS},
    {BEEP_OFF, BEEP_TIME_300MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//���ݵȼ���5
const MUSIC_BEEP_VALUE Tab_MUSIC_L5[] =
{
    {FREQ_XIMA_SOU, BEEP_TIME_200MS},
    {BEEP_OFF, BEEP_TIME_300MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//�¿�����_2
const MUSIC_BEEP_VALUE Tab_MUSIC_PowerOn_2[] =
{
    {956, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {852, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {760, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {640, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {424, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_85MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//�¿�����_2
const MUSIC_BEEP_VALUE Tab_MUSIC_PowerOff_2[] =
{
    {424, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {640, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {760, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {852, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {956, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_85MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};


//���ܿ�����
const MUSIC_BEEP_VALUE Tab_MUSIC_FuncOn[] =
{
    {760, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {600, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {568, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_765MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//���ܹر���
const MUSIC_BEEP_VALUE Tab_MUSIC_FuncOff[] =
{
    {508, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {672, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {760, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_765MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//test beep
const MUSIC_BEEP_VALUE Tab_MUSIC_Test4[] =
{
    {760, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {600, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_765MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//������_2
const MUSIC_BEEP_VALUE Tab_MUSIC_Normal_2[] =
{
    {600, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_765MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//��Ч��_2
const MUSIC_BEEP_VALUE Tab_MUSIC_Unuse_2[] =
{
    {904, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_45MS},
    {904, BEEP_TIME_45MS},
    {BEEP_OFF, BEEP_TIME_765MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};

//test beep
const MUSIC_BEEP_VALUE Tab_MUSIC_Test7[] =
{
    {508, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {760, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_50MS},
    {508, BEEP_TIME_50MS},
    {BEEP_OFF, BEEP_TIME_820MS},
    {BEEP_OFF, BEEP_TIME_OFF} //���ֽ���
};



//������(Խ����ȼ�Խ��,�ߵȼ����Դ�ϵ͵ȼ�)
const MUSIC_BEEP_VALUE *pAllBeepTable[] =
{
    Tab_MUSIC_Err,
    Tab_MUSIC_Long,
	Tab_MUSIC_Normal,
	Tab_MUSIC_Normal_2,
	Tab_MUSIC_FuncOn,
	Tab_MUSIC_FuncOff,
	Tab_MUSIC_L1,
	Tab_MUSIC_L2,
	Tab_MUSIC_L3,
	Tab_MUSIC_L4,
	Tab_MUSIC_L5,
	Tab_MUSIC_Unuse,
	Tab_MUSIC_Unuse_2,
	Tab_MUSIC_PowerOn,
	Tab_MUSIC_PowerOn_2,
	Tab_MUSIC_PowerOff,
	Tab_MUSIC_PowerOff_2
};

#define BEEP_TAB_SIZE (sizeof(pAllBeepTable)/(sizeof(pAllBeepTable[0])))

/*----------------------------------------------*
 * ģ�鼶��������                                      *
 *----------------------------------------------*/


#endif /* __MUSIC_BEEP_CONFIG_H__ */

