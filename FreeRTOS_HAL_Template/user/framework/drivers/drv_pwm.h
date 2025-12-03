#ifndef _drv_pwm_h
#define _drv_pwm_h

#include "stm32f4xx.h"

void TIM14_CH1_PWM_Init(uint16_t per, uint16_t psc);
void TIM14_SetCompare1(uint32_t compare);
#endif
