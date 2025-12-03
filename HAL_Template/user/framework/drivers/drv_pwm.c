#include "drv_pwm.h"

TIM_HandleTypeDef TIM14_Handler;      	//定时器句柄 
TIM_OC_InitTypeDef TIM14_CH1Handler;	//定时器14通道1句柄

/*******************************************************************************
* 函 数 名         : TIM14_CH1_PWM_Init
* 函数功能		   : TIM14通道1 PWM初始化函数
* 输    入         : per:重装载值
					 psc:分频系数
* 输    出         : 无
*******************************************************************************/
void TIM14_CH1_PWM_Init(uint16_t per,uint16_t psc)
{
	TIM14_Handler.Instance=TIM14;          	//定时器14
    TIM14_Handler.Init.Prescaler=psc;       //定时器分频
    TIM14_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    TIM14_Handler.Init.Period=per;          //自动重装载值
    TIM14_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM14_Handler);       //初始化PWM
    
    TIM14_CH1Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    TIM14_CH1Handler.Pulse=per/2;            //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    TIM14_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //输出比较极性为低 
    HAL_TIM_PWM_ConfigChannel(&TIM14_Handler,&TIM14_CH1Handler,TIM_CHANNEL_1);//配置TIM14通道1
	
    HAL_TIM_PWM_Start(&TIM14_Handler,TIM_CHANNEL_1);//开启PWM通道1	
}

//定时器底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_PWM_Init()调用
//htim:定时器句柄
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_TIM14_CLK_ENABLE();			//使能定时器14
	__HAL_RCC_GPIOF_CLK_ENABLE();			//开启GPIOF时钟
	
	GPIO_Initure.Pin=GPIO_PIN_9;           	//PF9
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
	GPIO_Initure.Alternate= GPIO_AF9_TIM14;	//PF9复用为TIM14_CH1
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);
}

//设置TIM通道4的占空比
//compare:比较值
void TIM14_SetCompare1(uint32_t compare)
{
	TIM14->CCR1=compare; 
}
