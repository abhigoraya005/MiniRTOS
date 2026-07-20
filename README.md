<div align="center">

# ⚙️ MiniRTOS

### A Lightweight RTOS Kernel & Task Scheduling Simulator Written in C

![Language](https://img.shields.io/badge/Language-C-blue)
![Compiler](https://img.shields.io/badge/Compiler-GCC-orange)
![Platform](https://img.shields.io/badge/Platform-Host%20Simulation-lightgrey)
![Architecture](https://img.shields.io/badge/Target-Cortex--M-green)
![Status](https://img.shields.io/badge/Status-In%20Development-orange)
![Progress](https://img.shields.io/badge/Progress-Day%2012%20of%2014-blue)

**MiniRTOS** is a lightweight Real-Time Operating System kernel and task scheduling simulator being developed from scratch in C to explore the internal concepts behind embedded RTOS architectures.

The project is being developed through a structured **14-day development roadmap**.

The current GitHub version has completed **Day 12**, covering kernel initialization, Task Control Blocks, dynamic task registration, Round-Robin scheduling, simulated System Tick management, task state management, tick-based task delays, automatic task wake-up, priority-based scheduling, simulated context management, a Cortex-M-oriented port abstraction, semaphore-based synchronization, mutex-based mutual exclusion, and FIFO message queues for inter-task communication.

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
- Mutex initialization
- Mutex lock and unlock operations
- Mutex ownership tracking
- Shared-resource mutual exclusion
- FIFO message queue initialization
- Message send and receive operations
- Queue empty and full detection
- FIFO data ordering
- Producer-consumer communication
- Inter-task communication

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
          │                 ▼        ┌────────┼────────┐
          │          Context Manager │        │        │
          │                 │        ▼        ▼        ▼
          │                 │    Semaphore  Mutex    Queue
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

Current IPC architecture:

```text
IPC
 │
 ├── Semaphore       ✅
 │
 ├── Mutex           ✅
 │
 └── Message Queue   ✅
        │
        ▼
Full System Integration  ⏳
        │
        ▼
Unit Testing             ⏳
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
---------------------------------
Task ID       : 2
Task Name     : Processing
Priority      : 2
State         : READY
---------------------------------
Task ID       : 3
Task Name     : Logger
Priority      : 1
State         : READY
---------------------------------
Task ID       : 4
Task Name     : Idle
Priority      : 0
State         : READY
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

---

# ⏱️ System Tick

Day 5 introduced a simulated **System Tick** that provides a basic time reference for the MiniRTOS kernel.

During scheduler execution, the tick counter advances with each scheduling cycle.

Example:

```text
[SCHEDULER] Cycle 1
[TICK] 1

[SCHEDULER] Cycle 2
[TICK] 2
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

A task in the `READY` state is available for scheduling.

A selected task temporarily enters the `RUNNING` state.

A `BLOCKED` task is unavailable for scheduling until it becomes READY.

A `SUSPENDED` task remains unavailable until explicitly resumed.

Supported operations include:

```text
Block Task
Unblock Task
Suspend Task
Resume Task
Delay Task
Automatic Wake-Up
```

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

The scheduler checks delayed tasks as the System Tick advances and automatically returns eligible tasks to the READY state.

---

# 🔄 Context Management Simulation

Day 9 introduced a simulated **Context Management layer**.

In a real ARM Cortex-M RTOS, context switching involves saving and restoring processor registers and task stack pointers.

Since MiniRTOS currently runs as a host-side GCC simulation, these operations are modeled logically.

Example:

```text
[CONTEXT] ---- Context Switch ----
[CONTEXT] Saving context of Task 1: Sensor
[CONTEXT] Restoring context of Task 2: Processing
[CONTEXT] Total Context Switches: 2
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

---

# 🧩 Cortex-M Port Abstraction

Day 9 also introduced a dedicated **Port layer**.

Current structure:

```text
Port
├── cortex_m_port.c
└── cortex_m_port.h
```

The port layer separates architecture-dependent functionality from the main MiniRTOS kernel.

The current implementation provides host-side simulation of context management and creates a foundation for future Cortex-M hardware support.

Potential future extensions include:

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

Day 10 introduced **Semaphore Synchronization**.

A semaphore maintains:

```text
Current Count
Maximum Count
```

Example:

```text
[SEMAPHORE] Initialized. Count: 1 / 1
[SEMAPHORE] Acquired. Count: 0 / 1
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
```

The current implementation demonstrates semaphore behavior in the cooperative host simulation.

---

# 🔒 Mutex Synchronization

Day 11 introduced **Mutex-Based Synchronization** for protecting shared resources.

Unlike a semaphore, the MiniRTOS mutex tracks the task that currently owns the lock.

Example:

```text
[MUTEX] Initialized. State: UNLOCKED
[MUTEX] Task 1 acquired mutex.
[MUTEX] Task 1 released mutex.
```

Conceptually:

```text
Task Requests Resource
        │
        ▼
    Check Mutex
        │
   ┌────┴─────┐
   │          │
UNLOCKED    LOCKED
   │          │
   ▼          ▼
Acquire     Access Denied
   │
   ▼
Set Task as Owner
   │
   ▼
Critical Section
   │
   ▼
Release Mutex
   │
   ▼
Mutex UNLOCKED
```

The mutex provides mutual exclusion and ensures that only one task can own the protected resource at a time.

The current implementation demonstrates mutex ownership and shared-resource protection within the cooperative host simulation.

---

# 📬 FIFO Message Queue

Day 12 introduced a **FIFO Message Queue** for inter-task communication.

The queue allows one task to send data that can later be received and processed by another task.

The current queue supports a capacity of eight messages.

Example initialization:

```text
[QUEUE] Message queue initialized. Capacity: 8
```

A producer task can send a message:

```text
[QUEUE] Message sent: 25 | Messages: 1 / 8
```

A consumer task can receive the oldest available message:

```text
[QUEUE] Message received: 25 | Messages: 0 / 8
```

The queue follows **First-In, First-Out (FIFO)** ordering.

Conceptually:

```text
Producer Task
     │
     ▼
Generate Data
     │
     ▼
Send Message
     │
     ▼
┌───────────────┐
│ Message Queue │
│   FIFO Order  │
└───────────────┘
     │
     ▼
Receive Message
     │
     ▼
Consumer Task
     │
     ▼
Process Data
```

The queue module currently supports:

```text
Queue Initialization
Message Send
Message Receive
Message Count
Empty Detection
Full Detection
FIFO Data Ordering
```

This provides the foundation for message-based inter-task communication in MiniRTOS.

---

# 🧪 Day 12 Message Queue Test

The Day 12 demonstration uses the Sensor task as a producer and the Processing task as a consumer.

The Sensor task generates data:

```text
[TASK] Sensor generated value: 25
[QUEUE] Message sent: 25 | Messages: 1 / 8
[TASK] Sensor successfully queued data.
```

The Processing task receives and processes the queued value:

```text
[TASK] Processing checking message queue.
[QUEUE] Message received: 25 | Messages: 0 / 8
[TASK] Processing received value: 25
[TASK] Processed result: 50
```

Additional messages demonstrate continued communication:

```text
Sensor: 30 → Processing Result: 60
Sensor: 35 → Processing Result: 70
```

The data flow is:

```text
Sensor Task
    │
    ▼
Generate Value
    │
    ▼
Queue Send
    │
    ▼
FIFO Message Queue
    │
    ▼
Queue Receive
    │
    ▼
Processing Task
    │
    ▼
Process Value
```

At the end of the Day 12 test:

```text
[SYSTEM] Messages Remaining in Queue: 0
[SYSTEM] Queue Empty: YES
[SYSTEM] Queue Full: NO
[SYSTEM] Final Kernel Tick: 12

[SYSTEM] MiniRTOS Day 12 Message Queue demo completed.
```

This confirms successful FIFO message transfer between simulated MiniRTOS tasks.

---

# 🧪 Current Demo Application

The MiniRTOS Day 12 demo application contains four simulated tasks.

## Sensor Task

The Sensor task acts as the message producer.

```text
[TASK] Sensor generated value: 25
[QUEUE] Message sent: 25
```

Priority:

```text
3
```

## Processing Task

The Processing task acts as the message consumer.

```text
[TASK] Processing checking message queue.
[QUEUE] Message received: 25
[TASK] Processed result: 50
```

Priority:

```text
2
```

## Logger Task

The Logger task reports the current message queue state.

```text
[TASK] Queue currently contains 0 message(s).
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
                   Scheduler
                        │
              ┌─────────┴─────────┐
              │                   │
              ▼                   ▼
         Round Robin           Priority
              │                   │
              └─────────┬─────────┘
                        │
                        ▼
                Context Manager
                        │
                        ▼
                Selected Task
                        │
          ┌─────────────┼─────────────┐
          │             │             │
          ▼             ▼             ▼
      Semaphore       Mutex         Queue
          │             │             │
          ▼             ▼             ▼
  Synchronization   Mutual       Inter-Task
                    Exclusion    Communication
```

---

# 📂 Current Project Structure

The public GitHub repository currently contains the components developed through **Day 12**.

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
│   ├── semaphore.h
│   ├── mutex.c
│   ├── mutex.h
│   ├── queue.c
│   └── queue.h
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

## Compile Day 12 MiniRTOS Version

From the project root directory:

```bash
gcc -Wall -Wextra Demo/main.c Kernel/minirtos.c Kernel/task.c Kernel/scheduler.c Kernel/systick.c Port/cortex_m_port.c IPC/queue.c -o MiniRTOS.exe
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
| Day 11 | Mutex implementation and shared resource protection | ✅ Completed |
| Day 12 | FIFO message queue and inter-task communication | ✅ Completed |
| Day 13 | Full kernel and IPC integration | ⏳ Upcoming |
| Day 14 | Unit testing, build setup and documentation | ⏳ Upcoming |

> **Current Progress: Day 12 of 14 — FIFO Message Queue and inter-task communication implemented.**

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
Message Queue                ██████████ 100%  ✅
Integration Demo             ░░░░░░░░░░   0%  ⏳
Unit Testing                 ░░░░░░░░░░   0%  ⏳
```

**Development Roadmap: 12 / 14 Days Completed**

---

# 🚀 Planned Features

The following features are planned for upcoming development stages:

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
- Blocking queue operations
- Task wait queues

---

# ⚠️ Current Limitations

MiniRTOS is currently an educational **host-side RTOS kernel simulation**.

At the current Day 12 development stage, it does not yet implement:

- Hardware-based context switching
- Actual ARM Cortex-M register save/restore
- PendSV-based context switching
- Hardware SysTick interrupts
- Preemptive multitasking
- Per-task hardware stacks
- Hardware interrupt handling
- Priority inheritance
- Dynamic memory management
- Automatic IPC task blocking and wake-up

The current context manager simulates task context transitions but does not save or restore physical processor registers.

The semaphore implementation demonstrates synchronization semantics within a sequential cooperative host simulation. It does not yet implement a waiting-task queue or automatically block and wake tasks when semaphore acquisition fails.

The mutex implementation demonstrates mutual exclusion and ownership tracking within the cooperative host simulation. It does not yet implement advanced RTOS mutex mechanisms such as priority inheritance or automatic task blocking and wake-up queues.

The message queue uses a fixed-size FIFO buffer and demonstrates basic inter-task data transfer. It does not automatically block producer or consumer tasks when the queue is full or empty.

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

Through the first twelve development stages, the following concepts have been explored:

- RTOS kernel architecture
- Modular C project organization
- Task Control Blocks
- Task representation
- Dynamic task registration
- Task function pointers
- Task priorities
- Task state representation
- READY, RUNNING, BLOCKED, and SUSPENDED states
- Task blocking and unblocking
- Task suspension and resumption
- Cooperative scheduling
- Round-Robin scheduling
- Priority-based scheduling
- Scheduler policy selection
- State-aware task scheduling
- System Tick architecture
- Kernel tick management
- Tick-based task delays
- Automatic delayed-task wake-up
- Context management concepts
- Context save and restore simulation
- Context switch tracking
- Cortex-M port abstraction
- Architecture-dependent port layers
- Semaphore fundamentals
- Semaphore acquisition and release
- Counting semaphore concepts
- Shared-resource synchronization
- Mutex fundamentals
- Mutual exclusion
- Mutex ownership tracking
- Critical section protection
- FIFO message queues
- Producer-consumer communication
- Inter-task communication
- Queue send and receive operations
- Queue empty and full detection
- FIFO data integrity
- Embedded software abstraction
- GCC-based C development

Future development will expand these concepts into full kernel and IPC integration, automated testing, build automation, and project documentation.

---

# 📌 Technical Note

MiniRTOS is designed as an educational implementation for understanding RTOS internals.

The current version is a **host-side simulation compiled using GCC**. It demonstrates the logical architecture of task management, multiple scheduling policies, kernel timing, delayed tasks, automatic wake-up, task state transitions, context management, synchronization, mutual exclusion, and inter-task communication.

It does not currently perform hardware-level context switching on an ARM Cortex-M processor.

The System Tick implementation is simulated in software and advances during scheduler execution rather than being generated by a physical hardware timer interrupt.

Task state transitions and delayed-task wake-ups are managed by the MiniRTOS Task Manager.

The scheduler currently supports both **Round-Robin** and **Priority-Based** scheduling policies.

The Cortex-M port layer provides a logical host-side abstraction for simulated context management.

The semaphore module provides counting-based synchronization.

The mutex module provides ownership-based mutual exclusion for shared resources.

The FIFO message queue provides basic producer-consumer inter-task communication.

The next development stage will integrate the kernel, scheduler, port layer, semaphore, mutex, and message queue into a complete MiniRTOS demonstration.

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

The project follows a structured 14-day development roadmap, progressively introducing task management, scheduling, timing, context management, synchronization, mutual exclusion, inter-task communication, integration, and testing.

By implementing these mechanisms individually, the project aims to build a stronger understanding of the software architecture underlying embedded Real-Time Operating Systems.

---

<div align="center">

### ⚙️ MiniRTOS

**Building RTOS concepts from scratch in C — one subsystem at a time.**

### Current Progress: Day 12 / 14 ✅

</div>