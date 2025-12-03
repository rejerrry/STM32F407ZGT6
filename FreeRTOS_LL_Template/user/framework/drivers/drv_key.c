#include "drv_key.h"
#include "drv_systick.h"

/*******************************************************************************
* 函 数 名         : Key_Init
* 函数功能		   : 按键初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOA,ENABLE); //使能端口时钟
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN; //输入模式
	GPIO_InitStructure.GPIO_Pin=KEY0_PIN|KEY1_PIN|KEY2_PIN;//管脚设置
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉
	GPIO_Init(KEY_PORT,&GPIO_InitStructure); //初始化结构体
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN; //输入模式
	GPIO_InitStructure.GPIO_Pin=KEY_UP_PIN;//管脚设置
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;//下拉
	GPIO_Init(KEY_UP_PORT,&GPIO_InitStructure); //初始化结构体
}

/*******************************************************************************
* 函 数 名         : Key_Scan
* 函数功能		   : 按键扫描检测
* 输    入         : mode=0:单次按下按键
					 mode=1：连续按下按键
* 输    出         : 0：未有按键按下
					 KEY_UP_PRESS：KEY_UP键按下
					 KEY0_PRESS：KEY0键按下
					 KEY1_PRESS：KEY1键按下
					 KEY2_PRESS：KEY2键按下
*******************************************************************************/
uint8_t Key_Scan(uint8_t mode)
{
	static uint8_t key=1;
	
	if(mode==1) //连续按键按下
		key=1;
	if(key==1&&(KEY_UP==1||KEY0==0||KEY1==0||KEY2==0)) //任意一个按键按下
	{
		delay_ms(10);  //消抖
		key=0;
		if(KEY_UP==1)
			return KEY_UP_PRESS; 
		else if(KEY0==0)
			return KEY0_PRESS; 
		else if(KEY1==0)
			return KEY1_PRESS; 
		else if(KEY2==0)
			return KEY2_PRESS; 
	}
	else if(KEY_UP==0&&KEY0==1&&KEY1==1&&KEY2==1)    //无按键按下
		key=1;
	return 0;
}
/*
int main()
{
	u8 key,i=0;
	SysTick_Init(168);
	LED_Init();
	BEEP_Init();
	KEY_Init();
	
	while(1)
	{
		key=KEY_Scan(0);   //扫描按键
		switch(key)
		{
			case KEY_UP_PRESS: LED2=0;break;      //点亮D2指示灯
			case KEY1_PRESS: LED2=1;break;    //熄灭D2指示灯
			case KEY2_PRESS: BEEP=1;break;    //蜂鸣器开
			case KEY0_PRESS: BEEP=0;break;    //蜂鸣器关
		}
		i++;
		if(i%20==0)
		{
			LED1=!LED1;      //LED1状态取反
		}
		delay_ms(10);
	}
}
*/
