/* LIBGTE.LIB, member SMP_00_5.OBJ (hand-written assembly)
 *
 * VECTOR *Square12(VECTOR *v0, VECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   v0  result (VECTOR *)
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	Square12
	.ent	Square12
Square12:
	lwc2	$9, 0($a0)
	lwc2	$10, 0x4($a0)
	lwc2	$11, 0x8($a0)
	nop
	SQR	1
	swc2	$25, 0($a1)
	swc2	$26, 0x4($a1)
	swc2	$27, 0x8($a1)
	move	$v0, $a1
	jr	$ra
	.end	Square12
