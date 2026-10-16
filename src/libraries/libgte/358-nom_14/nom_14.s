/* LIBGTE.LIB, member NOM_14.OBJ (hand-written assembly)
 *
 * void NormalColorDpq_nom(SVECTOR *v0, CVECTOR *v1, long p);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   a2  p
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	NormalColorDpq_nom
	.ent	NormalColorDpq_nom
NormalColorDpq_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$6, 0($a1)
	mtc2	$a2, $8
	nop
	NCDS
	jr	$ra
	nop
	.end	NormalColorDpq_nom
	.set	reorder
