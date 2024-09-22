#include "stdint.h"
#include "Timer.h"
#include "Hal_Timer.h"
#include "Hal_Interrupt.h"

extern volatile Timer_t* Timer;

void HAL_TIMER_init(void)
{
    // inerface reset
    Timer->timerxcontrol.bits.TimerEn = 0;
    Timer->timerxcontrol.bits.TimerMode = 0;
    Timer->timerxcontrol.bits.OneShot = 0;
    Timer->timerxcontrol.bits.TimerSize = 0;
    Timer->timerxcontrol.bits.TimerPre = 0;
    Timer->timerxcontrol.bits.IntEnable = 1;
    Timer->timerxload = 0;
    Timer->timerxvalue = 0xFFFFFFFF;

    // set periodic mode
    Timer->timerxcontrol.bits.TimerMode = TIMER_PERIOIC;
    Timer->timerxcontrol.bits.TimerSize = TIMER_32BIT_COUNTER;
    Timer->timerxcontrol.bits.OneShot = 0;
    Timer->timerxcontrol.bits.TimerPre = 0;
    Timer->timerxcontrol.bits.IntEnable = 1;

    uint32_t interval_1ms = TIMER_1MZ_INTERVAL / 1000;

    Timer->timerxload = interval_1ms;
    Timer->timerxcontrol.bits.TimerEn = 1;
}