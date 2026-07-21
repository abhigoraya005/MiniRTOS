CC = gcc

CFLAGS = -Wall -Wextra

TARGET = MiniRTOS.exe

SOURCES = \
	Demo/main.c \
	Kernel/minirtos.c \
	Kernel/task.c \
	Kernel/scheduler.c \
	Kernel/systick.c \
	Port/cortex_m_port.c \
	IPC/semaphore.c \
	IPC/mutex.c \
	IPC/queue.c

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	del /Q $(TARGET)

rebuild: clean all