.text ;
    .code 32

    .global vector_start
    .global vector_end

    vector_start:
        MOV    R0, R1
    vector_end:
        .space 1024, 0
.end ;
; ./Entry.S: Warning: end of file not at end of a line; newline inserted