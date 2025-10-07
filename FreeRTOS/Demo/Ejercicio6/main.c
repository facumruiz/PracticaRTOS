/************************************************************************************
 *  RTOS - Ejercicio 6
 *  2025
 *  Borrando tareas dinámicamente (basado en Ejercicio 5)
 ************************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "supporting_functions.h"

/* Escenario base: 80%-20% */
#define TASK1_RATIO 30

/* Número de ejecuciones de la Tarea 2 antes de eliminarse */
#define TASK2_RUN_COUNT 15

/* Contador de bucle para delay simulado */
#define MAIN_DELAY_LOOP_COUNT (0xffffff)

/* Handles de tareas */
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;

/*-----------------------------------------------------------*/
/* Tarea genérica — se usa tanto para Tarea 1 como Tarea 2 */
void vTaskWithParam(void *pvParameters)
{
    const char *msg = (const char *)pvParameters;
    volatile uint32_t ul;
    static uint32_t counter2 = 0;   /* Contador local estático para tarea 2 */

    for (;;)
    {
        vPrintString(msg);

        /* Delay bloqueante simulado (consume CPU) */
        for (ul = 0; ul < MAIN_DELAY_LOOP_COUNT; ul++) { }

        /* Si esta es la Tarea 2, controlar su cantidad de ejecuciones */
        if (pvParameters == (void *)"Tarea 2 ejecutando\n")
        {
            counter2++;
            if (counter2 >= TASK2_RUN_COUNT)
            {
                vPrintString("Tarea 2 finalizando y borrándose...\n");
                vTaskDelete(NULL);  /* Borra la tarea actual */
            }
        }
    }
}

/*-----------------------------------------------------------*/
int main(void)
{
    /* Crear tareas con prioridad inicial */
    xTaskCreate(vTaskWithParam, "Task 1", 1000, "Tarea 1 ejecutando\n", 1, &task1Handle);
    xTaskCreate(vTaskWithParam, "Task 2", 1000, "Tarea 2 ejecutando\n", 1, &task2Handle);

    /* Ajustar prioridades según el escenario */
    switch (TASK1_RATIO)
    {
        case 80: // Tarea 1 → 80%, Tarea 2 → 20%
            vTaskPrioritySet(task1Handle, 3);
            vTaskPrioritySet(task2Handle, 1);
            break;

        case 50: // 50% - 50%
            vTaskPrioritySet(task1Handle, 2);
            vTaskPrioritySet(task2Handle, 2);
            break;

        case 30: // Tarea 1 → 30%, Tarea 2 → 70%
            vTaskPrioritySet(task1Handle, 1);
            vTaskPrioritySet(task2Handle, 3);
            break;

        default: // Igual prioridad
            vTaskPrioritySet(task1Handle, 2);
            vTaskPrioritySet(task2Handle, 2);
            break;
    }

    /* Iniciar el scheduler */
    vTaskStartScheduler();

    /* No debería llegar aquí */
    for (;;);
}
