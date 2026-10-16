/* LIBGTE.LIB, member NOM_1.OBJ (hand-written assembly)
 *
 * void RotTransPers_nom(SVECTOR *v0);
 *
 * Register use:
 *   a0  v0
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotTransPers_nom
	.ent	RotTransPers_nom
RotTransPers_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	RTPS
	jr	$ra
	nop
	nop
	nop
	.end	RotTransPers_nom
	.set	reorder
