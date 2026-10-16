/* LIBGTE.LIB, member MTX_00B.OBJ (hand-written assembly)
 *
 * MATRIX *SetMulMatrix(MATRIX *m0, MATRIX *m1);
 *
 * Register use:
 *   a0  m0
 *   a1  m1
 *   v0  result (MATRIX *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	SetMulMatrix
	.ent	SetMulMatrix
SetMulMatrix:
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
	andi	$t5, $t5, 0xFFFF
	sll	$t8, $t8, 16
	or	$t8, $t8, $t5
	mfc2	$t0, $9
	mfc2	$t1, $10
	mfc2	$t2, $11
	andi	$t0, $t0, 0xFFFF
	sll	$t4, $t4, 16
	or	$t0, $t0, $t4
	andi	$t7, $t7, 0xFFFF
	sll	$t1, $t1, 16
	or	$t1, $t1, $t7
	ctc2	$t6, $0
	ctc2	$t0, $1
	ctc2	$t1, $2
	ctc2	$t8, $3
	ctc2	$t2, $4
	move	$v0, $a0
	jr	$ra
	nop
	.set	at
	.end	SetMulMatrix
	.set	reorder
