/* LIBGTE.LIB, member SMP_01_4.OBJ (hand-written assembly)
 *
 * VECTOR *SquareSL12(SVECTOR *v0, VECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   v0  result (VECTOR *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	SquareSL12
	.ent	SquareSL12
SquareSL12:
	lh	$v0, 0($a0)
	lh	$v1, 0x2($a0)
	mtc2	$v0, $9
	mtc2	$v1, $10
	lwc2	$11, 0x4($a0)
	nop
	SQR	1
	swc2	$9, 0($a1)
	swc2	$10, 0x4($a1)
	swc2	$11, 0x8($a1)
	jr	$ra
	move	$v0, $a1
	.end	SquareSL12
	.set	reorder
