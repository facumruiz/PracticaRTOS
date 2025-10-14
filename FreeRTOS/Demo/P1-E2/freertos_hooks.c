#include "FreeRTOS.h"
#include <stdio.h>

/* Hook obligatorio si configSUPPORT_STATIC_ALLOCATION = 1 */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/* Hook de malloc fallido */
void vApplicationMallocFailedHook(void)
{
    printf("Malloc failed!\n");
    fflush(stdout);
    for(;;);
}

/* Hook de assert de FreeRTOS */
void vAssertCalled(const char * const pcFileName, unsigned long ulLine)
{
    printf("ASSERT! %s:%lu\n", pcFileName, ulLine);
    fflush(stdout);
    for(;;);
}
