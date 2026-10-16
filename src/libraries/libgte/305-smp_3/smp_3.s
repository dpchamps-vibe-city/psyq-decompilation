/* LIBGTE.LIB, member SMP_3.OBJ (hand-written assembly)
 *
 * void NormalColor(SVECTOR *v0, CVECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	NormalColor
	.ent	NormalColor
NormalColor:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	NCS
	swc2	$22, 0($a1)
	jr	$ra
	nop
	nop
	.end	NormalColor
	.set	reorder
