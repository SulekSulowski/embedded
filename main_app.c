
#include <main_app.h>


QueueHandle_t Queue;
uint32_t length = 5;
uint8_t tab[] = "siema";
uint32_t num = 100;

int main_app(void)
{
	Queue = xQueueCreate(length, sizeof(uint32_t));
	if(Queue == NULL)
	{
		return 0;
	}

	xTaskCreate(period_print_task, "print task", 1000, (void*)tab, 1, NULL);

	vTaskStartScheduler();
	while(1);
}

void period_print_task( void *pvParameters )
{
	uint8_t *arr = pvParameters;
	uint8_t size = strlen((char*)arr);

	TickType_t pxPreviousWakeTime = xTaskGetTickCount();
	TickType_t ms2ticks = pdMS_TO_TICKS(1000);

	while(1)
	{
		HAL_UART_Transmit(&huart3, arr, size, 1);
		vTaskDelayUntil(&pxPreviousWakeTime, ms2ticks);
	}
}

void continous_print_task(void *pvParameters )
{
	uint8_t *arr = pvParameters;
	uint8_t size = strlen((char*)arr);

	while(1)
	{
		HAL_UART_Transmit(&huart3, arr, size, 1);
	}
}

void send_to_queue_task(void *pvParameters)
{

	BaseType_t rtrn;
	const TickType_t ticks = pdMS_TO_TICKS(0);

	uint8_t tab[] = "sent \n\r";
	uint8_t l = strlen((char*)tab);

	uint8_t tab1[] = "couldn't sent \n\r";
	uint8_t l1 = strlen((char*)tab1);

	while(1)
	{
		rtrn = xQueueSend(Queue, pvParameters , ticks);
		if(rtrn == pdPASS)
		{
			HAL_UART_Transmit(&huart3, tab, l, 100);

		}
		else
		{
			HAL_UART_Transmit(&huart3, tab1, l1, 1);
		}
	}

}

void receive_from_queue_task(void *pvParameters)
{
	uint32_t number;
	BaseType_t rtrn;
	const TickType_t ticks = pdMS_TO_TICKS(100);

	uint8_t tab[] = "received \n\r";
	uint8_t l = strlen((char*)tab);

	uint8_t tab1[] = "couldn't receive \n\r";
	uint8_t l1 = strlen((char*)tab1);

	while(1)
	{
		rtrn = xQueueReceive(Queue, &number, ticks);
		if(rtrn == pdPASS)
		{
			HAL_UART_Transmit(&huart3, tab, l, 1);
		}
		else
		{
			HAL_UART_Transmit(&huart3, tab1, l1, 1);
		}
	}
}
