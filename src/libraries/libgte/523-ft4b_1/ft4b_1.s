/* LIBGTE.LIB, member FT4B_1.OBJ (hand-written assembly)
 *
 * GsTMDfastTNF4B: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastTNF4B
	.ent	GsTMDfastTNF4B
GsTMDfastTNF4B:
	lw	$t9, 0x14($sp)
	lw	$t7, 0x10($sp)
	beqz	$a3, .L3
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
	lw	$t2, 0x18($a0)
	lhu	$t4, 0x1C($a0)
	srl	$t3, $t2, 16
	sll	$t2, $t2, 16
	srl	$t2, $t2, 13
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
	lw	$v0, 0x14($a0)
	lhu	$v1, 0x1E($a0)
	lw	$t3, GsTON
	lb	$t2, 0x3($a0)
	sll	$t3, $t3, 1
	or	$t2, $t2, $t3
	sll	$v0, $v0, 8
	srl	$v0, $v0, 8
	srl	$t2, $t2, 1
	sll	$t2, $t2, 25
	or	$v0, $v0, $t2
	sw	$v0, 0x4($a2)
	addiu	$a0, $a0, 0x20
	sll	$v1, $v1, 3
	addu	$v1, $v1, $a1
	lw	$t2, 0x18($a0)
	lhu	$t4, 0x1C($a0)
	srl	$t3, $t2, 16
	sll	$t2, $t2, 16
	srl	$t2, $t2, 13
	sll	$t3, $t3, 3
	sll	$t4, $t4, 3
	addu	$t2, $t2, $a1
	addu	$t3, $t3, $a1
	addu	$t4, $t4, $a1
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	lwc2	$0, 0($v1)
	lwc2	$1, 0x4($v1)
	swc2	$12, 0x8($a2)
	swc2	$13, 0x10($a2)
	swc2	$14, 0x18($a2)
	nop
	RTPS
	addiu	$v0, $a0, -0x20
	lw	$v1, 0x4($v0)
	lw	$t6, 0x8($v0)
	sw	$v1, 0xC($a2)
	sw	$t6, 0x14($a2)
	lw	$v1, 0xC($v0)
	lw	$t6, 0x10($v0)
	sw	$v1, 0x1C($a2)
	sw	$t6, 0x24($a2)
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	AVSZ4
	mfc2	$t6, $7
	swc2	$14, 0x20($a2)
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
	sw	$v0, 0($a2)
	xor	$v0, $a2, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	addiu	$a2, $a2, 0x28
.L2:
	addiu	$a3, $a3, -0x1
	bnez	$a3, .L1
	nop
.L3:
	move	$v0, $a2
	jr	$ra
	nop
	nop
	.end	GsTMDfastTNF4B
	.set	reorder
