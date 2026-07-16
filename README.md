<div align="center">

# ⚙️ MiniRTOS

### A Lightweight RTOS Kernel & Task Scheduling Simulator Written in C

![Language](https://img.shields.io/badge/Language-C-blue)
![Compiler](https://img.shields.io/badge/Compiler-GCC-orange)
![Platform](https://img.shields.io/badge/Platform-Host%20Simulation-lightgrey)
![Architecture](https://img.shields.io/badge/Target-Cortex--M-green)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![License](https://img.shields.io/badge/License-MIT-yellow)

**MiniRTOS** is a lightweight Real-Time Operating System kernel and scheduling simulator developed from scratch in C to explore the internal concepts behind embedded RTOS architectures.

The project implements task management, scheduling algorithms, system ticks, task delays, simulated context switching, semaphores, mutexes, and FIFO message queues without relying on an existing RTOS such as FreeRTOS.

</div>

---

## 📌 Project Overview

Real-Time Operating Systems are fundamental to modern embedded systems, automotive ECUs, IoT devices, robotics, industrial controllers, and safety-critical applications.

MiniRTOS was developed as a learning-oriented systems project to understand how core RTOS mechanisms operate internally.

The project demonstrates:

- Task Control Blocks (TCBs)
- Task creation and management
- Task state transitions
- Round-Robin scheduling
- Priority-based scheduling
- System Tick management
- Tick-based task delays
- Simulated context switching
- Semaphore synchronization
- Mutex-based resource protection
- FIFO message queues
- Inter-task communication
- Integrated multi-task application execution

The current implementation runs as a **host-side simulation using GCC** while maintaining a modular architecture designed around embedded RTOS concepts.

---

# 🏗️ System Architecture

```text
                        MiniRTOS
                           │
        ┌──────────────────┴──────────────────┐
        │                                     │
      Kernel                                Port
        │                                     │
        ├── Task Manager                      └── Cortex-M Context
        ├── Scheduler                             Manager Simulation
        ├── System Tick
        └── Task Delay
        │
        │
        ▼
       IPC
        │
        ├── Semaphore
        ├── Mutex
        └── Message Queue
        │
        ▼
 Demo Application
        │
        ├── Sensor Task
        ├── Processing Task
        ├── Logger Task
        └── Idle Task
```

---

# 🔄 Integrated Application Data Flow

The final MiniRTOS demonstration simulates a multi-task embedded application.

```text
┌──────────────────┐
│   Sensor Task    │
│ Generate Sample  │
└────────┬─────────┘
         │
         │ Send
         ▼
┌──────────────────┐
│  Message Queue   │
│    FIFO Buffer   │
└────────┬─────────┘
         │
         │ Semaphore signals data availability
         ▼
┌──────────────────┐
│ Processing Task  │
│ Process Sample   │
└────────┬─────────┘
         │
         │ Mutex-protected shared result
         ▼
┌──────────────────┐
│   Logger Task    │
│   Read Result    │
└──────────────────┘

All tasks are managed by:

Scheduler
   +
System Tick
   +
Task Manager
   +
Context Manager Simulation
```

---

# ✨ Features

## 🧠 Task Management

MiniRTOS provides a basic Task Control Block architecture for managing application tasks.

Each task contains information such as:

```text
Task ID
Task Name
Priority
Task State
Task Function
Stack Pointer
Wake Tick
```

Supported task states include:

```text
READY
RUNNING
BLOCKED
SUSPENDED
```

The Task Manager supports:

- Task creation
- Task registration
- Task lookup
- Task state transitions
- Task suspension
- Task resumption
- Task blocking
- Task unblocking
- Task table visualization

---

## 🔁 Round-Robin Scheduler

MiniRTOS implements a cooperative Round-Robin scheduling simulation.

Example:

```text
Sensor
   ↓
Processing
   ↓
Logger
   ↓
Idle
   ↓
Sensor
```

Only tasks in the `READY` state are selected for execution.

Blocked or suspended tasks are skipped automatically.

---

## 🚦 Priority-Based Scheduler

MiniRTOS also supports priority-based task selection.

Example priorities:

| Task | Priority |
|---|---:|
| Sensor | 3 |
| Processing | 2 |
| Logger | 1 |
| Idle | 0 |

The scheduler selects the highest-priority task currently in the `READY` state.

Round-Robin scheduling is used among eligible tasks where appropriate.

---

## ⏱️ System Tick

MiniRTOS includes a simulated kernel System Tick.

Example:

```text
[TICK] 1
[TICK] 2
[TICK] 3
[TICK] 4
```

The System Tick provides a time base for kernel operations such as delayed task wake-up.

---

## 💤 Tick-Based Task Delay

Tasks can be temporarily blocked for a specified number of kernel ticks.

Example:

```text
Processing Task
      │
      │ Delay
      ▼
BLOCKED
      │
      │ Wake Tick Reached
      ▼
READY
```

Example output:

```text
[TASK MANAGER] Task 2 (Processing) delayed until Tick 4.

...

[TASK MANAGER] Task 2 (Processing) woke up at Tick 4.
```

---

## 🔄 Context Management Simulation

MiniRTOS contains a Cortex-M-oriented port layer that demonstrates context transition concepts.

Example:

```text
[CONTEXT] ---- Context Switch ----
[CONTEXT] Saving context of Task 1: Sensor
[CONTEXT] Restoring context of Task 2: Processing
[CONTEXT] Total Context Switches: 2
```

The current implementation **simulates context switching on the host system**.

It does not yet perform real ARM Cortex-M register save/restore operations using PendSV or assembly-level stack switching.

---

# 🔗 Inter-Process Communication (IPC)

MiniRTOS implements three fundamental synchronization and communication mechanisms.

---

## 🚥 Semaphore

A counting semaphore is used to synchronize tasks and represent resource or event availability.

In the integrated application, the semaphore tracks whether sensor data is available for processing.

```text
Sensor Task
    │
    │ Queue Data
    ▼
Semaphore Signal
    │
    ▼
Processing Task
    │
    │ Semaphore Wait
    ▼
Process Data
```

Example:

```text
[SEMAPHORE] Released. Count: 1 / 8
[SEMAPHORE] Acquired. Count: 0 / 8
```

---

## 🔒 Mutex

The mutex provides ownership-based protection for shared resources.

In the final application, the processed result is protected by a mutex.

```text
Processing Task
      │
      │ Lock
      ▼
 Shared Result
      │
      │ Unlock
      ▼
 Logger Task
```

Example:

```text
[MUTEX] Task 2 acquired mutex.
[MUTEX] Task 2 released mutex.

[MUTEX] Task 3 acquired mutex.
[MUTEX] Task 3 released mutex.
```

The mutex tracks task ownership to prevent incorrect unlock operations.

---

## 📬 FIFO Message Queue

MiniRTOS implements a fixed-size FIFO message queue using a circular buffer.

The queue enables data transfer between tasks.

```text
Sensor Task
    │
    │ Send
    ▼
┌─────────────────────────┐
│      Message Queue      │
│  [25] [30] [35] [...]  │
└────────────┬────────────┘
             │
             │ Receive
             ▼
      Processing Task
```

The queue supports:

- Initialization
- Message sending
- Message receiving
- FIFO ordering
- Queue count tracking
- Empty detection
- Full detection
- Circular buffer wrap-around

Current queue messages use `uint32_t` values.

---

# 🧪 Final Integrated Demo

The final Day 13 integration test combines all major MiniRTOS components.

The application runs four tasks:

```text
Sensor Task
Processing Task
Logger Task
Idle Task
```

During execution:

1. The Sensor Task generates simulated data.
2. The value is inserted into the FIFO message queue.
3. The semaphore signals that data is available.
4. The Processing Task acquires the semaphore.
5. The Processing Task receives data from the queue.
6. The data is processed.
7. The processed result is protected using a mutex.
8. The Logger Task safely reads the shared result.
9. The Idle Task represents CPU idle execution.
10. The scheduler repeats the task sequence.

Example data flow:

```text
Sensor Value     Processed Result

25          →          50
30          →          60
35          →          70
40          →          80
```

Final integration result:

```text
=================================
     MiniRTOS System Summary
=================================
Final Kernel Tick        : 16
Context Switch Events    : 16
Samples Generated        : 4
Samples Processed        : 4
Logger Executions        : 4
Messages Remaining       : 0
Semaphore Count          : 0
Mutex State              : UNLOCKED
Final Processed Result   : 80
=================================
```

---

# 🧪 Unit Testing

A dedicated queue unit test validates the FIFO message queue implementation.

Test file:

```text
Tests/test_queue.c
```

The following functionality is tested:

- Queue initialization
- Initial empty state
- Message sending
- Queue count tracking
- Message receiving
- FIFO data integrity
- Empty state after receiving
- Rejection of receive operations on an empty queue

Final test result:

```text
=================================
Tests Passed : 8
Tests Failed : 0
=================================

[TEST] All MiniRTOS queue tests passed.
```

---

# 📂 Project Structure

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
├── Demo
│   └── main.c
│
├── Tests
│   └── test_queue.c
│
├── Docs
│
├── .gitignore
├── Makefile
└── README.md
```

---

# 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C | Kernel and application development |
| GCC | Compilation |
| MSYS2 | GCC toolchain environment |
| PowerShell | Build and execution environment |
| Visual Studio Code | Development environment |
| Git | Version control |
| GitHub | Source code hosting |

---

# ⚙️ Build Instructions

## Prerequisites

Install GCC and verify:

```bash
gcc --version
```

---

## Compile MiniRTOS

From the project root directory:

```bash
gcc -Wall -Wextra Demo/main.c Kernel/minirtos.c Kernel/task.c Kernel/scheduler.c Kernel/systick.c Port/cortex_m_port.c IPC/semaphore.c IPC/mutex.c IPC/queue.c -o MiniRTOS.exe
```

Run:

```bash
./MiniRTOS.exe
```

On Windows PowerShell:

```powershell
.\MiniRTOS.exe
```

---

# 🧪 Running Queue Unit Tests

Compile:

```bash
gcc -Wall -Wextra Tests/test_queue.c IPC/queue.c -o test_queue.exe
```

Run:

```bash
./test_queue.exe
```

On Windows PowerShell:

```powershell
.\test_queue.exe
```

Expected result:

```text
Tests Passed : 8
Tests Failed : 0
```

---

# 🗓️ 14-Day Development Roadmap

| Day | Development Milestone | Status |
|---|---|---|
| Day 1 | Project architecture and kernel initialization | ✅ |
| Day 2 | Task Control Block foundation | ✅ |
| Day 3 | Dynamic task registration and task table | ✅ |
| Day 4 | Round-Robin scheduler | ✅ |
| Day 5 | System Tick integration | ✅ |
| Day 6 | Task state management | ✅ |
| Day 7 | Tick-based task delays and wake-up | ✅ |
| Day 8 | Priority-based scheduling | ✅ |
| Day 9 | Context management simulation | ✅ |
| Day 10 | Semaphore implementation | ✅ |
| Day 11 | Mutex implementation | ✅ |
| Day 12 | FIFO message queue | ✅ |
| Day 13 | Full kernel and IPC integration | ✅ |
| Day 14 | Unit testing, build setup and documentation | ✅ |

---

# 📊 Project Status

```text
Kernel Initialization        ██████████ 100%
Task Management              ██████████ 100%
Round-Robin Scheduling       ██████████ 100%
Priority Scheduling          ██████████ 100%
System Tick                  ██████████ 100%
Task Delays                  ██████████ 100%
Context Simulation           ██████████ 100%
Semaphore                    ██████████ 100%
Mutex                        ██████████ 100%
Message Queue                ██████████ 100%
Integration Demo             ██████████ 100%
Queue Unit Tests             ██████████ 100%
```

**14-Day Development Roadmap: Completed ✅**

---

# ⚠️ Current Limitations

MiniRTOS is currently an educational **host-side RTOS kernel simulation**.

The current version does not yet implement:

- Real Cortex-M register context save/restore
- PendSV-based context switching
- Hardware SysTick interrupts
- Preemptive multitasking
- Per-task hardware stack allocation
- Interrupt Service Routine integration
- Priority inheritance
- Blocking semaphore wait queues
- Blocking mutex wait queues
- Blocking message queue operations
- Dynamic memory management

The current context manager demonstrates scheduling transitions but does not perform actual CPU register context switching.

---

# 🚀 Future Improvements

Potential future development includes:

- Port MiniRTOS to STM32 Cortex-M
- Implement real SysTick interrupts
- Implement PendSV context switching
- Add per-task stacks
- Implement preemptive scheduling
- Add task sleep APIs
- Add event flags
- Add software timers
- Add blocking IPC operations
- Add priority inheritance
- Add scheduler unit tests
- Add semaphore and mutex unit tests
- Add automated CI testing
- Add ARM GCC cross-compilation support

A future embedded version could target:

```text
STM32F103C8T6
ARM Cortex-M3
```

using an ARM GCC toolchain.

---

# 🎯 Learning Outcomes

Through this project, the following embedded systems and RTOS concepts were explored:

- RTOS kernel architecture
- Task Control Blocks
- Task lifecycle management
- Cooperative scheduling
- Round-Robin scheduling
- Priority scheduling
- System Tick concepts
- Task blocking and wake-up
- Context switching concepts
- Synchronization primitives
- Semaphore design
- Mutex ownership
- Inter-task communication
- FIFO message queues
- Circular buffers
- Modular C architecture
- Embedded software abstraction
- Unit testing in C

---

# 📌 Technical Note

MiniRTOS is designed as an educational implementation for understanding RTOS internals.

The Cortex-M port included in the current version is a **simulation layer**. It demonstrates the logical flow of context transitions but does not yet perform hardware-level context switching on an ARM Cortex-M processor.

This distinction is intentional and keeps the project technically accurate while providing a foundation for a future hardware port.

---

# 👨‍💻 Author

**Abhiney Kumar**

Electronics and Communication Engineering  
Dr. B.R. Ambedkar National Institute of Technology, Jalandhar

Areas of Interest:

- Embedded Systems
- Embedded Firmware
- Real-Time Operating Systems
- Microcontrollers
- VLSI
- Semiconductor Systems

---

# ⭐ Project Motivation

MiniRTOS was developed to move beyond simply using an existing RTOS API and instead explore how fundamental operating-system mechanisms can be designed from the ground up.

The project provides a foundation for further work in embedded firmware, ARM Cortex-M development, and real-time operating systems.

---

<div align="center">

### ⚙️ MiniRTOS

**Built from scratch in C to understand what happens beneath an RTOS API.**

</div>