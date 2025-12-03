#ifndef _drv_iwdg_h
#define _drv_iwdg_h

#include "stm32f4xx.h"
void IWDG_Init(uint8_t pre,uint16_t rlr);
void IWDG_FeedDog(void);  //Î¹¹·

#endif

