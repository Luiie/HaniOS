#include "stdint.h"
#include "event.h"

static uint32_t eventFlag;

void Kernel_EventFlagInit(void){
    eventFlag = 0;
};

void Kernel_EventFlagSet(KernelEventFlag_t event){
    eventFlag |= (uint32_t)event;
};

void Kernel_EventFlagClear(KernelEventFlag_t event){
    eventFlag &= ~((uint32_t)event);
};

bool Kernel_EventFlagCheck(KernelEventFlag_t event){
    if(eventFlag & (uint32_t)event){
        Kernel_EventFlagClear(event);
        return TRUE;
    }
    return FALSE;
};