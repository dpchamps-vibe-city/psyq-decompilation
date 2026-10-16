/* LIBGTE.LIB, member F3B_3.OBJ (hand-written assembly)
 *
 * GsTMDfastF3LB: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastF3LB
	.ent	GsTMDfastF3LB
GsTMDfastF3LB:
	lw	$t8, 0x10($sp)
	lw	$t9, 0x18($sp)
	lw	$t7, 0x14($sp)
	beqz	$t8, .L3
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
	lw	$t2, 0x8($a0)
	lw	$t3, 0xC($a0)
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
	sll	$t5, $t2, 16
	srl	$t5, $t5, 13
	addu	$t5, $t5, $a2
	lw	$t3, GsTON
	lw	$t2, 0x4($a0)
	sll	$t3, $t3, 25
	or	$t2, $t2, $t3
	mtc2	$t2, $6
	addiu	$a0, $a0, 0x10
	lw	$t2, 0x8($a0)
	lw	$t3, 0xC($a0)
	srl	$t4, $t2, 16
	sll	$t4, $t4, 3
	addu	$t4, $t4, $a1
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	AVSZ3
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
	li	$v0, 0x4000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($a3)
	xor	$v0, $a3, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	swc2	$12, 0x8($a3)
	swc2	$13, 0xC($a3)
	swc2	$14, 0x10($a3)
	swc2	$22, 0x4($a3)
	addiu	$a3, $a3, 0x14
.L2:
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L3:
	move	$v0, $a3
	jr	$ra
	nop
	nop
	nop
	nop
	.end	GsTMDfastF3LB
	.set	reorder
