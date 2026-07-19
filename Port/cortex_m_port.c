#include <stdio.h>

#include "cortex_m_port.h"

/*
 * Number of simulated context switches.
 */
static uint32_t context_switch_count = 0;


/*
 * Initialize port layer.
 */
void MiniRTOS_PortInit(void)
{
    context_switch_count = 0;

    printf(
        "[PORT] Cortex-M context manager simulation initialized.\n"
    );
}


/*
 * Simulate saving task context.
 */
void MiniRTOS_PortSaveContext(
    MiniRTOS_TCB_t *task
)
{
    if (task == NULL)
    {
        return;
    }

    printf(
        "[CONTEXT] Saving context of Task %lu: %s\n",
        (unsigned long)task->task_id,
        task->task_name
    );
}


/*
 * Simulate restoring task context.
 */
void MiniRTOS_PortRestoreContext(
    MiniRTOS_TCB_t *task
)
{
    if (task == NULL)
    {
        return;
    }

    printf(
        "[CONTEXT] Restoring context of Task %lu: %s\n",
        (unsigned long)task->task_id,
        task->task_name
    );
}


/*
 * Simulate switching execution
 * from one task to another.
 */
void MiniRTOS_PortContextSwitch(
    MiniRTOS_TCB_t *current_task,
    MiniRTOS_TCB_t *next_task
)
{
    if (next_task == NULL)
    {
        return;
    }

    printf(
        "[CONTEXT] ---- Context Switch ----\n"
    );

    if (current_task != NULL)
    {
        MiniRTOS_PortSaveContext(
            current_task
        );
    }
    else
    {
        printf(
            "[CONTEXT] No previous task context.\n"
        );
    }

    MiniRTOS_PortRestoreContext(
        next_task
    );

    context_switch_count++;

    printf(
        "[CONTEXT] Total Context Switches: %lu\n",
        (unsigned long)context_switch_count
    );
}


/*
 * Return total simulated
 * context switch count.
 */
uint32_t MiniRTOS_PortGetContextSwitchCount(void)
{
    return context_switch_count;
}