/* LIBGTE.LIB, member MTX_06.OBJ (hand-written assembly)
 *
 * SVECTOR *ApplyMatrixSV(MATRIX *m, SVECTOR *v0, SVECTOR *v1);
 *
 * Register use:
 *   a0  m
 *   a1  v0
 *   a2  v1
 *   v0  result (SVECTOR *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	ApplyMatrixSV
	.ent	ApplyMatrixSV
ApplyMatrixSV:
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
	lwc2	$0, 0($a1)
	lwc2	$1, 0x4($a1)
	nop
	MVMVA	1, 0, 0, 3, 0
	mfc2	$t0, $9
	mfc2	$t1, $10
	mfc2	$t2, $11
	sh	$t0, 0($a2)
	sh	$t1, 0x2($a2)
	sh	$t2, 0x4($a2)
	move	$v0, $a2
	jr	$ra
	nop
	nop
	.end	ApplyMatrixSV
	.set	reorder
