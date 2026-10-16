/* LIBGTE.LIB, member SMP_00_6.OBJ (hand-written assembly)
 *
 * VECTOR *Square0(VECTOR *v0, VECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   v0  result (VECTOR *)
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	Square0
	.ent	Square0
Square0:
	lwc2	$9, 0($a0)
	lwc2	$10, 0x4($a0)
	lwc2	$11, 0x8($a0)
	nop
	SQR	0
	swc2	$25, 0($a1)
	swc2	$26, 0x4($a1)
	swc2	$27, 0x8($a1)
	move	$v0, $a1
	jr	$ra
	.end	Square0
