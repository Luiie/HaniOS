#include "stdint.h"
#include "Interrupt.h"
#include "HAL_Interrupt.h"
#include "ARMcpu.h"
#include "memoryIO.h"

extern volatile GicCput_t* GicCpu;
extern volatile GicDist_t* GicDist;

static InterruptHandler_fptr InterruptHandlers[INTERRUPT_HANDLER_NUM]; //255

void HAL_INTERRUPT_init(void){
    GicCpu->cpucontrol.bits.Enable = 1;
    GicCpu->prioritymask.bits.Prioritymask = GIC_PRIORITY_MASK_NONE;
    GicDist->distributorctrl.bits.Enable = 1;

    for (uint32_t i = 0 ; i < INTERRUPT_HANDLER_NUM ; i++){
        InterruptHandlers[i] = NULL;
    }
    
    Enable_IRQ();
}

void HAL_INTERRUPT_enable(uint32_t interrupt_num){
    if((interrupt_num < GIC_IRQ_START) || (GIC_IRQ_END < interrupt_num)){
        return;
    }

    uint32_t bit_num = interrupt_num - GIC_IRQ_START;

    if(bit_num < GIC_IRQ_START){
        SET_BIT(GicDist->setenable1, bit_num);
    }
    else{
        bit_num -= GIC_IRQ_START;
        SET_BIT(GicDist->setenable2, bit_num);
    }
}

void HAL_INTERRUPT_disable(uint32_t interrupt_num){
    if((interrupt_num < GIC_IRQ_START) || (GIC_IRQ_END < interrupt_num)){
        return;
    }

    uint32_t bit_num = interrupt_num - GIC_IRQ_START;

    if(bit_num < GIC_IRQ_START){
        CLEAR_BIT(GicDist->setenable1, bit_num);
    }
    else{
        bit_num -= GIC_IRQ_START;
        CLEAR_BIT(GicDist->setenable2, bit_num);
    }
}

void HAL_INTERRUPT_register_handler(InterruptHandler_fptr handler, uint32_t interrupt_num){
    InterruptHandlers[interrupt_num] = handler;
}

void HAL_INTERRUPT_run_handler(void){
    uint32_t interrupt_num = GicCpu->interruptack.bits.InterruptID;
    
    if(InterruptHandlers[interrupt_num] != NULL){
        InterruptHandlers[interrupt_num]();
    }
    GicCpu->endofinterrupt.bits.InterruptID = interrupt_num;
}
