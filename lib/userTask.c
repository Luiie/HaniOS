#include "stdint.h"
#include "standardIO.h"
#include "kernel.h"
#include "event.h"

void dummyTask0(void){
    uint32_t local = 0;
    
    printingFormat("Dummy Task0, Stack Pointer=0x%h", &local);
    
    while(TRUE){
        bool pendingEvent = TRUE;
        while(pendingEvent){
            KernelEventFlag_t handleEvent = Kernel_WaitEvents(KernelEventFlag_MtIn|KernelEventFlag_MtOut);
            switch(handleEvent){
                case KernelEventFlag_MtIn:
                    printingString("MtIn Event sent from Task0\n");
                    break;
                case KernelEventFlag_MtOut:
                    printingString("MtOut Event sent from Task0\n");
                    break;
                default:
                    pendingEvent = FALSE;
                    break;
            }
        }
        Kernel_KernelYeild();
    }
};

void dummyTask1(void){
    uint32_t local = 0;

    printingFormat("Dummy Task1, Stack Pointer=0x%h", &local);
    
    while(TRUE){
        KernelEventFlag_t handleEvent = Kernel_WaitEvents(KernelEventFlag_UartIn);
        switch(handleEvent){
            case KernelEventFlag_UartIn:
                Kernel_SendEvents(KernelEventFlag_CmdIn);
                printingString("CmdIn Event sent from Task1\n");
                break;
        }
        Kernel_KernelYeild();
    }
};

void dummyTask2(void){
    uint32_t local = 0;

    printingFormat("Dummy Task2, Stack Pointer=0x%h\n", &local);
    
    while(TRUE){
        KernelEventFlag_t handleEvent = Kernel_WaitEvents(KernelEventFlag_CmdIn);
        switch(handleEvent){
            case KernelEventFlag_CmdIn:
                printingString("CmdIn Event got to Task2\n");
                break;
        }
        Kernel_KernelYeild();
    }
};
