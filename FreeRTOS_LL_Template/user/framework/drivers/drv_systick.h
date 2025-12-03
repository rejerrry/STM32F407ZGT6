#ifndef _drv_systick_h
#define _drv_systick_h

#include "stm32f4xx.h"
void SysTick_Init(uint8_t SYSCLK);
void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);
void delay_xms(uint32_t nms);


#endif /*_drv_sys_h_*/
