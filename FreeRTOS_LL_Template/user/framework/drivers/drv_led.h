#ifndef _drv_led_h
#define _drv_led_h

#include "stm32f4xx.h"

/*  LED时钟端口、引脚定义 */
#define LED1_PORT 			GPIOF   
#define LED1_PIN 			GPIO_Pin_9
#define LED1_PORT_RCC		RCC_AHB1Periph_GPIOF

#define LED2_PORT 			GPIOF   
#define LED2_PIN 			GPIO_Pin_10
#define LED2_PORT_RCC		RCC_AHB1Periph_GPIOF

void LED_Init(void);
void LED1_ON(void);
void LED1_OFF(void);
void LED2_ON(void);
void LED2_OFF(void);

#endif
