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
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	RCC_AHB1PeriphClockCmd(BEEP_PORT_RCC,ENABLE); //使能端口F时钟
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT; //输出模式
	GPIO_InitStructure.GPIO_Pin=BEEP_PIN;//管脚设置F8
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度为100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉
	GPIO_Init(BEEP_PORT,&GPIO_InitStructure); //初始化结构体
	
	GPIO_ResetBits(BEEP_PORT,BEEP_PIN); //关闭蜂鸣器
	
}

void Beep_On(void)
{
	GPIO_SetBits(BEEP_PORT,BEEP_PIN);
}

void Beep_Off(void)
{
	GPIO_ResetBits(BEEP_PORT,BEEP_PIN);
}
