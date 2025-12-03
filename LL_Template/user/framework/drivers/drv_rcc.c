#include "drv_rcc.h"

/*******************************************************************************
* 函 数 名         : RCC_HSE_Config
* 函数功能		   : 自定义系统时钟
* 输    入         : pllm：VCO 输入时钟 分频因子，范围0-63
					 plln：VCO 输出时钟 倍频因子，范围192-432
					 pllp：PLLCLK 时钟分频因子，范围2, 4, 6, or 8
					 pllq：OTG FS,SDIO,RNG 时钟分频因子，范围4-15
* 输    出         : 无
*******************************************************************************/
void RCC_HSE_Config(uint32_t pllm,uint32_t plln,uint32_t pllp,uint32_t pllq)
{
	RCC_DeInit(); //将外设RCC寄存器重设为缺省值
	RCC_HSEConfig(RCC_HSE_ON);//设置外部高速晶振（HSE）
	if(RCC_WaitForHSEStartUp()==SUCCESS) //等待HSE起振
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//设置AHB时钟（HCLK）
		RCC_PCLK2Config(RCC_HCLK_Div2);//设置低速APB2时钟（PCLK2）=HCLK/2
		RCC_PCLK1Config(RCC_HCLK_Div4);//设置低速APB1时钟（PCLK1）=HCLK/4 
		RCC_PLLConfig(RCC_PLLSource_HSE,pllm,plln,pllp,pllq);//设置PLL时钟源及倍频系数
		RCC_PLLCmd(ENABLE); //使能或者失能PLL
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);//检查指定的RCC标志位设置与否,PLL就绪
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//设置系统时钟（SYSCLK）
		while(RCC_GetSYSCLKSource()!=0x08);//返回用作系统时钟的时钟源,0x08：PLL作为系统时钟
	}	
}

/*设置168Mhz*/
/*
RCC_HSEConfig	 HSE 模块	8 MHz	外部晶振输入
RCC_PLLSource_HSE	PLL Source Mux	Select HSE	PLL源选择
pllm	Main PLL -> /M	/ 4	PLL 输入分频
plln	Main PLL -> *N	X 168	PLL 倍频
pllp	Main PLL -> /P	/ 2	PLL 主输出分频
RCC_SYSCLKSource_PLLCLK	System Clock Mux	Select PLLCLK	系统主时钟源
RCC_SYSCLK_Div1	AHB Prescaler	/ 1	决定 HCLK (168MHz)
RCC_HCLK_Div4	APB1 Prescaler	/ 4	决定 PCLK1 (42MHz)
RCC_HCLK_Div2	APB2 Prescaler	/ 2	决定 PCLK2 (84MHz)
*/

/*
/Q 输出通常是专门供给特定外设使用的，主要是 USB、SDIO（SD卡）和 RNG（随机数生成器）。
标准要求：这些外设通常严格要求 48 MHz 的时钟频率
*/

void RCC_Init(void)
{
	RCC_HSE_Config(4,168,2,4);
}

