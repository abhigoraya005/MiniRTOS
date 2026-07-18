<div align="center">

# ⚙️ MiniRTOS

### A Lightweight RTOS Kernel & Task Scheduling Simulator Written in C

![Language](https://img.shields.io/badge/Language-C-blue)
![Compiler](https://img.shields.io/badge/Compiler-GCC-orange)
![Platform](https://img.shields.io/badge/Platform-Host%20Simulation-lightgrey)
![Architecture](https://img.shields.io/badge/Target-Cortex--M-green)
![Status](https://img.shields.io/badge/Status-In%20Development-orange)
![Progress](https://img.shields.io/badge/Progress-Day%208%20of%2014-blue)

**MiniRTOS** is a lightweight Real-Time Operating System kernel and task scheduling simulator being developed from scratch in C to explore the internal concepts behind embedded RTOS architectures.

The project is being developed through a structured **14-day development roadmap**.

The current GitHub version has completed **Day 8**, covering kernel initialization, Task Control Blocks, dynamic task registration, Round-Robin scheduling, simulated System Tick management, task state management, tick-based task delays, automatic task wake-up, and priority-based scheduling.

</div>

---

# 📌 Project Overview

Real-Time Operating Systems are fundamental to modern embedded systems, automotive ECUs, IoT devices, robotics, industrial controllers, and real-time applications.

MiniRTOS is being developed as a learning-oriented systems project to understand how fundamental RTOS mechanisms operate internally.

Instead of relying directly on an existing RTOS such as FreeRTOS, this project explores the implementation of core RTOS concepts from scratch using the C programming language.

The project currently demonstrates:

- MiniRTOS kernel initialization
- Task Control Blocks (TCBs)
- Task creation
- Dynamic task registration
- Task identification
- Task priorities
- Task state representation
- Task table visualization
- Cooperative Round-Robin scheduling
- Priority-based scheduling
- Runtime scheduler policy selection
- READY task selection
- Automatic skipping of unavailable tasks
- Simulated System Tick
- Kernel tick counter
- Task blocking and unblocking
- Task suspension and resumption
- Tick-based task delays
- Automatic delayed-task wake-up
- Scheduler interaction with task states
- Priority-aware task selection

The current implementation runs as a **host-side simulation using GCC** while maintaining a modular architecture designed around embedded RTOS concepts.

---

# 🏗️ Current System Architecture

```text
                         MiniRTOS
                            │
                            ▼
                         Kernel
                            │
          ┌─────────────────┼─────────────────┐
          │                 │                 │
          ▼                 ▼                 ▼
    Task Manager        Scheduler         System Tick
          │                 │                 │
          │                 │                 ├── Tick Counter
          │                 │                 ├── Tick Increment
          │                 │                 └── Kernel Time Base
          │                 │
          │                 ├── Round Robin
          │                 ├── Priority Scheduling
          │                 ├── Scheduler Policy
          │                 ├── READY Task Selection
          │                 └── State-Aware Selection
          │
          ├── Task Creation
          ├── Task Registration
          ├── Task Control Blocks
          ├── Task States
          ├── Block / Unblock
          ├── Suspend / Resume
          ├── Tick-Based Delay
          └── Automatic Wake-Up
                            │
                            ▼
                     Demo Application
                            │
          ┌─────────────────┼─────────────────┐
          │                 │                 │
          ▼                 ▼                 ▼
       Sensor          Processing          Logger
         Task              Task             Task
                                              │
                                              ▼
                                          Idle Task
```

As development progresses, the architecture will be extended with:

```text
Context Manager
      │
      ▼
Cortex-M Port Layer
      │
      ▼
IPC
├── Semaphore
├── Mutex
└── Message Queue
      │
      ▼
Full System Integration
      │
      ▼
Unit Testing
```

---

# ✨ Current Features

## ⚙️ Kernel Initialization

The MiniRTOS kernel provides a centralized initialization mechanism for starting the simulated operating system environment.

Example output:

```text
=================================
       MiniRTOS Kernel v0.1
=================================
[KERNEL] Initializing MiniRTOS...
[KERNEL] Kernel initialized successfully.
```

The kernel initialization layer serves as the foundation for additional RTOS components.

---

# 🧠 Task Control Block

MiniRTOS implements a Task Control Block structure for representing individual tasks.

Each task contains information required by the kernel and scheduler, including:

```text
Task ID
Task Name
Priority
Task State
Task Function
Stack Pointer
Timing Information
```

The TCB architecture provides the foundation for task management, scheduling, and delayed task execution.

---

# 📝 Dynamic Task Registration

MiniRTOS supports dynamic registration of application tasks with the Task Manager.

Example tasks:

```text
Sensor
Processing
Logger
Idle
```

Each task is registered with:

```text
Task Name
Task Function
Priority
```

Example:

```c
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
```

The Task Manager automatically assigns each task a unique Task ID.

---

# 📋 Task Table

MiniRTOS can display information about all registered tasks.

Example:

```text
=================================
       MiniRTOS Task Table
=================================
---------------------------------
Task ID       : 1
Task Name     : Sensor
Priority      : 3
State         : READY
Stack Pointer : 0000000000000000
---------------------------------
Task ID       : 2
Task Name     : Processing
Priority      : 2
State         : READY
Stack Pointer : 0000000000000000
---------------------------------
Task ID       : 3
Task Name     : Logger
Priority      : 1
State         : READY
Stack Pointer : 0000000000000000
---------------------------------
Task ID       : 4
Task Name     : Idle
Priority      : 0
State         : READY
Stack Pointer : 0000000000000000
---------------------------------
Total Tasks: 4 / 8
=================================
```

The task table provides visibility into the current state of the MiniRTOS task system.

---

# 🔁 Round-Robin Scheduler

MiniRTOS implements a cooperative **Round-Robin scheduling policy**.

When all tasks are READY, tasks are selected sequentially:

```text
Sensor
   │
   ▼
Processing
   │
   ▼
Logger
   │
   ▼
Idle
   │
   ▼
Sensor
```

After reaching the final task, the scheduler returns to the first eligible task.

The scheduler only selects tasks that are currently in the `READY` state.

Tasks that are `BLOCKED` or `SUSPENDED` are automatically skipped.

---

# 🎯 Priority-Based Scheduler

Day 8 introduces a **Priority-Based Scheduling policy**.

MiniRTOS can now select the highest-priority task from the set of READY tasks.

Example task priorities:

```text
Sensor       Priority 3
Processing   Priority 2
Logger       Priority 1
Idle         Priority 0
```

When Priority-Based Scheduling is enabled:

```text
READY Tasks
     │
     ▼
Find Highest Priority
     │
     ▼
Sensor - Priority 3
     │
     ▼
Execute Sensor Task
```

In the current cooperative simulation, if the highest-priority task remains READY after execution, it can be selected again during the next scheduling cycle.

Example output:

```text
[DAY 8 TEST] Enabling Priority-Based Scheduler...
[SCHEDULER] Policy changed to PRIORITY.

[SCHEDULER] Cycle 1
[TICK] 1
[SCHEDULER] Running Task 1: Sensor (Priority 3)

[SCHEDULER] Cycle 2
[TICK] 2
[SCHEDULER] Running Task 1: Sensor (Priority 3)

[SCHEDULER] Cycle 3
[TICK] 3
[SCHEDULER] Running Task 1: Sensor (Priority 3)

[SCHEDULER] Cycle 4
[TICK] 4
[SCHEDULER] Running Task 1: Sensor (Priority 3)
```

This demonstrates strict priority selection among READY tasks.

---

# 🔀 Scheduler Policies

MiniRTOS currently supports two scheduling policies:

```text
MINIRTOS_SCHEDULER_ROUND_ROBIN
MINIRTOS_SCHEDULER_PRIORITY
```

The scheduling policy can be selected through the scheduler interface.

Example:

```c
MiniRTOS_SchedulerSetPolicy(
    MINIRTOS_SCHEDULER_PRIORITY
);
```

Conceptually:

```text
                 Scheduler
                     │
                     ▼
              Check Policy
                     │
          ┌──────────┴──────────┐
          │                     │
          ▼                     ▼
     ROUND ROBIN             PRIORITY
          │                     │
          ▼                     ▼
 Select Next READY      Find Highest Priority
       Task                  READY Task
          │                     │
          └──────────┬──────────┘
                     │
                     ▼
                 Run Task
```

This architecture allows MiniRTOS to support multiple scheduling strategies through a common scheduler interface.

---

# ⏱️ System Tick

Day 5 introduced a simulated **System Tick** that provides a basic time reference for the MiniRTOS kernel.

The System Tick module is initialized during system startup:

```text
[SYSTICK] System tick initialized.
```

During scheduler execution, the tick counter advances with each scheduling cycle.

Example:

```text
[SCHEDULER] Cycle 1
[TICK] 1

[SCHEDULER] Cycle 2
[TICK] 2

[SCHEDULER] Cycle 3
[TICK] 3
```

Conceptually:

```text
Scheduler Cycle
      │
      ▼
Increment System Tick
      │
      ▼
Update Delayed Tasks
      │
      ▼
Select READY Task
      │
      ▼
Execute Task
```

The System Tick now provides the time base used by the delayed-task mechanism.

At the current development stage, the System Tick is **simulated on the host system** and is not generated by a hardware SysTick interrupt.

---

# 🚦 Task State Management

Day 6 introduced explicit **Task State Management** to MiniRTOS.

Each task can exist in one of several states:

```text
READY
RUNNING
BLOCKED
SUSPENDED
```

These states allow the kernel and scheduler to control whether a task is eligible for execution.

---

## 🟢 READY

A task in the `READY` state is available for execution by the scheduler.

```text
Task State: READY
      │
      ▼
Eligible for Scheduling
```

---

## 🔵 RUNNING

A task selected by the scheduler is temporarily moved to the `RUNNING` state while its task function executes.

```text
READY
  │
  ▼
RUNNING
  │
  ▼
Task Function Executes
  │
  ▼
READY
```

Because the current implementation is a cooperative host simulation, the task returns to `READY` after its function completes.

---

## 🟠 BLOCKED

A task in the `BLOCKED` state is temporarily unavailable for scheduling.

Example:

```text
Task ID       : 2
Task Name     : Processing
Priority      : 2
State         : BLOCKED
```

Blocked tasks are skipped by the scheduler.

A task may be manually blocked or temporarily blocked as part of the tick-based delay mechanism.

---

## 🔴 SUSPENDED

A task can also be placed into the `SUSPENDED` state.

Example:

```text
Task ID       : 3
Task Name     : Logger
Priority      : 1
State         : SUSPENDED
```

Suspended tasks are not selected by the scheduler until explicitly resumed.

---

# 🔄 Task State Operations

MiniRTOS supports task management operations for controlling task execution.

Supported operations include:

```text
Block Task
Unblock Task
Suspend Task
Resume Task
Delay Task
Automatic Wake-Up
```

Example:

```c
MiniRTOS_BlockTask(2);

MiniRTOS_SuspendTask(3);
```

This changes the task states:

```text
Processing  → BLOCKED
Logger      → SUSPENDED
```

The scheduler automatically skips these tasks until they become READY again.

---

# ⏳ Tick-Based Task Delays

Day 7 introduces **Tick-Based Task Delays**.

A task can be temporarily blocked for a specified number of kernel ticks.

Conceptually:

```text
Task READY
    │
    ▼
Delay Requested
    │
    ▼
Calculate Wake Tick
    │
    ▼
Task BLOCKED
    │
    ▼
Kernel Tick Advances
    │
    ▼
Wake Tick Reached?
    │
    ├── NO ──► Remain BLOCKED
    │
    └── YES
         │
         ▼
      Task READY
```

This provides the foundation for RTOS-style timing and periodic task execution.

---

# ⏰ Automatic Task Wake-Up

The scheduler checks delayed tasks as the System Tick advances.

For example, if the Processing task is delayed until Tick 4:

```text
[TASK MANAGER] Task 2 (Processing) delayed until Tick 4.
```

Its state becomes:

```text
Task ID       : 2
Task Name     : Processing
State         : BLOCKED
```

During scheduling:

```text
Tick 1 → Processing BLOCKED
Tick 2 → Processing BLOCKED
Tick 3 → Processing BLOCKED
Tick 4 → Processing wakes up
```

Example output:

```text
[SCHEDULER] Cycle 4
[TICK] 4
[TASK MANAGER] Task 2 (Processing) woke up at Tick 4.
```

The task is then returned to the `READY` state and becomes eligible for scheduling.

Conceptually:

```text
Processing
    │
    ▼
BLOCKED Until Tick 4
    │
    ▼
Tick 1
    │
    ▼
Tick 2
    │
    ▼
Tick 3
    │
    ▼
Tick 4
    │
    ▼
Automatic Wake-Up
    │
    ▼
READY
    │
    ▼
Scheduler Can Execute Task
```

---

# 🧪 Day 7 Delay Test

The Day 7 demo delays the Processing task until Tick 4.

Initial state:

```text
Sensor       READY
Processing   BLOCKED
Logger       READY
Idle         READY
```

The first scheduler cycles execute:

```text
Tick 1 → Sensor
Tick 2 → Logger
Tick 3 → Idle
```

At Tick 4:

```text
[TASK MANAGER] Task 2 (Processing) woke up at Tick 4.
```

Processing returns to READY and is subsequently selected by the scheduler.

This demonstrates integration between:

```text
System Tick
    +
Task Manager
    +
Task States
    +
Scheduler
```

---

# 🧪 Day 8 Priority Scheduler Test

Day 8 tests the new Priority-Based Scheduling policy.

The registered tasks have priorities:

```text
Sensor       3
Processing   2
Logger       1
Idle         0
```

The scheduler is switched to priority mode:

```c
MiniRTOS_SchedulerSetPolicy(
    MINIRTOS_SCHEDULER_PRIORITY
);
```

The highest-priority READY task is Sensor.

The scheduler therefore executes:

```text
Cycle 1 → Sensor
Cycle 2 → Sensor
Cycle 3 → Sensor
Cycle 4 → Sensor
```

This demonstrates that the scheduler correctly identifies and executes the highest-priority READY task.

---

# 🧪 Current Demo Application

The MiniRTOS demo application contains four simulated tasks.

## Sensor Task

```text
[TASK] Reading simulated sensor data.
```

Priority:

```text
3
```

---

## Processing Task

```text
[TASK] Processing simulated data.
```

Priority:

```text
2
```

---

## Logger Task

```text
[TASK] Logging system information.
```

Priority:

```text
1
```

---

## Idle Task

```text
[TASK] CPU Idle.
```

Priority:

```text
0
```

---

# 🔄 Current System Flow

```text
                 MiniRTOS Kernel
                       │
                       ▼
                 Task Manager
                       │
                       ▼
                Register Tasks
                       │
                       ▼
                 System Tick
                       │
                       ▼
             Update Delayed Tasks
                       │
                       ▼
              Automatic Wake-Up
                       │
                       ▼
                  Scheduler
                       │
                       ▼
              Check Scheduler Policy
                       │
             ┌─────────┴─────────┐
             │                   │
             ▼                   ▼
        Round Robin           Priority
             │                   │
             ▼                   ▼
       Next READY Task    Highest-Priority
                              READY Task
             │                   │
             └─────────┬─────────┘
                       │
                       ▼
                  Task RUNNING
                       │
                       ▼
               Execute Function
                       │
                       ▼
                   Task READY
```

---

# 📂 Current Project Structure

The public GitHub repository currently contains the components developed through Day 8.

```text
MiniRTOS
│
├── Kernel
│   ├── minirtos.c
│   ├── minirtos.h
│   ├── task.c
│   ├── task.h
│   ├── scheduler.c
│   ├── scheduler.h
│   ├── systick.c
│   └── systick.h
│
├── Demo
│   └── main.c
│
├── DAY7.md
├── DAY8.md
├── .gitignore
└── README.md
```

The planned final architecture will additionally include:

```text
MiniRTOS
│
├── IPC
│   ├── semaphore.c
│   ├── semaphore.h
│   ├── mutex.c
│   ├── mutex.h
│   ├── queue.c
│   └── queue.h
│
├── Port
│   ├── cortex_m_port.c
│   └── cortex_m_port.h
│
├── Tests
│   └── test_queue.c
│
├── Docs
│
└── Makefile
```

---

# 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C | Kernel and RTOS development |
| GCC | Compilation |
| MSYS2 | GCC toolchain environment |
| PowerShell | Build and execution |
| Visual Studio Code | Development environment |
| Git | Version control |
| GitHub | Source code hosting |

---

# ⚙️ Build Instructions

## Prerequisites

GCC is required to compile the MiniRTOS host simulation.

Verify GCC installation:

```bash
gcc --version
```

---

## Compile Current MiniRTOS Version

From the project root directory:

```bash
gcc -Wall -Wextra Demo/main.c Kernel/minirtos.c Kernel/task.c Kernel/scheduler.c Kernel/systick.c -o MiniRTOS.exe
```

Run on Windows PowerShell:

```powershell
.\MiniRTOS.exe
```

---

# 🗓️ 14-Day Development Roadmap

| Day | Development Milestone | Status |
|---|---|---|
| Day 1 | Project architecture and kernel initialization | ✅ Completed |
| Day 2 | Task Control Block foundation | ✅ Completed |
| Day 3 | Dynamic task registration and task table | ✅ Completed |
| Day 4 | Round-Robin scheduler | ✅ Completed |
| Day 5 | System Tick integration | ✅ Completed |
| Day 6 | Task state management | ✅ Completed |
| Day 7 | Tick-based task delays and automatic wake-up | ✅ Completed |
| Day 8 | Priority-based scheduling | ✅ Completed |
| Day 9 | Context management simulation | ⏳ Upcoming |
| Day 10 | Semaphore implementation | ⏳ Upcoming |
| Day 11 | Mutex implementation | ⏳ Upcoming |
| Day 12 | FIFO message queue | ⏳ Upcoming |
| Day 13 | Full kernel and IPC integration | ⏳ Upcoming |
| Day 14 | Unit testing, build setup and documentation | ⏳ Upcoming |

> **Current Progress: Day 8 of 14 — Priority-Based Scheduling implemented.**

---

# 📊 Current Project Status

```text
Kernel Initialization        ██████████ 100%  ✅
Task Control Blocks          ██████████ 100%  ✅
Task Registration            ██████████ 100%  ✅
Task Table                   ██████████ 100%  ✅
Round-Robin Scheduling       ██████████ 100%  ✅
System Tick                  ██████████ 100%  ✅
Task State Management        ██████████ 100%  ✅
Task Delays                  ██████████ 100%  ✅
Automatic Task Wake-Up       ██████████ 100%  ✅
Priority Scheduling          ██████████ 100%  ✅
Context Simulation           ░░░░░░░░░░   0%  ⏳
Semaphore                    ░░░░░░░░░░   0%  ⏳
Mutex                        ░░░░░░░░░░   0%  ⏳
Message Queue                ░░░░░░░░░░   0%  ⏳
Integration Demo             ░░░░░░░░░░   0%  ⏳
Unit Testing                 ░░░░░░░░░░   0%  ⏳
```

**Development Roadmap: 8 / 14 Days Completed**

---

# 🚀 Planned Features

The following features are planned for upcoming development stages:

- Context management simulation
- Cortex-M-oriented port layer
- Semaphore synchronization
- Mutex-based shared resource protection
- FIFO message queues
- Inter-task communication
- Full kernel and IPC integration
- Unit testing
- Build automation

---

# ⚠️ Current Limitations

MiniRTOS is currently an educational **host-side RTOS kernel simulation**.

At the current Day 8 development stage, it does not yet implement:

- Hardware-based context switching
- ARM Cortex-M register save/restore
- PendSV-based context switching
- Hardware SysTick interrupts
- Preemptive multitasking
- Per-task hardware stacks
- Semaphore synchronization
- Mutex synchronization
- Message queues
- Hardware interrupt handling
- Priority inheritance
- Dynamic memory management

The current scheduler, System Tick, task delays, and priority scheduling are host-side simulations intended to demonstrate fundamental RTOS concepts.

The current strict priority scheduler will repeatedly select the highest-priority READY task. Therefore, lower-priority tasks may experience starvation if a higher-priority task remains continuously READY. Future improvements could introduce task blocking, delays, time slicing, or priority aging to address this behavior.

---

# 🚀 Future Embedded Port

After completing the host-side implementation, MiniRTOS could be extended to run on an ARM Cortex-M microcontroller.

A potential target is:

```text
STM32F103C8T6
ARM Cortex-M3
```

A future hardware port could implement:

```text
Hardware SysTick
      │
      ▼
Scheduler Trigger
      │
      ▼
PendSV Exception
      │
      ▼
Save Current Context
      │
      ▼
Select Next Task
      │
      ▼
Restore Next Context
```

This would transform the current educational scheduler simulation into a more hardware-oriented RTOS implementation.

---

# 🎯 Learning Outcomes

Through the first eight development stages, the following concepts have been explored:

- RTOS kernel architecture
- Modular C project organization
- Task Control Blocks
- Task representation
- Dynamic task registration
- Task function pointers
- Task priorities
- Task state representation
- READY state
- RUNNING state
- BLOCKED state
- SUSPENDED state
- Task blocking and unblocking
- Task suspension and resumption
- Cooperative scheduling
- Round-Robin scheduling
- Priority-based scheduling
- Scheduler policy selection
- Highest-priority task selection
- Scheduler task selection
- State-aware task scheduling
- System Tick architecture
- Kernel tick management
- Simulated kernel time base
- Tick-based task delays
- Wake tick management
- Automatic delayed-task wake-up
- Embedded software abstraction
- GCC-based C development

Future development will expand these concepts into context management, synchronization, inter-task communication, full system integration, and testing.

---

# 📌 Technical Note

MiniRTOS is designed as an educational implementation for understanding RTOS internals.

The current version is a **host-side simulation compiled using GCC**. It demonstrates the logical architecture of task management, multiple scheduling policies, kernel timing, delayed tasks, automatic wake-up, and task state transitions.

It does not currently perform hardware-level context switching on an ARM Cortex-M processor.

The System Tick implementation is simulated in software and advances during scheduler execution rather than being generated by a physical hardware timer interrupt.

Task state transitions and delayed-task wake-ups are managed by the MiniRTOS Task Manager. The scheduler checks task states and only selects eligible `READY` tasks.

The scheduler currently supports both **Round-Robin** and **Priority-Based** scheduling policies.

Future development stages will introduce context management and IPC mechanisms while maintaining a modular architecture suitable for exploring a potential Cortex-M port.

---

# 👨‍💻 Author

**Abhiney Kumar**

Electronics and Communication Engineering  
Dr. B.R. Ambedkar National Institute of Technology, Jalandhar

### Areas of Interest

- Embedded Systems
- Embedded Firmware
- Real-Time Operating Systems
- Microcontrollers
- VLSI
- Semiconductor Systems

---

# ⭐ Project Motivation

MiniRTOS was started to move beyond simply using existing RTOS APIs and instead explore how fundamental operating-system mechanisms can be designed from the ground up.

The project follows a structured 14-day development roadmap, progressively introducing task management, scheduling, timing, synchronization, inter-task communication, and RTOS architecture concepts.

---

<div align="center">

### ⚙️ MiniRTOS

**Building RTOS concepts from scratch in C — one subsystem at a time.**

### Current Progress: Day 8 / 14 ✅

</div>