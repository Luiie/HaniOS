#include "stdint.h"
#include "ARMv7AR.h"
#include "ARMswitch.h"
#include "standardIO.h"
#include "task.h"
#include "kernel.h"

static KernelTcb_t TaskList[MAX_TASK_NUM];
static uint32_t allocatedTCBIndex;
static uint32_t currentTCBIndex;

static KernelTcb_t* Scheduler_RoundRobinAlgorithm(void);
static KernelTcb_t* Scheduler_PriorityAlgorithm(void);

KernelTcb_t* currentTCB;
KernelTcb_t* nextTCB;

void Kernel_TaskInit(void){
    allocatedTCBIndex = 0;
    currentTCBIndex = 0;

    for(uint32_t i = 0 ; i < MAX_TASK_NUM ; i++){
        TaskList[i].stackBase = (uint8_t *)(TASK_STACK_START + (i * USR_TASK_STACK_SIZE));
        TaskList[i].stackPointer = (uint32_t *)(TaskList[i].stackBase + USR_TASK_STACK_SIZE - 4);
        TaskList[i].priority = 0x00;
        
        KernelTaskContext_t *context = (KernelTaskContext_t *) TaskList[i].stackPointer;
        context->pc = 0;
        context->spsr = ARM_MODE_BIT_SYS;
    }
};

uint32_t Kernel_TaskCreate(KernelTaskFunc_t startFunction, uint8_t priority){
    KernelTcb_t * newTCB = &TaskList[allocatedTCBIndex++];

    if(allocatedTCBIndex > MAX_TASK_NUM){
        return NOT_ENOUGH_TASK_NUM;
    }

    newTCB->priority = priority;

    KernelTaskContext_t *context = (KernelTaskContext_t *) newTCB->stackPointer;
    context->pc = (uint32_t)startFunction;

    return allocatedTCBIndex - 1;
};

void Kernel_TaskScheduler(void){
    currentTCB = &TaskList[currentTCBIndex];
    nextTCB = Scheduler_RoundRobinAlgorithm();

    ContextSwitching();
};

void Kernel_TaskStart(void){
    nextTCB = &TaskList[currentTCBIndex];

    RestoreContext();
};


void dummyTask0(void){
    uint32_t local = 0;

    while(TRUE){
        printingFormat("Dummy Task0, Stack Pointer=0x%h", &local);
        Kernel_KernelYeild();
    }
};

void dummyTask1(void){
    uint32_t local = 0;

    while(TRUE){
        printingFormat("Dummy Task1, Stack Pointer=0x%h", &local);
        Kernel_KernelYeild();
    }
};

void dummyTask2(void){
    uint32_t local = 0;

    while(TRUE){
        printingFormat("Dummy Task2, Stack Pointer=0x%h", &local);
        Kernel_KernelYeild();
    }
};


static KernelTcb_t* Scheduler_RoundRobinAlgorithm(void){
    currentTCBIndex++;
    currentTCBIndex %= allocatedTCBIndex;

    return &TaskList[currentTCBIndex];
};

static KernelTcb_t* Scheduler_PriorityAlgorithm(void){
    for(uint32_t i = 0 ; i < allocatedTCBIndex ; i++){
        KernelTcb_t * tmpNextTCB = &TaskList[i];
        if(tmpNextTCB != currentTCB){
            if(tmpNextTCB->priority <= currentTCB->priority){
                return tmpNextTCB;
            }
        }
    }
    return currentTCB;
};