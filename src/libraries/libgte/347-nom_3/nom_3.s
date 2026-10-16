/* LIBGTE.LIB, member NOM_3.OBJ (hand-written assembly)
 *
 * void RotTrans_nom(SVECTOR *v0);
 *
 * Register use:
 *   a0  v0
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotTrans_nom
	.ent	RotTrans_nom
RotTrans_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	MVMVA	1, 0, 0, 0, 0
	jr	$ra
	nop
	nop
	nop
	.end	RotTrans_nom
	.set	reorder
