/* LIBGTE.LIB, member SMP_00_7.OBJ (hand-written assembly)
 *
 * long AverageZ3(long sz0, long sz1, long sz2);
 *
 * Register use:
 *   a0  sz0
 *   a1  sz1
 *   a2  sz2
 *   v0  result (long)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	AverageZ3
	.ent	AverageZ3
AverageZ3:
	mtc2	$a0, $17
	mtc2	$a1, $18
	mtc2	$a2, $19
	nop
	AVSZ3
	mfc2	$v0, $7
	jr	$ra
	nop
	.end	AverageZ3
	.set	reorder
