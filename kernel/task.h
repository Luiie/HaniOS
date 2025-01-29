#ifndef KERNEL_TASK_H_
#define KERNEL_TASK_H_

#include "MemoryMap.h"

#define NOT_ENOUGH_TASK_NUM 0xFFFFFFFF
#define MAX_TASK_NUM (TASK_STACK_SIZE / USR_TASK_STACK_SIZE) // 64 tasks

typedef struct KernelTaskContext_t
{
    uint32_t spsr;
    uint32_t r0_r12[13];
    uint32_t pc;
} KernelTaskContext_t;

typedef struct KernelTcb_t
{
    uint32_t* stackPointer;
    uint8_t* stackBase;
    uint8_t priority;
} KernelTcb_t;

typedef void (*KernelTaskFunc_t)(void);

void Kernel_TaskInit(void);
uint32_t Kernel_TaskCreate(KernelTaskFunc_t startFunction, uint8_t priority);
void Kernel_TaskScheduler(void);
void Kernel_TaskStart(void);

#endif