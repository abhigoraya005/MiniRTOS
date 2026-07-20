#ifndef MINIRTOS_MUTEX_H
#define MINIRTOS_MUTEX_H

#include <stdint.h>


/*
 * MiniRTOS Mutex
 *
 * locked:
 * 0 = Unlocked
 * 1 = Locked
 *
 * owner_task_id:
 * ID of the task that currently
 * owns the mutex.
 */
typedef struct
{
    uint8_t locked;
    uint32_t owner_task_id;

} MiniRTOS_Mutex_t;


/*
 * Initialize mutex.
 *
 * Returns:
 *  0  Success
 * -1  Invalid mutex pointer
 */
int MiniRTOS_MutexInit(
    MiniRTOS_Mutex_t *mutex
);


/*
 * Attempt to lock mutex.
 *
 * Returns:
 *  0  Mutex acquired
 * -1  Mutex already locked
 */
int MiniRTOS_MutexLock(
    MiniRTOS_Mutex_t *mutex,
    uint32_t task_id
);


/*
 * Unlock mutex.
 *
 * Only the owning task can unlock.
 *
 * Returns:
 *  0  Mutex released
 * -1  Operation failed
 */
int MiniRTOS_MutexUnlock(
    MiniRTOS_Mutex_t *mutex,
    uint32_t task_id
);


/*
 * Check whether mutex is locked.
 */
uint8_t MiniRTOS_MutexIsLocked(
    const MiniRTOS_Mutex_t *mutex
);


/*
 * Return mutex owner task ID.
 *
 * Returns 0 when mutex is unlocked.
 */
uint32_t MiniRTOS_MutexGetOwner(
    const MiniRTOS_Mutex_t *mutex
);

#endif