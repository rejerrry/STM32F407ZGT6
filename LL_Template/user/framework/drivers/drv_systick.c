#include "drv_systick.h"

static uint8_t  fac_us=0;							//us延时倍乘数			   
static uint16_t fac_ms=0;							//ms延时倍乘数

/*******************************************************************************
* 函 数 名         : SysTick_Init
* 函数功能		   : SysTick初始化，SYSTICK的时钟固定为AHB时钟的1/8
* 输    入         : SYSCLK:系统时钟频率
* 输    出         : 无
*******************************************************************************/
void SysTick_Init(uint8_t SYSCLK)
{
 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	fac_us=SYSCLK/8;						//SYSCLK的8分频 保存1us所需的计数次数
	fac_ms=(uint16_t)fac_us*1000;				//每个ms需要的systick时钟数   
}								    

/*******************************************************************************
* 函 数 名         : delay_us
* 函数功能		   : us延时，
* 输    入         : nus：要延时的us数
					注意:nus的值,不要大于798915us(最大值即2^24/fac_us@fac_us=21)
* 输    出         : 无
*******************************************************************************/
void delay_us(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//时间加载	  		 
	SysTick->VAL=0x00;        				//清空计数器
	SysTick->CTRL|=0x01 ; //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~0x01; //关闭计数器
	SysTick->VAL =0X00;       				//清空计数器 
}

/*******************************************************************************
* 函 数 名         : delay_nms
* 函数功能		   : ms延时，
* 输    入         : nms：要延时的ms数
					注意:nms的值,SysTick->LOAD为24位寄存器，
					不要大于0xffffff*8*1000/SYSCLK
					对168M条件下,nms<=798ms 
* 输    出         : 无  必须初始化SysTick_Init
*******************************************************************************/
void delay_nms(uint16_t nms)
{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(uint32_t)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL|=0x01 ; //开始倒数 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL&=~0x01; //关闭计数器
	SysTick->VAL =0X00;     		  		//清空计数器	  	    
}

/*******************************************************************************
* 函 数 名         : delay_ms
* 函数功能		   : ms延时，
* 输    入         : nms：要延时的ms数 0~65535
* 输    出         : 无 必须初始化SysTick_Init
*******************************************************************************/
void delay_ms(uint16_t nms)
{	 	 
	uint8_t repeat=nms/540;		//这里用540,是考虑到某些客户可能超频使用,
							//比如超频到248M的时候,delay_nms最大只能延时541ms左右了
	uint16_t remain=nms%540;
	while(repeat)
	{
		delay_nms(540);
		repeat--;
	}
	if(remain)delay_nms(remain);
} 


