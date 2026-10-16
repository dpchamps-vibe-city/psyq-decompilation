/* LIBGTE.LIB, member GT4M_01.OBJ (hand-written assembly)
 *
 * GsTMDfastTG4NLM: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastTG4NLM
	.ent	GsTMDfastTG4NLM
GsTMDfastTG4NLM:
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
	lhu	$t2, 0x16($a0)
	lhu	$t3, 0x1A($a0)
	lhu	$t4, 0x1E($a0)
	sll	$t2, $t2, 3
	sll	$t3, $t3, 3
	sll	$t4, $t4, 3
	addu	$t2, $t2, $a1
	addu	$t3, $t3, $a1
	addu	$t4, $t4, $a1
.L1:
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	lwc2	$2, 0($t3)
	lwc2	$3, 0x4($t3)
	lwc2	$4, 0($t4)
	lwc2	$5, 0x4($t4)
	nop
	RTPT
	lhu	$t5, 0x22($a0)
	move	$v1, $a0
	addiu	$a0, $a0, 0x24
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lhu	$t2, 0x16($a0)
	lhu	$t3, 0x1A($a0)
	lhu	$t4, 0x1E($a0)
	sll	$t2, $t2, 3
	sll	$t3, $t3, 3
	sll	$t4, $t4, 3
	addu	$t2, $t2, $a1
	addu	$t3, $t3, $a1
	addu	$t4, $t4, $a1
	cfc2	$v0, $31
	nop
	bltz	$v0, .L6
	nop
	NCLIP
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
	mfc2	$s4, $24
	nop
	blez	$s4, .L6
	nop
	swc2	$12, 0x8($a3)
	swc2	$13, 0x10($a3)
	swc2	$14, 0x18($a3)
	nop
	RTPS
	lb	$t5, 0x3($v1)
	lw	$t6, GsTON
	andi	$t5, $t5, 0x2
	sll	$t6, $t6, 1
	or	$t5, $t6, $t5
	sll	$t5, $t5, 24
	li	$t6, 0x2d808080
	or	$t6, $t5, $t6
	sw	$t6, 0x4($a3)
	lw	$t5, 0x4($v1)
	lw	$t6, 0x8($v1)
	cfc2	$v0, $31
	nop
	bltz	$v0, .L6
	nop
	AVSZ4
	lw	$v0, 0xC($v1)
	sw	$t5, 0xC($a3)
	sw	$t6, 0x14($a3)
	sw	$v0, 0x1C($a3)
	lw	$t5, 0x10($v1)
	mfc2	$t6, $7
	sw	$t5, 0x24($a3)
	swc2	$14, 0x20($a3)
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
	mflo	$t5
	sra	$s3, $t5, 6
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
	sra	$s3, $t5, 4
	slt	$s3, $s4, $s3
	beqz	$s3, .L3
	sra	$s3, $t5, 2
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
	.end	GsTMDfastTG4NLM
	.set	reorder
