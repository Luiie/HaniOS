#include "stdint.h"
#include "Uart.h"
#include "HAL_Uart.h"

//connect HW register struct to base address
    //PL011_t, UART of RealViewPB platform
volatile PL011_t* Uart = (PL011_t*) UART_BASE_ADDRESS0;