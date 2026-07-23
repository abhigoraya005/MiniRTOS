<div align="center">

# ⚙️ MiniRTOS

### A Lightweight RTOS Kernel & Task Scheduling Simulator Written in C

![Language](https://img.shields.io/badge/Language-C-blue)
![Compiler](https://img.shields.io/badge/Compiler-GCC-orange)
![Platform](https://img.shields.io/badge/Platform-Host%20Simulation-lightgrey)
![Architecture](https://img.shields.io/badge/Target-Cortex--M-green)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Progress](https://img.shields.io/badge/Progress-Day%2014%20of%2014-brightgreen)

**MiniRTOS** is a lightweight Real-Time Operating System kernel and task scheduling simulator developed from scratch in C to explore the internal concepts behind embedded RTOS architectures.

The project was developed through a structured **14-day development roadmap** and has now reached **Day 14 / 14 — Completed**.

MiniRTOS implements task management, multiple scheduling policies, simulated system timing, task delays, context management, synchronization primitives, inter-task communication, system integration, unit testing, and build automation.

</div>

---

# 📌 Project Overview

Real-Time Operating Systems are widely used in embedded systems, automotive ECUs, IoT devices, robotics, industrial controllers, and other real-time applications.

MiniRTOS was developed as a learning-oriented systems project to understand how fundamental RTOS mechanisms operate internally.

Instead of directly relying on an existing RTOS such as FreeRTOS, this project implements and simulates several core RTOS concepts from scratch using the C programming language.

The current implementation runs as a **host-side simulation using GCC** while maintaining a modular architecture inspired by embedded RTOS designs.

---

# ✨ Features

MiniRTOS currently implements:

- Kernel initialization
- Task Control Blocks (TCBs)
- Dynamic task registration
- Task identification
- Task priorities
- Task state management
- READY, RUNNING, BLOCKED, and SUSPENDED states
- Task table visualization
- Cooperative Round-Robin scheduling
- Priority-based scheduling
- Runtime scheduler policy selection
- Simulated System Tick
- Kernel tick counter
- Task blocking and unblocking
- Task suspension and resumption
- Tick-based task delays
- Automatic delayed-task wake-up
- Simulated context switching
- Context save and restore visualization
- Context switch event tracking
- Cortex-M-oriented port abstraction
- Counting semaphores
- Mutex-based mutual exclusion
- Mutex ownership tracking
- FIFO message queues
- Producer-consumer communication
- Inter-task communication
- Full kernel and IPC integration
- Integrated Sensor → Processing → Logger pipeline
- Runtime system statistics
- Queue unit testing
- Makefile-based build configuration

---

# 🏗️ System Architecture

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
          │                          ▼        ▼        ▼
          │                      Semaphore  Mutex    Queue
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
    │       │           │
    ▼       ▼           ▼
 Queue  Semaphore     Mutex
```

---

# 🧠 Task Management

MiniRTOS uses a **Task Control Block (TCB)** to represent each task.

Each task contains information such as:

```text
Task ID
Task Name
Priority
Task State
Task Function
Stack Pointer
Timing Information
```

The demo application registers four tasks:

| Task | Priority | Purpose |
|---|---:|---|
| Sensor | 3 | Generates simulated sensor data |
| Processing | 2 | Processes received sensor data |
| Logger | 1 | Logs the latest processed result |
| Idle | 0 | Represents CPU idle execution |

Tasks can transition between:

```text
READY
RUNNING
BLOCKED
SUSPENDED
```

MiniRTOS also supports:

```text
Block Task
Unblock Task
Suspend Task
Resume Task
Delay Task
Automatic Wake-Up
```

---

# 🔁 Scheduling

MiniRTOS implements two scheduling policies.

## Round-Robin Scheduling

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

Only tasks in the `READY` state are selected.

Blocked or suspended tasks are automatically skipped.

## Priority-Based Scheduling

The priority scheduler selects the highest-priority READY task.

Example:

```text
Sensor       Priority 3
Processing   Priority 2
Logger       Priority 1
Idle         Priority 0
```

The scheduler policy can be changed at runtime:

```c
MiniRTOS_SchedulerSetPolicy(
    MINIRTOS_SCHEDULER_PRIORITY
);
```

Supported policies:

```text
MINIRTOS_SCHEDULER_ROUND_ROBIN
MINIRTOS_SCHEDULER_PRIORITY
```

---

# ⏱️ System Tick & Task Delays

MiniRTOS implements a simulated **System Tick**.

Each scheduler cycle advances the kernel tick:

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

Tasks can be delayed for a specified number of ticks.

```text
Task READY
    │
    ▼
Delay Requested
    │
    ▼
Task BLOCKED
    │
    ▼
Kernel Tick Advances
    │
    ▼
Wake Tick Reached
    │
    ▼
Task READY
```

The Task Manager automatically wakes delayed tasks when their configured wake tick is reached.

---

# 🔄 Context Management

MiniRTOS includes a simulated context management layer.

Example:

```text
[CONTEXT] ---- Context Switch ----
[CONTEXT] Saving context of Task 1: Sensor
[CONTEXT] Restoring context of Task 2: Processing
[CONTEXT] Total Context Switches: 2
```

The logical flow is:

```text
Current Task
     │
     ▼
Save Context
     │
     ▼
Select Next Task
     │
     ▼
Restore Context
     │
     ▼
Execute Task
```

The current implementation is a host-side simulation and does not physically save or restore ARM processor registers.

---

# 🧩 Cortex-M Port Layer

MiniRTOS includes a dedicated port abstraction:

```text
Port
├── cortex_m_port.c
└── cortex_m_port.h
```

The Port layer separates architecture-specific concepts from the core kernel.

It currently simulates context management while providing a foundation for future ARM Cortex-M hardware support.

A future embedded port could implement:

- Hardware SysTick
- PendSV
- PSP / MSP management
- Per-task stacks
- ARM register save and restore
- Hardware context switching

---

# 🚦 Semaphore

Day 10 introduced semaphore-based synchronization.

Example:

```text
[SEMAPHORE] Initialized. Count: 1 / 1
[SEMAPHORE] Acquired. Count: 0 / 1
[SEMAPHORE] Released. Count: 1 / 1
```

In the integrated application, the semaphore represents the availability of sensor data.

```text
Sensor
   │
   ▼
Queue Data
   │
   ▼
Release Semaphore
   │
   ▼
Processing
   │
   ▼
Acquire Semaphore
   │
   ▼
Receive Data
```

---

# 🔒 Mutex

Day 11 introduced mutex-based mutual exclusion.

The mutex tracks which task currently owns the lock.

Example:

```text
[MUTEX] Task 2 acquired mutex.
[MUTEX] Task 2 released mutex.
```

The integrated application uses the mutex to protect the shared processed result.

```text
Processing
    │
    ▼
Acquire Mutex
    │
    ▼
Update Shared Result
    │
    ▼
Release Mutex
    │
    ▼
Logger
    │
    ▼
Acquire Mutex
    │
    ▼
Read Shared Result
    │
    ▼
Release Mutex
```

---

# 📬 FIFO Message Queue

Day 12 introduced a FIFO message queue for inter-task communication.

Example:

```text
[QUEUE] Message queue initialized. Capacity: 8
```

Sending:

```text
[QUEUE] Message sent: 25 | Messages: 1 / 8
```

Receiving:

```text
[QUEUE] Message received: 25 | Messages: 0 / 8
```

The queue supports:

- Queue initialization
- Message send
- Message receive
- Message counting
- Empty detection
- Full detection
- FIFO data ordering

The queue enables producer-consumer communication between the Sensor and Processing tasks.

---

# 🔗 Full Kernel & IPC Integration

Day 13 integrated the major MiniRTOS components into one complete application.

```text
Sensor Task
     │
     ▼
Generate Sensor Value
     │
     ▼
Message Queue
     │
     ▼
Release Semaphore
     │
     ▼
Processing Task
     │
     ▼
Acquire Semaphore
     │
     ▼
Receive Queue Message
     │
     ▼
Process Data
     │
     ▼
Acquire Mutex
     │
     ▼
Update Shared Result
     │
     ▼
Release Mutex
     │
     ▼
Logger Task
     │
     ▼
Acquire Mutex
     │
     ▼
Read Shared Result
     │
     ▼
Release Mutex
```

During the integration test:

```text
Sensor Value 25 → Processed Result 50
Sensor Value 30 → Processed Result 60
Sensor Value 35 → Processed Result 70
Sensor Value 40 → Processed Result 80
```

The scheduler executes:

```text
Sensor → Processing → Logger → Idle
```

across four complete Round-Robin sequences.

---

# 📊 Integration Test Result

The final integrated demo produced:

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

This confirms that:

- 4 samples were generated.
- All 4 samples were processed.
- The Logger executed 4 times.
- The queue was empty after processing.
- The semaphore returned to zero.
- The mutex was correctly released.
- The final processed result was 80.

---

# 🧪 Unit Testing

Day 14 introduced unit testing for the FIFO message queue.

The test suite verifies:

- Queue initialization
- Initial empty state
- Message sending
- Queue count after sending
- Message receiving
- FIFO data integrity
- Empty state after receiving
- Rejection of receive operation on an empty queue

Test result:

```text
=================================
      MiniRTOS Queue Tests
=================================

[PASS] Queue initialization
[PASS] Queue initially empty
[PASS] Send message
[PASS] Queue count after send
[PASS] Receive message
[PASS] FIFO data integrity
[PASS] Queue empty after receive
[PASS] Reject receive from empty queue

=================================
Tests Passed : 8
Tests Failed : 0
=================================

[TEST] All MiniRTOS queue tests passed.
```

### Test Status

```text
8 / 8 Tests Passed ✅
0 Tests Failed
```

This validates the fundamental FIFO queue operations used by the MiniRTOS inter-task communication layer.

---

# 📂 Project Structure

```text
MiniRTOS
│
├── Demo
│   └── main.c
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
├── Tests
│   └── test_queue.c
│
├── Docs
│
├── Makefile
├── .gitignore
└── README.md
```

---

# 🛠️ Technologies Used

| Technology | Purpose |
|---|---|
| C | Kernel and RTOS implementation |
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

Verify that GCC is installed:

```bash
gcc --version
```

## Compile MiniRTOS

From the project root:

```bash
gcc -Wall -Wextra Demo/main.c Kernel/minirtos.c Kernel/task.c Kernel/scheduler.c Kernel/systick.c Port/cortex_m_port.c IPC/semaphore.c IPC/mutex.c IPC/queue.c -o MiniRTOS.exe
```

Run:

```powershell
.\MiniRTOS.exe
```

---

# 🧪 Run Queue Unit Tests

Compile:

```bash
gcc -Wall -Wextra Tests/test_queue.c IPC/queue.c -o test_queue.exe
```

Run:

```powershell
.\test_queue.exe
```

Expected result:

```text
Tests Passed : 8
Tests Failed : 0

[TEST] All MiniRTOS queue tests passed.
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
| Day 13 | Full kernel and IPC integration | ✅ Completed |
| Day 14 | Unit testing, build setup and documentation | ✅ Completed |

> **Current Progress: Day 14 of 14 — MiniRTOS development roadmap completed.**

---

# 📊 Project Status

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
Full System Integration      ██████████ 100%  ✅
Queue Unit Testing           ██████████ 100%  ✅
Build Setup                  ██████████ 100%  ✅
```

### Development Roadmap: 14 / 14 Days Completed ✅

---

# ⚠️ Current Limitations

MiniRTOS is an educational **host-side RTOS kernel simulation**.

The current version does not implement:

- Hardware-based context switching
- Actual ARM Cortex-M register save and restore
- PendSV-based context switching
- Hardware SysTick interrupts
- Preemptive multitasking
- Per-task hardware stacks
- Hardware interrupt handling
- Priority inheritance
- Dynamic memory management
- Automatic IPC wait queues

The context manager logically simulates task transitions rather than physically switching CPU execution contexts.

The semaphore and mutex implementations demonstrate synchronization concepts but do not yet automatically block and wake waiting tasks.

The message queue uses a fixed-size FIFO buffer and does not automatically block producers or consumers when full or empty.

The strict priority scheduler may repeatedly execute the highest-priority READY task, potentially causing lower-priority task starvation.

---

# 🚀 Future Improvements

MiniRTOS could be extended with:

- Hardware SysTick integration
- PendSV-based context switching
- Real Cortex-M task stacks
- Preemptive scheduling
- Priority inheritance
- Dynamic memory management
- Blocking message queues
- Task wait queues
- Expanded kernel and IPC unit tests
- STM32 hardware deployment

A future hardware port could target:

```text
STM32F103C8T6
ARM Cortex-M3
```

Potential hardware execution flow:

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
Store Stack Pointer
      │
      ▼
Select Next Task
      │
      ▼
Load Stack Pointer
      │
      ▼
Restore Context
      │
      ▼
Resume Task
```

---

# 🎯 Learning Outcomes

This project provided practical exposure to:

- RTOS kernel architecture
- Modular embedded C development
- Task Control Blocks
- Task creation and registration
- Function pointers
- Task priorities
- Task state management
- Cooperative scheduling
- Round-Robin scheduling
- Priority-based scheduling
- System Tick architecture
- Tick-based task delays
- Automatic task wake-up
- Context switching concepts
- Cortex-M port abstraction
- Semaphores
- Mutexes
- Mutual exclusion
- FIFO message queues
- Producer-consumer communication
- Inter-task communication
- Kernel and IPC integration
- Scheduler-driven application execution
- Shared-data protection
- Runtime system statistics
- Unit testing in C
- Build automation concepts
- GCC-based development
- Git and GitHub version control

---

# 📌 Technical Note

MiniRTOS is designed as an educational implementation for understanding RTOS internals.

The completed host-side version demonstrates the logical architecture of:

```text
Kernel
Task Manager
Scheduler
System Tick
Task Delays
Context Management
Cortex-M Port Abstraction
Semaphores
Mutexes
Message Queues
IPC Integration
Unit Testing
```

It does not currently perform true hardware-level context switching on an ARM Cortex-M processor.

The project provides a foundation for future development toward a hardware-based RTOS implementation.

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

MiniRTOS was developed to move beyond simply using existing RTOS APIs and instead explore how fundamental operating-system mechanisms can be designed from scratch.

The project followed a structured **14-day development roadmap**, progressively introducing kernel architecture, task management, scheduling, timing, context management, synchronization, mutual exclusion, inter-task communication, full system integration, unit testing, and build setup.

By implementing these mechanisms individually and integrating them into a complete application pipeline, the project builds a practical understanding of the software architecture underlying embedded Real-Time Operating Systems.

---

<div align="center">

### ⚙️ MiniRTOS

**Building RTOS concepts from scratch in C — one subsystem at a time.**

### 🎉 Development Roadmap Completed

### Day 14 / 14 ✅


</div>