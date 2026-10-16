/* LIBGTE.LIB, member NOM_2.OBJ (hand-written assembly)
 *
 * void RotTransPers3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2);
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

	.globl	RotTransPers3_nom
	.ent	RotTransPers3_nom
RotTransPers3_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	RTPT
	jr	$ra
	nop
	nop
	nop
	.end	RotTransPers3_nom
	.set	reorder
