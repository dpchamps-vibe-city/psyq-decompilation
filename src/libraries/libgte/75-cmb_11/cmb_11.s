/* LIBGTE.LIB, member CMB_11.OBJ (hand-written assembly)
 *
 * void ColorMatCol(SVECTOR *v0, CVECTOR *v1, CVECTOR *v2, long matc);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   a2  v2
 *   a3  matc
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	ColorMatCol
	.ent	ColorMatCol
ColorMatCol:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	MVMVA	1, 1, 0, 3, 1
	move	$t0, $a3
.L1:
	SQR	1
	addi	$t0, $t0, -0x1
	bgtz	$t0, .L1
	nop
	lwc2	$6, 0($a1)
	nop
	CC
	swc2	$22, 0($a2)
	jr	$ra
	nop
	nop
	.end	ColorMatCol
	.set	reorder
