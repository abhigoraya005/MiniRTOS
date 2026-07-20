#include <stdio.h>

#include "queue.h"


/*
 * Initialize message queue.
 */
int MiniRTOS_MessageQueueInit(
    MiniRTOS_MessageQueue_t *queue
)
{
    uint32_t i;

    if (queue == NULL)
    {
        printf(
            "[QUEUE] Error: NULL queue.\n"
        );

        return -1;
    }


    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;


    /*
     * Clear queue buffer.
     */
    for (
        i = 0;
        i < MINIRTOS_QUEUE_SIZE;
        i++
    )
    {
        queue->buffer[i] = 0;
    }


    printf(
        "[QUEUE] Message queue initialized. Capacity: %u\n",
        MINIRTOS_QUEUE_SIZE
    );


    return 0;
}


/*
 * Send message to queue.
 */
int MiniRTOS_MessageQueueSend(
    MiniRTOS_MessageQueue_t *queue,
    uint32_t message
)
{
    if (queue == NULL)
    {
        return -1;
    }


    /*
     * Check whether queue is full.
     */
    if (
        queue->count >=
        MINIRTOS_QUEUE_SIZE
    )
    {
        printf(
            "[QUEUE] Send failed. Queue is FULL.\n"
        );

        return -1;
    }


    /*
     * Store message at tail.
     */
    queue->buffer[
        queue->tail
    ] = message;


    /*
     * Move tail using circular
     * buffer wrap-around.
     */
    queue->tail =
        (queue->tail + 1) %
        MINIRTOS_QUEUE_SIZE;


    queue->count++;


    printf(
        "[QUEUE] Message sent: %lu | Messages: %lu / %u\n",
        (unsigned long)message,
        (unsigned long)queue->count,
        MINIRTOS_QUEUE_SIZE
    );


    return 0;
}


/*
 * Receive message from queue.
 */
int MiniRTOS_MessageQueueReceive(
    MiniRTOS_MessageQueue_t *queue,
    uint32_t *message
)
{
    if (
        queue == NULL ||
        message == NULL
    )
    {
        return -1;
    }


    /*
     * Check whether queue is empty.
     */
    if (queue->count == 0)
    {
        printf(
            "[QUEUE] Receive failed. Queue is EMPTY.\n"
        );

        return -1;
    }


    /*
     * Read oldest message.
     */
    *message =
        queue->buffer[
            queue->head
        ];


    /*
     * Move head using circular
     * buffer wrap-around.
     */
    queue->head =
        (queue->head + 1) %
        MINIRTOS_QUEUE_SIZE;


    queue->count--;


    printf(
        "[QUEUE] Message received: %lu | Messages: %lu / %u\n",
        (unsigned long)*message,
        (unsigned long)queue->count,
        MINIRTOS_QUEUE_SIZE
    );


    return 0;
}


/*
 * Return queue message count.
 */
uint32_t MiniRTOS_MessageQueueGetCount(
    const MiniRTOS_MessageQueue_t *queue
)
{
    if (queue == NULL)
    {
        return 0;
    }

    return queue->count;
}


/*
 * Check whether queue is empty.
 */
uint8_t MiniRTOS_MessageQueueIsEmpty(
    const MiniRTOS_MessageQueue_t *queue
)
{
    if (queue == NULL)
    {
        return 1;
    }

    return (
        queue->count == 0
    );
}


/*
 * Check whether queue is full.
 */
uint8_t MiniRTOS_MessageQueueIsFull(
    const MiniRTOS_MessageQueue_t *queue
)
{
    if (queue == NULL)
    {
        return 0;
    }

    return (
        queue->count >=
        MINIRTOS_QUEUE_SIZE
    );
}