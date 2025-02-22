#include "stdint.h"
#include "Uart.h"
#include "HAL_Uart.h"
#include "HAL_Interrupt.h"
#include "kernel.h"
#include "userTask.h"

//connect HW register struct to base address
    //PL011_t, UART of RealViewPB platform
extern volatile PL011_t* Uart;

static void InterruptHandler(void);

void HAL_UartInit(void){
    // Enable UART
    Uart->uartcr.bits.UARTEN = 0;
    Uart->uartcr.bits.TXE = 1;
    Uart->uartcr.bits.RXE = 1;
    Uart->uartcr.bits.UARTEN = 1;

    //Enable Input Interrupt
    Uart->uartimsc.bits.RXIM = 1;
    
    // Register UART Interrupt Handler
        //[HAL\RealViewPB\Uart.h] #define UART_INTERRUPT0 44
    HAL_InterruptEnable(UART_INTERRUPT0);
    HAL_InterruptRegisterHandler(InterruptHandler, UART_INTERRUPT0);
};

void HAL_UartPutChar(uint8_t ch){
    while(Uart->uartfr.bits.TXFF);
    Uart->uartdr.all = (ch & 0xFF);
};

uint8_t HAL_UartGetChar(void){
    uint32_t data;

    while(Uart->uartfr.bits.RXFE);
    
    data = Uart->uartdr.all;

    // Check for Error flages
    if(data & 0xFFFFFF00){
        // Clear Error flages
        Uart->uartrsr.all = 0xFF;
        return 0;
    }
    
    return (uint8_t) (data & 0xFF);
};

static void InterruptHandler(void){
    uint8_t ch = HAL_UartGetChar();
    HAL_UartPutChar(ch);

    Kernel_SendEvents(KernelEventFlag_UartIn|KernelEventFlag_MtIn);
    if(ch == 'x'){
        Kernel_SendEvents(KernelEventFlag_MtOut);
    }

    Kernel_SendMessage(KernelMessageQ_Task0, &ch, 1);
    Kernel_SendEvents(KernelEventFlag_MessageIn);

};