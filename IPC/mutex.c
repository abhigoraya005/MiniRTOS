#include <stdio.h>

#include "mutex.h"


/*
 * Initialize mutex.
 */
int MiniRTOS_MutexInit(
    MiniRTOS_Mutex_t *mutex
)
{
    if (mutex == NULL)
    {
        printf(
            "[MUTEX] Error: NULL mutex.\n"
        );

        return -1;
    }

    mutex->locked = 0;
    mutex->owner_task_id = 0;

    printf(
        "[MUTEX] Initialized. State: UNLOCKED\n"
    );

    return 0;
}


/*
 * Attempt to acquire mutex.
 */
int MiniRTOS_MutexLock(
    MiniRTOS_Mutex_t *mutex,
    uint32_t task_id
)
{
    if (
        mutex == NULL ||
        task_id == 0
    )
    {
        return -1;
    }


    /*
     * Mutex already locked.
     */
    if (mutex->locked)
    {
        printf(
            "[MUTEX] Task %lu failed to acquire mutex. "
            "Owned by Task %lu.\n",
            (unsigned long)task_id,
            (unsigned long)mutex->owner_task_id
        );

        return -1;
    }


    /*
     * Assign ownership.
     */
    mutex->locked = 1;

    mutex->owner_task_id =
        task_id;


    printf(
        "[MUTEX] Task %lu acquired mutex.\n",
        (unsigned long)task_id
    );


    return 0;
}


/*
 * Release mutex.
 */
int MiniRTOS_MutexUnlock(
    MiniRTOS_Mutex_t *mutex,
    uint32_t task_id
)
{
    if (
        mutex == NULL ||
        task_id == 0
    )
    {
        return -1;
    }


    /*
     * Mutex is not locked.
     */
    if (!mutex->locked)
    {
        printf(
            "[MUTEX] Task %lu cannot unlock. Mutex is already unlocked.\n",
            (unsigned long)task_id
        );

        return -1;
    }


    /*
     * Verify ownership.
     */
    if (
        mutex->owner_task_id !=
        task_id
    )
    {
        printf(
            "[MUTEX] Task %lu cannot unlock mutex. "
            "Owner is Task %lu.\n",
            (unsigned long)task_id,
            (unsigned long)mutex->owner_task_id
        );

        return -1;
    }


    /*
     * Release ownership.
     */
    mutex->locked = 0;

    mutex->owner_task_id = 0;


    printf(
        "[MUTEX] Task %lu released mutex.\n",
        (unsigned long)task_id
    );


    return 0;
}


/*
 * Return mutex lock state.
 */
uint8_t MiniRTOS_MutexIsLocked(
    const MiniRTOS_Mutex_t *mutex
)
{
    if (mutex == NULL)
    {
        return 0;
    }

    return mutex->locked;
}


/*
 * Return mutex owner.
 */
uint32_t MiniRTOS_MutexGetOwner(
    const MiniRTOS_Mutex_t *mutex
)
{
    if (mutex == NULL)
    {
        return 0;
    }

    return mutex->owner_task_id;
}