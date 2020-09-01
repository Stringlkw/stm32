/*******************************************************
 * 模块名称 : MH-Z19B驱动模块
 * 文件名	  : BSPMH_Z19B.H
 * 说明  	  : 头文件,提供自定义数据类型及外部调用的接口函数的声明
 * 版本号	  : v1.0
 * 修改记录 :
 * 	版本号		日期		作者
 * 	v1.0	     2020-4-16	               李康伟
 ********************************************************/

#ifndef INCLUDE_BSP_MH_Z19B_H_
#define INCLUDE_BSP_MH_Z19B_H_


#include "stm32f1xx_hal.h"
#include "stdbool.h"
#include "string.h"

#include "main.h"
#include "usart.h"
#include "gpio.h"

/********************************************************
 本模块提供给外部调用的函数
 ********************************************************/

uint8_t getCheckSum();
void BSP_CO2_Tx (uint16_t *CO2Data);




#endif /* INCLUDE_BSP_MH_Z19B_H_ */
