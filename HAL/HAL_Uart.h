#ifndef HAL_UART_H_
#define HAL_UART_H_

void HAL_UartInit(void);
void HAL_UartPutChar(uint8_t ch);
uint8_t HAL_UartGetChar(void);

#endif /* HAL_UART_H_ */