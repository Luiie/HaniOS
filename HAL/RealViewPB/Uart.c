#include "stdint.h"
#include "Uart.h"
#include "HAL_Uart.h"

//connect HW register struct to base address
    //PL011_t, UART of RealViewPB platform
extern volatile PL011_t* Uart;

void HAL_UART_init(void){
    Uart->uartcr.bits.UARTEN = 0;
    Uart->uartcr.bits.TXE = 1;
    Uart->uartcr.bits.RXE = 1;
    Uart->uartcr.bits.UARTEN = 1;
};
void HAL_UART_put_char(uint8_t ch){
    while(Uart->uartfr.bits.TXFF);
    Uart->uartdr.all = (ch & 0xFF);
};