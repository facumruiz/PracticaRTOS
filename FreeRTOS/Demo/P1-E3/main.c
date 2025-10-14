/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Ejercicio 3
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
    /* Mensajes distintos para cada tarea */
    const char* msg1 = "Tarea 1 ejecutando \r\n";
    const char* msg2 = "Tarea 2 ejecutando \r\n";

    /* Creación de la primera tarea usando parámetro */
    xTaskCreate(vTaskWithParam, "Task 1", 1000, (void*)msg1, 1, NULL);

    /* Creación de la segunda tarea usando parámetro */
    xTaskCreate(vTaskWithParam, "Task 2", 1000, (void*)msg2, 1, NULL);

    /* Arranque del scheduler */
    vTaskStartScheduler();

    /* Esta línea no debería ser alcanzada */
    for (;;);

    return 0;
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
