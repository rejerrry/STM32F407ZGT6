#ifndef _drv_input_h
#define _drv_input_h

#include "stm32f4xx.h"

extern uint8_t TIM5_CH1_CAPTURE_STA; //输入捕获的状态
extern uint32_t TIM5_CH1_CAPTURE_VAL;//输入捕获值


void TIM5_CH1_Input_Init(uint32_t arr,uint16_t psc);
void Input_IRQHandler(void);
#endif
