/* LIBGTE.LIB, member SMP_00_4.OBJ (hand-written assembly)
 *
 * void Intpl(VECTOR *v0, long p, CVECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  p
 *   a2  v1
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	Intpl
	.ent	Intpl
Intpl:
	lwc2	$9, 0($a0)
	lwc2	$10, 0x4($a0)
	lwc2	$11, 0x8($a0)
	mtc2	$a1, $8
	nop
	INTPL
	swc2	$22, 0($a2)
	jr	$ra
	nop
	nop
	nop
	nop
	.end	Intpl
	.set	reorder
