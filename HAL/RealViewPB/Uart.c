#include "stdint.h"
#include "Uart.h"
#include "HAL_Uart.h"
#include "HAL_Interrupt.h"

//connect HW register struct to base address
    //PL011_t, UART of RealViewPB platform
extern volatile PL011_t* Uart;

static void InterruptHandler(void);

void HAL_UART_init(void){
    // Enable UART
    Uart->uartcr.bits.UARTEN = 0;
    Uart->uartcr.bits.TXE = 1;
    Uart->uartcr.bits.RXE = 1;
    Uart->uartcr.bits.UARTEN = 1;

    // Register UART Interrupt Handler
        //[HAL\RealViewPB\Uart.h] #define UART_INTERRUPT0 44
    HAL_INTERRUPT_enable(UART_INTERRUPT0);
    HAL_INTERRUPT_register_handler(InterruptHandler, UART_INTERRUPT0);
};

void HAL_UART_put_char(uint8_t ch){
    while(Uart->uartfr.bits.TXFF);
    Uart->uartdr.all = (ch & 0xFF);
};

uint8_t HAL_UART_get_char(void){
    uint8_t data;

    while(Uart->uartfr.bits.RXFE);

    // Check for Error flages
    data = Uart->uartdr.all;
    if(data & 0xFFFFFF00){
        // Clear Error flages
        Uart->uartdr.all = 0xFF;
        return 0;
    }
    
    return (uint8_t) (data & 0xFF);
};

static void InterruptHandler(void){
    uint8_t ch = HAL_UART_get_char();
    HAL_UART_put_char(ch);
};