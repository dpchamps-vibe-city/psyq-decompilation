/* LIBGTE.LIB, member SMP_02.OBJ (hand-written assembly)
 *
 * long RotTransPers(SVECTOR *v0, long *sxy, long *p, long *flag);
 *
 * Register use:
 *   a0  v0
 *   a1  sxy
 *   a2  p
 *   a3  flag
 *   v0  result (long)
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	RotTransPers
	.ent	RotTransPers
RotTransPers:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	RTPS
	swc2	$14, 0($a1)
	swc2	$8, 0($a2)
	cfc2	$v1, $31
	mfc2	$v0, $19
	sw	$v1, 0($a3)
	sra	$v0, $v0, 2
	jr	$ra
	.end	RotTransPers
