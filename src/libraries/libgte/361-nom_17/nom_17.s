/* LIBGTE.LIB, member NOM_17.OBJ (hand-written assembly)
 *
 * void NormalColorCol3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2,
 *                          CVECTOR *v3);
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

	.globl	NormalColorCol3_nom
	.ent	NormalColorCol3_nom
NormalColorCol3_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	lwc2	$6, 0($a3)
	nop
	NCCT
	jr	$ra
	nop
	nop
	.end	NormalColorCol3_nom
	.set	reorder
