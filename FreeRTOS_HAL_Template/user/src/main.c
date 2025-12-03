/**
  ******************************************************************************
  * @file    Templates/Src/main.c
  * @author  MCD Application Team
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

  /* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "bsp_system.h"
#include "FreeRTOS.h"
#include "task.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

#define START_TASK_PRIO		1 //任务优先级
#define START_STK_SIZE 		128   //任务堆栈大小	
#define LED1_TASK_PRIO		2 //任务优先级
#define LED1_STK_SIZE 		50 //任务堆栈大小	
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TaskHandle_t StartTask_Handler;//任务句柄
TaskHandle_t LED1Task_Handler;//任务句柄
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void start_task(void* pvParameters);//任务函数
void led1_task(void* pvParameters);//任务函数

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

  /* Configure the system clock to 168 MHz */
  /* Initialize the system */
  HAL_Init();//初始化HAL库 hal_delay-timer6
  SystemClock_SetSysClk168M();
  SysTick_Init(168);//freertos系统节拍
  LED_Init();
  USART1_Init(115200);

  //创建开始任务
  xTaskCreate((TaskFunction_t)start_task,            //任务函数
    (const char*)"start_task",          //任务名称
    (uint16_t)START_STK_SIZE,        //任务堆栈大小
    (void*)NULL,                  //传递给任务函数的参数
    (UBaseType_t)START_TASK_PRIO,       //任务优先级
    (TaskHandle_t*)&StartTask_Handler);   //任务句柄              
  vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void* pvParameters)
{
  taskENTER_CRITICAL();           //进入临界区
  //创建LED1任务
  xTaskCreate((TaskFunction_t)led1_task,
    (const char*)"led1_task",
    (uint16_t)LED1_STK_SIZE,
    (void*)NULL,
    (UBaseType_t)LED1_TASK_PRIO,
    (TaskHandle_t*)&LED1Task_Handler);
  vTaskDelete(StartTask_Handler); //删除开始任务
  taskEXIT_CRITICAL();            //退出临界区
}


void led1_task(void* pvParameters)//LED1任务函数
{
  while (1)
  {
    LED1_ON();
    LED2_ON();
    vTaskDelay(500);
    LED1_OFF();
    LED2_OFF();
    vTaskDelay(500);
  }
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

     /* Infinite loop */
  while (1)
  {
  }
}
#endif

