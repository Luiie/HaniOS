#include "stdint.h"
#include "HAL_Timer.h"

void delay(uint32_t ms){
    uint32_t goal = HAL_TimerGet1msCounter() + ms;
    while(goal != HAL_TimerGet1msCounter());
}

void memoryClear(void* destination, uint32_t count)
{
    uint8_t* tmpDestination = (uint8_t*)destination;

    while(count--)
    {
        *tmpDestination++ = 0;
    }
}