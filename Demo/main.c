#include <stdio.h>
#include <stdint.h>

#include "../Kernel/minirtos.h"
#include "../Kernel/task.h"
#include "../Kernel/scheduler.h"
#include "../Kernel/systick.h"

#include "../Port/cortex_m_port.h"

#include "../IPC/semaphore.h"
#include "../IPC/mutex.h"
#include "../IPC/queue.h"


/*
 * ============================================================
 * MiniRTOS Day 13
 * Integrated Demo Application
 * ============================================================
 *
 * Data Flow:
 *
 * Sensor Task
 *      |
 *      | Message Queue
 *      v
 * Processing Task
 *      |
 *      | Mutex Protected Result
 *      v
 * Logger Task
 *
 * Semaphore indicates availability
 * of unprocessed sensor messages.
 */


/*
 * IPC Objects
 */
static MiniRTOS_MessageQueue_t sensor_queue;

static MiniRTOS_Mutex_t result_mutex;

static MiniRTOS_Semaphore_t data_ready_semaphore;


/*
 * Shared processed result.
 *
 * Protected by result_mutex.
 */
static uint32_t processed_result = 0;


/*
 * Simulated sensor value.
 */
static uint32_t sensor_value = 20;


/*
 * Statistics.
 */
static uint32_t samples_generated = 0;
static uint32_t samples_processed = 0;
static uint32_t logs_generated = 0;


/*
 * ============================================================
 * Sensor Task
 * ============================================================
 *
 * Generates simulated sensor data.
 * Sends data to the message queue.
 * Signals the data-ready semaphore.
 */
void SensorTask(void)
{
    sensor_value += 5;


    printf(
        "    [SENSOR] Generated sensor value: %lu\n",
        (unsigned long)sensor_value
    );


    /*
     * Send sensor value to queue.
     */
    if (
        MiniRTOS_MessageQueueSend(
            &sensor_queue,
            sensor_value
        ) == 0
    )
    {
        samples_generated++;


        /*
         * Signal that one message
         * is available for processing.
         */
        MiniRTOS_SemaphoreSignal(
            &data_ready_semaphore
        );


        printf(
            "    [SENSOR] Data queued successfully.\n"
        );
    }
    else
    {
        printf(
            "    [SENSOR] Queue full. Sample dropped.\n"
        );
    }
}


/*
 * ============================================================
 * Processing Task
 * ============================================================
 *
 * Checks the semaphore for available data.
 * Receives data from the message queue.
 * Processes it.
 * Stores result using mutex protection.
 */
void ProcessingTask(void)
{
    uint32_t received_value;
    uint32_t new_result;


    printf(
        "    [PROCESSING] Checking for sensor data.\n"
    );


    /*
     * Attempt to consume one
     * data-ready semaphore token.
     */
    if (
        MiniRTOS_SemaphoreWait(
            &data_ready_semaphore
        ) != 0
    )
    {
        printf(
            "    [PROCESSING] No data ready.\n"
        );

        return;
    }


    /*
     * Receive sensor data.
     */
    if (
        MiniRTOS_MessageQueueReceive(
            &sensor_queue,
            &received_value
        ) != 0
    )
    {
        printf(
            "    [PROCESSING] Queue receive failed.\n"
        );

        return;
    }


    /*
     * Simulated processing algorithm.
     */
    new_result =
        received_value * 2;


    printf(
        "    [PROCESSING] Input: %lu\n",
        (unsigned long)received_value
    );


    printf(
        "    [PROCESSING] Result: %lu\n",
        (unsigned long)new_result
    );


    /*
     * Protect shared result
     * using mutex.
     *
     * Processing Task ID = 2.
     */
    if (
        MiniRTOS_MutexLock(
            &result_mutex,
            2
        ) == 0
    )
    {
        processed_result =
            new_result;


        samples_processed++;


        MiniRTOS_MutexUnlock(
            &result_mutex,
            2
        );
    }
    else
    {
        printf(
            "    [PROCESSING] Failed to acquire result mutex.\n"
        );
    }
}


/*
 * ============================================================
 * Logger Task
 * ============================================================
 *
 * Reads processed_result while
 * respecting mutex ownership.
 */
void LoggerTask(void)
{
    printf(
        "    [LOGGER] Requesting access to processed result.\n"
    );


    /*
     * Logger Task ID = 3.
     */
    if (
        MiniRTOS_MutexLock(
            &result_mutex,
            3
        ) == 0
    )
    {
        printf(
            "    [LOGGER] Latest processed result: %lu\n",
            (unsigned long)
                processed_result
        );


        logs_generated++;


        MiniRTOS_MutexUnlock(
            &result_mutex,
            3
        );
    }
    else
    {
        printf(
            "    [LOGGER] Shared result currently unavailable.\n"
        );
    }
}


/*
 * ============================================================
 * Idle Task
 * ============================================================
 */
void IdleTask(void)
{
    printf(
        "    [IDLE] CPU Idle.\n"
    );
}


/*
 * ============================================================
 * Main Application
 * ============================================================
 */
int main(void)
{
    printf(
        "\nStarting MiniRTOS Integrated Demo Application...\n\n"
    );


    /*
     * --------------------------------------------------------
     * Initialize Kernel
     * --------------------------------------------------------
     */

    MiniRTOS_Init();

    MiniRTOS_TaskManagerInit();

    MiniRTOS_SysTickInit();

    MiniRTOS_PortInit();


    /*
     * --------------------------------------------------------
     * Initialize IPC
     * --------------------------------------------------------
     */

    printf(
        "\n[DAY 13] Initializing IPC Modules...\n"
    );


    /*
     * Message Queue
     */
    MiniRTOS_MessageQueueInit(
        &sensor_queue
    );


    /*
     * Mutex
     */
    MiniRTOS_MutexInit(
        &result_mutex
    );


    /*
     * Counting Semaphore
     *
     * Initial Count = 0
     *
     * No sensor data is available
     * when the application starts.
     *
     * Maximum Count = Queue Size
     */
    MiniRTOS_SemaphoreInit(
        &data_ready_semaphore,
        0,
        MINIRTOS_QUEUE_SIZE
    );


    /*
     * --------------------------------------------------------
     * Register Tasks
     * --------------------------------------------------------
     */

    printf(
        "\n[TASK MANAGER] Registering integrated application tasks...\n\n"
    );


    MiniRTOS_CreateTask(
        "Sensor",
        SensorTask,
        3
    );


    MiniRTOS_CreateTask(
        "Processing",
        ProcessingTask,
        2
    );


    MiniRTOS_CreateTask(
        "Logger",
        LoggerTask,
        1
    );


    MiniRTOS_CreateTask(
        "Idle",
        IdleTask,
        0
    );


    MiniRTOS_PrintTaskTable();


    /*
     * --------------------------------------------------------
     * Initialize Scheduler
     * --------------------------------------------------------
     */

    MiniRTOS_SchedulerInit();


    /*
     * Round Robin is used so all
     * application tasks execute.
     */
    MiniRTOS_SchedulerSetPolicy(
        MINIRTOS_SCHEDULER_ROUND_ROBIN
    );


    /*
     * --------------------------------------------------------
     * Start Integrated Simulation
     * --------------------------------------------------------
     */

    printf(
        "\n[DAY 13] Starting Full System Integration Test...\n"
    );


    /*
     * Run 16 scheduler cycles.
     *
     * Four complete application rounds:
     *
     * Sensor
     * Processing
     * Logger
     * Idle
     */
    MiniRTOS_SchedulerRun(
        16
    );


    /*
     * --------------------------------------------------------
     * System Summary
     * --------------------------------------------------------
     */

    printf(
        "\n=================================\n"
    );

    printf(
        "     MiniRTOS System Summary\n"
    );

    printf(
        "=================================\n"
    );


    printf(
        "Final Kernel Tick        : %lu\n",
        (unsigned long)
            MiniRTOS_GetTick()
    );


    printf(
        "Context Switch Events    : %lu\n",
        (unsigned long)
            MiniRTOS_PortGetContextSwitchCount()
    );


    printf(
        "Samples Generated        : %lu\n",
        (unsigned long)
            samples_generated
    );


    printf(
        "Samples Processed        : %lu\n",
        (unsigned long)
            samples_processed
    );


    printf(
        "Logger Executions        : %lu\n",
        (unsigned long)
            logs_generated
    );


    printf(
        "Messages Remaining       : %lu\n",
        (unsigned long)
            MiniRTOS_MessageQueueGetCount(
                &sensor_queue
            )
    );


    printf(
        "Semaphore Count          : %lu\n",
        (unsigned long)
            MiniRTOS_SemaphoreGetCount(
                &data_ready_semaphore
            )
    );


    printf(
        "Mutex State              : %s\n",
        MiniRTOS_MutexIsLocked(
            &result_mutex
        )
            ? "LOCKED"
            : "UNLOCKED"
    );


    printf(
        "Final Processed Result   : %lu\n",
        (unsigned long)
            processed_result
    );


    printf(
        "=================================\n"
    );


    printf(
        "\n[SYSTEM] MiniRTOS Day 13 Full Integration demo completed.\n"
    );


    return 0;
}