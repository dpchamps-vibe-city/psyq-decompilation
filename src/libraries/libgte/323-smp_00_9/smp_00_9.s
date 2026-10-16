/* LIBGTE.LIB, member SMP_00_9.OBJ (hand-written assembly)
 *
 * void OuterProduct12(VECTOR *v0, VECTOR *v1, VECTOR *v2);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   a2  v2
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	OuterProduct12
	.ent	OuterProduct12
OuterProduct12:
	cfc2	$t5, $0
	cfc2	$t6, $2
	cfc2	$t7, $4
	lw	$t0, 0($a0)
	lw	$t1, 0x4($a0)
	lw	$t2, 0x8($a0)
	ctc2	$t0, $0
	ctc2	$t1, $2
	ctc2	$t2, $4
	lwc2	$11, 0x8($a1)
	lwc2	$9, 0($a1)
	lwc2	$10, 0x4($a1)
	nop
	OP	1
	swc2	$25, 0($a2)
	swc2	$26, 0x4($a2)
	swc2	$27, 0x8($a2)
	ctc2	$t5, $0
	ctc2	$t6, $2
	ctc2	$t7, $4
	jr	$ra
	.end	OuterProduct12
