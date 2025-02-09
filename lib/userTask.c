#include "stdint.h"
#include "standardIO.h"
#include "standardLib.h"
#include "kernel.h"
#include "event.h"
#include "message.h"

#define ESC 27

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

void messageTask0(void){
    printingFormat("Message Task0\n");
    
    uint8_t buffer[16];
    uint32_t bufferIndex = 0;
    uint8_t uartCh = 0;
    while(TRUE){
        KernelEventFlag_t handleEvent = Kernel_WaitEvents(KernelEventFlag_MessageIn);
        Kernel_ReceiveMessage(KernelMessageQ_Task0, &uartCh, 1);
        switch(handleEvent){
            case KernelEventFlag_MessageIn:
                if(uartCh == ESC){
                    buffer[bufferIndex] = '\0';

                    Kernel_SendMessage(KernelMessageQ_Task1, &bufferIndex, 1);
                    Kernel_SendMessage(KernelMessageQ_Task1, buffer, bufferIndex);
                    Kernel_SendEvents(KernelEventFlag_MessageOut);

                    printingString("MessageOut Event\n");
                    bufferIndex = 0;
                    
                } else{
                    buffer[bufferIndex] = uartCh;
                    bufferIndex++;
                    bufferIndex %= 16;
                }
                break;
        }
        Kernel_KernelYeild();
    }
};

void messageTask1(void){
    printingFormat("Message Task1\n");
    
    uint8_t commandLength = 0;
    uint8_t command[16];
    while(TRUE){
        KernelEventFlag_t handleEvent = Kernel_WaitEvents(KernelEventFlag_MessageOut);
        switch(handleEvent){
            case KernelEventFlag_MessageOut:
                memoryClear(command, 16);
                Kernel_ReceiveMessage(KernelMessageQ_Task1, &commandLength, 1);
                Kernel_ReceiveMessage(KernelMessageQ_Task1, command, commandLength);
                printingFormat("Received command: %s\n", command);
                break;
        }
        Kernel_KernelYeild();
    }
};