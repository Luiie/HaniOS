#include "stdint.h"
#include "Uart.h"
#include "HAL_Uart.h"
#include "Interrupt.h"

//connect HW register struct to base address
    //PL011_t, UART of RealViewPB platform
volatile PL011_t* Uart = (PL011_t*) UART_BASE_ADDRESS0;
volatile GicCput_t* GicCpu = (GicCput_t*)GIC_CPU_BASE;
volatile GicDist_t* GicDist = (GicDist_t*)GIC_DIST_BASE;