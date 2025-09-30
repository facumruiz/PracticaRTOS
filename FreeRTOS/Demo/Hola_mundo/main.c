#include <stdio.h>
// #include <conio.h>

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

void func_1(void);

TaskHandle_t TASK_1 = NULL;

int main(void) {
	xTaskCreate(func_1, "TASK_1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	vTaskStartScheduler();
	for (;;);
}

void func_1(void) {
	TaskHandle_t tsk1;
	while (1) {
		tsk1 = xTaskGetCurrentTaskHandle();
		printf("\n %s Hola mundo! \n", pcTaskGetName(tsk1));
	}
	vTaskDelay(1000);
}