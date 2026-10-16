/* LIBGTE.LIB, member MTX_001.OBJ (hand-written assembly)
 *
 * MATRIX *MulRotMatrix(MATRIX *m0);
 *
 * Register use:
 *   a0  m0
 *   v0  result (MATRIX *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	MulRotMatrix
	.ent	MulRotMatrix
MulRotMatrix:
	.set	noat
	lw	$t0, 0($a0)
	lw	$t1, 0x4($a0)
	lw	$t2, 0xC($a0)
	andi	$t0, $t0, 0xFFFF
	li	$at, 0xffff0000
	and	$t1, $t1, $at
	or	$t0, $t0, $t1
	mtc2	$t0, $0
	mtc2	$t2, $1
	nop
	MVMVA	1, 0, 0, 3, 0
	lhu	$t0, 0x2($a0)
	lw	$t1, 0x8($a0)
	lh	$t2, 0xE($a0)
	sll	$t1, $t1, 16
	or	$t0, $t0, $t1
	mfc2	$t3, $9
	mfc2	$t4, $10
	mfc2	$t5, $11
	mtc2	$t0, $0
	mtc2	$t2, $1
	nop
	MVMVA	1, 0, 0, 3, 0
	lhu	$t0, 0x4($a0)
	lw	$t1, 0x8($a0)
	lw	$t2, 0x10($a0)
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
	sw	$t6, 0($a0)
	andi	$t5, $t5, 0xFFFF
	sll	$t8, $t8, 16
	or	$t8, $t8, $t5
	sw	$t8, 0xC($a0)
	mfc2	$t0, $9
	mfc2	$t1, $10
	andi	$t0, $t0, 0xFFFF
	sll	$t4, $t4, 16
	or	$t0, $t0, $t4
	sw	$t0, 0x4($a0)
	andi	$t7, $t7, 0xFFFF
	sll	$t1, $t1, 16
	or	$t1, $t1, $t7
	sw	$t1, 0x8($a0)
	swc2	$11, 0x10($a0)
	move	$v0, $a0
	jr	$ra
	nop
	nop
	nop
	.set	at
	.end	MulRotMatrix
	.set	reorder
