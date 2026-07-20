#ifndef MINIRTOS_MESSAGE_QUEUE_H
#define MINIRTOS_MESSAGE_QUEUE_H

#include <stdint.h>

#define MINIRTOS_QUEUE_SIZE 8


/*
 * MiniRTOS Message Queue
 *
 * Fixed-size FIFO queue storing
 * 32-bit unsigned integer messages.
 */
typedef struct
{
    uint32_t buffer[MINIRTOS_QUEUE_SIZE];

    uint32_t head;
    uint32_t tail;
    uint32_t count;

} MiniRTOS_MessageQueue_t;


/*
 * Initialize message queue.
 *
 * Returns:
 *  0  Success
 * -1  Invalid queue pointer
 */
int MiniRTOS_MessageQueueInit(
    MiniRTOS_MessageQueue_t *queue
);


/*
 * Send message to queue.
 *
 * Returns:
 *  0  Message successfully added
 * -1  Queue full or invalid
 */
int MiniRTOS_MessageQueueSend(
    MiniRTOS_MessageQueue_t *queue,
    uint32_t message
);


/*
 * Receive message from queue.
 *
 * Returns:
 *  0  Message successfully received
 * -1  Queue empty or invalid
 */
int MiniRTOS_MessageQueueReceive(
    MiniRTOS_MessageQueue_t *queue,
    uint32_t *message
);


/*
 * Return number of messages
 * currently stored in queue.
 */
uint32_t MiniRTOS_MessageQueueGetCount(
    const MiniRTOS_MessageQueue_t *queue
);


/*
 * Check if queue is empty.
 */
uint8_t MiniRTOS_MessageQueueIsEmpty(
    const MiniRTOS_MessageQueue_t *queue
);


/*
 * Check if queue is full.
 */
uint8_t MiniRTOS_MessageQueueIsFull(
    const MiniRTOS_MessageQueue_t *queue
);

#endif