#include "stdint.h"
#include "ARMcpu.h"
#include "ARMswitch.h"
#include "task.h"

extern KernelTcb_t* currentTCB;
extern KernelTcb_t* nextTCB;

__attribute__ ((naked)) void ContextSwitching(void){
    __asm__ ("B SaveContext");
    __asm__ ("B RestoreContext");
}

__attribute__ ((naked)) void SaveContext(void){
    // save current task context into the current task stack
    __asm__ ("PUSH {lr}");
    __asm__ ("PUSH {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
    __asm__ ("MRS   r0, cpsr");
    __asm__ ("PUSH {r0}");
    // save current task stack pointer into the current TCB
    __asm__ ("LDR   r0, =currentTCB");
    __asm__ ("LDR   r0, [r0]");
    __asm__ ("STMIA r0!, {sp}");
}

__attribute__ ((naked)) void RestoreContext(void){
    // restore next task stack pointer from the next TCB
    __asm__ ("LDR   r0, =nextTCB");
    __asm__ ("LDR   r0, [r0]");
    __asm__ ("LDMIA r0!, {sp}");
    // restore next task context from the next task stack
    __asm__ ("POP  {r0}");
    __asm__ ("MSR   cpsr, r0");
    __asm__ ("POP  {r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12}");
    __asm__ ("POP  {pc}");
}