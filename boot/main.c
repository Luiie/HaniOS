#include "stdint.h"
#include "HAL_Uart.h"
#include "standardIO.h"
#include "HAL_Interrupt.h"
#include "standardLib.h"
#include "HAL_Timer.h"
#include "kernel.h"
#include "event.h"

static void HwInit(void);
static void PrintTest(void);
static void GetTimerSysCtrl0(void);
static void TimerTest(void);

void main(void)
{
    // write 0x00000004 at 0x6400000
    uint32_t* dummyAddr = (uint32_t*) (1024*1024*100);
    *dummyAddr = sizeof(long);

    // UART init
    HwInit();

    // printString from standardIO
    uint32_t result = printingString("Hello, world!");
    uint32_t result1 = printingString("test");

    // gettingString from standardIO
    // uint32_t result2 = gettingString();

    // printingFormat from standardIO
    PrintTest();

    //Timer Test
    GetTimerSysCtrl0();
    TimerTest();

    Kernel_KernelInit();

    // while loop
    while(TRUE);
}

static void HwInit(void){
    HAL_InterruptInit();
    HAL_UartInit();
    HAL_TimerInit();
};

static void PrintTest(void){
    char* test_str = "printingFormat pointer test";
    char* test_nullptr = 0;
    uint32_t test_i = 5;

    printingFormat("%s", "Hello printingFormat");
    printingFormat("string pointer: %s", test_str);
    printingFormat("null pointer: %s", test_nullptr);
    printingFormat("%c", 'A');
    printingFormat("%d", test_i);
    printingFormat("%h", test_i);
    printingFormat("%b", test_i);
    printingFormat("zero: %d", 0);
    printingString("\n");
};

static void TimerTest(void){
    for(uint32_t i = 0; i < 4 ; i++){
        printingFormat("current count: %d\n", HAL_TimerGet1msCounter());
        delay(1000);
    };
};

static void GetTimerSysCtrl0(void){
    uint32_t* timerSysCtrl0 = (uint32_t*)0x10001000;

    printingFormat("sysCtrl0: %h", *timerSysCtrl0);
}