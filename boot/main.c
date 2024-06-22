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

    // HAL_UART_put_char & HAL_UART_get_char
    uint32_t i = 10;
    while(i--){
        uint32_t ch = HAL_UART_get_char();
        HAL_UART_put_char(ch);
    };
}

static void HW_init(void){
    HAL_UART_init();
};