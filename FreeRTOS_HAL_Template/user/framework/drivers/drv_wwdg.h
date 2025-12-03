#ifndef _drv_wwdg_h
#define _drv_wwdg_h


#include "stm32f4xx.h" 

void WWDG_Init(uint8_t tr, uint8_t wr, uint32_t fprer);
#endif
