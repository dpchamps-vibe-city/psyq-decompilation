/* LIBHMD.LIB, member 00300014.OBJ (hand-written assembly)
 *
 * u_long *GsU_00300014(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x00300014 (GsUBSTPG4): back-face semi-trans gouraud quad.
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_00300014
	.ent	GsU_00300014
GsU_00300014:
	.set	noat
	lw	$a3, 0($a0)
	lw	$t9, 0x4($a0)
	lw	$t8, 0($a3)
	addiu	$a3, $a3, 0x4
	srl	$t8, $t8, 16
	lw	$a2, 0($a3)
	lw	$a1, 0x14($a0)
	sll	$a2, $a2, 2
	lw	$t7, 0x8($a0)
	beqz	$t8, .L10
	addu	$a3, $a1, $a2
	lw	$t0, 0x4($t9)
	lw	$t1, 0xC($a0)
	addiu	$v0, $a0, 0x10
	lw	$t9, 0($v0)
	lw	$a1, 0x18($a0)
	lw	$a2, 0x1C($a0)
.L1:
	lw	$t2, 0x4($a3)
	lw	$t3, 0x8($a3)
	lw	$t4, 0xC($a3)
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
	lw	$t5, 0x10($a3)
	sll	$t2, $t2, 16
	srl	$t2, $t2, 13
	addu	$t2, $t2, $a2
	sll	$t3, $t3, 16
	srl	$t3, $t3, 13
	addu	$t3, $t3, $a2
	sll	$t4, $t4, 16
	srl	$t4, $t4, 13
	addu	$t4, $t4, $a2
	srl	$v1, $t5, 16
	sll	$v1, $v1, 3
	addu	$v1, $v1, $a1
	sll	$t5, $t5, 16
	srl	$t5, $t5, 13
	addu	$t5, $t5, $a2
	cfc2	$v0, $31
	nop
	bltz	$v0, .L9
	nop
	NCLIP
	lwc2	$0, 0($v1)
	lwc2	$1, 0x4($v1)
	mfc2	$v1, $24
	nop
	swc2	$12, 0x8($t9)
	swc2	$13, 0x10($t9)
	swc2	$14, 0x18($t9)
	nop
	nop
	RTPS
	lw	$v0, 0($a3)
	nop
	li	$at, 0x2000000
	or	$v0, $v0, $at
	mtc2	$v0, $6
	bgez	$v1, .L3
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
	mtc2	$t6, $2
	mtc2	$v0, $3
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
	mtc2	$t6, $4
	mtc2	$v0, $5
	j	.L4
	nop
.L3:
	lwc2	$2, 0($t3)
	lwc2	$3, 0x4($t3)
	lwc2	$4, 0($t4)
	lwc2	$5, 0x4($t4)
.L4:
	cfc2	$v0, $31
	nop
	bltz	$v0, .L9
	nop
	AVSZ4
	bgez	$v1, .L5
	nop
	lw	$t6, 0($t5)
	lw	$v0, 0x4($t5)
	negu	$t6, $t6
	sll	$t5, $t6, 16
	negu	$t5, $t5
	srl	$t5, $t5, 16
	li	$at, 0xffff0000
	and	$t6, $t6, $at
	or	$t6, $t6, $t5
	sll	$v0, $v0, 16
	negu	$v0, $v0
	srl	$v0, $v0, 16
	mtc2	$t6, $0
	mtc2	$v0, $1
	j	.L6
	nop
.L5:
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
.L6:
	mfc2	$t6, $7
	nop
	nop
	NCCS
	swc2	$22, 0x1C($t9)
	nop
	bgez	$v1, .L7
	nop
	lw	$t5, 0($t2)
	lw	$v0, 0x4($t2)
	negu	$t5, $t5
	sll	$t2, $t5, 16
	negu	$t2, $t2
	srl	$t2, $t2, 16
	li	$at, 0xffff0000
	and	$t5, $t5, $at
	or	$t5, $t5, $t2
	sll	$v0, $v0, 16
	negu	$v0, $v0
	srl	$v0, $v0, 16
	mtc2	$t5, $0
	mtc2	$v0, $1
	j	.L8
	nop
.L7:
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	nop
	nop
.L8:
	NCCT
	addiu	$a3, $a3, 0x14
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t5, 0($t6)
	li	$v0, 0x8000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($t9)
	xor	$v0, $t9, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	lw	$t2, 0x4($a3)
	lw	$t3, 0x8($a3)
	lw	$t4, 0xC($a3)
	nop
	swc2	$14, 0x20($t9)
	swc2	$20, 0x4($t9)
	swc2	$21, 0xC($t9)
	swc2	$22, 0x14($t9)
	addiu	$t9, $t9, 0x24
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L2
	nop
	b	.L10
	nop
.L9:
	addiu	$a3, $a3, 0x14
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L10:
	lw	$v0, 0($a0)
	lui	$at, %hi(GsOUT_PACKET_P)
	sw	$t9, %lo(GsOUT_PACKET_P)($at)
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	nop
	nop
	nop
	.set	at
	.end	GsU_00300014
	.set	reorder
