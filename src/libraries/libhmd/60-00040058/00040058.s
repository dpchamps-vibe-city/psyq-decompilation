/* LIBHMD.LIB, member 00040058.OBJ (hand-written assembly)
 *
 * u_long *GsU_00040058(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x00040058 (GsUMNF3): mesh nonLight flat triangle.
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_00040058
	.ent	GsU_00040058
GsU_00040058:
	lw	$a3, 0($a0)
	lw	$t9, 0x4($a0)
	lw	$t8, 0($a3)
	lw	$t7, 0x8($a0)
	addiu	$a3, $a3, 0x4
	lw	$a2, 0($a3)
	lw	$a1, 0x14($a0)
	sll	$a2, $a2, 2
	srl	$t8, $t8, 16
	beqz	$t8, .L6
	addu	$a3, $a1, $a2
	lw	$t0, 0x4($t9)
	lw	$t1, 0xC($a0)
	addiu	$v0, $a0, 0x10
	lw	$t9, 0($v0)
	lw	$a1, 0x18($a0)
.L1:
	lw	$t2, 0x8($a3)
	lw	$t3, 0xC($a3)
	sll	$t4, $t2, 16
	srl	$t4, $t4, 13
	addu	$t4, $t4, $a1
	lwc2	$0, 0($t4)
	lwc2	$1, 0x4($t4)
	srl	$t5, $t2, 16
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lwc2	$2, 0($t5)
	lwc2	$3, 0x4($t5)
	sll	$t5, $t3, 16
	srl	$t5, $t5, 13
	addu	$t5, $t5, $a1
	lwc2	$4, 0($t5)
	lwc2	$5, 0x4($t5)
	nop
	nop
	RTPT
	lw	$t3, 0($a3)
	lw	$t2, 0x4($a3)
	addiu	$t3, $t3, -0x1
	sw	$t2, 0x4($t9)
	addiu	$a3, $a3, 0x10
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	NCLIP
	mfc2	$v0, $24
	nop
	blez	$v0, .L2
	nop
	AVSZ3
	mfc2	$t6, $7
	nop
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
	sw	$v0, 0($t9)
	nop
	xor	$v0, $t9, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	swc2	$12, 0x8($t9)
	swc2	$13, 0xC($t9)
	swc2	$14, 0x10($t9)
	nop
	addiu	$t9, $t9, 0x14
.L2:
	li	$t5, 0
.L3:
	lw	$t2, 0x4($a3)
	nop
	sll	$t4, $t2, 16
	srl	$t4, $t4, 13
	addu	$t4, $t4, $a1
	lwc2	$0, 0($t4)
	lwc2	$1, 0x4($t4)
	nop
	nop
	RTPS
	lw	$t2, 0($a3)
	nop
	sw	$t2, 0x4($t9)
	nop
	cfc2	$v0, $31
	nop
	bltz	$v0, .L5
	nop
	NCLIP
	andi	$v1, $t5, 0x1
	mfc2	$v0, $24
	nop
	bnez	$v1, .L4
	nop
	neg	$v0, $v0
.L4:
	blez	$v0, .L5
	nop
	AVSZ3
	mfc2	$t6, $7
	nop
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t4, 0($t6)
	li	$v0, 0x4000000
	sll	$v1, $t4, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($t9)
	nop
	xor	$v0, $t9, $t4
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t4
	sw	$v1, 0($t6)
	swc2	$12, 0x8($t9)
	swc2	$13, 0xC($t9)
	swc2	$14, 0x10($t9)
	nop
	addiu	$t9, $t9, 0x14
.L5:
	addiu	$a3, $a3, 0x8
	addiu	$t3, $t3, -0x1
	bnez	$t3, .L3
	addi	$t5, $t5, 0x1
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L6:
	lw	$v0, 0($a0)
	sw	$t9, GsOUT_PACKET_P
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	nop
	nop
	nop
	.end	GsU_00040058
	.set	reorder
