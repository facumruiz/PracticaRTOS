/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Práctica 2 - Ejercicio 1
 *  Simulación de un Watchdog con Software Timers
 ************************************************************************************/


#include "FreeRTOS.h"
#include "task.h"
#include "supporting_functions.h"  

/* Declaración de funciones de tareas */
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

        /* Delay de 500 ms liberando la CPU */
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
