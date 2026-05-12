/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId NormalTaskHandle;
osThreadId LowTaskHandle;
osThreadId HighTaskHandle;
osThreadId VeryHighTaskHandle;
osMutexId myMutexHandle;
osSemaphoreId BinarySemHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartNormalTask(void const * argument);
void StartLowTask(void const * argument);
void StartHighTask(void const * argument);
void StartV_HighTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of myMutex */
  osMutexDef(myMutex);
  myMutexHandle = osMutexCreate(osMutex(myMutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of BinarySem */
  osSemaphoreDef(BinarySem);
  BinarySemHandle = osSemaphoreCreate(osSemaphore(BinarySem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of NormalTask */
  osThreadDef(NormalTask, StartNormalTask, osPriorityNormal, 0, 512);
  NormalTaskHandle = osThreadCreate(osThread(NormalTask), NULL);

  /* definition and creation of LowTask */
  osThreadDef(LowTask, StartLowTask, osPriorityBelowNormal, 0, 512);
  LowTaskHandle = osThreadCreate(osThread(LowTask), NULL);

  /* definition and creation of HighTask */
  osThreadDef(HighTask, StartHighTask, osPriorityAboveNormal, 0, 512);
  HighTaskHandle = osThreadCreate(osThread(HighTask), NULL);

  /* definition and creation of VeryHighTask */
  osThreadDef(VeryHighTask, StartV_HighTask, osPriorityHigh, 0, 512);
  VeryHighTaskHandle = osThreadCreate(osThread(VeryHighTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartNormalTask */
/**
  * @brief  Function implementing the NormalTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartNormalTask */
void StartNormalTask(void const * argument)
{
  /* USER CODE BEGIN StartNormalTask */
  /* Infinite loop */
  for(;;)
  {

	  /* Example of Creating Tasks with 3 different levels of Priorities */
//	  send_normaltask();

	  /* Example of Semaphore */
//	  char *str1 = "Entering NormalTask\n";
//	  HAL_UART_Transmit(&huart2, (uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);
//
//	  char *str2 = "Leaving NormalTask\n\n";
//	  HAL_UART_Transmit(&huart2, (uint8_t *)str2, strlen(str2), HAL_MAX_DELAY);
//	  osDelay(500);

	  /* Example of Mutex */
	  UART_print("Entered NormalTask, performing task\n\n");

	  // using osWait: pausing the current task --> make others higher priority preempting
	  // using parameter wait: the current task continuously running
	  uint32_t wait = 50000000;
	  while(wait--);	// running empty loop ~5s

	  UART_print("NormalTask finished, leaving NormalTask\n\n");
	  osDelay(200);

  }
  /* USER CODE END StartNormalTask */
}

/* USER CODE BEGIN Header_StartLowTask */
/**
* @brief Function implementing the LowTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLowTask */
void StartLowTask(void const * argument)
{
  /* USER CODE BEGIN StartLowTask */
  /* Infinite loop */
  for(;;)
  {
	  /* Example of Creating Tasks with 3 different levels of Priorities */
//	  send_lowtask();

	  /* Example of Semaphore */
//	  char *str1 = "Entering LowTask and Waiting for Semaphore\n";
//	  HAL_UART_Transmit(&huart2, (uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);
//
//	  osSemaphoreWait(BinarySemHandle, osWaitForever);	// Wait until there is 1 available Semaphore
//
//	  char *str3 = "Semaphore acquired by LowTask\n";
//	  HAL_UART_Transmit(&huart2, (uint8_t *)str3, strlen(str3), HAL_MAX_DELAY);
//
//	  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
//	  // Wait unit the button (PA8) is pressed
//	  // Otherwise LowTask will not Release Semaphore and other Tasks that requiring Semaphore must be waiting
//
//	  char *str2 = "Leaving LowTask and Releasing Semaphore\n\n";
//	  HAL_UART_Transmit(&huart2, (uint8_t *)str2, strlen(str2), HAL_MAX_DELAY);
//
//	  osSemaphoreRelease(BinarySemHandle);
//	  osDelay(500);

	  /* Example of Mutex */
	  /* With Mutex, the program itself will know which Task is holding Mutex
	   * and possible for Priority Inheritance for Priority Inversion */
	  UART_print("Entered LowTask, waiting for Mutex\n\n");
	  osMutexWait(myMutexHandle, osWaitForever);
	  UART_print("LowTask acquired Mutex, Using Resource\n\n");

	  // for Priority Inheritance: LowTask = HighTask (since HighTask blocks by Mutex)
	  // for VeryHighTask display Priority of each Task
	  uint32_t wait = 10000000;
	  while(wait--);	// running empty loop ~1s

	  UART_print("LowTask finished, released Mutex\n\n");
	  osMutexRelease(myMutexHandle);
	  UART_print("Leaving LowTask\n\n");

	  osDelay(300);

  }
  /* USER CODE END StartLowTask */
}

/* USER CODE BEGIN Header_StartHighTask */
/**
* @brief Function implementing the HighTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartHighTask */
void StartHighTask(void const * argument)
{
  /* USER CODE BEGIN StartHighTask */
  /* Infinite loop */
	osDelay(500);
  for(;;)
  {
	  /* Example of Creating Tasks with 3 different levels of Priorities */
//	  send_hightask();

	  /* Example of Semaphore */
//	  char *str1 = "Entering HighTask and Waiting for Semaphore\n";
//	  HAL_UART_Transmit(&huart2, (uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);
//
//	  osSemaphoreWait(BinarySemHandle, osWaitForever);	// Wait until there is 1 available Semaphore
//
//	  char *str3 = "Semaphore acquired by HighTask\n";
//	  HAL_UART_Transmit(&huart2, (uint8_t *)str3, strlen(str3), HAL_MAX_DELAY);
//
//	  char *str2 = "Leaving HighTask and Releasing Semaphore\n\n";
//	  HAL_UART_Transmit(&huart2, (uint8_t *)str2, strlen(str2), HAL_MAX_DELAY);
//
//	  osSemaphoreRelease(BinarySemHandle);
//	  osDelay(500);

	  /* Example of Mutex */
	  UART_print("Entered HighTask, waiting for Mutex\n\n");
	  osMutexWait(myMutexHandle, osWaitForever);
	  UART_print("HighTask acquired and now releasing Mutex\n\n");
	  osMutexRelease(myMutexHandle);
	  osDelay(500);
  }
  /* USER CODE END StartHighTask */
}

/* USER CODE BEGIN Header_StartV_HighTask */
/**
* @brief Function implementing the VeryHighTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartV_HighTask */
void StartV_HighTask(void const * argument)
{
  /* USER CODE BEGIN StartV_HighTask */
  /* Infinite loop */
  for(;;)
  {
	  /* Example of Mutex */
      UART_print_priority("Priorities --> LPT:%d MPT:%d HPT:%d\n\n",
              osThreadGetPriority(LowTaskHandle),
              osThreadGetPriority(NormalTaskHandle),
              osThreadGetPriority(HighTaskHandle));
      osDelay(1000);
  }
  /* USER CODE END StartV_HighTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void UART_print(char *str)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

void UART_print_priority(const char *format, ...)
{
    char buffer[128];

    va_list args;

    va_start(args, format);

    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
}
/* USER CODE END Application */
