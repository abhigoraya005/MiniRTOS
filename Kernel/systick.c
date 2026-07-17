#include <stdio.h>
#include <stdint.h>

#include "systick.h"


/*
 * Global kernel tick counter.
 *
 * Static keeps the variable private
 * to this source file.
 */
static uint32_t system_tick = 0;


/*
 * Initialize System Tick.
 */
void MiniRTOS_SysTickInit(void)
{
    system_tick = 0;

    printf(
        "[SYSTICK] System tick initialized.\n"
    );
}


/*
 * Increment system tick.
 */
void MiniRTOS_SysTickIncrement(void)
{
    system_tick++;
}


/*
 * Return current system tick.
 */
uint32_t MiniRTOS_GetTick(void)
{
    return system_tick;
}


/*
 * Reset system tick.
 */
void MiniRTOS_ResetTick(void)
{
    system_tick = 0;

    printf(
        "[SYSTICK] System tick reset.\n"
    );
}