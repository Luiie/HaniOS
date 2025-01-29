#include "stdint.h"
#include "ARMv7AR.h"
#include "task.h"

static KernelTcb_t TaskList[MAX_TASK_NUM];
static uint32_t allocatedTCBIndex;

void Kernel_TaskInit(void){
    allocatedTCBIndex = 0;

    for(uint32_t i = 0 ; i < MAX_TASK_NUM ; i++){
        TaskList[i].stackBase = (uint8_t *)(TASK_STACK_START + (i * USR_TASK_STACK_SIZE));
        TaskList[i].stackPointer = (uint32_t *)(TaskList[i].stackBase + USR_TASK_STACK_SIZE - 4);
        
        KernelTaskContext_t *context = (KernelTaskContext_t *) TaskList[i].stackPointer;
        context->pc = 0;
        context->spsr = ARM_MODE_BIT_SYS;
    }
};

uint32_t Kernel_TaskCreate(KernelTaskFunc_t startFunction){
    KernelTcb_t * newTCB = &TaskList[allocatedTCBIndex++];

    if(allocatedTCBIndex > MAX_TASK_NUM){
        return NOT_ENOUGH_TASK_NUM;
    }

    KernelTaskContext_t *context = (KernelTaskContext_t *) newTCB.stackPointer;
    context->pc = (uint32_t)startFunction;

    return allocatedTCBIndex - 1;
};