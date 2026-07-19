#include <stdio.h>

#include "semaphore.h"


/*
 * Initialize semaphore.
 */
int MiniRTOS_SemaphoreInit(
    MiniRTOS_Semaphore_t *semaphore,
    uint32_t initial_count,
    uint32_t max_count
)
{
    if (semaphore == NULL)
    {
        printf(
            "[SEMAPHORE] Error: NULL semaphore.\n"
        );

        return -1;
    }

    if (
        max_count == 0 ||
        initial_count > max_count
    )
    {
        printf(
            "[SEMAPHORE] Error: Invalid semaphore configuration.\n"
        );

        return -1;
    }

    semaphore->count =
        initial_count;

    semaphore->max_count =
        max_count;

    printf(
        "[SEMAPHORE] Initialized. Count: %lu / %lu\n",
        (unsigned long)semaphore->count,
        (unsigned long)semaphore->max_count
    );

    return 0;
}


/*
 * Attempt to acquire semaphore.
 */
int MiniRTOS_SemaphoreWait(
    MiniRTOS_Semaphore_t *semaphore
)
{
    if (semaphore == NULL)
    {
        return -1;
    }

    if (semaphore->count == 0)
    {
        printf(
            "[SEMAPHORE] Resource unavailable. Wait failed.\n"
        );

        return -1;
    }

    semaphore->count--;

    printf(
        "[SEMAPHORE] Acquired. Count: %lu / %lu\n",
        (unsigned long)semaphore->count,
        (unsigned long)semaphore->max_count
    );

    return 0;
}


/*
 * Release semaphore.
 */
int MiniRTOS_SemaphoreSignal(
    MiniRTOS_Semaphore_t *semaphore
)
{
    if (semaphore == NULL)
    {
        return -1;
    }

    if (
        semaphore->count >=
        semaphore->max_count
    )
    {
        printf(
            "[SEMAPHORE] Cannot signal. Semaphore already at maximum.\n"
        );

        return -1;
    }

    semaphore->count++;

    printf(
        "[SEMAPHORE] Released. Count: %lu / %lu\n",
        (unsigned long)semaphore->count,
        (unsigned long)semaphore->max_count
    );

    return 0;
}


/*
 * Return current semaphore count.
 */
uint32_t MiniRTOS_SemaphoreGetCount(
    const MiniRTOS_Semaphore_t *semaphore
)
{
    if (semaphore == NULL)
    {
        return 0;
    }

    return semaphore->count;
}