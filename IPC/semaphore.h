#ifndef MINIRTOS_SEMAPHORE_H
#define MINIRTOS_SEMAPHORE_H

#include <stdint.h>

/*
 * MiniRTOS Counting Semaphore
 */
typedef struct
{
    uint32_t count;
    uint32_t max_count;

} MiniRTOS_Semaphore_t;


/*
 * Initialize semaphore.
 *
 * initial_count:
 * Number of initially available resources.
 *
 * max_count:
 * Maximum semaphore count.
 *
 * Returns:
 *  0  Success
 * -1  Invalid parameters
 */
int MiniRTOS_SemaphoreInit(
    MiniRTOS_Semaphore_t *semaphore,
    uint32_t initial_count,
    uint32_t max_count
);


/*
 * Attempt to acquire semaphore.
 *
 * Returns:
 *  0  Semaphore acquired
 * -1  Semaphore unavailable
 */
int MiniRTOS_SemaphoreWait(
    MiniRTOS_Semaphore_t *semaphore
);


/*
 * Release semaphore.
 *
 * Returns:
 *  0  Semaphore released
 * -1  Semaphore already at maximum
 */
int MiniRTOS_SemaphoreSignal(
    MiniRTOS_Semaphore_t *semaphore
);


/*
 * Return current semaphore count.
 */
uint32_t MiniRTOS_SemaphoreGetCount(
    const MiniRTOS_Semaphore_t *semaphore
);

#endif