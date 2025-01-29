#include "stdint.h"
#include "kernel.h"

void Kernel_KernelYeild(void){
    Kernel_TaskScheduler();
};