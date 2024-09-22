#include "stdint.h"
#include "HAL_Interrupt.h"

__attribute__ ((interrupt ("IRQ"))) void IRQHandler(void){
    HAL_INTERRUPT_run_handler();
}

__attribute__ ((interrupt ("FIQ"))) void FIQHandler(void){
    while(TRUE);
}