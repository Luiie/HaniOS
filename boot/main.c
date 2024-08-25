#include "stdint.h"
#include "HAL_Uart.h"
#include "standardIO.h"
#include "HAL_Interrupt.h"

static void HW_init(void);
static void PrintTest(void);

void main(void)
{
    // write 0x00000004 at 0x6400000
    uint32_t* dummyAddr = (uint32_t*) (1024*1024*100);
    *dummyAddr = sizeof(long);

    // UART init
    HW_init();

    // printString from standardIO
    uint32_t result = printingString("Hello, world!");

    // gettingString from standardIO
    // uint32_t result2 = gettingString();

    // printingFormat from standardIO
    PrintTest();
    printingString("\n");

    // while loop
    while(TRUE);
}

static void HW_init(void){
    HAL_INTERRUPT_init();
    HAL_UART_init();
};

static void PrintTest(void){
    char* test_str = "printingFormat pointer test";
    char* test_nullptr = 0;
    uint32_t test_i = 5;

    printingFormat("%s", "Hello printingFormat");
    printingFormat("string pointer: %s", test_str);
    printingFormat("null pointer: %s", test_nullptr);
    printingFormat("%c", 'A');
    printingFormat("%d", test_i);
    printingFormat("%h", test_i);
    printingFormat("%b", test_i);
    printingFormat("zero: %d", 0);
};