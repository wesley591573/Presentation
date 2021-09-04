        .data
title:  .asciz"*****Print Name*****\n"
team:   .asciz"Team09\n"
name1:  .asciz"Brian Liao\n"
name2:  .asciz"Wesley Yo\n"
name3:  .asciz"Wesley Yo\n"
end:    .asciz"*****End Print*****\n"
        .text
        .globl  name

name:   stmfd   sp!,{lr}
        ldr     r0, =title
        bl      printf
        ldr     r0, =team
        mov     r4, r0
        bl      printf
        ldr     r0, =name1
        mov     r5, r0
        bl      printf
        ldr     r0, =name2
        mov     r6, r0
        bl      printf
        ldr     r0, =name3
        mov     r7, r0
        bl      printf
        ldr     r0, =end
        bl      printf
        sbcs    r0, r3, r4
        ldr     r0, Data
        ldmfd   sp!,{lr}
        mov     pc, lr

Data:
        .word   team
        .word   name1
        .word   name2
        .word   name3
