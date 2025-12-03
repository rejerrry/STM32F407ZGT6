#include "drv_beep.h"
/*有源蜂鸣器*/
/*******************************************************************************
* 函 数 名         : Beep_Init
* 函数功能		   : 蜂鸣器初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	BEEP_PORT_RCC_ENABLE;

	GPIO_InitStructure.Pin = BEEP_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  //推挽输出
	GPIO_InitStructure.Pull = GPIO_PULLUP;          //上拉
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(BEEP_PORT, &GPIO_InitStructure);

	HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, GPIO_PIN_RESET);

}

void Beep_On(void)
{
	HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, GPIO_PIN_SET);
}

void Beep_Off(void)
{
	HAL_GPIO_WritePin(BEEP_PORT, BEEP_PIN, GPIO_PIN_RESET);
}
