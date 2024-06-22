#include "stdint.h"
#include "HAL_Uart.h"
#include "standardIO.h"
#define ESC 27

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

uint32_t gettingString(void){
    uint32_t counter = 0;

    // HAL_UART_put_char & HAL_UART_get_char
    uint32_t ch = 0;
    HAL_UART_put_char('\n');
    while(1){
        ch = HAL_UART_get_char();
        // End when the ESC key is enterd
        if(ch == ESC){
            HAL_UART_put_char('\n');
            break;
        };
        HAL_UART_put_char(ch);
        counter++;
    };

    return counter;
}
