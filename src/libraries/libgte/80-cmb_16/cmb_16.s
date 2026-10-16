/* LIBGTE.LIB, member CMB_16.OBJ (hand-written assembly)
 *
 * void RotTransPersN(SVECTOR *v0, DVECTOR *v1, u_short *sz, u_short *p,
 *                    u_short *flag, long n);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        sz
 *   a3        p
 *   0x10(sp)  flag
 *   0x14(sp)  n
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotTransPersN
	.ent	RotTransPersN
RotTransPersN:
	lw	$t0, 0x14($sp)
	lw	$t3, 0x10($sp)
	nop
.L1:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	RTPS
	addi	$a0, $a0, 0x8
	addi	$t0, $t0, -0x1
	swc2	$14, 0($a1)
	mfc2	$t2, $19
	mfc2	$t4, $8
	cfc2	$t1, $31
	sh	$t2, 0($a2)
	sh	$t4, 0($a3)
	srl	$t1, $t1, 12
	sh	$t1, 0($t3)
	addi	$a1, $a1, 0x4
	addi	$a2, $a2, 0x2
	addi	$a3, $a3, 0x2
	addi	$t3, $t3, 0x2
	bgtz	$t0, .L1
	nop
	jr	$ra
	nop
	nop
	nop
	nop
	.end	RotTransPersN
	.set	reorder
