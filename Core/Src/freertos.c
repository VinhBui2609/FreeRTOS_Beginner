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
#include <string.h>
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
osSemaphoreId BinarySemHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartNormalTask(void const * argument);
void StartLowTask(void const * argument);
void StartHighTask(void const * argument);

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
  osThreadDef(NormalTask, StartNormalTask, osPriorityNormal, 0, 128);
  NormalTaskHandle = osThreadCreate(osThread(NormalTask), NULL);

  /* definition and creation of LowTask */
  osThreadDef(LowTask, StartLowTask, osPriorityLow, 0, 128);
  LowTaskHandle = osThreadCreate(osThread(LowTask), NULL);

  /* definition and creation of HighTask */
  osThreadDef(HighTask, StartHighTask, osPriorityAboveNormal, 0, 128);
  HighTaskHandle = osThreadCreate(osThread(HighTask), NULL);

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
	  // ****Example of Creating Tasks with 3 different levels of Priorities****
//	  send_normaltask();

	  // ****Example of Semaphore****
	  char *str1 = "Entering NormalTask and Waiting for Semaphore\n";
	  HAL_UART_Transmit(&huart2, (uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);

	  osSemaphoreWait(BinarySemHandle, osWaitForever);	// Wait until there is 1 available Semaphore

	  char *str3 = "Semaphore acquired by NormalTask\n";
	  HAL_UART_Transmit(&huart2, (uint8_t *)str3, strlen(str3), HAL_MAX_DELAY);

	  HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
	  // Wait unit the button (PA13) is pressed
	  // Otherwise NormalTaks will not Release Semaphore and other Tasks that requiring Semaphore must be waiting

	  char *str2 = "Leaving NormalTask and Releasing Semaphore\n\n";
	  HAL_UART_Transmit(&huart2, (uint8_t *)str2, strlen(str2), HAL_MAX_DELAY);

	  osSemaphoreRelease(BinarySemHandle);
	  osDelay(500);
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
	  // ****Example of Creating Tasks with 3 different levels of Priorities****
//	  send_lowtask();

	  // ****Example of Semaphore****
	  char *str1 = "Entering LowTask\n";
	  HAL_UART_Transmit(&huart2, (uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);

	  char *str2 = "Leaving LowTask\n\n";
	  HAL_UART_Transmit(&huart2, (uint8_t *)str2, strlen(str2), HAL_MAX_DELAY);
	  osDelay(500);
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
  for(;;)
  {
	  // ****Example of Creating Tasks with 3 different levels of Priorities****
//	  send_hightask();

	  // ****Example of Semaphore****
	  char *str1 = "Entering HighTask and Waiting for Semaphore\n";
	  HAL_UART_Transmit(&huart2, (uint8_t *)str1, strlen(str1), HAL_MAX_DELAY);

	  osSemaphoreWait(BinarySemHandle, osWaitForever);	// Wait until there is 1 available Semaphore

	  char *str3 = "Semaphore acquired by HighTask\n";
	  HAL_UART_Transmit(&huart2, (uint8_t *)str3, strlen(str3), HAL_MAX_DELAY);

	  char *str2 = "Leaving HighTask and Releasing Semaphore\n\n";
	  HAL_UART_Transmit(&huart2, (uint8_t *)str2, strlen(str2), HAL_MAX_DELAY);

	  osSemaphoreRelease(BinarySemHandle);
	  osDelay(500);
  }
  /* USER CODE END StartHighTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
