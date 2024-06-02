.text
    .code 32

    .global vector_start
    .global vector_end

    vector_start:
        LDR PC, reset_handler_addr
        LDR PC, svc_handler_addr
        B .
        LDR PC, irq_handler_addr
        
        reset_handler_addr: .word reset_handler
        svc_handler_addr: .word dummy_handler
        irq_handler_addr: .word dummy_handler
        
    vector_end:

    reset_handler:
        LDR R0, =0x10000000
        LDR R1, [R0]

    dummy_handler:
        B .
    
.end
