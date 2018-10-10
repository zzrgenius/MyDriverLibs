/*******************************************************************************
  * @file    drive.h
  * @author  钟昊翰
  * @version V1.0.0
  * @date    2017-09-25
  * @brief   该头文件包含此项目所有驱动头文件
*******************************************************************************/

#ifndef __DRIVE_H__
#define __DRIVE_H__

/* Includes ------------------------------------------------------------------*/
//#include<iostm8s105k4.h>
#include<iostm8s003f3.h>

#include<stdint.h>
#include<stdbool.h>

#include"stm8s_clock.h"
#include"stm8s_wd.h"
#include"stm8s_gpio.h"
#include"stm8s_ad.h"
#include"stm8s_uart1.h"
#include"stm8s_uart2.h"
#include"stm8s_beep.h"
#include"stm8s_tim1.h"
#include"stm8s_tim2.h"
#include"stm8s_tim3.h"
#include"stm8s_tim4.h"
#include"stm8s_flash.h"


#include"typedef.h"

#include"parm_check.h"
#include"mid_adder_subtractor.h"
#include"mid_adc.h"
#include"test_mid_uart_rx.h"
#include"test_mid_uart_tx.h"
#include"mid_key.h"

#include"bsp.h"
#include"timer.h"
#include"key_app.h"
#include"key_cfg.h"
#include"key_hardware.h"



/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Exported variables ------------------------------------------------------- */

#endif
