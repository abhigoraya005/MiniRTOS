<div align="center">

# ⚙️ MiniRTOS

### A Lightweight RTOS Kernel & Task Scheduling Simulator Written in C

![Language](https://img.shields.io/badge/Language-C-blue)
![Compiler](https://img.shields.io/badge/Compiler-GCC-orange)
![Platform](https://img.shields.io/badge/Platform-Host%20Simulation-lightgrey)
![Architecture](https://img.shields.io/badge/Target-Cortex--M-green)
![Status](https://img.shields.io/badge/Status-In%20Development-orange)
![Progress](https://img.shields.io/badge/Progress-Day%2010%20of%2014-blue)

**MiniRTOS** is a lightweight Real-Time Operating System kernel and task scheduling simulator being developed from scratch in C to explore the internal concepts behind embedded RTOS architectures.

The project is being developed through a structured **14-day development roadmap**.

The current GitHub version has completed **Day 10**, covering kernel initialization, Task Control Blocks, dynamic task registration, Round-Robin scheduling, simulated System Tick management, task state management, tick-based task delays, automatic task wake-up, priority-based scheduling, simulated context management, a Cortex-M-oriented port abstraction, and semaphore-based synchronization.

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
- Simulated context switching
- Context save and restore visualization
- Context switch event tracking
- Cortex-M-oriented port abstraction
- Semaphore initialization
- Semaphore acquire and release operations
- Counting semaphore support
- Shared-resource synchronization simulation

The current implementation runs as a **host-side simulation using GCC** while maintaining a modular architecture designed around embedded RTOS concepts.

---

# 🏗️ Current System Architecture

```text
                         MiniRTOS
                            │
          ┌─────────────────┼─────────────────┐
          │                 │                 │
          ▼                 ▼                 ▼
        Kernel             Port              IPC
          │                 │                 │
          │                 ▼                 ▼
          │          Context Manager      Semaphore
          │                 │
          │                 ▼
          │          Cortex-M Port
          │
    ┌─────┼─────────────┐
    │     │             │
    ▼     ▼             ▼
  Task  Scheduler    System Tick
Manager
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
    ┌─────┼───────────┐
    │     │           │
    ▼     ▼           ▼
 Sensor Processing  Logger
                       │
                       ▼
                     Idle
```

As development progresses, the IPC architecture will be extended with:

```text
IPC
 │
 ├── Semaphore       ✅
 │
 ├── Mutex           ⏳
 │
 └── Message Queue   ⏳
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

The TCB architecture provides the foundation for task management, scheduling, delayed task execution, and future hardware-level context management.

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

Day 8 introduced a **Priority-Based Scheduling policy**.

MiniRTOS can select the highest-priority task from the set of READY tasks.

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

Example:

```text
[DAY 8 TEST] Enabling Priority-Based Scheduler...
[SCHEDULER] Policy changed to PRIORITY.

[SCHEDULER] Cycle 1
[TICK] 1
[SCHEDULER] Running Task 1: Sensor (Priority 3)

[SCHEDULER] Cycle 2
[TICK] 2
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
Context Transition
      │
      ▼
Execute Task
```

The System Tick provides the time base used by the delayed-task mechanism.

At the current development stage, the System Tick is **simulated on the host system** and is not generated by a hardware SysTick interrupt.

---

# 🚦 Task State Management

Day 6 introduced explicit **Task State Management**.

Each task can exist in one of several states:

```text
READY
RUNNING
BLOCKED
SUSPENDED
```

These states allow the kernel and scheduler to control whether a task is eligible for execution.

## 🟢 READY

A task in the `READY` state is available for execution.

```text
Task State: READY
      │
      ▼
Eligible for Scheduling
```

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

## 🟠 BLOCKED

A task in the `BLOCKED` state is temporarily unavailable for scheduling.

Blocked tasks are skipped by the scheduler.

A task may be manually blocked or temporarily blocked as part of the tick-based delay mechanism.

## 🔴 SUSPENDED

A task can also be placed into the `SUSPENDED` state.

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

The scheduler automatically skips unavailable tasks until they become READY again.

---

# ⏳ Tick-Based Task Delays

Day 7 introduced **Tick-Based Task Delays**.

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

For example:

```text
[TASK MANAGER] Task 2 (Processing) delayed until Tick 4.
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

The task is returned to the `READY` state and becomes eligible for scheduling.

---

# 🔄 Context Management Simulation

Day 9 introduced a simulated **Context Management layer**.

The context manager represents the logical process that occurs when an RTOS switches execution from one task to another.

In a real ARM Cortex-M RTOS, context switching involves saving and restoring processor registers and task stack pointers.

Since MiniRTOS currently runs as a host-side GCC simulation, these operations are modeled logically.

Example:

```text
[CONTEXT] ---- Context Switch ----
[CONTEXT] Saving context of Task 1: Sensor
[CONTEXT] Restoring context of Task 2: Processing
[CONTEXT] Total Context Switches: 2
```

For the first scheduled task:

```text
[CONTEXT] ---- Context Switch ----
[CONTEXT] No previous task context.
[CONTEXT] Restoring context of Task 1: Sensor
[CONTEXT] Total Context Switches: 1
```

Conceptually:

```text
Current Task
     │
     ▼
Save Current Context
     │
     ▼
Scheduler Selects Next Task
     │
     ▼
Restore Next Context
     │
     ▼
Execute Next Task
```

The Cortex-M port abstraction provides a foundation for a future hardware-specific implementation.

---

# 🔢 Context Switch Tracking

MiniRTOS tracks simulated context switch events.

Example:

```text
[CONTEXT] Total Context Switches: 8
```

The final application output can report:

```text
[SYSTEM] Total Simulated Context Switches: 8
```

This provides visibility into scheduler-driven task transitions.

The current implementation simulates the logical context transition process rather than saving and restoring actual ARM Cortex-M CPU registers.

---

# 🧩 Cortex-M Port Abstraction

Day 9 also introduces a dedicated **Port layer**.

The port layer separates architecture-dependent functionality from the main MiniRTOS kernel.

Current structure:

```text
Port
├── cortex_m_port.c
└── cortex_m_port.h
```

The current port implementation provides a host-side simulation of context management.

Conceptually:

```text
MiniRTOS Scheduler
       │
       ▼
Cortex-M Port Interface
       │
       ▼
Context Transition Simulation
       │
       ▼
Save Previous Task
       │
       ▼
Restore Next Task
```

In a future hardware port, this abstraction could be extended with:

```text
ARM Cortex-M Register Management
Hardware Task Stacks
SysTick Interrupt
PendSV Exception
PSP / MSP Management
Hardware Context Switching
```

---

# 🚦 Semaphore Synchronization

Day 10 introduces **Semaphore Synchronization**.

The semaphore module provides a synchronization primitive for controlling access to shared resources and coordinating task execution.

A semaphore maintains:

```text
Current Count
Maximum Count
```

Example initialization:

```text
[SEMAPHORE] Initialized. Count: 1 / 1
```

A task can acquire the semaphore:

```text
[SEMAPHORE] Acquired. Count: 0 / 1
```

After accessing the protected resource, the task releases it:

```text
[SEMAPHORE] Released. Count: 1 / 1
```

Conceptually:

```text
Task Requests Resource
        │
        ▼
 Check Semaphore
        │
   ┌────┴────┐
   │         │
Count > 0  Count = 0
   │         │
   ▼         ▼
Acquire    Acquire Fails
   │
   ▼
Use Shared Resource
   │
   ▼
Release Semaphore
   │
   ▼
Count Incremented
```

The current implementation demonstrates semaphore behavior in the cooperative host simulation.

---

# 🧪 Day 10 Semaphore Test

The Day 10 demonstration uses a semaphore to synchronize access to a simulated shared resource.

The Sensor task requests the resource:

```text
[TASK] Sensor requesting shared resource.
[SEMAPHORE] Acquired. Count: 0 / 1
[TASK] Sensor acquired shared resource.
[TASK] Sensor reading simulated data.
[SEMAPHORE] Released. Count: 1 / 1
```

The Processing task also accesses the shared resource:

```text
[TASK] Processing requesting shared resource.
[SEMAPHORE] Acquired. Count: 0 / 1
[TASK] Processing acquired shared resource.
[TASK] Processing simulated data.
[SEMAPHORE] Released. Count: 1 / 1
```

The synchronization lifecycle is:

```text
Resource Available
       │
       ▼
Semaphore Acquire
       │
       ▼
Semaphore Count = 0
       │
       ▼
Critical Section
       │
       ▼
Semaphore Release
       │
       ▼
Semaphore Count = 1
       │
       ▼
Resource Available
```

At the end of the test:

```text
[SYSTEM] Final Semaphore Count: 1
[SYSTEM] Final Kernel Tick: 8
[SYSTEM] Total Simulated Context Switches: 8
```

The final semaphore count confirms that the shared resource was correctly released after execution.

---

# 🧪 Current Demo Application

The MiniRTOS demo application contains four simulated tasks.

## Sensor Task

```text
[TASK] Sensor requesting shared resource.
[TASK] Sensor acquired shared resource.
[TASK] Sensor reading simulated data.
```

Priority:

```text
3
```

## Processing Task

```text
[TASK] Processing requesting shared resource.
[TASK] Processing acquired shared resource.
[TASK] Processing simulated data.
```

Priority:

```text
2
```

## Logger Task

```text
[TASK] Logging system information.
```

Priority:

```text
1
```

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
               Context Manager
                       │
                       ▼
               Save / Restore
                       │
                       ▼
                  Task RUNNING
                       │
                       ▼
             Semaphore Acquire
                       │
                       ▼
               Shared Resource
                       │
                       ▼
             Semaphore Release
                       │
                       ▼
                   Task READY
```

---

# 📂 Current Project Structure

The public GitHub repository currently contains the components developed through **Day 10**.

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
├── Port
│   ├── cortex_m_port.c
│   └── cortex_m_port.h
│
├── IPC
│   ├── semaphore.c
│   └── semaphore.h
│
├── Demo
│   └── main.c
│
├── .gitignore
└── README.md
```

The planned final architecture will additionally include:

```text
MiniRTOS
│
├── IPC
│   ├── mutex.c
│   ├── mutex.h
│   ├── queue.c
│   └── queue.h
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
| GCC | Host-side compilation |
| MSYS2 | GCC toolchain environment |
| PowerShell | Build and execution |
| Visual Studio Code | Development environment |
| Git | Version control |
| GitHub | Source code hosting |
| ARM Cortex-M Concepts | Target architecture abstraction |

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
gcc -Wall -Wextra Demo/main.c Kernel/minirtos.c Kernel/task.c Kernel/scheduler.c Kernel/systick.c Port/cortex_m_port.c IPC/semaphore.c -o MiniRTOS.exe
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
| Day 9 | Context management simulation and Cortex-M port abstraction | ✅ Completed |
| Day 10 | Semaphore implementation and synchronization | ✅ Completed |
| Day 11 | Mutex implementation | ✅ Completed |
| Day 12 | FIFO message queue | ⏳ Upcoming |
| Day 13 | Full kernel and IPC integration | ⏳ Upcoming |
| Day 14 | Unit testing, build setup and documentation | ⏳ Upcoming |

> **Current Progress: Day 11 of 14 — Mutex Synchronization implemented.**

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
Context Simulation           ██████████ 100%  ✅
Cortex-M Port Layer          ██████████ 100%  ✅
Semaphore                    ██████████ 100%  ✅
Mutex                        ██████████ 100%  ✅
Message Queue                ░░░░░░░░░░   0%  ⏳
Integration Demo             ░░░░░░░░░░   0%  ⏳
Unit Testing                 ░░░░░░░░░░   0%  ⏳
```

**Development Roadmap: 11 / 14 Days Completed**

---

# 🚀 Planned Features

The following features are planned for upcoming development stages:

- Mutex-based shared resource protection
- FIFO message queues
- Inter-task communication
- Full kernel and IPC integration
- Unit testing
- Build automation
- Extended documentation

Potential future improvements include:

- Hardware SysTick integration
- PendSV-based context switching
- Real Cortex-M task stacks
- Preemptive scheduling
- Priority inheritance
- Dynamic memory management

---

# ⚠️ Current Limitations

MiniRTOS is currently an educational **host-side RTOS kernel simulation**.

At the current Day 11  development stage, it does not yet implement:

- Hardware-based context switching
- Actual ARM Cortex-M register save/restore
- PendSV-based context switching
- Hardware SysTick interrupts
- Preemptive multitasking
- Per-task hardware stacks
- Mutex synchronization
- Message queues
- Hardware interrupt handling
- Priority inheritance
- Dynamic memory management

The current context manager simulates task context transitions but does not save or restore physical processor registers.

The current semaphore implementation demonstrates synchronization semantics within a sequential cooperative host simulation. It does not yet implement a waiting-task queue or automatically block and wake tasks when semaphore acquisition fails.

The strict priority scheduler can repeatedly select the highest-priority READY task. Therefore, lower-priority tasks may experience starvation if a higher-priority task remains continuously READY.

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
Store Current Stack Pointer
      │
      ▼
Select Next Task
      │
      ▼
Load Next Stack Pointer
      │
      ▼
Restore Next Context
      │
      ▼
Resume Task Execution
```

This would transform the current educational scheduler simulation into a more hardware-oriented RTOS implementation.

---

# 🎯 Learning Outcomes

Through the first eleven development stages, the following concepts have been explored:

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
- State-aware task scheduling
- System Tick architecture
- Kernel tick management
- Simulated kernel time base
- Tick-based task delays
- Wake tick management
- Automatic delayed-task wake-up
- Context management concepts
- Context save and restore simulation
- Context switch tracking
- Cortex-M port abstraction
- Architecture-dependent port layers
- Semaphore fundamentals
- Semaphore acquisition
- Semaphore release
- Counting semaphore concepts
- Shared-resource synchronization
- Embedded software abstraction
- GCC-based C development

Future development will expand these concepts into mutex synchronization, inter-task communication, full system integration, and unit testing.

---

# 📌 Technical Note

MiniRTOS is designed as an educational implementation for understanding RTOS internals.

The current version is a **host-side simulation compiled using GCC**. It demonstrates the logical architecture of task management, multiple scheduling policies, kernel timing, delayed tasks, automatic wake-up, task state transitions, context management, and semaphore synchronization.

It does not currently perform hardware-level context switching on an ARM Cortex-M processor.

The System Tick implementation is simulated in software and advances during scheduler execution rather than being generated by a physical hardware timer interrupt.

Task state transitions and delayed-task wake-ups are managed by the MiniRTOS Task Manager. The scheduler checks task states and only selects eligible `READY` tasks.

The scheduler currently supports both **Round-Robin** and **Priority-Based** scheduling policies.

The Cortex-M port layer currently provides a logical host-side abstraction for simulated context management.

The semaphore implementation provides the first MiniRTOS IPC and synchronization mechanism.

Future development stages will introduce mutexes, message queues, complete IPC integration, and unit testing while maintaining a modular architecture suitable for exploring a future Cortex-M hardware port.

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

The project follows a structured 14-day development roadmap, progressively introducing task management, scheduling, timing, context management, synchronization, inter-task communication, and RTOS architecture concepts.

By implementing these mechanisms individually, the project aims to build a stronger understanding of the software architecture underlying embedded Real-Time Operating Systems.

---

<div align="center">

### ⚙️ MiniRTOS

**Building RTOS concepts from scratch in C — one subsystem at a time.**

### Current Progress: Day 11 / 14 ✅

</div>