/* LIBGTE.LIB, member SMP_10.OBJ (hand-written assembly)
 *
 * void ColorCol(VECTOR *v0, CVECTOR *v1, CVECTOR *v2);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   a2  v2
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	ColorCol
	.ent	ColorCol
ColorCol:
	lwc2	$9, 0($a0)
	lwc2	$10, 0x4($a0)
	lwc2	$11, 0x8($a0)
	lwc2	$6, 0($a1)
	nop
	CC
	swc2	$22, 0($a2)
	jr	$ra
	nop
	nop
	nop
	nop
	.end	ColorCol
	.set	reorder
