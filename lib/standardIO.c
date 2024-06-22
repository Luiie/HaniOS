#include "stdint.h"
#include "HAL_Uart.h"
#include "standardIO.h"

uint32_t printingString(const char* s){
    uint32_t counter = 0;

    // at first, change a line
    HAL_UART_put_char('\n');

    while(*s){
        HAL_UART_put_char(*s++);
        counter++;
    };

    return counter;
};