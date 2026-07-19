#ifndef MINIRTOS_CORTEX_M_PORT_H
#define MINIRTOS_CORTEX_M_PORT_H

#include <stdint.h>

#include "../Kernel/task.h"

/*
 * Initialize the MiniRTOS port layer.
 */
void MiniRTOS_PortInit(void);

/*
 * Simulate saving the context
 * of the currently running task.
 */
void MiniRTOS_PortSaveContext(
    MiniRTOS_TCB_t *task
);

/*
 * Simulate restoring the context
 * of the next task.
 */
void MiniRTOS_PortRestoreContext(
    MiniRTOS_TCB_t *task
);

/*
 * Simulate a context switch.
 */
void MiniRTOS_PortContextSwitch(
    MiniRTOS_TCB_t *current_task,
    MiniRTOS_TCB_t *next_task
);

/*
 * Return total number of simulated
 * context switches.
 */
uint32_t MiniRTOS_PortGetContextSwitchCount(void);

#endif