/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Ejercicio 5 - Modificado (ambas tareas funcionan)
 *
 ************************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "supporting_functions.h"

/* Periodo del delay en ticks (ej: 500 ms si configTICK_RATE_HZ = 1000) */
#define mainTASK_DELAY    pdMS_TO_TICKS(500)

void vTaskWithParam(void* pvParameters);

int main(void)
{
    /* Tarea 1: prioridad alta */
    xTaskCreate(vTaskWithParam, "Task 1", 1000, "Mensaje Tarea 1\n", 2, NULL);

    /* Tarea 2: prioridad baja */
    xTaskCreate(vTaskWithParam, "Task 2", 1000, "Mensaje Tarea 2\n", 1, NULL);

    vTaskStartScheduler();

    for (;;);
}

void vTaskWithParam(void* pvParameters)
{
    const char* pcTaskName = (const char*) pvParameters;

    for (;;)
    {
        vPrintString(pcTaskName);

        /* Cede la CPU al menos durante 500 ms */
        vTaskDelay(mainTASK_DELAY);
    }
}
