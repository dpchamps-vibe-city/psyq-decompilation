/* LIBGTE.LIB, member MTX_05.OBJ (hand-written assembly)
 *
 * VECTOR *ApplyMatrix(MATRIX *m, SVECTOR *v0, VECTOR *v1);
 *
 * Register use:
 *   a0  m
 *   a1  v0
 *   a2  v1
 *   v0  result (VECTOR *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	ApplyMatrix
	.ent	ApplyMatrix
ApplyMatrix:
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
	swc2	$25, 0($a2)
	swc2	$26, 0x4($a2)
	swc2	$27, 0x8($a2)
	move	$v0, $a2
	jr	$ra
	nop
	.end	ApplyMatrix
	.set	reorder
