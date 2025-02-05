#ifndef KERNEL_KERNEL_H_
#define KERNEL_KERNEL_H_

#include "event.h"
#include "stdbool.h"
#include "message.h"

void Kernel_KernelStart(void);
void Kernel_KernelYeild(void);
void Kernel_KernelInit(void);

void Kernel_SendEvents(uint32_t eventList);
KernelEventFlag_t Kernel_WaitEvents(uint32_t eventList);

bool Kernel_SendMessage(KernelMessageQ_t QName, void* data, uint32_t count);
uint32_t Kernel_ReceiveMessage(KernelMessageQ_t QName, void* outData, uint32_t count);

#endif /* KERNEL_KERNEL_H_ */