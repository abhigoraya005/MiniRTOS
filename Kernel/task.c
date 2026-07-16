#include "systick.h"
#include <stdio.h>
#include <string.h>

#include "task.h"


/*
 * MiniRTOS Task Table
 *
 * Stores all Task Control Blocks registered
 * with the kernel.
 */

static MiniRTOS_TCB_t task_table[MINIRTOS_MAX_TASKS];


/*
 * Number of currently registered tasks.
 */

static uint32_t task_count = 0;


/*
 * Initialize Task Manager
 */

void MiniRTOS_TaskManagerInit(void)
{
    task_count = 0;

    memset(
        task_table,
        0,
        sizeof(task_table)
    );

    printf(
        "[TASK MANAGER] Initialized. Maximum tasks: %d\n",
        MINIRTOS_MAX_TASKS
    );
}


/*
 * Create and register a task
 */

int MiniRTOS_CreateTask(
    const char *task_name,
    MiniRTOS_TaskFunction_t task_function,
    uint8_t priority
)
{
    MiniRTOS_TCB_t *task;

    /* Check if task table is full */

    if (task_count >= MINIRTOS_MAX_TASKS)
    {
        printf(
            "[ERROR] Task creation failed. Task table is full.\n"
        );

        return -1;
    }


    /* Validate parameters */

    if (task_name == NULL || task_function == NULL)
    {
        printf(
            "[ERROR] Task creation failed. Invalid parameters.\n"
        );

        return -1;
    }


    /*
     * Get next available Task Control Block
     */

    task = &task_table[task_count];


    /*
     * Assign Task ID
     *
     * IDs start from 1.
     */

    task->task_id = task_count + 1;


    /*
     * Copy task name safely
     */

    strncpy(
        task->task_name,
        task_name,
        MINIRTOS_TASK_NAME_LENGTH - 1
    );

    task->task_name[
        MINIRTOS_TASK_NAME_LENGTH - 1
    ] = '\0';


    /*
     * Store task function
     */

    task->task_function = task_function;


    /*
     * Store task priority
     */

    task->priority = priority;


    /*
     * New tasks start in READY state
     */

    task->state = MINIRTOS_TASK_READY;


    /*
     * Stack handling will be implemented
     * later during context management.
     */

    task->stack_pointer = NULL;
task->wake_tick = 0;

    /*
     * Increase registered task count
     */

    task_count++;


    printf(
        "[TASK MANAGER] Task created: %s (ID: %lu)\n",
        task->task_name,
        (unsigned long)task->task_id
    );


    return 0;
}


/*
 * Get task using table index
 */

MiniRTOS_TCB_t *MiniRTOS_GetTask(
    uint32_t index
)
{
    if (index >= task_count)
    {
        return NULL;
    }

    return &task_table[index];
}


/*
 * Return number of registered tasks
 */

uint32_t MiniRTOS_GetTaskCount(void)
{
    return task_count;
}


/*
 * Convert task state to string
 */

const char *MiniRTOS_TaskStateToString(
    MiniRTOS_TaskState_t state
)
{
    switch (state)
    {
        case MINIRTOS_TASK_READY:
            return "READY";

        case MINIRTOS_TASK_RUNNING:
            return "RUNNING";

        case MINIRTOS_TASK_BLOCKED:
            return "BLOCKED";

        case MINIRTOS_TASK_SUSPENDED:
            return "SUSPENDED";

        default:
            return "UNKNOWN";
    }
}


/*
 * Print information about one task
 */

void MiniRTOS_TaskPrintInfo(
    const MiniRTOS_TCB_t *task
)
{
    if (task == NULL)
    {
        return;
    }

    printf("---------------------------------\n");

    printf(
        "Task ID       : %lu\n",
        (unsigned long)task->task_id
    );

    printf(
        "Task Name     : %s\n",
        task->task_name
    );

    printf(
        "Priority      : %u\n",
        task->priority
    );

    printf(
        "State         : %s\n",
        MiniRTOS_TaskStateToString(
            task->state
        )
    );

    printf(
        "Stack Pointer : %p\n",
        task->stack_pointer
    );
}


/*
 * Print complete task table
 */

void MiniRTOS_PrintTaskTable(void)
{
    uint32_t i;

    printf("\n");
    printf("=================================\n");
    printf("       MiniRTOS Task Table       \n");
    printf("=================================\n");

    for (i = 0; i < task_count; i++)
    {
        MiniRTOS_TaskPrintInfo(
            &task_table[i]
        );
    }

    printf("---------------------------------\n");

    printf(
        "Total Tasks: %lu / %d\n",
        (unsigned long)task_count,
        MINIRTOS_MAX_TASKS
    );

    printf("=================================\n");
}
/*
 * Find a task using its public Task ID.
 */
MiniRTOS_TCB_t *MiniRTOS_GetTaskByID(
    uint32_t task_id
)
{
    uint32_t i;

    for (i = 0; i < task_count; i++)
    {
        if (task_table[i].task_id == task_id)
        {
            return &task_table[i];
        }
    }

    return NULL;
}


/*
 * Set task state.
 */
int MiniRTOS_SetTaskState(
    uint32_t task_id,
    MiniRTOS_TaskState_t new_state
)
{
    MiniRTOS_TCB_t *task;

    task = MiniRTOS_GetTaskByID(task_id);

    if (task == NULL)
    {
        printf(
            "[TASK MANAGER] Error: Task ID %lu not found.\n",
            (unsigned long)task_id
        );

        return -1;
    }

    task->state = new_state;

    printf(
        "[TASK MANAGER] Task %lu (%s) state changed to %s.\n",
        (unsigned long)task->task_id,
        task->task_name,
        MiniRTOS_TaskStateToString(task->state)
    );

    return 0;
}


/*
 * Suspend Task.
 */
int MiniRTOS_SuspendTask(
    uint32_t task_id
)
{
    return MiniRTOS_SetTaskState(
        task_id,
        MINIRTOS_TASK_SUSPENDED
    );
}


/*
 * Resume Task.
 */
int MiniRTOS_ResumeTask(
    uint32_t task_id
)
{
    MiniRTOS_TCB_t *task;

    task = MiniRTOS_GetTaskByID(task_id);

    if (task == NULL)
    {
        return -1;
    }

    if (task->state != MINIRTOS_TASK_SUSPENDED)
    {
        printf(
            "[TASK MANAGER] Cannot resume Task %lu. Task is not SUSPENDED.\n",
            (unsigned long)task_id
        );

        return -1;
    }

    return MiniRTOS_SetTaskState(
        task_id,
        MINIRTOS_TASK_READY
    );
}


/*
 * Block Task.
 */
int MiniRTOS_BlockTask(
    uint32_t task_id
)
{
    return MiniRTOS_SetTaskState(
        task_id,
        MINIRTOS_TASK_BLOCKED
    );
}


/*
 * Unblock Task.
 */
int MiniRTOS_UnblockTask(
    uint32_t task_id
)
{
    MiniRTOS_TCB_t *task;

    task = MiniRTOS_GetTaskByID(task_id);

    if (task == NULL)
    {
        return -1;
    }

    if (task->state != MINIRTOS_TASK_BLOCKED)
    {
        printf(
            "[TASK MANAGER] Cannot unblock Task %lu. Task is not BLOCKED.\n",
            (unsigned long)task_id
        );

        return -1;
    }

    return MiniRTOS_SetTaskState(
        task_id,
        MINIRTOS_TASK_READY
    );
}
/*
 * Delay a task for a specified
 * number of kernel ticks.
 */
int MiniRTOS_DelayTask(
    uint32_t task_id,
    uint32_t delay_ticks
)
{
    MiniRTOS_TCB_t *task;

    task = MiniRTOS_GetTaskByID(task_id);

    if (task == NULL)
    {
        printf(
            "[TASK MANAGER] Cannot delay Task %lu. Task not found.\n",
            (unsigned long)task_id
        );

        return -1;
    }

    /*
     * A zero-tick delay has no effect.
     */
    if (delay_ticks == 0)
    {
        return 0;
    }

    /*
     * Calculate the tick at which
     * the task should wake.
     */
    task->wake_tick =
        MiniRTOS_GetTick() + delay_ticks;

    /*
     * Delayed tasks enter BLOCKED state.
     */
    task->state = MINIRTOS_TASK_BLOCKED;

    printf(
        "[TASK MANAGER] Task %lu (%s) delayed until Tick %lu.\n",
        (unsigned long)task->task_id,
        task->task_name,
        (unsigned long)task->wake_tick
    );

    return 0;
}
/*
 * Check delayed tasks and automatically
 * return expired tasks to READY state.
 */
void MiniRTOS_UpdateDelayedTasks(
    uint32_t current_tick
)
{
    uint32_t i;

    for (i = 0; i < task_count; i++)
    {
        MiniRTOS_TCB_t *task =
            &task_table[i];

        /*
         * Only automatically wake BLOCKED
         * tasks that have a non-zero
         * wake tick.
         */
        if (
            task->state == MINIRTOS_TASK_BLOCKED &&
            task->wake_tick != 0 &&
            current_tick >= task->wake_tick
        )
        {
            task->state =
                MINIRTOS_TASK_READY;

            task->wake_tick = 0;

            printf(
                "[TASK MANAGER] Task %lu (%s) woke up at Tick %lu.\n",
                (unsigned long)task->task_id,
                task->task_name,
                (unsigned long)current_tick
            );
        }
    }
}