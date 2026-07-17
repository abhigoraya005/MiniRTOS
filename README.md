<div align="center">

# ⚙️ MiniRTOS

### A Lightweight RTOS Kernel & Task Scheduling Simulator Written in C

![Language](https://img.shields.io/badge/Language-C-blue)
![Compiler](https://img.shields.io/badge/Compiler-GCC-orange)
![Platform](https://img.shields.io/badge/Platform-Host%20Simulation-lightgrey)
![Architecture](https://img.shields.io/badge/Target-Cortex--M-green)
![Status](https://img.shields.io/badge/Status-In%20Development-orange)
![Progress](https://img.shields.io/badge/Progress-Day%205%20of%2014-blue)

**MiniRTOS** is a lightweight Real-Time Operating System kernel and task scheduling simulator being developed from scratch in C to explore the internal concepts behind embedded RTOS architectures.

The project is being developed through a structured **14-day development roadmap**.

The current GitHub version has completed **Day 5**, covering kernel initialization, Task Control Blocks, dynamic task registration, task state representation, cooperative Round-Robin task scheduling, and simulated System Tick management.

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
- Multi-task execution simulation
- Simulated System Tick
- Kernel tick counter
- Tick advancement during scheduler execution

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
          │                 └── Task Execution
          │
          ├── Task Creation
          ├── Task Registration
          ├── Task Control Blocks
          ├── Task States
          └── Task Table
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
Task State Management
        │
        ▼
Tick-Based Task Delays
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

# 🚦 Task States

MiniRTOS defines multiple task states to represent the lifecycle of a task.

Supported task states include:

```text
READY
RUNNING
BLOCKED
SUSPENDED
```

At the current development stage, the scheduler primarily operates on tasks in the `READY` state.

Future development will extend state transitions through blocking, suspension, delays, and synchronization mechanisms.

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

Day 4 introduced the first scheduling algorithm in MiniRTOS.

The current scheduler uses a cooperative **Round-Robin scheduling policy**.

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
      ├── Not READY ──► Skip Task
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

This provides a basic cooperative task scheduling simulation.

---

## READY Task Selection

The scheduler only executes tasks that are currently in the `READY` state.

Tasks in other states can be skipped.

Conceptually:

```text
Task 1: Sensor       READY       → Execute
Task 2: Processing   READY       → Execute
Task 3: Logger       BLOCKED     → Skip
Task 4: Idle         READY       → Execute
```

This provides the foundation for future task blocking, delays, synchronization, and IPC mechanisms.

---

# ⏱️ System Tick

Day 5 introduces a simulated **System Tick** that provides a basic time reference for the MiniRTOS kernel.

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

[SCHEDULER] Cycle 4
[TICK] 4
```

The current System Tick provides the kernel with a simulated time base.

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

The kernel tick can be retrieved using the System Tick API.

The System Tick provides the timing foundation required for upcoming MiniRTOS features such as:

- Tick-based task delays
- Automatic delayed-task wake-up
- Time-based scheduling operations
- Software timers

At the current development stage, the System Tick is **simulated on the host system** and is not generated by a hardware SysTick interrupt.

---

# 🧪 Current Demo Application

The MiniRTOS demo application currently contains four simulated tasks.

## Sensor Task

```text
[TASK] Reading simulated sensor data.
```

Represents a task responsible for collecting data from a simulated sensor.

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

Represents an idle execution path when no higher-level application work is required.

---

# 🔄 Current Task Execution Flow

The current MiniRTOS application follows this simulated execution sequence:

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
           Initialize Scheduler
                    │
                    ▼
              Scheduler Cycle
                    │
                    ▼
            Increment Tick
                    │
                    ▼
          Round-Robin Scheduling
                    │
       ┌────────────┼────────────┐
       │            │            │
       ▼            ▼            ▼
    Sensor      Processing     Logger
       │            │            │
       └────────────┼────────────┘
                    │
                    ▼
                   Idle
                    │
                    ▼
              Repeat Cycle
```

---

# 📂 Current Project Structure

The public GitHub repository currently contains the components developed through Day 5.

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
| C | Kernel and task management development |
| GCC | Compilation |
| MSYS2 | GCC toolchain environment |
| PowerShell | Build and execution |
| Visual Studio Code | Development environment |
| Git | Version control |
| GitHub | Source code hosting |

---

# ⚙️ Build Instructions

## Prerequisites

GCC is required to compile the current MiniRTOS host simulation.

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
| Day 6 | Task state management | ⏳ Upcoming |
| Day 7 | Tick-based task delays and wake-up | ⏳ Upcoming |
| Day 8 | Priority-based scheduling | ⏳ Upcoming |
| Day 9 | Context management simulation | ⏳ Upcoming |
| Day 10 | Semaphore implementation | ⏳ Upcoming |
| Day 11 | Mutex implementation | ⏳ Upcoming |
| Day 12 | FIFO message queue | ⏳ Upcoming |
| Day 13 | Full kernel and IPC integration | ⏳ Upcoming |
| Day 14 | Unit testing, build setup and documentation | ⏳ Upcoming |

> **Current Progress: Day 5 of 14 — System Tick integration completed.**

---

# 📊 Current Project Status

```text
Kernel Initialization        ██████████ 100%  ✅
Task Control Blocks          ██████████ 100%  ✅
Task Registration            ██████████ 100%  ✅
Task Table                   ██████████ 100%  ✅
Round-Robin Scheduling       ██████████ 100%  ✅
System Tick                  ██████████ 100%  ✅
Task State Management        ░░░░░░░░░░   0%  ⏳
Task Delays                  ░░░░░░░░░░   0%  ⏳
Priority Scheduling          ░░░░░░░░░░   0%  ⏳
Context Simulation           ░░░░░░░░░░   0%  ⏳
Semaphore                    ░░░░░░░░░░   0%  ⏳
Mutex                        ░░░░░░░░░░   0%  ⏳
Message Queue                ░░░░░░░░░░   0%  ⏳
Integration Demo             ░░░░░░░░░░   0%  ⏳
Unit Testing                 ░░░░░░░░░░   0%  ⏳
```

**Development Roadmap: 5 / 14 Days Completed**

---

# 🚀 Planned Features

The following features are planned for upcoming development stages:

- Task state management
- Task suspension and resumption
- Task blocking and unblocking
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

At the current Day 5 development stage, it does not yet implement:

- Hardware-based context switching
- ARM Cortex-M register save/restore
- PendSV-based context switching
- Hardware SysTick interrupts
- Preemptive multitasking
- Per-task hardware stacks
- Tick-based task blocking
- Semaphore synchronization
- Mutex synchronization
- Message queues
- Hardware interrupt handling
- Priority inheritance
- Dynamic memory management

The current scheduler and System Tick are host-side simulations intended to demonstrate fundamental RTOS scheduling and timing concepts.

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

Through the first five development stages, the following concepts have been explored:

- RTOS kernel architecture
- Modular C project organization
- Task Control Blocks
- Task representation
- Task lifecycle concepts
- Dynamic task registration
- Task function pointers
- Task priorities
- Task state representation
- Cooperative scheduling
- Round-Robin scheduling
- Scheduler task selection
- System Tick architecture
- Kernel tick management
- Simulated kernel time base
- Embedded software abstraction
- GCC-based C development

Future development will expand these learning outcomes into task state management, task delays, synchronization, inter-task communication, priority scheduling, and context management.

---

# 📌 Technical Note

MiniRTOS is designed as an educational implementation for understanding RTOS internals.

The current version is a **host-side simulation compiled using GCC**. It demonstrates the logical architecture of task management, scheduling, and kernel timing but does not currently perform hardware-level context switching on an ARM Cortex-M processor.

The System Tick implementation is currently simulated in software and advances during scheduler execution rather than being generated by a physical hardware timer interrupt.

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

### Current Progress: Day 5 / 14 ✅

</div>