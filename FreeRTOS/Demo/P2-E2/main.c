/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Práctica 2 - Ejercicio 2
 *  Delays - Uso de vTaskDelayUntil
 ************************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "supporting_functions.h"  

void vTaskFunction(void* pvParameters);

int main(void)
{
    xTaskCreate(vTaskFunction, "Task", 1000, "Hola desde la tarea\n", 1, NULL);
    vTaskStartScheduler();

    for (;;);
}

void vTaskFunction(void* pvParameters)
{
    const char* pcTaskName = (const char*) pvParameters;
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(500);

    // Inicializa xLastWakeTime con el tiempo actual
    xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        vPrintString(pcTaskName);

        // Espera hasta que pasen exactamente 500ms desde el último "wake time"
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
