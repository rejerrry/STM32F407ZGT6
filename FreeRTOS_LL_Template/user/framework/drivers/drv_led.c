#include "drv_led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
	
	RCC_AHB1PeriphClockCmd(LED1_PORT_RCC|LED2_PORT_RCC,ENABLE); //使能端口时钟
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT; //输出模式
	GPIO_InitStructure.GPIO_Pin=LED1_PIN;//管脚设置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度为100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;//上下拉电阻不使能
	GPIO_Init(LED1_PORT,&GPIO_InitStructure); //初始化结构体
	GPIO_SetBits(LED1_PORT,LED1_PIN);
	
	GPIO_InitStructure.GPIO_Pin=LED2_PIN;//管脚设置
	GPIO_Init(LED2_PORT,&GPIO_InitStructure); //初始化结构体
	GPIO_SetBits(LED2_PORT,LED2_PIN);
}
void LED1_ON(void)
{
	GPIO_ResetBits(LED1_PORT,LED1_PIN);
}
void LED1_OFF(void)
{
	GPIO_SetBits(LED1_PORT,LED1_PIN);
}
void LED2_ON(void)
{
	GPIO_ResetBits(LED2_PORT,LED2_PIN);
}
void LED2_OFF(void)
{
	GPIO_SetBits(LED2_PORT,LED2_PIN);
}
