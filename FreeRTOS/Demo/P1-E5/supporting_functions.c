#include <stdio.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

/* Deshabilitamos la detención con tecla en POSIX */
BaseType_t xKeyPressesStopApplication = pdFALSE;

/*-----------------------------------------------------------*/

void vPrintString( const char *pcString )
{
    /* Se protege la impresión con secciones críticas */
    taskENTER_CRITICAL();
    {
        printf("%s", pcString);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
}

/*-----------------------------------------------------------*/

void vPrintStringAndNumber( const char *pcString, uint32_t ulValue )
{
    taskENTER_CRITICAL();
    {
        printf("%s %lu\r\n", pcString, ulValue);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
}

/*-----------------------------------------------------------*/

void vPrintTwoStrings( const char *pcString1, const char *pcString2 )
{
    vTaskSuspendAll();
    {
        printf("At time %lu: %s %s\r\n", xTaskGetTickCount(), pcString1, pcString2);
        fflush(stdout);
    }
    xTaskResumeAll();
}

/*-----------------------------------------------------------*/
/*
void vApplicationMallocFailedHook(void)
{
    printf("Malloc failed!\n");
    fflush(stdout);
    for (;;);
}
*/
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    (void) pxTask;
    (void) pcTaskName;
    printf("Stack overflow!\n");
    fflush(stdout);
    for (;;);
}

/*-----------------------------------------------------------*/

void vApplicationTickHook(void)
{
    /* Nada que hacer en POSIX */
}

/*-----------------------------------------------------------*/
/*
void vAssertCalled(const char * const pcFileName, unsigned long ulLine)
{
    printf("ASSERT! %s:%lu\n", pcFileName, ulLine);
    fflush(stdout);
    for (;;);
}
*/