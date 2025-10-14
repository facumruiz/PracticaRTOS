/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Práctica 2 - Ejercicio 4
 *  Software Timers: auto-reload (periódico) y one-shot
 ************************************************************************************/

/* Bibliotecas FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* Funciones de soporte del ejemplo (para imprimir, etc.) */
#include "supporting_functions.h"


/* Definiciones de periodos     */


/* Periodo del timer auto-reload (500 ms) */
#define AUTO_RELOAD_TIMER_PERIOD    ( pdMS_TO_TICKS( 500UL ) )

/* Periodo del timer one-shot (3,333 ms) */
#define ONE_SHOT_TIMER_PERIOD       ( pdMS_TO_TICKS( 3333UL ) )


/* Prototipos de funciones      */

static void prvAutoReloadTimerCallback( TimerHandle_t xTimer );
static void prvOneShotTimerCallback( TimerHandle_t xTimer );


/* Función principal            */

int main( void )
{
    /* Manejadores de los timers */
    TimerHandle_t xAutoReloadTimer;
    TimerHandle_t xOneShotTimer;

    /* Variables para verificar el arranque */
    BaseType_t xTimer1Started, xTimer2Started;

    
    /* Creación del timer auto-reload (periódico cada 500 ms)   */
    
    xAutoReloadTimer = xTimerCreate(
                            "AutoReload",               /* Nombre (debug) */
                            AUTO_RELOAD_TIMER_PERIOD,   /* Periodo en ticks */
                            pdTRUE,                     /* pdTRUE → auto-reload */
                            0,                          /* ID del timer (no usado) */
                            prvAutoReloadTimerCallback  /* Función callback */
                        );

    
    /* Creación del timer one-shot (única ejecución a 3,333 s)  */
    
    xOneShotTimer = xTimerCreate(
                        "OneShot",                     /* Nombre (debug) */
                        ONE_SHOT_TIMER_PERIOD,         /* Periodo en ticks */
                        pdFALSE,                       /* pdFALSE → one-shot */
                        0,                             /* ID del timer (no usado) */
                        prvOneShotTimerCallback        /* Función callback */
                    );

    
    /* Inicio de los timers si se crearon correctamente          */
    
    if( ( xAutoReloadTimer != NULL ) && ( xOneShotTimer != NULL ) )
    {
        /* Arranque sin tiempo de bloqueo */
        xTimer1Started = xTimerStart( xAutoReloadTimer, 0 );
        xTimer2Started = xTimerStart( xOneShotTimer, 0 );

        /* Si ambos timers iniciaron correctamente → iniciar scheduler */
        if( ( xTimer1Started == pdPASS ) && ( xTimer2Started == pdPASS ) )
        {
            vTaskStartScheduler();
        }
    }

    /* Si el scheduler arranca correctamente, nunca se llega aquí */
    for( ;; );
    return 0;
}


/* Callbacks de los timers      */


/* Callback del timer auto-reload */
static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
    TickType_t xTimeNow = xTaskGetTickCount();
    vPrintStringAndNumber( "Auto-reload timer callback executing", xTimeNow );
}

/* Callback del timer one-shot */
static void prvOneShotTimerCallback( TimerHandle_t xTimer )
{
    TickType_t xTimeNow = xTaskGetTickCount();
    vPrintStringAndNumber( "One-shot timer callback executing", xTimeNow );
}
