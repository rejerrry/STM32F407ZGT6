#ifndef _drv_ds18b20_h
#define _drv_ds18b20_h

#include "stm32f4xx.h"
#include "system.h"
//IO方向设置
//#define DS18B20_IO_IN()  {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=0<<9*2;}	//PG9输入模式
//#define DS18B20_IO_OUT() {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=1<<9*2;} 	//PG9输出模式
 
////IO操作函数											   
#define	DS18B20_DQ_OUT PGout(9) //数据端口	PG9
#define	DS18B20_DQ_IN  PGin(9)  //数据端口	PG9 
   	
uint8_t DS18B20_Init(void);			//初始化DS18B20
float DS18B20_GetTemperture(void);	//获取温度
void DS18B20_Start(void);		//开始温度转换
void DS18B20_Write_Byte(uint8_t dat);//写入一个字节
uint8_t DS18B20_Read_Byte(void);		//读出一个字节
uint8_t DS18B20_Read_Bit(void);		//读出一个位
uint8_t DS18B20_Check(void);			//检测是否存在DS18B20
void DS18B20_Reset(void);			//复位DS18B20   




#endif
