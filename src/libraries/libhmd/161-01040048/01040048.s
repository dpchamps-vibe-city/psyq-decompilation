/* LIBHMD.LIB, member 01040048.OBJ (hand-written assembly)
 *
 * u_long *GsU_01040048(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x01040048 (GsUSNF3): shared nonLight flat triangle.
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_01040048
	.ent	GsU_01040048
GsU_01040048:
	lw	$t0, 0($a0)
	lw	$t1, 0x10($a0)
	lhu	$t2, 0x2($t0)
	lw	$t3, 0x4($t0)
	lw	$t4, 0x14($a0)
	sll	$t3, $t3, 2
	beqz	$t2, .L3
	addu	$t7, $t4, $t3
	lw	$t9, 0x4($a0)
	lw	$t6, 0xC($a0)
	lw	$a3, 0x4($t9)
	lw	$t5, 0x1C($a0)
	lw	$t9, 0x8($a0)
.L1:
	lw	$a1, 0x4($t7)
	lw	$a2, 0x8($t7)
	sll	$v0, $a1, 16
	srl	$v0, $v0, 13
	addu	$t3, $v0, $t5
	lw	$v0, 0x4($t3)
	li	$t0, -0x1
	beq	$v0, $t0, .L2
	nop
	mtc2	$v0, $17
	nop
	srl	$v0, $a1, 16
	sll	$v0, $v0, 3
	addu	$t4, $v0, $t5
	lw	$v0, 0x4($t4)
	nop
	beq	$v0, $t0, .L2
	nop
	mtc2	$v0, $18
	nop
	sll	$v0, $a2, 16
	srl	$v0, $v0, 13
	addu	$v1, $v0, $t5
	lw	$v0, 0x4($v1)
	nop
	beq	$v0, $t0, .L2
	nop
	mtc2	$v0, $19
	nop
	lw	$v0, 0($t3)
	lw	$t0, 0($t4)
	lw	$t3, 0($v1)
	mtc2	$v0, $12
	mtc2	$t0, $13
	mtc2	$t3, $14
	nop
	nop
	NCLIP
	sw	$v0, 0x8($t1)
	sw	$t0, 0xC($t1)
	sw	$t3, 0x10($t1)
	mfc2	$v0, $24
	nop
	blez	$v0, .L2
	nop
	AVSZ3
	lw	$v0, 0($t7)
	nop
	sw	$v0, 0x4($t1)
	mfc2	$t4, $7
	nop
	subu	$t4, $t4, $t6
	srlv	$t4, $t4, $t9
	andi	$t4, $t4, 0xFFFF
	sll	$t4, $t4, 2
	addu	$t4, $t4, $a3
	lw	$v0, 0($t4)
	li	$v1, 0x4000000
	sll	$t3, $v0, 8
	srl	$t3, $t3, 8
	or	$v1, $v1, $t3
	sw	$v1, 0($t1)
	xor	$v1, $t1, $v0
	sll	$t3, $v1, 8
	srl	$v1, $t3, 8
	xor	$t3, $v1, $v0
	sw	$t3, 0($t4)
	addiu	$t1, $t1, 0x14
.L2:
	addiu	$t2, $t2, -0x1
	bnez	$t2, .L1
	addiu	$t7, $t7, 0xC
.L3:
	lw	$v0, 0($a0)
	sw	$t1, GsOUT_PACKET_P
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	nop
	nop
	.end	GsU_01040048
	.set	reorder
