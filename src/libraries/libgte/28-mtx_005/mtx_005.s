/* LIBGTE.LIB, member MTX_005.OBJ (hand-written assembly)
 *
 * VECTOR *ApplyRotMatrix(SVECTOR *v0, VECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   v0  result (VECTOR *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	ApplyRotMatrix
	.ent	ApplyRotMatrix
ApplyRotMatrix:
	lw	$t0, 0($a0)
	lw	$t1, 0x4($a0)
	mtc2	$t0, $0
	mtc2	$t1, $1
	nop
	MVMVA	1, 0, 0, 3, 0
	swc2	$9, 0($a1)
	swc2	$10, 0x4($a1)
	swc2	$11, 0x8($a1)
	move	$v0, $a1
	jr	$ra
	nop
	.end	ApplyRotMatrix
	.set	reorder
