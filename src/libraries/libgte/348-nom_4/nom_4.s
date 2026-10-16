/* LIBGTE.LIB, member NOM_4.OBJ (hand-written assembly)
 *
 * void RotTransPers4_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2,
 *                        SVECTOR *v3);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   a2  v2
 *   a3  v3
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotTransPers4_nom
	.ent	RotTransPers4_nom
RotTransPers4_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	RTPT
	cfc2	$v0, $31
	mfc2	$v1, $12
	lwc2	$0, 0($a3)
	lwc2	$1, 0x4($a3)
	nop
	RTPS
	jr	$ra
	nop
	.end	RotTransPers4_nom
	.set	reorder
