#ifndef HAL_INTERRUPT_H_
#define HAL_INTERRUPT_H_

#define INTERRUPT_HANDLER_NUM 255

typedef void (*InterruptHandler_fptr)(void);

void HAL_InterruptInit(void);
void HAL_InterruptEnable(uint32_t interrupt_num);
void HAL_InterruptDisable(uint32_t interrupt_num);
void HAL_InterruptRegisterHandler(InterruptHandler_fptr handler, uint32_t interrupt_num);
void HAL_InterruptRunHandler(void);

#endif /* HAL_INTERRUPT_H_ */