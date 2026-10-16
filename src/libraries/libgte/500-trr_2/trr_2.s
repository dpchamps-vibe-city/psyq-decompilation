/* LIBGTE.LIB, member TRR_2.OBJ (hand-written assembly)
 *
 * long TransRotPers(SVECTOR *v0, long *sxy, long *p, long *flag);
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
	.set	noreorder

	.globl	TransRotPers
	.ent	TransRotPers
TransRotPers:
	cfc2	$t3, $5
	cfc2	$t4, $6
	cfc2	$t5, $7
	ctc2	$zero, $5
	ctc2	$zero, $6
	ctc2	$zero, $7
	lh	$t0, 0($a0)
	lh	$t1, 0x2($a0)
	lh	$t2, 0x4($a0)
	add	$t0, $t0, $t3
	add	$t1, $t1, $t4
	add	$t2, $t2, $t5
	andi	$t0, $t0, 0xFFFF
	sll	$t1, $t1, 16
	or	$t1, $t1, $t0
	mtc2	$t1, $0
	mtc2	$t2, $1
	nop
	RTPS
	swc2	$14, 0($a1)
	swc2	$8, 0($a2)
	cfc2	$v1, $31
	mfc2	$v0, $19
	ctc2	$t3, $5
	ctc2	$t4, $6
	ctc2	$t5, $7
	sw	$v1, 0($a3)
	jr	$ra
	sra	$v0, $v0, 2
	nop
	nop
	nop
	.end	TransRotPers
	.set	reorder
