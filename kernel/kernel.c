#include "stdint.h"
#include "standardIO.h"
#include "userTask.h"
#include "task.h"
#include "kernel.h"

void Kernel_KernelStart(void){
    Kernel_TaskStart();
};

void Kernel_KernelYeild(void){
    Kernel_TaskScheduler();
};

void Kernel_KernelInit(void){
    uint32_t taskId;

    Kernel_TaskInit();

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