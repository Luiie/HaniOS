#include "stdint.h"
#include "standardIO.h"
#include "memoryIO.h"
#include "userTask.h"
#include "task.h"
#include "kernel.h"
#include "event.h"

void Kernel_KernelStart(void){
    Kernel_TaskStart();
};

void Kernel_KernelYeild(void){
    Kernel_TaskScheduler();
};

void Kernel_KernelInit(void){
    uint32_t taskId;

    Kernel_TaskInit();
    Kernel_EventFlagInit();

    taskId = Kernel_TaskCreate(dummyTask0, 0xFF);
    if(taskId == NOT_ENOUGH_TASK_NUM){
        printingString("Task0 creation fail!\n");
    }

    taskId = Kernel_TaskCreate(dummyTask1, 0xFF);
    if(taskId == NOT_ENOUGH_TASK_NUM){
        printingString("Task1 creation fail!\n");
    }

    taskId = Kernel_TaskCreate(dummyTask2, 0xFF);
    if(taskId == NOT_ENOUGH_TASK_NUM){
        printingString("Task2 creation fail!\n");
    }

    Kernel_KernelStart();
};

void Kernel_SendEvents(uint32_t eventList){
    KernelEventFlag_t sendingEvent = KernelEventFlag_Empty;
    for (uint32_t i = 0 ; i < MAX_EVENT_NUM ; i++){
        if ((eventList >> i) & 1){
            SET_BIT(sendingEvent, i);
            Kernel_EventFlagSet(sendingEvent);
        }
    }
};

KernelEventFlag_t Kernel_WaitEvents(uint32_t eventList){
    KernelEventFlag_t waitingEvent = KernelEventFlag_Empty;
    for (uint32_t i = 0 ; i < MAX_EVENT_NUM ; i++){
        if ((eventList >> i) & 1){
            SET_BIT(waitingEvent, i);
            if(Kernel_EventFlagCheck(waitingEvent)){
                Kernel_EventFlagClear(waitingEvent);
                return waitingEvent;
            }
        }
    }
    return KernelEventFlag_Empty;
};