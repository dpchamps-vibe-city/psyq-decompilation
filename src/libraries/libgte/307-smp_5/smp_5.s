/* LIBGTE.LIB, member SMP_5.OBJ (hand-written assembly)
 *
 * void NormalColorDpq(SVECTOR *v0, CVECTOR *v1, long p, CVECTOR *v2);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   a2  p
 *   a3  v2
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	NormalColorDpq
	.ent	NormalColorDpq
NormalColorDpq:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$6, 0($a1)
	mtc2	$a2, $8
	nop
	NCDS
	swc2	$22, 0($a3)
	jr	$ra
	nop
	nop
	nop
	nop
	.end	NormalColorDpq
	.set	reorder
