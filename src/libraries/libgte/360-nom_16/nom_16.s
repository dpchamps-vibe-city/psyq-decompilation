/* LIBGTE.LIB, member NOM_16.OBJ (hand-written assembly)
 *
 * void NormalColorCol_nom(SVECTOR *v0, CVECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	NormalColorCol_nom
	.ent	NormalColorCol_nom
NormalColorCol_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$6, 0($a1)
	nop
	NCCS
	jr	$ra
	nop
	nop
	.end	NormalColorCol_nom
	.set	reorder
