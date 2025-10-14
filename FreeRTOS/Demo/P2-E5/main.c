/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Práctica 2 - Ejercicio 5 (Timer Reset)
 *  Software Timers: reset de un timer one-shot desde otro timer
 ************************************************************************************/

/* Bibliotecas FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* Funciones de soporte del ejemplo */
#include "supporting_functions.h"


/* Definiciones de periodos     */

#define AUTO_RELOAD_TIMER_PERIOD    ( pdMS_TO_TICKS( 500UL ) )
#define ONE_SHOT_TIMER_PERIOD       ( pdMS_TO_TICKS( 3333UL ) )


/* Prototipos de funciones      */

static void prvAutoReloadTimerCallback( TimerHandle_t xTimer );
static void prvOneShotTimerCallback( TimerHandle_t xTimer );

/* Manejador global del timer one-shot, para poder resetearlo desde el callback */
static TimerHandle_t xOneShotTimer = NULL;


/* Función principal            */

int main( void )
{
    TimerHandle_t xAutoReloadTimer;
    BaseType_t xTimer1Started, xTimer2Started;

    /* Creación del timer auto-reload (periódico de 500 ms) */
    xAutoReloadTimer = xTimerCreate(
                            "AutoReload",
                            AUTO_RELOAD_TIMER_PERIOD,
                            pdTRUE,   /* auto-reload */
                            0,
                            prvAutoReloadTimerCallback
                        );

    /* Creación del timer one-shot (única ejecución a los 3.333 s) */
    xOneShotTimer = xTimerCreate(
                        "OneShot",
                        ONE_SHOT_TIMER_PERIOD,
                        pdFALSE,  /* one-shot */
                        0,
                        prvOneShotTimerCallback
                    );

    if( ( xAutoReloadTimer != NULL ) && ( xOneShotTimer != NULL ) )
    {
        xTimer1Started = xTimerStart( xAutoReloadTimer, 0 );
        xTimer2Started = xTimerStart( xOneShotTimer, 0 );

        if( ( xTimer1Started == pdPASS ) && ( xTimer2Started == pdPASS ) )
        {
            vTaskStartScheduler();
        }
    }

    for( ;; );
    return 0;
}


/* Callbacks de los timers      */


/* Timer periódico: cada 500 ms imprime y resetea el one-shot */
static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
    TickType_t xTimeNow = xTaskGetTickCount();

    vPrintStringAndNumber( "Auto-reload timer callback executing", xTimeNow );

    /* Cada vez que se ejecuta el timer periódico, reinicia el one-shot */
    if( xTimerReset( xOneShotTimer, 0 ) == pdPASS )
    {
        vPrintString( "One-shot timer reset by auto-reload timer\n" );
    }
    else
    {
        vPrintString( "Failed to reset one-shot timer\n" );
    }
}

/* Timer one-shot: imprime cuando logra ejecutarse (si no fue reseteado) */
static void prvOneShotTimerCallback( TimerHandle_t xTimer )
{
    TickType_t xTimeNow = xTaskGetTickCount();
    vPrintStringAndNumber( "One-shot timer callback executing\n", xTimeNow );
}
