/* LIBGTE.LIB, member SMP_1.OBJ (hand-written assembly)
 *
 * void LocalLight(SVECTOR *v0, VECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	LocalLight
	.ent	LocalLight
LocalLight:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	MVMVA	1, 1, 0, 3, 1
	swc2	$9, 0($a1)
	swc2	$10, 0x4($a1)
	swc2	$11, 0x8($a1)
	jr	$ra
	nop
	nop
	nop
	nop
	.end	LocalLight
	.set	reorder
