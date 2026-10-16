/* LIBGTE.LIB, member SMP_01_2.OBJ (hand-written assembly)
 *
 * SVECTOR *SquareSS12(SVECTOR *v0, SVECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   v0  result (SVECTOR *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	SquareSS12
	.ent	SquareSS12
SquareSS12:
	lh	$v0, 0($a0)
	lh	$v1, 0x2($a0)
	mtc2	$v0, $9
	mtc2	$v1, $10
	lwc2	$11, 0x4($a0)
	nop
	SQR	1
	mfc2	$v0, $9
	mfc2	$v1, $10
	swc2	$11, 0x4($a1)
	sh	$v0, 0($a1)
	sh	$v1, 0x2($a1)
	jr	$ra
	move	$v0, $a1
	nop
	nop
	.end	SquareSS12
	.set	reorder
