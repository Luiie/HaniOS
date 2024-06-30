#include "ARMcpu.h"

void Enable_IRQ(void){
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS r0, cpsr");
    __asm__ ("BIC r1, r0, #0x80");
    __asm__ ("MSR cpsr, r1");
    __asm__ ("POP {r0, r1}");
}

void Disable_IRQ(void){
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS r0, cpsr");
    __asm__ ("ORR r1, r0, #0x80");
    __asm__ ("MSR cpsr, r1");
    __asm__ ("POP {r0, r1}");
}

void Enable_FIQ(void){
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS r0, cpsr");
    __asm__ ("BIC r1, r0, #0x40");
    __asm__ ("MSR cpsr, r1");
    __asm__ ("POP {r0, r1}");
}

void Disable_FIQ(void){
    __asm__ ("PUSH {r0, r1}");
    __asm__ ("MRS r0, cpsr");
    __asm__ ("ORR r1, r0, #0x40");
    __asm__ ("MSR cpsr, r1");
    __asm__ ("POP {r0, r1}");
}