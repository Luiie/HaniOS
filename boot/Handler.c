#include "stdint.h"
#include "HAL_Interrupt.h"

__attribute__ ((interrupt ("IRQ"))) void IRQHandler(void){
    HAL_InterruptRunHandler();
}

__attribute__ ((interrupt ("FIQ"))) void FIQHandler(void){
    while(TRUE);
}