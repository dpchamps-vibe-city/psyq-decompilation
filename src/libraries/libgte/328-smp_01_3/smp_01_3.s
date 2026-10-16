/* LIBGTE.LIB, member SMP_01_3.OBJ (hand-written assembly)
 *
 * SVECTOR *SquareSS0(SVECTOR *v0, SVECTOR *v1);
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

	.globl	SquareSS0
	.ent	SquareSS0
SquareSS0:
	lh	$v0, 0($a0)
	lh	$v1, 0x2($a0)
	mtc2	$v0, $9
	mtc2	$v1, $10
	lwc2	$11, 0x4($a0)
	nop
	SQR	0
	mfc2	$v0, $9
	mfc2	$v1, $10
	swc2	$11, 0x4($a1)
	sh	$v0, 0($a1)
	sh	$v1, 0x2($a1)
	jr	$ra
	move	$v0, $a1
	nop
	nop
	.end	SquareSS0
	.set	reorder
