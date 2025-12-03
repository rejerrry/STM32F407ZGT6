#include "drv_input.h"

TIM_HandleTypeDef TIM5_Handler;         //定时器5句柄


//定时器5通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM5_CH1_Input_Init(uint32_t arr, uint16_t psc)
{
	TIM_IC_InitTypeDef TIM5_CH1Config;

	TIM5_Handler.Instance = TIM5;                          //通用定时器5
	TIM5_Handler.Init.Prescaler = psc;                     //分频系数
	TIM5_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;    //向上计数器
	TIM5_Handler.Init.Period = arr;                        //自动装载值
	TIM5_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//时钟分频银子
	HAL_TIM_IC_Init(&TIM5_Handler);//初始化输入捕获时基参数

	TIM5_CH1Config.ICPolarity = TIM_ICPOLARITY_RISING;    //上升沿捕获
	TIM5_CH1Config.ICSelection = TIM_ICSELECTION_DIRECTTI;//映射到TI1上
	TIM5_CH1Config.ICPrescaler = TIM_ICPSC_DIV1;          //配置输入分频，不分频
	TIM5_CH1Config.ICFilter = 0;                          //配置输入滤波器，不滤波
	HAL_TIM_IC_ConfigChannel(&TIM5_Handler, &TIM5_CH1Config, TIM_CHANNEL_1);//配置TIM5通道1

	HAL_TIM_IC_Start_IT(&TIM5_Handler, TIM_CHANNEL_1);   //开启TIM5的捕获通道1，并且开启捕获中断
	__HAL_TIM_ENABLE_IT(&TIM5_Handler, TIM_IT_UPDATE);   //使能更新中断
}


//定时器5底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_IC_Init()调用
//htim:定时器5句柄
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef* htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_TIM5_CLK_ENABLE();            //使能TIM5时钟
	__HAL_RCC_GPIOA_CLK_ENABLE();			//开启GPIOA时钟

	GPIO_Initure.Pin = GPIO_PIN_0;            //PA0
	GPIO_Initure.Mode = GPIO_MODE_AF_PP;      //复用推挽输出
	GPIO_Initure.Pull = GPIO_PULLDOWN;        //下拉
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;     //高速
	GPIO_Initure.Alternate = GPIO_AF2_TIM5;   //PA0复用为TIM5通道1
	HAL_GPIO_Init(GPIOA, &GPIO_Initure);

	HAL_NVIC_SetPriority(TIM5_IRQn, 2, 0);    //设置中断优先级，抢占优先级2，子优先级0
	HAL_NVIC_EnableIRQ(TIM5_IRQn);          //开启ITM5中断通道  
}


//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
uint8_t  TIM5_CH1_CAPTURE_STA = 0;	//输入捕获状态		    				
uint32_t	TIM5_CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)


//定时器5中断服务函数
void TIM5_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TIM5_Handler);//定时器共用处理函数
}


//定时器更新中断（计数溢出）中断处理回调函数， 该函数在HAL_TIM_IRQHandler中会被调用
void Input_IRQHandler(void)
{
	if ((TIM5_CH1_CAPTURE_STA & 0X80) == 0)//还未成功捕获
	{
		if (TIM5_CH1_CAPTURE_STA & 0X40)//已经捕获到高电平了
		{
			if ((TIM5_CH1_CAPTURE_STA & 0X3F) == 0X3F)//高电平太长了
			{
				TIM5_CH1_CAPTURE_STA |= 0X80;		//标记成功捕获了一次
				TIM5_CH1_CAPTURE_VAL = 0XFFFFFFFF;
			}
			else
				TIM5_CH1_CAPTURE_STA++;
		}
	}
}

//定时器输入捕获中断处理回调函数，该函数在HAL_TIM_IRQHandler中会被调用
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* htim)//捕获中断发生时执行
{
	if ((TIM5_CH1_CAPTURE_STA & 0X80) == 0)//还未成功捕获
	{
		if (TIM5_CH1_CAPTURE_STA & 0X40)		//捕获到一个下降沿 		
		{
			TIM5_CH1_CAPTURE_STA |= 0X80;		//标记成功捕获到一次高电平脉宽
			TIM5_CH1_CAPTURE_VAL = HAL_TIM_ReadCapturedValue(&TIM5_Handler, TIM_CHANNEL_1);//获取当前的捕获值.
			TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler, TIM_CHANNEL_1);   //一定要先清除原来的设置！！
			TIM_SET_CAPTUREPOLARITY(&TIM5_Handler, TIM_CHANNEL_1, TIM_ICPOLARITY_RISING);//配置TIM5通道1上升沿捕获
		}
		else  								//还未开始,第一次捕获上升沿
		{
			TIM5_CH1_CAPTURE_STA = 0;			//清空
			TIM5_CH1_CAPTURE_VAL = 0;
			TIM5_CH1_CAPTURE_STA |= 0X40;		//标记捕获到了上升沿
			__HAL_TIM_DISABLE(&TIM5_Handler);        //关闭定时器5
			__HAL_TIM_SET_COUNTER(&TIM5_Handler, 0);
			TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler, TIM_CHANNEL_1);   //一定要先清除原来的设置！！
			TIM_SET_CAPTUREPOLARITY(&TIM5_Handler, TIM_CHANNEL_1, TIM_ICPOLARITY_FALLING);//定时器5通道1设置为下降沿捕获
			__HAL_TIM_ENABLE(&TIM5_Handler);//使能定时器5
		}
	}
}



