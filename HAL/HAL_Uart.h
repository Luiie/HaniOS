#ifndef HAL_UART_H_
#define HAL_UART_H_

void HAL_UART_init(void);
void HAL_UART_put_char(uint8_t ch);
uint8_t HAL_UART_get_char(void);

#endif /* HAL_UART_H_ */