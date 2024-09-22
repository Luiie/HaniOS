#include "stdint.h"
#include "HAL_Timer.h"

void delay(uint32_t ms){
    uint32_t goal = HAL_TIMER_get1msCounter() + ms;
    while(goal != HAL_TIMER_get1msCounter());
}