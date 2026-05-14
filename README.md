-----------------------------------------------------------------
|  This project is worked on STM32CubeIDE and board STM32F411RC |
----------------------------------------------------------------- 

# Feature
How to use QUEUE features in FreeRTOS via CMSIS-v2

## Description
- Creating Handle for QUEUE
- Tx_Tasks store messages into QUEUE and Rx_Task pull the messages from the QUEUE
- No Priority for messages, follow strictly FIFO rule
- Also using Semaphore to avoid the procces of retrieving the messages being corrupted by sending Task preempting
