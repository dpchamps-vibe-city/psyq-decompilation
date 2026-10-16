/* LIBHMD.LIB, member 0010000F.OBJ (hand-written assembly)
 *
 * u_long *GsU_0010000f(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x0010000f (GsUBCGT3): back-face colored texture gouraud triangle.
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_0010000f
	.ent	GsU_0010000f
GsU_0010000f:
	.set	noat
	lw	$a3, 0($a0)
	lw	$t9, 0x4($a0)
	lw	$t8, 0($a3)
	lw	$t7, 0x8($a0)
	addiu	$a3, $a3, 0x4
	lw	$a2, 0($a3)
	lw	$a1, 0x14($a0)
	sll	$a2, $a2, 2
	srl	$t8, $t8, 16
	beqz	$t8, .L9
	addu	$a3, $a1, $a2
	lw	$t0, 0x4($t9)
	lw	$t1, 0xC($a0)
	addiu	$v0, $a0, 0x10
	lw	$t9, 0($v0)
	lw	$a1, 0x18($a0)
	lw	$a2, 0x1C($a0)
	sw	$s0, 0x10($a0)
.L1:
	lw	$t2, 0x18($a3)
	lw	$t3, 0x1C($a3)
	lw	$t4, 0x20($a3)
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
	sll	$t2, $t2, 16
	nop
	RTPT
	srl	$t2, $t2, 13
	addu	$t2, $t2, $a2
	sll	$t3, $t3, 16
	srl	$t3, $t3, 13
	addu	$t3, $t3, $a2
	sll	$t4, $t4, 16
	srl	$t4, $t4, 13
	addu	$t4, $t4, $a2
	lw	$t5, 0($a3)
	nop
	mtc2	$t5, $6
	cfc2	$v0, $31
	nop
	bltz	$v0, .L8
	nop
	NCLIP
	mfc2	$s0, $24
	nop
	nop
	AVSZ3
	bgez	$s0, .L2
	nop
	lw	$t6, 0($t2)
	lw	$v0, 0x4($t2)
	negu	$t6, $t6
	sll	$t2, $t6, 16
	negu	$t2, $t2
	srl	$t2, $t2, 16
	li	$at, 0xffff0000
	and	$t6, $t6, $at
	or	$t6, $t6, $t2
	sll	$v0, $v0, 16
	negu	$v0, $v0
	srl	$v0, $v0, 16
	mtc2	$t6, $0
	mtc2	$v0, $1
	j	.L3
	nop
.L2:
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
.L3:
	mfc2	$t6, $7
	nop
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
	sw	$v0, 0($t9)
	nop
	xor	$v0, $t9, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	lw	$t5, 0x4($a3)
	swc2	$12, 0x8($t9)
	swc2	$22, 0x4($t9)
	bgez	$s0, .L4
	nop
	lw	$t6, 0($t3)
	lw	$v0, 0x4($t3)
	negu	$t6, $t6
	sll	$t3, $t6, 16
	negu	$t3, $t3
	srl	$t3, $t3, 16
	li	$at, 0xffff0000
	and	$t6, $t6, $at
	or	$t6, $t6, $t3
	sll	$v0, $v0, 16
	negu	$v0, $v0
	srl	$v0, $v0, 16
	mtc2	$t6, $0
	mtc2	$v0, $1
	j	.L5
	nop
.L4:
	lwc2	$0, 0($t3)
	lwc2	$1, 0x4($t3)
.L5:
	mtc2	$t5, $6
	nop
	nop
	NCCS
	lw	$t5, 0x8($a3)
	nop
	swc2	$13, 0x14($t9)
	swc2	$22, 0x10($t9)
	bgez	$s0, .L6
	nop
	lw	$t6, 0($t4)
	lw	$v0, 0x4($t4)
	negu	$t6, $t6
	sll	$t4, $t6, 16
	negu	$t4, $t4
	srl	$t4, $t4, 16
	li	$at, 0xffff0000
	and	$t6, $t6, $at
	or	$t6, $t6, $t4
	sll	$v0, $v0, 16
	negu	$v0, $v0
	srl	$v0, $v0, 16
	mtc2	$t6, $0
	mtc2	$v0, $1
	j	.L7
	nop
.L6:
	lwc2	$0, 0($t4)
	lwc2	$1, 0x4($t4)
.L7:
	mtc2	$t5, $6
	nop
	nop
	NCCS
	lw	$t2, 0xC($a3)
	lw	$t3, 0x10($a3)
	lw	$t4, 0x14($a3)
	sw	$t2, 0xC($t9)
	sw	$t3, 0x18($t9)
	sw	$t4, 0x24($t9)
	swc2	$14, 0x20($t9)
	swc2	$22, 0x1C($t9)
	addiu	$t9, $t9, 0x28
.L8:
	addiu	$a3, $a3, 0x24
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L9:
	lw	$s0, 0x10($a0)
	lw	$v0, 0($a0)
	lui	$at, %hi(GsOUT_PACKET_P)
	sw	$t9, %lo(GsOUT_PACKET_P)($at)
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	nop
	.set	at
	.end	GsU_0010000f
	.set	reorder
