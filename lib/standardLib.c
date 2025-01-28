#include "stdint.h"
#include "HAL_Timer.h"

void delay(uint32_t ms){
    uint32_t goal = HAL_TimerGet1msCounter() + ms;
    while(goal != HAL_TimerGet1msCounter());
}