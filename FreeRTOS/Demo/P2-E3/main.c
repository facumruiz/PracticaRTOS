/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Práctica 2 - Ejercicio 3
 *  Delays - Tareas continuas y tareas periódicas
 ************************************************************************************/


#include "FreeRTOS.h"
#include "task.h"
#include "supporting_functions.h"

// Prototipos de tareas
void vContinuousTask(void* pvParameters);
void vPeriodicTask(void* pvParameters);

int main(void)
{
    // Crear dos tareas continuas con prioridad 1
    xTaskCreate(vContinuousTask, "Cont1", 1000, "Tarea Continua 1\n", 1, NULL);
    xTaskCreate(vContinuousTask, "Cont2", 1000, "Tarea Continua 2\n", 1, NULL);

    // Crear tarea periódica con prioridad 2
    xTaskCreate(vPeriodicTask, "Periodic", 1000, ">>> Tarea Periodica <<<\n", 2, NULL);

    vTaskStartScheduler();

    for (;;);
}

// Tarea continua: imprime sin demora
void vContinuousTask(void* pvParameters)
{
    const char* msg = (const char*) pvParameters;
    for (;;)
    {
        vPrintString(msg);
        // Lazo nulo (sin delay): ocupa CPU todo el tiempo
    }
}

// Tarea periódica: imprime cada 1000 ms
void vPeriodicTask(void* pvParameters)
{
    const char* msg = (const char*) pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(1000);  // 1 segundo

    for (;;)
    {
        vPrintString(msg);
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}
