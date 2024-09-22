#ifndef HAL_INTERRUPT_H_
#define HAL_INTERRUPT_H_

#define INTERRUPT_HANDLER_NUM 255

typedef void (*InterruptHandler_fptr)(void);

void HAL_INTERRUPT_init(void);
void HAL_INTERRUPT_enable(uint32_t interrupt_num);
void HAL_INTERRUPT_disable(uint32_t interrupt_num);
void HAL_INTERRUPT_register_handler(InterruptHandler_fptr handler, uint32_t interrupt_num);
void HAL_INTERRUPT_run_handler(void);

#endif /* HAL_INTERRUPT_H_ */