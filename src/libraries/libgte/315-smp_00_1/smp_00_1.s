/* LIBGTE.LIB, member SMP_00_1.OBJ (hand-written assembly)
 *
 * void LightColor(VECTOR *v0, VECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	LightColor
	.ent	LightColor
LightColor:
	lwc2	$9, 0($a0)
	lwc2	$10, 0x4($a0)
	lwc2	$11, 0x8($a0)
	nop
	MVMVA	1, 2, 3, 1, 1
	swc2	$9, 0($a1)
	swc2	$10, 0x4($a1)
	swc2	$11, 0x8($a1)
	jr	$ra
	nop
	nop
	nop
	.end	LightColor
	.set	reorder
