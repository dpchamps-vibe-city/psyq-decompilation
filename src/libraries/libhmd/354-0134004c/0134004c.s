/* LIBHMD.LIB, member 0134004C.OBJ (hand-written assembly)
 *
 * u_long *GsU_0134004c(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x0134004c (GsUBSTPSNG3): back-face semi-trans shared nonLight gouraud triangle.
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_0134004c
	.ent	GsU_0134004c
GsU_0134004c:
	.set	noat
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
	lw	$a1, 0xC($t7)
	lw	$a2, 0x10($t7)
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
	sw	$v0, 0x8($t1)
	sw	$t0, 0x10($t1)
	sw	$t3, 0x18($t1)
	AVSZ3
	lw	$v0, 0($t7)
	lw	$t0, 0x4($t7)
	lw	$t3, 0x8($t7)
	li	$at, 0x2000000
	or	$v0, $v0, $at
	sw	$v0, 0x4($t1)
	sw	$t0, 0xC($t1)
	sw	$t3, 0x14($t1)
	mfc2	$t4, $7
	nop
	subu	$t4, $t4, $t6
	srlv	$t4, $t4, $t9
	andi	$t4, $t4, 0xFFFF
	sll	$t4, $t4, 2
	addu	$t4, $t4, $a3
	lw	$v0, 0($t4)
	li	$v1, 0x6000000
	sll	$t3, $v0, 8
	srl	$t3, $t3, 8
	or	$v1, $v1, $t3
	sw	$v1, 0($t1)
	xor	$v1, $t1, $v0
	sll	$t3, $v1, 8
	srl	$v1, $t3, 8
	xor	$t3, $v1, $v0
	sw	$t3, 0($t4)
	addiu	$t1, $t1, 0x1C
.L2:
	addiu	$t2, $t2, -0x1
	bnez	$t2, .L1
	addiu	$t7, $t7, 0x14
.L3:
	lw	$v0, 0($a0)
	lui	$at, %hi(GsOUT_PACKET_P)
	sw	$t1, %lo(GsOUT_PACKET_P)($at)
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	nop
	nop
	.set	at
	.end	GsU_0134004c
	.set	reorder
