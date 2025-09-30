/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Ejercicio 6 - Borrado de tareas
 *
 ************************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "supporting_functions.h"

/* Delay en ms (si tick = 1 ms) */
#define mainTASK_DELAY    pdMS_TO_TICKS(500)

/* Estructura para pasar parámetros a la tarea */
typedef struct {
    const char* pcMessage;
    int nRepetitions;
} TaskParams_t;

/* Declaración de funciones de tareas */
void vTaskWithParam(void* pvParameters);

/* Parámetros para las tareas */
TaskParams_t xTask1Params = { "Mensaje Tarea 1\n", -1 };   // -1 = infinito
TaskParams_t xTask2Params = { "Mensaje Tarea 2\n", 5 };    // ejecuta 5 veces y se borra

/*-----------------------------------------------------------*/
int main(void)
{
    /* Tarea 1: prioridad alta (nunca se borra) */
    xTaskCreate(vTaskWithParam, "Task 1", 1000, &xTask1Params, 2, NULL);

    /* Tarea 2: prioridad baja (se borra después de N repeticiones) */
    xTaskCreate(vTaskWithParam, "Task 2", 1000, &xTask2Params, 1, NULL);

    vTaskStartScheduler();

    for (;;);
}
/*-----------------------------------------------------------*/

/* Función de tarea */
void vTaskWithParam(void* pvParameters)
{
    TaskParams_t* pxParams = (TaskParams_t*) pvParameters;
    int counter = pxParams->nRepetitions;

    for (;;)
    {
        vPrintString(pxParams->pcMessage);

        /* Si tiene un número limitado de repeticiones */
        if (counter > 0) {
            counter--;
            if (counter == 0) {
                vPrintString("Tarea finalizada, se elimina a sí misma.\n");
                vTaskDelete(NULL);   // Borra esta tarea
            }
        }

        vTaskDelay(mainTASK_DELAY);
    }
}
