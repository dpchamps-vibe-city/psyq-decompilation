/* LIBGTE.LIB, member FT4M_02.OBJ (hand-written assembly)
 *
 * GsTMDfastTF4LM: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastTF4LM
	.ent	GsTMDfastTF4LM
GsTMDfastTF4LM:
	lw	$t8, 0x10($sp)
	lw	$t9, 0x18($sp)
	lw	$t7, 0x14($sp)
	beqz	$t8, .L7
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
	addiu	$sp, $sp, -0x18
	sw	$s0, 0($sp)
	sw	$s1, 0x4($sp)
	sw	$s2, 0x8($sp)
	sw	$s3, 0xC($sp)
	sw	$s4, 0x10($sp)
	lw	$t2, 0x14($a0)
	lw	$t3, 0x18($a0)
	srl	$t4, $t2, 16
	sll	$t4, $t4, 3
	addu	$t4, $t4, $a1
.L1:
	lwc2	$0, 0($t4)
	lwc2	$1, 0x4($t4)
	sll	$t5, $t3, 16
	srl	$t5, $t5, 13
	addu	$t5, $t5, $a1
	lwc2	$2, 0($t5)
	lwc2	$3, 0x4($t5)
	srl	$t5, $t3, 16
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lwc2	$4, 0($t5)
	lwc2	$5, 0x4($t5)
	nop
	RTPT
	lw	$t6, GsTON
	lb	$v1, 0x3($a0)
	sll	$t6, $t6, 1
	or	$v1, $v1, $t6
	sll	$v1, $v1, 24
	li	$t6, 0x808080
	or	$v1, $v1, $t6
	mtc2	$v1, $6
	sll	$t5, $t2, 16
	srl	$t5, $t5, 13
	addu	$t5, $t5, $a2
	lhu	$v1, 0x1C($a0)
	addiu	$a0, $a0, 0x20
	sll	$v1, $v1, 3
	addu	$v1, $v1, $a1
	lw	$t2, 0x14($a0)
	lw	$t3, 0x18($a0)
	srl	$t4, $t2, 16
	sll	$t4, $t4, 3
	addu	$t4, $t4, $a1
	cfc2	$v0, $31
	nop
	bltz	$v0, .L6
	nop
	NCLIP
	lwc2	$0, 0($v1)
	lwc2	$1, 0x4($v1)
	mfc2	$s4, $24
	nop
	blez	$s4, .L6
	nop
	swc2	$12, 0x8($a3)
	swc2	$13, 0x10($a3)
	swc2	$14, 0x18($a3)
	nop
	RTPS
	addiu	$v0, $a0, -0x20
	lw	$v1, 0x4($v0)
	lw	$t6, 0x8($v0)
	sw	$v1, 0xC($a3)
	sw	$t6, 0x14($a3)
	lw	$v1, 0xC($v0)
	lw	$t6, 0x10($v0)
	sw	$v1, 0x1C($a3)
	sw	$t6, 0x24($a3)
	cfc2	$v0, $31
	nop
	bltz	$v0, .L6
	nop
	lbu	$s0, 0xC($a3)
	lbu	$s1, 0x24($a3)
	lbu	$s2, 0xD($a3)
	lbu	$s3, 0x25($a3)
	subu	$s1, $s1, $s0
	addiu	$s1, $s1, 0x1
	andi	$s1, $s1, 0xFFFE
	subu	$s3, $s3, $s2
	addiu	$s3, $s3, 0x1
	andi	$v1, $s3, 0xFFFE
	mult	$s1, $v1
	addu	$v0, $s0, $s1
	mflo	$t6
	sra	$s3, $t6, 6
	slt	$s3, $s4, $s3
	beqz	$s3, .L2
	sra	$s3, $v1, 1
	sra	$s1, $s1, 3
	addu	$v0, $v0, $s1
	addu	$s3, $s2, $s3
	sra	$s0, $v1, 3
	addu	$s3, $s3, $s0
	addiu	$s1, $s1, -0x1
	addu	$s1, $v0, $s1
	addiu	$s0, $s0, -0x1
	sb	$s3, 0xD($a3)
	sb	$s3, 0x15($a3)
	addu	$s3, $s3, $s0
	sb	$v0, 0xC($a3)
	j	.L4
	sb	$s1, 0x14($a3)
.L2:
	sra	$s3, $t6, 4
	slt	$s3, $s4, $s3
	beqz	$s3, .L3
	sra	$s3, $t6, 2
	sra	$s0, $s1, 2
	addu	$s3, $v0, $s0
	sra	$s1, $v1, 1
	addu	$s1, $s2, $s1
	addiu	$s0, $s0, -0x1
	addu	$s0, $s3, $s0
	sb	$s3, 0xC($a3)
	sb	$s3, 0x1C($a3)
	sra	$s3, $v1, 2
	addiu	$s3, $s3, -0x1
	sb	$s1, 0xD($a3)
	sb	$s1, 0x15($a3)
	addu	$s1, $s1, $s3
	sb	$s0, 0x14($a3)
	sb	$s1, 0x1D($a3)
	sb	$s0, 0x24($a3)
	j	.L5
	sb	$s1, 0x25($a3)
.L3:
	slt	$s3, $s4, $s3
	beqz	$s3, .L5
	sra	$s1, $s1, 1
	addiu	$s1, $s1, -0x1
	addu	$s1, $v0, $s1
	sra	$s3, $v1, 1
	addiu	$s3, $s3, -0x1
	addu	$s3, $s2, $s3
	sb	$v0, 0xC($a3)
	sb	$s2, 0xD($a3)
	sb	$s1, 0x14($a3)
	sb	$s2, 0x15($a3)
.L4:
	sb	$v0, 0x1C($a3)
	sb	$s3, 0x1D($a3)
	sb	$s1, 0x24($a3)
	sb	$s3, 0x25($a3)
	nop
.L5:
	AVSZ4
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
	mfc2	$t6, $7
	nop
	NCCS
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t5, 0($t6)
	li	$v0, 0x9000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($a3)
	xor	$v0, $a3, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	swc2	$14, 0x20($a3)
	swc2	$22, 0x4($a3)
	addiu	$a3, $a3, 0x28
.L6:
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
	lw	$s0, 0($sp)
	lw	$s1, 0x4($sp)
	lw	$s2, 0x8($sp)
	lw	$s3, 0xC($sp)
	lw	$s4, 0x10($sp)
	addiu	$sp, $sp, 0x18
.L7:
	move	$v0, $a3
	jr	$ra
	nop
	nop
	nop
	nop
	.end	GsTMDfastTF4LM
	.set	reorder
