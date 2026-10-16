/* LIBGTE.LIB, member NOM_12.OBJ (hand-written assembly)
 *
 * void NormalColor_nom(SVECTOR *v0);
 *
 * Register use:
 *   a0  v0
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	NormalColor_nom
	.ent	NormalColor_nom
NormalColor_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	NCS
	jr	$ra
	nop
	nop
	nop
	.end	NormalColor_nom
	.set	reorder
