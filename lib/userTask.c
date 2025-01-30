#include "stdint.h"
#include "standardIO.h"
#include "kernel.h"
#include "event.h"

void dummyTask0(void){
    uint32_t local = 0;
    
    printingFormat("Dummy Task0, Stack Pointer=0x%h", &local);
    
    for(uint32_t i = 0; i < 5 ; i++){
        KernelEventFlag_t handleEvent = Kernel_WaitEvents(KernelEventFlag_UartIn);
        switch(handleEvent){
            case KernelEventFlag_UartIn:
                printingString("Event handled!");
                break;
        }
        Kernel_KernelYeild();
    }
};

void dummyTask1(void){
    uint32_t local = 0;

    for(uint32_t i = 0; i < 5 ; i++){
        printingFormat("Dummy Task1, Stack Pointer=0x%h", &local);
        Kernel_KernelYeild();
    }
};

void dummyTask2(void){
    uint32_t local = 0;

    for(uint32_t i = 0; i < 5 ; i++){
        printingFormat("Dummy Task2, Stack Pointer=0x%h", &local);
        Kernel_KernelYeild();
    }
};
