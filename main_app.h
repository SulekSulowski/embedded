#ifndef NAUKA_H_
#define NAUKA_H_

#include "main.h"
#include "string.h"
#include "stdio.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32h7xx_hal_conf.h"
#include "stm32h7xx_it.h"
#include "usart.h"
#include "strings.h"
#include "queue.h"


int main_app(void);
void period_print_task( void *pvParameters );
void continous_print_task(void *pvParameters );
void send_to_queue_task(void *pvParameters);
void receive_from_queue_task(void *pvParameters);

#endif
