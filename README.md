<div align="center">

# ⚙️ MiniRTOS

### A Lightweight RTOS Kernel & Task Scheduling Simulator Written in C

![Language](https://img.shields.io/badge/Language-C-blue)
![Compiler](https://img.shields.io/badge/Compiler-GCC-orange)
![Platform](https://img.shields.io/badge/Platform-Host%20Simulation-lightgrey)
![Architecture](https://img.shields.io/badge/Target-Cortex--M-green)
![Status](https://img.shields.io/badge/Status-In%20Development-orange)
![Progress](https://img.shields.io/badge/Progress-Day%206%20of%2014-blue)

**MiniRTOS** is a lightweight Real-Time Operating System kernel and task scheduling simulator being developed from scratch in C to explore the internal concepts behind embedded RTOS architectures.

The project is being developed through a structured **14-day development roadmap**.

The current GitHub version has completed **Day 6**, covering kernel initialization, Task Control Blocks, dynamic task registration, Round-Robin scheduling, simulated System Tick management, and task state management with blocking, unblocking, suspension, and resumption.

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
- READY task selection
- Automatic skipping of unavailable tasks
- Simulated System Tick
- Kernel tick counter
- Task blocking and unblocking
- Task suspension and resumption
- Scheduler interaction with task states

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
          │                 ├── READY Task Selection
          │                 ├── Skip BLOCKED Tasks
          │                 └── Skip SUSPENDED Tasks
          │
          ├── Task Creation
          ├── Task Registration
          ├── Task Control Blocks
          ├── Task States
          ├── Block / Unblock
          └── Suspend / Resume
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
Tick-Based Task Delays
        │
        ▼
Automatic Task Wake-Up
        │
        ▼
Priority Scheduler
        │
        ▼
Context Manager
        │
        ▼
IPC
├── Semaphore
├── Mutex
└── Message Queue
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

Each task contains information such as:

```text
Task ID
Task Name
Priority
Task State
Task Function
Stack Pointer
```

The TCB architecture provides the foundation for task management and scheduling.

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

MiniRTOS currently implements a cooperative **Round-Robin scheduling policy**.

Tasks are selected sequentially:

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

---

## Scheduler Execution

A scheduler cycle performs the following operations:

```text
Scheduler Cycle
      │
      ▼
Increment System Tick
      │
      ▼
Find Next Task
      │
      ▼
Check Task State
      │
      ├── BLOCKED ─────► Skip
      │
      ├── SUSPENDED ───► Skip
      │
      ▼
Task READY
      │
      ▼
Mark RUNNING
      │
      ▼
Execute Task Function
      │
      ▼
Return Task to READY
```

This provides a basic cooperative task scheduling simulation with task-state awareness.

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
Update Kernel Time
      │
      ▼
Select READY Task
      │
      ▼
Execute Task
```

The System Tick provides the timing foundation required for upcoming tick-based task delays and automatic task wake-up.

At the current development stage, the System Tick is **simulated on the host system** and is not generated by a hardware SysTick interrupt.

---

# 🚦 Task State Management

Day 6 introduces explicit **Task State Management** to MiniRTOS.

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

A blocked task is automatically skipped by the scheduler.

Conceptually:

```text
Processing Task
      │
      ▼
BLOCKED
      │
      ▼
Scheduler Skips Task
      │
      ▼
UNBLOCK
      │
      ▼
READY
```

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

Conceptually:

```text
Logger Task
     │
     ▼
SUSPENDED
     │
     ▼
Scheduler Skips Task
     │
     ▼
RESUME
     │
     ▼
READY
```

---

# 🔄 Task State Operations

Day 6 introduces task management operations for controlling task execution.

Supported operations include:

```text
Block Task
Unblock Task
Suspend Task
Resume Task
```

Example API usage:

```c
MiniRTOS_BlockTask(2);

MiniRTOS_SuspendTask(3);
```

This changes the Processing and Logger tasks:

```text
Processing  → BLOCKED
Logger      → SUSPENDED
```

The scheduler then executes only eligible READY tasks:

```text
Sensor
  │
  ▼
Idle
  │
  ▼
Sensor
  │
  ▼
Idle
```

The blocked and suspended tasks are skipped.

---

## Restoring Task States

Tasks can later be restored to the `READY` state.

Example:

```c
MiniRTOS_UnblockTask(2);

MiniRTOS_ResumeTask(3);
```

The task states become:

```text
Sensor       READY
Processing   READY
Logger       READY
Idle         READY
```

The scheduler can then execute all four tasks again:

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
```

---

# 🧪 Day 6 Task State Test

The Day 6 demo demonstrates the interaction between the Task Manager and the Round-Robin scheduler.

Initial state:

```text
Sensor       READY
Processing   READY
Logger       READY
Idle         READY
```

Task states are then modified:

```text
[DAY 6 TEST] Changing task states...

[TASK MANAGER] Task 3 (Logger) state changed to SUSPENDED.
[TASK MANAGER] Task 2 (Processing) state changed to BLOCKED.
```

The scheduler now executes:

```text
Sensor
Idle
Sensor
Idle
Sensor
Idle
Sensor
Idle
```

After restoring the tasks:

```text
[DAY 6 TEST] Restoring task states...

[TASK MANAGER] Task 2 (Processing) state changed to READY.
[TASK MANAGER] Task 3 (Logger) state changed to READY.
```

The scheduler returns to normal Round-Robin execution:

```text
Sensor
Processing
Logger
Idle
Sensor
Processing
Logger
Idle
```

This demonstrates that the scheduler correctly respects task states when selecting tasks for execution.

---

# 🧪 Current Demo Application

The MiniRTOS demo application contains four simulated tasks.

## Sensor Task

```text
[TASK] Reading simulated sensor data.
```

Represents a task responsible for collecting simulated sensor data.

---

## Processing Task

```text
[TASK] Processing simulated data.
```

Represents a task responsible for processing sensor information.

---

## Logger Task

```text
[TASK] Logging system information.
```

Represents a task responsible for recording system information.

---

## Idle Task

```text
[TASK] CPU Idle.
```

Represents an idle execution path.

---

# 🔄 Current System Flow

```text
              MiniRTOS Kernel
                    │
                    ▼
              Task Manager
                    │
                    ▼
            Register 4 Tasks
                    │
                    ▼
             Print Task Table
                    │
                    ▼
           Initialize System Tick
                    │
                    ▼
          Modify Task States
                    │
          ┌─────────┴─────────┐
          │                   │
          ▼                   ▼
      Processing            Logger
       BLOCKED             SUSPENDED
          │                   │
          └─────────┬─────────┘
                    │
                    ▼
           Initialize Scheduler
                    │
                    ▼
            Increment Tick
                    │
                    ▼
          Round-Robin Selection
                    │
                    ▼
           Execute READY Tasks
                    │
                    ▼
          Restore Task States
                    │
                    ▼
         All Tasks Return READY
```

---

# 📂 Current Project Structure

The public GitHub repository currently contains the components developed through Day 6.

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
| Day 7 | Tick-based task delays and wake-up | ⏳ Upcoming |
| Day 8 | Priority-based scheduling | ⏳ Upcoming |
| Day 9 | Context management simulation | ⏳ Upcoming |
| Day 10 | Semaphore implementation | ⏳ Upcoming |
| Day 11 | Mutex implementation | ⏳ Upcoming |
| Day 12 | FIFO message queue | ⏳ Upcoming |
| Day 13 | Full kernel and IPC integration | ⏳ Upcoming |
| Day 14 | Unit testing, build setup and documentation | ⏳ Upcoming |

> **Current Progress: Day 6 of 14 — Task State Management implemented.**

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
Task Delays                  ░░░░░░░░░░   0%  ⏳
Priority Scheduling          ░░░░░░░░░░   0%  ⏳
Context Simulation           ░░░░░░░░░░   0%  ⏳
Semaphore                    ░░░░░░░░░░   0%  ⏳
Mutex                        ░░░░░░░░░░   0%  ⏳
Message Queue                ░░░░░░░░░░   0%  ⏳
Integration Demo             ░░░░░░░░░░   0%  ⏳
Unit Testing                 ░░░░░░░░░░   0%  ⏳
```

**Development Roadmap: 6 / 14 Days Completed**

---

# 🚀 Planned Features

The following features are planned for upcoming development stages:

- Tick-based task delays
- Automatic delayed-task wake-up
- Priority-based scheduling
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

At the current Day 6 development stage, it does not yet implement:

- Hardware-based context switching
- ARM Cortex-M register save/restore
- PendSV-based context switching
- Hardware SysTick interrupts
- Preemptive multitasking
- Per-task hardware stacks
- Tick-based task delays
- Automatic timed wake-up
- Semaphore synchronization
- Mutex synchronization
- Message queues
- Hardware interrupt handling
- Priority inheritance
- Dynamic memory management

The current scheduler and System Tick are host-side simulations intended to demonstrate fundamental RTOS scheduling, timing, and task-state concepts.

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

Through the first six development stages, the following concepts have been explored:

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
- Scheduler task selection
- State-aware task scheduling
- System Tick architecture
- Kernel tick management
- Simulated kernel time base
- Embedded software abstraction
- GCC-based C development

Future development will expand these concepts into tick-based delays, priority scheduling, context management, synchronization, and inter-task communication.

---

# 📌 Technical Note

MiniRTOS is designed as an educational implementation for understanding RTOS internals.

The current version is a **host-side simulation compiled using GCC**. It demonstrates the logical architecture of task management, scheduling, kernel timing, and task state transitions but does not currently perform hardware-level context switching on an ARM Cortex-M processor.

The System Tick implementation is simulated in software and advances during scheduler execution rather than being generated by a physical hardware timer interrupt.

Task state transitions are also simulated through the MiniRTOS Task Manager. The scheduler checks task states and only selects eligible `READY` tasks.

Future development stages will introduce additional RTOS concepts while maintaining a modular architecture suitable for exploring a potential Cortex-M port.

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

### Current Progress: Day 6 / 14 ✅

</div>