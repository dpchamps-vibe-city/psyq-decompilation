/* LIBGTE.LIB, member MTX_00C.OBJ (hand-written assembly)
 *
 * MATRIX *CompMatrixLV(MATRIX *m0, MATRIX *m1, MATRIX *m2);
 *
 * Register use:
 *   a0  m0
 *   a1  m1
 *   a2  m2
 *   v0  result (MATRIX *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	CompMatrixLV
	.ent	CompMatrixLV
CompMatrixLV:
	.set	noat
	lw	$t0, 0($a0)
	lw	$t1, 0x4($a0)
	lw	$t2, 0x8($a0)
	lw	$t3, 0xC($a0)
	lw	$t4, 0x10($a0)
	ctc2	$t0, $0
	ctc2	$t1, $1
	ctc2	$t2, $2
	ctc2	$t3, $3
	ctc2	$t4, $4
	lhu	$t0, 0($a1)
	lw	$t1, 0x4($a1)
	lw	$t2, 0xC($a1)
	li	$at, 0xffff0000
	and	$t1, $t1, $at
	or	$t0, $t0, $t1
	mtc2	$t0, $0
	mtc2	$t2, $1
	nop
	MVMVA	1, 0, 0, 3, 0
	lhu	$t0, 0x2($a1)
	lw	$t1, 0x8($a1)
	lh	$t2, 0xE($a1)
	sll	$t1, $t1, 16
	or	$t0, $t0, $t1
	mfc2	$t3, $9
	mfc2	$t4, $10
	mfc2	$t5, $11
	mtc2	$t0, $0
	mtc2	$t2, $1
	nop
	MVMVA	1, 0, 0, 3, 0
	lhu	$t0, 0x4($a1)
	lw	$t1, 0x8($a1)
	lw	$t2, 0x10($a1)
	li	$at, 0xffff0000
	and	$t1, $t1, $at
	or	$t0, $t0, $t1
	mfc2	$t6, $9
	mfc2	$t7, $10
	mfc2	$t8, $11
	mtc2	$t0, $0
	mtc2	$t2, $1
	nop
	MVMVA	1, 0, 0, 3, 0
	andi	$t3, $t3, 0xFFFF
	sll	$t6, $t6, 16
	or	$t6, $t6, $t3
	sw	$t6, 0($a2)
	andi	$t5, $t5, 0xFFFF
	sll	$t8, $t8, 16
	or	$t8, $t8, $t5
	sw	$t8, 0xC($a2)
	mfc2	$t0, $9
	mfc2	$t1, $10
	swc2	$11, 0x10($a2)
	sll	$t4, $t4, 16
	andi	$t0, $t0, 0xFFFF
	or	$t0, $t0, $t4
	sw	$t0, 0x4($a2)
	andi	$t7, $t7, 0xFFFF
	sll	$t1, $t1, 16
	or	$t1, $t1, $t7
	sw	$t1, 0x8($a2)
	lw	$t0, 0x14($a1)
	lw	$t1, 0x18($a1)
	lw	$t2, 0x1C($a1)
	bgez	$t0, .L1
	nop
	negu	$t0, $t0
	sra	$t3, $t0, 15
	negu	$t3, $t3
	andi	$t0, $t0, 0x7FFF
	b	.L2
	negu	$t0, $t0
.L1:
	sra	$t3, $t0, 15
	andi	$t0, $t0, 0x7FFF
.L2:
	bgez	$t1, .L3
	nop
	negu	$t1, $t1
	sra	$t4, $t1, 15
	negu	$t4, $t4
	andi	$t1, $t1, 0x7FFF
	b	.L4
	negu	$t1, $t1
.L3:
	sra	$t4, $t1, 15
	andi	$t1, $t1, 0x7FFF
.L4:
	bgez	$t2, .L5
	nop
	negu	$t2, $t2
	sra	$t5, $t2, 15
	negu	$t5, $t5
	andi	$t2, $t2, 0x7FFF
	b	.L6
	negu	$t2, $t2
.L5:
	sra	$t5, $t2, 15
	andi	$t2, $t2, 0x7FFF
.L6:
	mtc2	$t3, $9
	mtc2	$t4, $10
	mtc2	$t5, $11
	nop
	MVMVA	0, 0, 3, 3, 0
	mfc2	$t3, $25
	mfc2	$t4, $26
	mfc2	$t5, $27
	mtc2	$t0, $9
	mtc2	$t1, $10
	mtc2	$t2, $11
	nop
	MVMVA	1, 0, 3, 3, 0
	bgez	$t3, .L7
	nop
	negu	$t3, $t3
	sll	$t3, $t3, 3
	b	.L8
	negu	$t3, $t3
.L7:
	sll	$t3, $t3, 3
.L8:
	bgez	$t4, .L9
	nop
	negu	$t4, $t4
	sll	$t4, $t4, 3
	b	.L10
	negu	$t4, $t4
.L9:
	sll	$t4, $t4, 3
.L10:
	bgez	$t5, .L11
	nop
	negu	$t5, $t5
	sll	$t5, $t5, 3
	b	.L12
	negu	$t5, $t5
.L11:
	sll	$t5, $t5, 3
.L12:
	mfc2	$t0, $25
	mfc2	$t1, $26
	mfc2	$t2, $27
	addu	$t0, $t0, $t3
	addu	$t1, $t1, $t4
	addu	$t2, $t2, $t5
	lw	$t3, 0x14($a0)
	lw	$t4, 0x18($a0)
	lw	$t5, 0x1C($a0)
	addu	$t0, $t0, $t3
	addu	$t1, $t1, $t4
	addu	$t2, $t2, $t5
	sw	$t0, 0x14($a2)
	sw	$t1, 0x18($a2)
	sw	$t2, 0x1C($a2)
	jr	$ra
	move	$v0, $a2
	.set	at
	.end	CompMatrixLV
	.set	reorder
