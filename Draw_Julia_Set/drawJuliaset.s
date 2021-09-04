	.arch armv6
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"Untitled1.c"
	.global	__aeabi_idiv
	.text
	.align	2
	.global	drawJuliaSet
	.type	drawJuliaSet, %function
drawJuliaSet:
	@ args = 4, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	sub	sp, sp, #48
	str	r0, [fp, #-40]	@ cX
	str	r1, [fp, #-44]	@ cY
	str	r2, [fp, #-48]	@ width
	str	r3, [fp, #-52]	@ height
	mov	r3, #255
	str	r3, [fp, #-28]	@ maxIter
	mov	r3, #0
	str	r3, [fp, #-20]	@ x
	b	.L2
.L8:
	mov	r3, #0
	str	r3, [fp, #-24]	@ y
	b	.L3
.L7:
	ldr	r3, [fp, #-48]
	mov	r3, r3, asr #1
	ldr	r2, [fp, #-20]
	rsb	r3, r3, r2
	ldr	r2, .L9
	mul	r2, r2, r3
	ldr	r3, [fp, #-48]
	mov	r3, r3, asr #1
	mov	r0, r2
	mov	r1, r3
	bl	__aeabi_idiv	@ 除法函數
	mov	r3, r0
	str	r3, [fp, #-8]	@ zx
	ldr	r3, [fp, #-52]
	mov	r3, r3, asr #1
	ldr	r2, [fp, #-24]
	rsb	r3, r3, r2
	mov	r2, #1000
	mul	r2, r2, r3
	ldr	r3, [fp, #-52]
	mov	r3, r3, asr #1
	mov	r0, r2
	mov	r1, r3
	bl	__aeabi_idiv
	mov	r3, r0
	str	r3, [fp, #-12]	@ zy
	ldr	r3, [fp, #-28]
	str	r3, [fp, #-16]	@ i
	b	.L4
.L6:
	ldr	r3, [fp, #-8]
	ldr	r2, [fp, #-8]
	mul	r2, r2, r3
	ldr	r3, [fp, #-12]
	ldr	r1, [fp, #-12]
	mul	r3, r1, r3
	rsb	r3, r3, r2

	@ 除1000
	ldr	r2, .L9+4
	smull	r1, r2, r2, r3
	mov	r2, r2, asr #6
	mov	r3, r3, asr #31
	rsb	r2, r3, r2

	ldr	r3, [fp, #-40]
	add	r3, r2, r3
	str	r3, [fp, #-32]	@ tmp
	ldr	r3, [fp, #-8]
	mov	r3, r3, asl #1
	ldr	r2, [fp, #-12]
	mul	r3, r2, r3

	@ 除1000
	ldr	r2, .L9+4
	smull	r1, r2, r2, r3
	mov	r2, r2, asr #6
	mov	r3, r3, asr #31
	rsb	r2, r3, r2

	ldr	r3, [fp, #-44]
	add	r3, r2, r3
	str	r3, [fp, #-12]	@ zy
	ldr	r3, [fp, #-32]
	str	r3, [fp, #-8]
	ldr	r3, [fp, #-16]	@ i
	sub	r3, r3, #1
	str	r3, [fp, #-16]
.L4:
	ldr	r3, [fp, #-8]
	ldr	r2, [fp, #-8]
	mul	r2, r2, r3
	ldr	r3, [fp, #-12]
	ldr	r1, [fp, #-12]
	mul	r3, r1, r3
	add	r2, r2, r3
	ldr	r3, .L9+8
	cmp	r2, r3
	bgt	.L5
	ldr	r3, [fp, #-16]
	cmp	r3, #0
	bgt	.L6
.L5:
	ldr	r3, [fp, #-16]
	mov	r3, r3, asl #8
	uxth	r2, r3
	ldr	r3, [fp, #-16]
	uxth	r3, r3
	uxtb	r3, r3
	uxth	r3, r3
	orr	r3, r2, r3
	strh	r3, [fp, #-34]	@ movhi
	ldrh	r3, [fp, #-34]	@ movhi
	mvn	r3, r3
	strh	r3, [fp, #-34]	@ movhi
	ldr	r2, [fp, #-24]
	mov	r3, r2
	mov	r3, r3, asl #2
	add	r3, r3, r2          @Opperand2
	mov	r3, r3, asl #8
	ldr	r2, [fp, #4]
	add	r2, r2, r3
	ldr	r3, [fp, #-20]
	mov	r3, r3, asl #1      @Opperand2
	add	r3, r2, r3
	ldrh	r2, [fp, #-34]	@ movhi
	strh	r2, [r3, #0]	@ movhi
	ldr	r3, [fp, #-24]
	add	r3, r3, #1
	str	r3, [fp, #-24]
.L3:
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-52]
	cmp	r2, r3
	blt	.L7
	ldr	r3, [fp, #-20]
	add	r3, r3, #1          @Opperand2
	str	r3, [fp, #-20]
.L2:
	ldr	r2, [fp, #-20]
	ldr	r3, [fp, #-48]
	cmp	r2, r3
	blt	.L8
	sub	sp, fp, #4
	adds    r14, r0, r1

	moveq   r0, r0
	movne   r1, r1
	movge   r2, r2

	ldmfd	sp!, {fp, pc}
.L10:
	.align	2
.L9:
	.word	1500
	.word	274877907
	.word	3999999
	.size	drawJuliaSet, .-drawJuliaSet
	.ident	"GCC: (Debian 4.6.3-8+rpi1) 4.6.3"
	.section	.note.GNU-stack,"",%progbits
