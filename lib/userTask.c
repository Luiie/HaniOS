#include "stdint.h"
#include "standardIO.h"
#include "kernel.h"

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
