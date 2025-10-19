/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Ejercicio 5 
 *  Control de porcentaje de CPU usando prioridades
 ************************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "supporting_functions.h"

/* Configuración de porcentaje de CPU */
#define TASK1_RATIO 80    // Cambiar: 80, 50 o 30

/* Delay simulado (busy loop) */
#define MAIN_DELAY_LOOP_COUNT (0x0FFFFF)

/* Handles de tareas */
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

/-----------------------------------------------------------/
/* Tarea genérica */
void vTaskWithParam(void *pvParameters)
{
    const char *msg = (const char *)pvParameters;
    volatile uint32_t ul;

    for (;;)
    {
        /* Mostrar mensaje */
        vPrintString(msg);

        /* Simular trabajo bloqueante */
        for (ul = 0; ul < MAIN_DELAY_LOOP_COUNT; ul++) { }

        /* Cede la CPU para alternancia */
        taskYIELD();
    }
}

/-----------------------------------------------------------/
int main(void)
{
    /* Crear tareas con prioridad base */
    xTaskCreate(vTaskWithParam, "Task 1", 1000, "Tarea 1 ejecutando\n", 1, &task1Handle);
    xTaskCreate(vTaskWithParam, "Task 2", 1000, "Tarea 2 ejecutando\n", 1, &task2Handle);

    /* Ajustar prioridades según TASK1_RATIO */
    switch (TASK1_RATIO)
    {
        case 80: // Task1 80%, Task2 20%
            vTaskPrioritySet(task1Handle, 3);
            vTaskPrioritySet(task2Handle, 1);
            break;

        case 50: // 50%-50%
            vTaskPrioritySet(task1Handle, 2);
            vTaskPrioritySet(task2Handle, 2);
            break;

        case 30: // Task1 30%, Task2 70%
            vTaskPrioritySet(task1Handle, 1);
            vTaskPrioritySet(task2Handle, 3);
            break;

        default: // Igual prioridad
            vTaskPrioritySet(task1Handle, 2);
            vTaskPrioritySet(task2Handle, 2);
            break;
    }

    /* Inicia scheduler */
    vTaskStartScheduler();

    /* No debería llegar aquí */
    for (;;);
}
