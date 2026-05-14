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
/* Definitions for Tx_Task1 */
osThreadId_t Tx_Task1Handle;
const osThreadAttr_t Tx_Task1_attributes = {
  .name = "Tx_Task1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Tx_Task2 */
osThreadId_t Tx_Task2Handle;
const osThreadAttr_t Tx_Task2_attributes = {
  .name = "Tx_Task2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Rx_Task */
osThreadId_t Rx_TaskHandle;
const osThreadAttr_t Rx_Task_attributes = {
  .name = "Rx_Task",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};
/* Definitions for messageQueue */
osMessageQueueId_t messageQueueHandle;
const osMessageQueueAttr_t messageQueue_attributes = {
  .name = "messageQueue"
};
/* Definitions for BinarySem */
osSemaphoreId_t BinarySemHandle;
const osSemaphoreAttr_t BinarySem_attributes = {
  .name = "BinarySem"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
typedef struct {
	uint8_t event_id;		// Identify which Task message belongs to
	uint32_t timestamp;
} messageQueue_t;
/* USER CODE END FunctionPrototypes */

void Task1_Init(void *argument);
void Task2_Init(void *argument);
void Rx_Task_Init(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of BinarySem */
  BinarySemHandle = osSemaphoreNew(1, 1, &BinarySem_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of messageQueue */
  messageQueueHandle = osMessageQueueNew (10, sizeof(messageQueue_t), &messageQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Tx_Task1 */
  Tx_Task1Handle = osThreadNew(Task1_Init, NULL, &Tx_Task1_attributes);

  /* creation of Tx_Task2 */
  Tx_Task2Handle = osThreadNew(Task2_Init, NULL, &Tx_Task2_attributes);

  /* creation of Rx_Task */
  Rx_TaskHandle = osThreadNew(Rx_Task_Init, NULL, &Rx_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Task1_Init */
/**
  * @brief  Sending data to Queue whenever the button is pressed
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task1_Init */
void Task1_Init(void *argument)
{
  /* USER CODE BEGIN Task1_Init */
  /* Infinite loop */

	messageQueue_t msg;

  for(;;)
  {
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET)
	  {
		  msg.event_id = 0x01;		// Belongs to Task 1
		  msg.timestamp = HAL_GetTick();

		  /** osMessageQueuePut (osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)
		    * @param:
		    * mq_id: handler for Queue
		    * *msg_ptr: &msg: the message to put into Queue
		    * *msg_prio: 0: all the message has same priority --> FIFO rule
		    * timeout: 0: no waiting --> only in case ensuring that Queue does not out of space
		    */
		  osMessageQueuePut(messageQueueHandle, &msg, 0, 0);

		  osDelay(200);		// Prevent button debouncing
	  }
	  osDelay(20);
  }
  /* USER CODE END Task1_Init */
}

/* USER CODE BEGIN Header_Task2_Init */
/**
* @brief Sending data to Queue every second
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task2_Init */
void Task2_Init(void *argument)
{
  /* USER CODE BEGIN Task2_Init */
  /* Infinite loop */

	messageQueue_t msg;

  for(;;)
  {
	  msg.event_id = 0x02;	// Belongs to Task2
	  msg.timestamp = HAL_GetTick() / 1000;

	  /** osMessageQueuePut (osMessageQueueId_t mq_id, const void *msg_ptr, uint8_t msg_prio, uint32_t timeout)
	    * @param:
	    * mq_id: handler for Queue
	    * *msg_ptr: &msg: the message to put into Queue
	    * *msg_prio: 0: all the message has same priority --> FIFO rule
	    * timeout: 0: no waiting --> only in case ensuring that Queue does not out of space
	    */
	  osMessageQueuePut(messageQueueHandle, &msg, 0, 0);

	  osDelay(1000);
  }
  /* USER CODE END Task2_Init */
}

/* USER CODE BEGIN Header_Rx_Task_Init */
/**
* @brief Function implementing the Rx_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Rx_Task_Init */
void Rx_Task_Init(void *argument)
{
  /* USER CODE BEGIN Rx_Task_Init */
  /* Infinite loop */

	messageQueue_t msg;

  for(;;)
  {
	  /** osMessageQueueGet (osMessageQueueId_t mq_id, void *msg_ptr, uint8_t *msg_prio, uint32_t timeout)
	    * @param
	    * mq_id: handler for Queue
	    * *msg_ptr: &msg: the message to retrieve from Queue
	    * *msg_prio: 0: all the message has same priority --> FIFO rule
	    * timeout: osWaitForever: unlimited waiting --> only print when the read is successful
	    */
	  if(osMessageQueueGet(messageQueueHandle, &msg, 0, osWaitForever) == osOK)
	  {
		  UART_print("Event ID: %d, Timestamp: %lu\n", msg.event_id, msg.timestamp);
	  }

	  osDelay(1);
  }
  /* USER CODE END Rx_Task_Init */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void UART_print(char* str, ...)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}
/* USER CODE END Application */

