#ifndef KERNEL_MESSAGE_H_
#define KERNEL_MESSAGE_H_

#include "stdbool.h"

#define MESSAGE_Q_SIZE_BYTE     512

typedef enum KernelMessageQ_t
{
    KernelMessageQ_Task0,
    KernelMessageQ_Task1,
    KernelMessageQ_Task2,

    KernelMessageQ_Num
} KernelMessageQ_t;

typedef struct KernelCircleQ_t
{
    uint32_t front;
    uint32_t rear;
    uint8_t  Queue[MESSAGE_Q_SIZE_BYTE];
} KernelCircleQ_t;

void 	 Kernel_MessageQInit(void);
bool 	 Kernel_MessageQIsEmpty(KernelMessageQ_t QName);
bool 	 Kernel_MessageQIsFull(KernelMessageQ_t QName);
bool 	 Kernel_MessageQEnqueue(KernelMessageQ_t QName, uint8_t data);
bool 	 Kernel_MessageQDequeue(KernelMessageQ_t QName, uint8_t* outData);
uint32_t Kernel_MessageQCount(KernelMessageQ_t QName);

#endif /* KERNEL_MESSAGE_H_ */