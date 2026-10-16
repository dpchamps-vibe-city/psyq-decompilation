/* LIBGTE.LIB, member NOM_6.OBJ (hand-written assembly)
 *
 * void RotNclip3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2);
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

	.globl	RotNclip3_nom
	.ent	RotNclip3_nom
RotNclip3_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	RTPT
	cfc2	$v0, $31
	NCLIP
	jr	$ra
	nop
	.end	RotNclip3_nom
	.set	reorder
