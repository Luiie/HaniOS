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

uint8_t HAL_UART_get_char(void);{
    uint8_t data;

    while(Uart->uartfr.bits.RXFE);

    // Check for Error flages
    if(Uart->uartdr.bits.BE || Uart->uartdr.bits.FE || Uart->uartdr.bits.OE || Uart->uartdr.bits.PE){
        // Clear Error flages
        Uart->uartdr.bits.BE = 1;
        Uart->uartdr.bits.FE = 1;
        Uart->uartdr.bits.OE = 1;
        Uart->uartdr.bits.PE = 1;
        return 0;
    }

    data = Uart->uartdr.bits.DATA;
    return data;
}