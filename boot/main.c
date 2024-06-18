#include "stdint.h"
#include "HAL_Uart.h"

static void HW_init(void);

void main(void)
{
    uint32_t* dummyAddr = (uint32_t*) (1024*1024*100);
    *dummyAddr = sizeof(long);

    HW_init();
    uint32_t i = 100;
    while(i--){
        HAL_UART_put_char('A');
    }
}

static void HW_init(void){
    HAL_UART_init();
};