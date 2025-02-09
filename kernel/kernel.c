#include "stdint.h"
#include "stdbool.h"
#include "standardIO.h"
#include "memoryIO.h"
#include "userTask.h"
#include "task.h"
#include "kernel.h"
#include "event.h"
#include "message.h"

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

    taskId = Kernel_TaskCreate(messageTask0, 0xFF);
    if(taskId == NOT_ENOUGH_TASK_NUM){
        printingString("MessageTask0 creation fail!\n");
    }

    taskId = Kernel_TaskCreate(messageTask1, 0xFF);
    if(taskId == NOT_ENOUGH_TASK_NUM){
        printingString("MessageTask1 creation fail!\n");
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
    for (uint32_t i = 0 ; i < MAX_EVENT_NUM ; i++){
        KernelEventFlag_t waitingEvent = KernelEventFlag_Empty;
        if ((eventList >> i) & 1){
            SET_BIT(waitingEvent, i);
            if(Kernel_EventFlagCheck(waitingEvent)){
                return waitingEvent;
            }
        }
    }
    return KernelEventFlag_Empty;
};

bool Kernel_SendMessage(KernelMessageQ_t QName, void* data, uint32_t count){
    uint8_t* tmpData = (uint8_t*)data;

    for(uint32_t i = 0 ; i < count ; i++){
        if(!Kernel_MessageQEnqueue(QName, *tmpData)){
            for(uint32_t i = 0 ; i < count ; i++){
                uint8_t* rollback;
                Kernel_MessageQDequeue(QName, rollback);
            }
            return FALSE;
        }
        tmpData++;
    }

    return TRUE;
};

uint32_t Kernel_ReceiveMessage(KernelMessageQ_t QName, void* outData, uint32_t count){
    uint8_t* tmpData = (uint8_t*) outData;

    for(uint32_t i = 0 ; i < count ; i++){
        if(!Kernel_MessageQDequeue(QName, tmpData)){
            return i;
        }
        tmpData++;
    }

    return count;
};