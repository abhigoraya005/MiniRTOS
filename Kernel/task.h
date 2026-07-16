#ifndef MINIRTOS_TASK_H
#define MINIRTOS_TASK_H

#include <stdint.h>
#include <stddef.h>

/* Maximum number of tasks supported by MiniRTOS */
#define MINIRTOS_MAX_TASKS 8

/* Maximum length of a task name */
#define MINIRTOS_TASK_NAME_LENGTH 16

/* Task function pointer type */
typedef void (*MiniRTOS_TaskFunction_t)(void);

/* Possible task states */
typedef enum
{
    MINIRTOS_TASK_READY = 0,
    MINIRTOS_TASK_RUNNING,
    MINIRTOS_TASK_BLOCKED,
    MINIRTOS_TASK_SUSPENDED

} MiniRTOS_TaskState_t;

/* Task Control Block */
typedef struct
{
    uint32_t task_id;

    char task_name[MINIRTOS_TASK_NAME_LENGTH];

    MiniRTOS_TaskFunction_t task_function;

    uint8_t priority;

    MiniRTOS_TaskState_t state;

    void *stack_pointer;
  uint32_t wake_tick;
} MiniRTOS_TCB_t;


/* Initialize the task manager */
void MiniRTOS_TaskManagerInit(void);


/* Create and register a new task */
int MiniRTOS_CreateTask(
    const char *task_name,
    MiniRTOS_TaskFunction_t task_function,
    uint8_t priority
);


/* Get task using its index */
MiniRTOS_TCB_t *MiniRTOS_GetTask(
    uint32_t index
);


/* Get total number of registered tasks */
uint32_t MiniRTOS_GetTaskCount(void);


/* Print information about a task */
void MiniRTOS_TaskPrintInfo(
    const MiniRTOS_TCB_t *task
);


/* Print all registered tasks */
void MiniRTOS_PrintTaskTable(void);


/* Convert task state to readable string */
const char *MiniRTOS_TaskStateToString(
    MiniRTOS_TaskState_t state
);
/*
 * Set the state of a task.
 */
int MiniRTOS_SetTaskState(
    uint32_t task_id,
    MiniRTOS_TaskState_t new_state
);


/*
 * Get task using its Task ID.
 */
MiniRTOS_TCB_t *MiniRTOS_GetTaskByID(
    uint32_t task_id
);


/*
 * Suspend a task.
 */
int MiniRTOS_SuspendTask(
    uint32_t task_id
);


/*
 * Resume a suspended task.
 */
int MiniRTOS_ResumeTask(
    uint32_t task_id
);


/*
 * Block a task.
 */
int MiniRTOS_BlockTask(
    uint32_t task_id
);


/*
 * Unblock a blocked task.
 */
int MiniRTOS_UnblockTask(
    uint32_t task_id
);
/*
 * Delay a task for a specified number
 * of simulated kernel ticks.
 */
int MiniRTOS_DelayTask(
    uint32_t task_id,
    uint32_t delay_ticks
);


/*
 * Check all delayed tasks and wake
 * tasks whose delay has expired.
 */
void MiniRTOS_UpdateDelayedTasks(
    uint32_t current_tick
);
#endif