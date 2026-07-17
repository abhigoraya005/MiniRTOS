#include "../Port/cortex_m_port.h"
#include <stdio.h>

#include "scheduler.h"
#include "task.h"
#include "systick.h"


/*
 * Round-robin index.
 */
static uint32_t current_task_index = 0;
/*
 * Previously scheduled task.
 *
 * Used by the host simulation to
 * demonstrate context transitions.
 */
static MiniRTOS_TCB_t *previous_task = NULL;

/*
 * Current scheduling policy.
 *
 * Default: Round Robin
 */
static MiniRTOS_SchedulerPolicy_t current_policy =
    MINIRTOS_SCHEDULER_ROUND_ROBIN;


/*
 * Initialize scheduler.
 */
void MiniRTOS_SchedulerInit(void)
{
    current_task_index = 0;
    previous_task = NULL;

    current_policy =
        MINIRTOS_SCHEDULER_ROUND_ROBIN;

    printf(
        "[SCHEDULER] Scheduler initialized.\n"
    );
}


/*
 * Set scheduling policy.
 */
void MiniRTOS_SchedulerSetPolicy(
    MiniRTOS_SchedulerPolicy_t policy
)
{
    current_policy = policy;

    /*
     * Reset selection position whenever
     * scheduling policy changes.
     */
    current_task_index = 0;

    if (
        policy ==
        MINIRTOS_SCHEDULER_PRIORITY
    )
    {
        printf(
            "[SCHEDULER] Policy changed to PRIORITY.\n"
        );
    }
    else
    {
        printf(
            "[SCHEDULER] Policy changed to ROUND ROBIN.\n"
        );
    }
}


/*
 * Return current scheduler policy.
 */
MiniRTOS_SchedulerPolicy_t
MiniRTOS_SchedulerGetPolicy(void)
{
    return current_policy;
}


/*
 * Round-Robin Task Selection
 */
MiniRTOS_TCB_t *MiniRTOS_SchedulerGetNextTask(void)
{
    uint32_t task_count;
    uint32_t checked_tasks;

    MiniRTOS_TCB_t *task;

    task_count = MiniRTOS_GetTaskCount();

    if (task_count == 0)
    {
        return NULL;
    }

    for (
        checked_tasks = 0;
        checked_tasks < task_count;
        checked_tasks++
    )
    {
        task =
            MiniRTOS_GetTask(
                current_task_index
            );

        current_task_index++;

        if (
            current_task_index >=
            task_count
        )
        {
            current_task_index = 0;
        }

        if (
            task != NULL &&
            task->state ==
                MINIRTOS_TASK_READY
        )
        {
            return task;
        }
    }

    return NULL;
}


/*
 * Priority-Based Task Selection
 *
 * Finds the highest priority among
 * READY tasks, then selects one task
 * at that priority using round-robin
 * table order.
 */
MiniRTOS_TCB_t *
MiniRTOS_SchedulerGetHighestPriorityTask(void)
{
    uint32_t task_count;
    uint32_t i;
    uint32_t checked_tasks;

    uint8_t highest_priority = 0;
    int ready_task_found = 0;

    MiniRTOS_TCB_t *task;

    task_count =
        MiniRTOS_GetTaskCount();

    if (task_count == 0)
    {
        return NULL;
    }


    /*
     * First pass:
     * Find highest priority among
     * all READY tasks.
     */
    for (
        i = 0;
        i < task_count;
        i++
    )
    {
        task =
            MiniRTOS_GetTask(i);

        if (
            task != NULL &&
            task->state ==
                MINIRTOS_TASK_READY
        )
        {
            if (
                !ready_task_found ||
                task->priority >
                    highest_priority
            )
            {
                highest_priority =
                    task->priority;

                ready_task_found = 1;
            }
        }
    }


    if (!ready_task_found)
    {
        return NULL;
    }


    /*
     * Second pass:
     * Round-robin selection among
     * READY tasks with the highest
     * priority.
     */
    for (
        checked_tasks = 0;
        checked_tasks < task_count;
        checked_tasks++
    )
    {
        task =
            MiniRTOS_GetTask(
                current_task_index
            );

        current_task_index++;

        if (
            current_task_index >=
            task_count
        )
        {
            current_task_index = 0;
        }


        if (
            task != NULL &&
            task->state ==
                MINIRTOS_TASK_READY &&
            task->priority ==
                highest_priority
        )
        {
            return task;
        }
    }


    return NULL;
}


/*
 * Execute one scheduler cycle.
 */
void MiniRTOS_SchedulerRunOnce(void)
{
    MiniRTOS_TCB_t *task;


    /*
     * Advance simulated kernel time.
     */
    MiniRTOS_SysTickIncrement();


    printf(
        "[TICK] %lu\n",
        (unsigned long)
            MiniRTOS_GetTick()
    );


    /*
     * Wake delayed tasks.
     */
    MiniRTOS_UpdateDelayedTasks(
        MiniRTOS_GetTick()
    );


    /*
     * Select task according to
     * current scheduling policy.
     */
    if (
        current_policy ==
        MINIRTOS_SCHEDULER_PRIORITY
    )
    {
        task =
            MiniRTOS_SchedulerGetHighestPriorityTask();
    }
    else
    {
        task =
            MiniRTOS_SchedulerGetNextTask();
    }


if (task == NULL)
{
    printf(
        "[SCHEDULER] No READY tasks available.\n"
    );

    return;
}


/*
 * Simulate a context switch when
 * execution moves to a different task.
 */
if (previous_task != task)
{
    MiniRTOS_PortContextSwitch(
        previous_task,
        task
    );
}


/*
 * Mark selected task RUNNING.
 */
task->state =
    MINIRTOS_TASK_RUNNING;


    printf(
        "[SCHEDULER] Running Task %lu: %s (Priority %u)\n",
        (unsigned long)
            task->task_id,
        task->task_name,
        task->priority
    );


    /*
     * Execute task.
     */
 if (
    task->task_function != NULL
)
{
    task->task_function();
}


/*
 * Remember the task that was
 * most recently executed.
 */
previous_task = task;


/*
 * Cooperative host simulation:
 * task returns to READY after
 * function execution.
 */
task->state =
    MINIRTOS_TASK_READY;


    /*
     * Cooperative host simulation:
     * task returns to READY after
     * function execution.
     */
    task->state =
        MINIRTOS_TASK_READY;
}


/*
 * Run scheduler.
 */
void MiniRTOS_SchedulerRun(
    uint32_t cycles
)
{
    uint32_t i;


    printf(
        "\n[SCHEDULER] Starting scheduler simulation...\n\n"
    );


    for (
        i = 0;
        i < cycles;
        i++
    )
    {
        printf(
            "[SCHEDULER] Cycle %lu\n",
            (unsigned long)(i + 1)
        );


        MiniRTOS_SchedulerRunOnce();


        printf("\n");
    }


    printf(
        "[SCHEDULER] Scheduler simulation completed.\n"
    );
}