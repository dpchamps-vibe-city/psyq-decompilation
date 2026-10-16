/* LIBGTE.LIB, member SMP_2.OBJ (hand-written assembly)
 *
 * void DpqColor(CVECTOR *v0, long p, CVECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  p
 *   a2  v1
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	DpqColor
	.ent	DpqColor
DpqColor:
	lwc2	$6, 0($a0)
	mtc2	$a1, $8
	nop
	DPCS
	swc2	$22, 0($a2)
	jr	$ra
	nop
	nop
	.end	DpqColor
	.set	reorder
