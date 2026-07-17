#ifndef MINIRTOS_SCHEDULER_H
#define MINIRTOS_SCHEDULER_H

#include <stdint.h>
#include "task.h"

/*
 * Available scheduling policies.
 */
typedef enum
{
    MINIRTOS_SCHEDULER_ROUND_ROBIN = 0,
    MINIRTOS_SCHEDULER_PRIORITY

} MiniRTOS_SchedulerPolicy_t;


/*
 * Initialize scheduler.
 */
void MiniRTOS_SchedulerInit(void);


/*
 * Set scheduler policy.
 */
void MiniRTOS_SchedulerSetPolicy(
    MiniRTOS_SchedulerPolicy_t policy
);


/*
 * Get current scheduler policy.
 */
MiniRTOS_SchedulerPolicy_t MiniRTOS_SchedulerGetPolicy(void);


/*
 * Select next READY task using
 * round-robin scheduling.
 */
MiniRTOS_TCB_t *MiniRTOS_SchedulerGetNextTask(void);


/*
 * Select highest-priority READY task.
 */
MiniRTOS_TCB_t *MiniRTOS_SchedulerGetHighestPriorityTask(void);


/*
 * Execute one scheduler cycle.
 */
void MiniRTOS_SchedulerRunOnce(void);


/*
 * Run scheduler for a specified
 * number of cycles.
 */
void MiniRTOS_SchedulerRun(
    uint32_t cycles
);

#endif