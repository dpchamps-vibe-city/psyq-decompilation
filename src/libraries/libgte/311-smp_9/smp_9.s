/* LIBGTE.LIB, member SMP_9.OBJ (hand-written assembly)
 *
 * void ColorDpq(VECTOR *v0, CVECTOR *v1, long p, CVECTOR *v2);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   a2  p
 *   a3  v2
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	ColorDpq
	.ent	ColorDpq
ColorDpq:
	lwc2	$9, 0($a0)
	lwc2	$10, 0x4($a0)
	lwc2	$11, 0x8($a0)
	lwc2	$6, 0($a1)
	mtc2	$a2, $8
	nop
	CDP
	swc2	$22, 0($a3)
	jr	$ra
	nop
	nop
	nop
	.end	ColorDpq
	.set	reorder
