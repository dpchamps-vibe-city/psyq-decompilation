/* LIBGTE.LIB, member SMP_04.OBJ (hand-written assembly)
 *
 * void RotTrans(SVECTOR *v0, VECTOR *v1, long *flag);
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

	.globl	RotTrans
	.ent	RotTrans
RotTrans:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	MVMVA	1, 0, 0, 0, 0
	swc2	$25, 0($a1)
	swc2	$26, 0x4($a1)
	swc2	$27, 0x8($a1)
	cfc2	$v0, $31
	jr	$ra
	sw	$v0, 0($a2)
	nop
	nop
	.end	RotTrans
	.set	reorder
