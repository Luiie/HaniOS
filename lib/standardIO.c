#include "stdint.h"
#include "stdarg.h"
#include "HAL_Uart.h"
#include "standardIO.h"

#define ESC 27
#define PRINTINGFORMAT_BUFFER_LENGTH  1024
static char printingFormat_buffer[PRINTINGFORMAT_BUFFER_LENGTH];   // 1KB

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
    uint32_t ch;
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

uint32_t printingFormat(const char* format, ...){
    va_list args;
    va_start(args, format);
    printFormatString(printingFormat_buffer, format, args);
    va_end(args);

    return printingString(printingFormat_buffer);
}

uint32_t printFormatString(char* buffer, const char* format, va_list arg){
    uint32_t counter = 0;
    
    char ch;
    char* str;
    uint32_t unint;
    uint32_t hex;
    uint32_t bin;

    for( uint32_t i = 0 ; format[i] ; i++){
        if (format[i] == '%'){
            i++;
            switch(format[i]){
                case 'c':
                    // read va_list, arg and just print it
                    ch = (char) va_arg(arg, int32_t);
                    buffer[counter++] = ch;
                    break;
                case 's':
                    str = (char*) va_arg(arg, char*);
                    // NULL pointer Error
                    if(str == NULL){
                        str = "(null)";
                    }
                    while(*str){
                        buffer[counter++] = (*str++);
                    }
                    break;
                case 'd':
                    unint = (uint32_t) va_arg(arg, uint32_t);
                    counter += toASCII(&buffer[counter], unint, toASCII_dec);
                    break;
                case 'h':
                    hex = (uint32_t) va_arg(arg, uint32_t);
                    counter += toASCII(&buffer[counter], hex, toASCII_hex);
                    break;
                case 'b':
                    bin = (uint32_t) va_arg(arg, uint32_t);
                    counter += toASCII(&buffer[counter], bin, toASCII_bin);
                    break;
            }
        }
        else{
            buffer[counter++] = format[i];
        }
    }

    if( counter >= PRINTINGFORMAT_BUFFER_LENGTH){
        buffer[0] = '\0';
        return 0;
    }

    buffer[counter] = '\0';
    return counter;
}

uint32_t toASCII(char* buffer, uint32_t value, toASCII_t base){
    uint32_t counter = 0;
    int32_t index = 0;
    char tmp[33]; //32-bit size data does not exceed 11 decimal digits, but binary!

    // Convert value to base notation, tmp[]
    do{
        uint32_t t = value % (uint32_t) base;
        // When in hexadecimal
        if(t >= 10){
            t += 'A' - '0' - 10; // 'A'=65 ,'0'=48
        }
        // Convert number t to ASCII
        tmp[index] = (t + '0');
        value /= base;
        index++;
    } while(value);

    // Using the reverse order, tmp[] as a string buffer
    index--;
    while(index >= 0){
        buffer[counter++] = tmp[index];
        index--;
    };

    return counter;
}