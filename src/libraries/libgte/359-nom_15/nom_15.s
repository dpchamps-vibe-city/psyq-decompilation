/* LIBGTE.LIB, member NOM_15.OBJ (hand-written assembly)
 *
 * void NormalColorDpq3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2,
 *                          CVECTOR *v3, long p);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        v3
 *   0x10(sp)  p
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	NormalColorDpq3_nom
	.ent	NormalColorDpq3_nom
NormalColorDpq3_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	lwc2	$6, 0($a3)
	lwc2	$8, 0x10($sp)
	nop
	NCDT
	jr	$ra
	nop
	.end	NormalColorDpq3_nom
	.set	reorder
