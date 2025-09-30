/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Ejercicio 4
 *
 ************************************************************************************/


 /* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"


/* Demo includes. */
#include "supporting_functions.h"


/* Usado como contador de loop para implementar un delay bloqueante */
#define mainDELAY_LOOP_COUNT    ( 0xffffff )


/*-----------------------------------------------------------*/
/* Declaración de funciones de tareas */

void vTaskWithParam(void* pvParameters);

/*-----------------------------------------------------------*/
int main(void)
{
    /* Tarea 1: prioridad alta */
    xTaskCreate(vTaskWithParam, "Task 1", 1000, "Mensaje Tarea 1\n", 2, NULL);

    /* Tarea 2: prioridad baja */
    xTaskCreate(vTaskWithParam, "Task 2", 1000, "Mensaje Tarea 2\n", 1, NULL);

    vTaskStartScheduler();

    for (;;);
}
/*-----------------------------------------------------------*/

/* Función de tarea que recibe un parámetro */
void vTaskWithParam(void* pvParameters)
{
    /* pvParameters contiene un puntero al mensaje */
    const char* pcTaskName = (const char*) pvParameters;
    volatile uint32_t ul;

    for (;;)
    {
        /* Imprime el mensaje de la tarea recibido como parámetro */
        vPrintString(pcTaskName);

        /* Delay bloqueante simulado */
        for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++) { }
    }
}
