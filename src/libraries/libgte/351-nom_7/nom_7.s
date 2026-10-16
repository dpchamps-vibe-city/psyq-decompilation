/* LIBGTE.LIB, member NOM_7.OBJ (hand-written assembly)
 *
 * void RotAverageNclip3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2);
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

	.globl	RotAverageNclip3_nom
	.ent	RotAverageNclip3_nom
RotAverageNclip3_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	RTPT
	cfc2	$v0, $31
	AVSZ3
	NCLIP
	jr	$ra
	nop
	nop
	nop
	nop
	.end	RotAverageNclip3_nom
	.set	reorder
