/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Ejercicio 1
 *  Delays - Uso del estado blocked para generar una demora
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

void vTask1(void* pvParameters);
void vTask2(void* pvParameters);

/*-----------------------------------------------------------*/


int main(void)
{
    /* Creación de una tarea. */
    xTaskCreate(vTask1,   /* Puntero a la función que implimenta la tarea. */
        "Task 1", /* Nombre de texto de la tarea, solo se usa en debugging. */
        1000,     /* Profundidad de la pila - la mayoria de los microcontroladores chicos usan mucho menos que esto. */
        NULL,     /* No usamos parámetros de tarea. */
        1,        /* Esta tarea se ejecutará en prioridad 1. */
        NULL);   /* No usamos handle de tarea. */

    /* Creación de nueva tarea (Tarea 2). */
    xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);   
  

    /* Arranque del scheduler. */
    vTaskStartScheduler();


    /* Esta linea no debería ser alcanzada porque vTaskStartScheduler()
    *  solo retornará si no hay suficiente memoria en la heap de FreeRTOS disponible para
    *  crear la tarea Idle. */
    for (; ; )
    {
    }


    return 0;
}
/*-----------------------------------------------------------*/


void vTask1(void* pvParameters)
{
    const char* pcTaskName = "Tarea 1 ejecutando \r\n";
    volatile uint32_t ul;


    /* Como la mayoria, esta tarea esta implementada con un loop infinito. */
    for (; ; )
    {
        /* Imprime el nombre de la tarea. */
        vPrintString(pcTaskName);


        /* Delay bloqueante. */
        for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++)
        {
            /* Este delay no hace nada. Más adelante se utilizará 
             * una función apropiada para hacer delay/ sleep. */
        }
    }
}



void vTask2(void* pvParameters)
{
    const char* pcTaskName = "Tarea 2 ejecutando \r\n";
    volatile uint32_t ul;


    /* Como la mayoria, esta tarea esta implementada con un loop infinito. */
    for (; ; )
    {
        /* Imprime el nombre de la tarea. */
        vPrintString(pcTaskName);


        /* Delay bloqueante. */
        for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++)
        {
            /* Este delay no hace nada. Más adelante se utilizará 
             * una función apropiada para hacer delay/ sleep. */
        }
    }
}