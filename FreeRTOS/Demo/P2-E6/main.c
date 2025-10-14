/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Práctica 2 - Ejercicio 6
 *  Simulación de un Watchdog con Software Timers
 ************************************************************************************/

/* Bibliotecas FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* Biblioteca de soporte para impresión */
#include "supporting_functions.h"


/* Definiciones de periodos     */

#define HEARTBEAT_PERIOD_MS     pdMS_TO_TICKS( 500UL )    /* Heartbeat cada 500 ms */
#define WATCHDOG_TIMEOUT_MS     pdMS_TO_TICKS( 2000UL )   /* 4 heartbeats perdidos = 2 s */


/* Prototipos de funciones      */

static void vHeartbeatTimerCallback( TimerHandle_t xTimer );
static void vWatchdogTimerCallback( TimerHandle_t xTimer );


/* Variables globales           */

static TimerHandle_t xHeartbeatTimer = NULL;
static TimerHandle_t xWatchdogTimer  = NULL;

/* Contador de heartbeats para simular una falla */
static int heartbeatCount = 0;
#define HEARTBEATS_BEFORE_FAILURE   10


/* Función principal            */

int main( void )
{
    BaseType_t xStarted1, xStarted2;

    /* Creación del timer de watchdog (one-shot) */
    xWatchdogTimer = xTimerCreate(
                        "Watchdog",
                        WATCHDOG_TIMEOUT_MS,
                        pdFALSE,   /* one-shot */
                        0,
                        vWatchdogTimerCallback
                    );

    /* Creación del timer heartbeat (periódico) */
    xHeartbeatTimer = xTimerCreate(
                        "Heartbeat",
                        HEARTBEAT_PERIOD_MS,
                        pdTRUE,    /* auto-reload */
                        0,
                        vHeartbeatTimerCallback
                    );

    if( ( xHeartbeatTimer != NULL ) && ( xWatchdogTimer != NULL ) )
    {
        /* Inicia ambos timers */
        xStarted1 = xTimerStart( xHeartbeatTimer, 0 );
        xStarted2 = xTimerStart( xWatchdogTimer, 0 );

        if( ( xStarted1 == pdPASS ) && ( xStarted2 == pdPASS ) )
        {
            vTaskStartScheduler();
        }
    }

    for( ;; );
    return 0;
}


/* Callbacks de los timers      */


/* Callback del heartbeat */
static void vHeartbeatTimerCallback( TimerHandle_t xTimer )
{
    TickType_t xTimeNow = xTaskGetTickCount();
    heartbeatCount++;

    /* Simula envío de señal de vida */
    vPrintStringAndNumber( "Heartbeat signal sent at", xTimeNow );

    /* Simula una falla después de 10 heartbeats */
    if( heartbeatCount > HEARTBEATS_BEFORE_FAILURE )
    {
        vPrintString( "!! FAILURE: Heartbeat stopped !!" );
        xTimerStop( xHeartbeatTimer, 0 );
        return;
    }

    /* Reset del watchdog → señal de vida recibida */
    if( xTimerReset( xWatchdogTimer, 0 ) == pdPASS )
    {
        vPrintString( "Watchdog reset by heartbeat\n" );
    }
}

/* Callback del watchdog */
static void vWatchdogTimerCallback( TimerHandle_t xTimer )
{
    TickType_t xTimeNow = xTaskGetTickCount();
    vPrintStringAndNumber( ">>> WATCHDOG ACTIVATED! <<< at", xTimeNow );
}
