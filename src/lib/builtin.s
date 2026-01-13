	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p1_m2p0_a2p1_c2p0"
	.file	"builtin.c"
	.globl	Builtin_malloc                  # -- Begin function Builtin_malloc
	.p2align	1
	.type	Builtin_malloc,@function
Builtin_malloc:                         # @Builtin_malloc
# %bb.0:
	tail	malloc
.Lfunc_end0:
	.size	Builtin_malloc, .Lfunc_end0-Builtin_malloc
                                        # -- End function
	.globl	Builtin_strcat                  # -- Begin function Builtin_strcat
	.p2align	1
	.type	Builtin_strcat,@function
Builtin_strcat:                         # @Builtin_strcat
# %bb.0:
	addi	sp, sp, -32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	sw	s1, 20(sp)                      # 4-byte Folded Spill
	sw	s2, 16(sp)                      # 4-byte Folded Spill
	sw	s3, 12(sp)                      # 4-byte Folded Spill
	sw	s4, 8(sp)                       # 4-byte Folded Spill
	sw	s5, 4(sp)                       # 4-byte Folded Spill
	mv	s0, a1
	beqz	a0, .LBB1_4
# %bb.1:
	beqz	s0, .LBB1_3
# %bb.2:
	mv	s2, a0
	call	strlen
	mv	s4, a0
	mv	a0, s0
	call	strlen
	mv	s3, a0
	add	s5, a0, s4
	addi	a0, s5, 1
	call	malloc
	mv	s1, a0
	mv	a1, s2
	mv	a2, s4
	call	memcpy
	add	a0, s1, s4
	mv	a1, s0
	mv	a2, s3
	call	memcpy
	add	s5, s5, s1
	sb	zero, 0(s5)
	mv	s0, s1
	j	.LBB1_4
.LBB1_3:
	mv	s0, a0
.LBB1_4:
	mv	a0, s0
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	lw	s1, 20(sp)                      # 4-byte Folded Reload
	lw	s2, 16(sp)                      # 4-byte Folded Reload
	lw	s3, 12(sp)                      # 4-byte Folded Reload
	lw	s4, 8(sp)                       # 4-byte Folded Reload
	lw	s5, 4(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end1:
	.size	Builtin_strcat, .Lfunc_end1-Builtin_strcat
                                        # -- End function
	.globl	Builtin_callocArray             # -- Begin function Builtin_callocArray
	.p2align	1
	.type	Builtin_callocArray,@function
Builtin_callocArray:                    # @Builtin_callocArray
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	mv	s0, a0
	addi	a0, a0, 1
	li	a1, 4
	call	calloc
	addi	a1, a0, 4
	sw	s0, 0(a0)
	mv	a0, a1
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end2:
	.size	Builtin_callocArray, .Lfunc_end2-Builtin_callocArray
                                        # -- End function
	.globl	print                           # -- Begin function print
	.p2align	1
	.type	print,@function
print:                                  # @print
# %bb.0:
	addi	sp, sp, -32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	sw	s1, 20(sp)                      # 4-byte Folded Spill
	sw	s2, 16(sp)                      # 4-byte Folded Spill
	sw	s3, 12(sp)                      # 4-byte Folded Spill
	sw	s4, 8(sp)                       # 4-byte Folded Spill
	mv	s0, a0
	li	s1, 0
	li	s4, 92
	li	s2, 34
	li	s3, 110
	j	.LBB3_3
.LBB3_1:                                #   in Loop: Header=BB3_3 Depth=1
	beqz	a0, .LBB3_11
.LBB3_2:                                #   in Loop: Header=BB3_3 Depth=1
	call	putchar
	addi	s1, s1, 1
.LBB3_3:                                # =>This Inner Loop Header: Depth=1
	add	a0, s0, s1
	lbu	a0, 0(a0)
	bne	a0, s4, .LBB3_1
# %bb.4:                                #   in Loop: Header=BB3_3 Depth=1
	addi	a1, s1, 1
	add	a0, s0, a1
	lbu	a0, 0(a0)
	beq	a0, s2, .LBB3_9
# %bb.5:                                #   in Loop: Header=BB3_3 Depth=1
	beq	a0, s3, .LBB3_8
# %bb.6:                                #   in Loop: Header=BB3_3 Depth=1
	bne	a0, s4, .LBB3_10
# %bb.7:                                #   in Loop: Header=BB3_3 Depth=1
	li	a0, 92
	mv	s1, a1
	j	.LBB3_2
.LBB3_8:                                #   in Loop: Header=BB3_3 Depth=1
	li	a0, 10
	mv	s1, a1
	j	.LBB3_2
.LBB3_9:                                #   in Loop: Header=BB3_3 Depth=1
	li	a0, 34
	mv	s1, a1
	j	.LBB3_2
.LBB3_10:                               #   in Loop: Header=BB3_3 Depth=1
	li	a0, 48
	call	putchar
	li	a0, 48
	call	putchar
	li	a0, 48
	call	putchar
	li	a0, 48
	call	putchar
	li	a0, 48
	call	putchar
	li	a0, 48
	j	.LBB3_2
.LBB3_11:
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	lw	s1, 20(sp)                      # 4-byte Folded Reload
	lw	s2, 16(sp)                      # 4-byte Folded Reload
	lw	s3, 12(sp)                      # 4-byte Folded Reload
	lw	s4, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end3:
	.size	print, .Lfunc_end3-print
                                        # -- End function
	.globl	println                         # -- Begin function println
	.p2align	1
	.type	println,@function
println:                                # @println
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	call	print
	li	a0, 10
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 16
	tail	putchar
.Lfunc_end4:
	.size	println, .Lfunc_end4-println
                                        # -- End function
	.globl	printInt                        # -- Begin function printInt
	.p2align	1
	.type	printInt,@function
printInt:                               # @printInt
# %bb.0:
	lui	a1, %hi(.L.str)
	addi	a1, a1, %lo(.L.str)
	mv	a2, a0
	mv	a0, a1
	mv	a1, a2
	tail	printf
.Lfunc_end5:
	.size	printInt, .Lfunc_end5-printInt
                                        # -- End function
	.globl	printlnInt                      # -- Begin function printlnInt
	.p2align	1
	.type	printlnInt,@function
printlnInt:                             # @printlnInt
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	mv	a1, a0
	lui	a0, %hi(.L.str)
	addi	a0, a0, %lo(.L.str)
	call	printf
	li	a0, 10
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 16
	tail	putchar
.Lfunc_end6:
	.size	printlnInt, .Lfunc_end6-printlnInt
                                        # -- End function
	.globl	getString                       # -- Begin function getString
	.p2align	1
	.type	getString,@function
getString:                              # @getString
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	li	a0, 1024
	call	malloc
	mv	s0, a0
	lui	a0, %hi(.L.str.1)
	addi	a0, a0, %lo(.L.str.1)
	mv	a1, s0
	call	scanf
	mv	a0, s0
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end7:
	.size	getString, .Lfunc_end7-getString
                                        # -- End function
	.globl	getInt                          # -- Begin function getInt
	.p2align	1
	.type	getInt,@function
getInt:                                 # @getInt
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	lui	a0, %hi(.L.str)
	addi	a0, a0, %lo(.L.str)
	addi	a1, sp, 8
	call	scanf
	lw	a0, 8(sp)
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end8:
	.size	getInt, .Lfunc_end8-getInt
                                        # -- End function
	.globl	toString                        # -- Begin function toString
	.p2align	1
	.type	toString,@function
toString:                               # @toString
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	sw	s1, 4(sp)                       # 4-byte Folded Spill
	mv	s0, a0
	li	a0, 128
	call	malloc
	mv	s1, a0
	lui	a0, %hi(.L.str)
	addi	a1, a0, %lo(.L.str)
	mv	a0, s1
	mv	a2, s0
	call	sprintf
	mv	a0, s1
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	lw	s1, 4(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end9:
	.size	toString, .Lfunc_end9-toString
                                        # -- End function
	.globl	String_length                   # -- Begin function String_length
	.p2align	1
	.type	String_length,@function
String_length:                          # @String_length
# %bb.0:
	tail	strlen
.Lfunc_end10:
	.size	String_length, .Lfunc_end10-String_length
                                        # -- End function
	.globl	String_substring                # -- Begin function String_substring
	.p2align	1
	.type	String_substring,@function
String_substring:                       # @String_substring
# %bb.0:
	addi	sp, sp, -32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	sw	s1, 20(sp)                      # 4-byte Folded Spill
	sw	s2, 16(sp)                      # 4-byte Folded Spill
	sw	s3, 12(sp)                      # 4-byte Folded Spill
	mv	s3, a1
	mv	s2, a0
	sub	s1, a2, a1
	addi	a0, s1, 1
	call	malloc
	mv	s0, a0
	add	a1, s2, s3
	mv	a2, s1
	call	memcpy
	add	s1, s1, s0
	sb	zero, 0(s1)
	mv	a0, s0
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	lw	s1, 20(sp)                      # 4-byte Folded Reload
	lw	s2, 16(sp)                      # 4-byte Folded Reload
	lw	s3, 12(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end11:
	.size	String_substring, .Lfunc_end11-String_substring
                                        # -- End function
	.globl	String_parseInt                 # -- Begin function String_parseInt
	.p2align	1
	.type	String_parseInt,@function
String_parseInt:                        # @String_parseInt
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	mv	s0, a0
	call	strlen
	beqz	a0, .LBB12_3
# %bb.1:
	mv	a1, a0
	li	a0, 0
	add	a1, a1, s0
	li	a2, 10
.LBB12_2:                               # =>This Inner Loop Header: Depth=1
	lbu	a3, 0(s0)
	mul	a0, a0, a2
	add	a0, a0, a3
	addi	s0, s0, 1
	addi	a0, a0, -48
	bne	s0, a1, .LBB12_2
.LBB12_3:
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end12:
	.size	String_parseInt, .Lfunc_end12-String_parseInt
                                        # -- End function
	.globl	String_ord                      # -- Begin function String_ord
	.p2align	1
	.type	String_ord,@function
String_ord:                             # @String_ord
# %bb.0:
	add	a0, a0, a1
	lbu	a0, 0(a0)
	ret
.Lfunc_end13:
	.size	String_ord, .Lfunc_end13-String_ord
                                        # -- End function
	.globl	Array_size                      # -- Begin function Array_size
	.p2align	1
	.type	Array_size,@function
Array_size:                             # @Array_size
# %bb.0:
	lw	a0, -4(a0)
	ret
.Lfunc_end14:
	.size	Array_size, .Lfunc_end14-Array_size
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d"
	.size	.L.str, 3

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"%s"
	.size	.L.str.1, 3

	.ident	"clang version 18.1.8"
	.section	".note.GNU-stack","",@progbits
	.addrsig
