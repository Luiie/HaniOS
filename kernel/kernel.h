#ifndef KERNEL_KERNEL_H_
#define KERNEL_KERNEL_H_

#include "event.h"

void Kernel_KernelStart(void);
void Kernel_KernelYeild(void);
void Kernel_KernelInit(void);

void Kernel_SendEvents(uint32_t eventList);
KernelEventFlag_t Kernel_WaitEvents(uint32_t eventList);

#endif /* KERNEL_KERNEL_H_ */