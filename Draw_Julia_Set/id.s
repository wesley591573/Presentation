            .data
title:      .asciz  "*****Input ID*****"

question1:  .asciz  "\n**Please enter Member 1 ID:**\n"
question2:  .asciz  "\n**Please enter Member 2 ID:**\n"
question3:  .asciz  "\n**Please enter Member 3 ID:**\n"
question4:  .asciz  "\n**Please enter command**\n"
question5:  .asciz  "\n*****Print Team Member ID and ID Summation*****\n"
question6:  .asciz  "\nID Summation="
changeLine: .asciz  "\n"

end:        .asciz  "*****End Print*****"

number:     .asciz  "%d"
char:       .asciz  "%s"

Data:
            .word   0
            .word   0
            .word   0
            .word   0

c1:         .word   0


            .text
            .globl  id
            .globl  print

id:         stmfd   sp!,{r4,lr}
            ldr     r0, =title
            bl      printf

            ldr     r0, =question1
            bl      printf
            ldr     r0, =number
            ldr     r1, =Data
            bl      scanf

            ldr     r0, =question2
            bl      printf
            ldr     r0, =number
            ldr     r1, =Data+4
            bl      scanf

            ldr     r0, =question3
            bl      printf
            ldr     r0, =number
            ldr     r1, =Data+8
            bl      scanf



            mov     r2, #0

            ldr     r1, =Data+8
            ldr     r1, [r1]
            add     r2, r2, r1

            ldr     r1, =Data+4
            ldr     r1, [r1]
            add     r2, r2, r1

            ldr     r1, =Data
            ldr     r1, [r1]
            add     r2, r2, r1

            ldr     r1, =Data+12
            str     r2, [r1]


            ldr     r0, =number
            ldr     r1, =Data
            mov     r8, r1

            ldr     r0, =number
            ldr     r1, =Data+4
            mov     r9, r1

            ldr     r0, =number
            ldr     r1, =Data+8
            mov     r10, r1



            ldr     r0, =question4
            bl      printf
            ldr     r0, =char
            ldr     r1, =c1
            bl      scanf

            ldr     r1, =c1
            ldr     r1, [r1]
            cmp     r1, #'p'
            beq     print
            b       after


print:      ldr     r0, =question5
            bl      printf

            ldr     r0, =number
            ldr     r1, =Data
            ldr     r1, [r1]
            bl      printf
            ldr     r0, =changeLine
            bl      printf

            ldr     r0, =number
            ldr     r1, =Data+4
            ldr     r1, [r1]
            bl      printf
            ldr     r0, =changeLine
            bl      printf

            ldr     r0, =number
            ldr     r1, =Data+8
            ldr     r1, [r1]
            bl      printf
            ldr     r0, =changeLine
            bl      printf

            ldr     r0, =question6
            bl      printf

            ldr     r0, =number
            ldr     r1, =Data+12
            ldr     r1, [r1]
            bl      printf

            ldr     r0, =changeLine
            bl      printf

            ldr     r0, =end
            bl      printf


after:      ldr     r0, =Data
            ldmfd   sp!,{r4,lr}
            mov     pc, lr

