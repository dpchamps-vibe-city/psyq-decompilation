/* LIBHMD.LIB, member 0002000D.OBJ (hand-written assembly)
 *
 * u_long *GsU_0002000d(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x0002000d (GsUFGT3): fog texture gouraud triangle.
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_0002000d
	.ent	GsU_0002000d
GsU_0002000d:
	lw	$a3, 0($a0)
	lw	$t9, 0x4($a0)
	lw	$t8, 0($a3)
	lw	$t7, 0x8($a0)
	addiu	$a3, $a3, 0x4
	lw	$a2, 0($a3)
	lw	$a1, 0x14($a0)
	sll	$a2, $a2, 2
	srl	$t8, $t8, 16
	beqz	$t8, .L4
	addu	$a3, $a1, $a2
	li	$v0, 0x34808080
	lw	$t0, 0x4($t9)
	mtc2	$v0, $6
	lw	$t1, 0xC($a0)
	addiu	$v0, $a0, 0x10
	lw	$t9, 0($v0)
	lw	$a1, 0x18($a0)
	lw	$a2, 0x1C($a0)
.L1:
	lw	$t2, 0xC($a3)
	lw	$t3, 0x10($a3)
	lw	$t4, 0x14($a3)
.L2:
	srl	$t5, $t2, 16
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
	srl	$t5, $t3, 16
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lwc2	$2, 0($t5)
	lwc2	$3, 0x4($t5)
	srl	$t5, $t4, 16
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lwc2	$4, 0($t5)
	lwc2	$5, 0x4($t5)
	nop
	nop
	RTPT
	sll	$t2, $t2, 16
	srl	$t2, $t2, 13
	addu	$t2, $t2, $a2
	sll	$t3, $t3, 16
	srl	$t3, $t3, 13
	addu	$t3, $t3, $a2
	sll	$t4, $t4, 16
	srl	$t4, $t4, 13
	addu	$t4, $t4, $a2
	cfc2	$v0, $31
	nop
	bltz	$v0, .L3
	nop
	NCLIP
	mfc2	$v0, $24
	nop
	blez	$v0, .L3
	nop
	AVSZ3
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	lwc2	$2, 0($t3)
	lwc2	$3, 0x4($t3)
	lwc2	$4, 0($t4)
	lwc2	$5, 0x4($t4)
	mfc2	$t6, $7
	nop
	nop
	NCDT
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
	sw	$v0, 0($t9)
	xor	$v0, $t9, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	lw	$t2, 0($a3)
	lw	$t3, 0x4($a3)
	lw	$t4, 0x8($a3)
	sw	$t2, 0xC($t9)
	sw	$t3, 0x18($t9)
	sw	$t4, 0x24($t9)
	swc2	$12, 0x8($t9)
	swc2	$13, 0x14($t9)
	swc2	$14, 0x20($t9)
	swc2	$20, 0x4($t9)
	swc2	$21, 0x10($t9)
	swc2	$22, 0x1C($t9)
	addiu	$a3, $a3, 0x18
	lw	$t2, 0xC($a3)
	lw	$t3, 0x10($a3)
	lw	$t4, 0x14($a3)
	addiu	$t9, $t9, 0x28
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L2
	nop
	b	.L4
	nop
.L3:
	addiu	$a3, $a3, 0x18
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L4:
	lw	$v0, 0($a0)
	sw	$t9, GsOUT_PACKET_P
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	nop
	nop
	.end	GsU_0002000d
	.set	reorder
