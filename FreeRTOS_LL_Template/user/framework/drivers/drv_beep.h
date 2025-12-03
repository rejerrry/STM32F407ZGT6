#ifndef _drv_beep_h_
#define _drv_beep_h_

#include "stm32f4xx.h"
/*  蜂鸣器时钟端口、引脚定义 */
#define BEEP_PORT 			GPIOF   
#define BEEP_PIN 			GPIO_Pin_8
#define BEEP_PORT_RCC		RCC_AHB1Periph_GPIOF

void Beep_Init(void);
void Beep_On(void);
void Beep_Off(void);
#endif /*_drv_beep_h_*/
