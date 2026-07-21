#include <stdio.h>
#include <stdint.h>

#include "../IPC/queue.h"


static int tests_passed = 0;
static int tests_failed = 0;


#define TEST_ASSERT(condition, name)          \
    do                                        \
    {                                         \
        if (condition)                        \
        {                                     \
            printf("[PASS] %s\n", name);      \
            tests_passed++;                   \
        }                                     \
        else                                  \
        {                                     \
            printf("[FAIL] %s\n", name);      \
            tests_failed++;                   \
        }                                     \
    } while (0)


int main(void)
{
    MiniRTOS_MessageQueue_t queue;

    uint32_t value;


    printf(
        "\n=================================\n"
        "      MiniRTOS Queue Tests\n"
        "=================================\n"
    );


    /*
     * Initialize queue.
     */
    TEST_ASSERT(
        MiniRTOS_MessageQueueInit(
            &queue
        ) == 0,
        "Queue initialization"
    );


    /*
     * Queue should initially
     * be empty.
     */
    TEST_ASSERT(
        MiniRTOS_MessageQueueIsEmpty(
            &queue
        ),
        "Queue initially empty"
    );


    /*
     * Send value.
     */
    TEST_ASSERT(
        MiniRTOS_MessageQueueSend(
            &queue,
            42
        ) == 0,
        "Send message"
    );


    TEST_ASSERT(
        MiniRTOS_MessageQueueGetCount(
            &queue
        ) == 1,
        "Queue count after send"
    );


    /*
     * Receive value.
     */
    TEST_ASSERT(
        MiniRTOS_MessageQueueReceive(
            &queue,
            &value
        ) == 0,
        "Receive message"
    );


    TEST_ASSERT(
        value == 42,
        "FIFO data integrity"
    );


    TEST_ASSERT(
        MiniRTOS_MessageQueueIsEmpty(
            &queue
        ),
        "Queue empty after receive"
    );


    /*
     * Empty queue test.
     */
    TEST_ASSERT(
        MiniRTOS_MessageQueueReceive(
            &queue,
            &value
        ) != 0,
        "Reject receive from empty queue"
    );


    /*
     * Summary.
     */
    printf(
        "\n=================================\n"
    );


    printf(
        "Tests Passed : %d\n",
        tests_passed
    );


    printf(
        "Tests Failed : %d\n",
        tests_failed
    );


    printf(
        "=================================\n"
    );


    if (tests_failed == 0)
    {
        printf(
            "\n[TEST] All MiniRTOS queue tests passed.\n"
        );

        return 0;
    }


    printf(
        "\n[TEST] MiniRTOS tests failed.\n"
    );


    return 1;
}