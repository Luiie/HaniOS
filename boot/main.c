#include "stdint.h"
#include "HAL_Uart.h"
#include "standardIO.h"

static void HW_init(void);

void main(void)
{
    // write 0x00000004 at 0x6400000
    uint32_t* dummyAddr = (uint32_t*) (1024*1024*100);
    *dummyAddr = sizeof(long);

    // UART init
    HW_init();

    // printString from standardIO
    uint32_t result = printingString("Hello, world!");

    // gettingString  from standardIO
    uint32_t result2 = gettingString();
}

static void HW_init(void){
    HAL_UART_init();
};