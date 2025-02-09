#include "stdint.h"
#include "stdbool.h"

#include "message.h"

static KernelCircleQ_t MessageQ[KernelMessageQ_Num];

void Kernel_MessageQInit(void){
    for(uint32_t i = 0 ; i < KernelMessageQ_Num ; i++){
        MessageQ[i].front = 0;
        MessageQ[i].rear = 0;
        memoryClear(MessageQ[i].Queue, MESSAGE_Q_SIZE_BYTE);
    }
};

bool Kernel_MessageQIsEmpty(KernelMessageQ_t QName){
    if(QName >= KernelMessageQ_Num){
        return FALSE;
    }

    if(MessageQ[QName].front == MessageQ[QName].rear){
        return TRUE;
    }

    return FALSE;
};

bool Kernel_MessageQIsFull(KernelMessageQ_t QName){
    if(QName >= KernelMessageQ_Num){
        return FALSE;
    }

    if(((MessageQ[QName].rear + 1) % MESSAGE_Q_SIZE_BYTE) == MessageQ[QName].front){
        return TRUE;
    }

    return FALSE;
};

bool Kernel_MessageQEnqueue(KernelMessageQ_t QName, uint8_t data){
    if(QName >= KernelMessageQ_Num){
        return FALSE;
    }

    if(Kernel_MessageQIsFull(QName)){
        return FALSE;
    }

    MessageQ[QName].rear++;
    MessageQ[QName].rear %= MESSAGE_Q_SIZE_BYTE;
    
    uint32_t index = MessageQ[QName].rear;
    MessageQ[QName].Queue[index] = data;

    return TRUE;
};

bool Kernel_MessageQDequeue(KernelMessageQ_t QName, uint8_t* outData){
    if(QName >= KernelMessageQ_Num){
        return FALSE;
    }

    if(Kernel_MessageQIsEmpty(QName)){
        return FALSE;
    }

    MessageQ[QName].front++;
    MessageQ[QName].front %= MESSAGE_Q_SIZE_BYTE;
    
    uint32_t index = MessageQ[QName].front;
    *outData = MessageQ[QName].Queue[index];

    MessageQ[QName].Queue[index] = 0; //clear data

    return TRUE;
};

uint32_t Kernel_MessageQCount(KernelMessageQ_t QName){
    if(MessageQ[QName].rear >= KernelMessageQ_Num){
        return MessageQ[QName].rear - MessageQ[QName].front;
    }
    return 0xFFFF;
};