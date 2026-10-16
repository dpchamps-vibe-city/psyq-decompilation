/* LIBGTE.LIB, member SMP_01_1.OBJ (hand-written assembly)
 *
 * void RotTransSV(SVECTOR *v0, SVECTOR *v1, long *flag);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   a2  flag
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotTransSV
	.ent	RotTransSV
RotTransSV:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	MVMVA	1, 0, 0, 0, 0
	mfc2	$v0, $9
	mfc2	$v1, $10
	swc2	$11, 0x4($a1)
	sh	$v0, 0($a1)
	sh	$v1, 0x2($a1)
	cfc2	$v0, $31
	jr	$ra
	sw	$v0, 0($a2)
	.end	RotTransSV
	.set	reorder
