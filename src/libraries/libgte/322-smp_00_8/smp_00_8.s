/* LIBGTE.LIB, member SMP_00_8.OBJ (hand-written assembly)
 *
 * long AverageZ4(long sz0, long sz1, long sz2, long sz3);
 *
 * Register use:
 *   a0  sz0
 *   a1  sz1
 *   a2  sz2
 *   a3  sz3
 *   v0  result (long)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	AverageZ4
	.ent	AverageZ4
AverageZ4:
	mtc2	$a0, $16
	mtc2	$a1, $17
	mtc2	$a2, $18
	mtc2	$a3, $19
	nop
	AVSZ4
	mfc2	$v0, $7
	jr	$ra
	nop
	nop
	nop
	nop
	.end	AverageZ4
	.set	reorder
