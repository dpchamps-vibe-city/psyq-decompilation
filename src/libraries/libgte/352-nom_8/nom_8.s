/* LIBGTE.LIB, member NOM_8.OBJ (hand-written assembly)
 *
 * void RotColorDpq_nom(SVECTOR *v0, SVECTOR *v1, CVECTOR *v2);
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

	.globl	RotColorDpq_nom
	.ent	RotColorDpq_nom
RotColorDpq_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	RTPS
	cfc2	$v0, $31
	lwc2	$0, 0($a1)
	lwc2	$1, 0x4($a1)
	lwc2	$6, 0($a2)
	nop
	NCDS
	jr	$ra
	nop
	.end	RotColorDpq_nom
	.set	reorder
