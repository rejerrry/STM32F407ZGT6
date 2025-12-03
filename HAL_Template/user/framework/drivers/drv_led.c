#include "drv_led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*LED1*/
	LED1_PORT_RCC_ENABLE();//使能GPIOF端口时钟
	GPIO_InitStructure.Pin = LED1_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  //推挽输出
	GPIO_InitStructure.Pull = GPIO_PULLUP;          //上拉
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(LED1_PORT, &GPIO_InitStructure);

	/*LED2*/
	LED2_PORT_RCC_ENABLE();//使能GPIOF端口时钟
	GPIO_InitStructure.Pin = LED2_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;  //推挽输出
	GPIO_InitStructure.Pull = GPIO_PULLUP;          //上拉
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;     //高速
	HAL_GPIO_Init(LED2_PORT, &GPIO_InitStructure);

	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);	//PF9置1，默认初始化后灯灭
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET);	//PF10置1，默认初始化后灯灭
}

void LED1_ON(void)
{
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_RESET);	//PF9置0，LED1亮	
}
void LED1_OFF(void)
{
	HAL_GPIO_WritePin(LED1_PORT, LED1_PIN, GPIO_PIN_SET);	//PF9置1，LED1灭
}
void LED2_ON(void)
{
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_RESET);	//PF10置0，LED2亮
}
void LED2_OFF(void)
{
	HAL_GPIO_WritePin(LED2_PORT, LED2_PIN, GPIO_PIN_SET);	//PF10置1，LED2灭
}
