/* LIBGTE.LIB, member SMP_7.OBJ (hand-written assembly)
 *
 * void NormalColorCol(SVECTOR *v0, CVECTOR *v1, CVECTOR *v2);
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

	.globl	NormalColorCol
	.ent	NormalColorCol
NormalColorCol:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$6, 0($a1)
	nop
	NCCS
	swc2	$22, 0($a2)
	jr	$ra
	nop
	.end	NormalColorCol
	.set	reorder
