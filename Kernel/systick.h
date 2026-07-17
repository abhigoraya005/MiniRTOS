#ifndef MINIRTOS_SYSTICK_H
#define MINIRTOS_SYSTICK_H

#include <stdint.h>

/*
 * Initialize the MiniRTOS system tick.
 */
void MiniRTOS_SysTickInit(void);


/*
 * Increment the system tick counter.
 *
 * In the host simulation this function
 * is called manually by the scheduler.
 *
 * On ARM Cortex-M it can later be called
 * from a hardware SysTick interrupt.
 */
void MiniRTOS_SysTickIncrement(void);


/*
 * Return the current system tick value.
 */
uint32_t MiniRTOS_GetTick(void);


/*
 * Reset the system tick counter.
 */
void MiniRTOS_ResetTick(void);

#endif