#ifndef _drv_rcc_h_
#define _drv_rcc_h_

#include "stm32f4xx.h"
void RCC_HSE_Config(uint32_t pllm, uint32_t plln, uint32_t pllp, uint32_t pllq);
void RCC_Init(void); //初始化时钟
#endif /*_drv_rcc_h_*/

