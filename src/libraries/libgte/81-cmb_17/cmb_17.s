/* LIBGTE.LIB, member CMB_17.OBJ (hand-written assembly)
 *
 * void RotTransPers3N(SVECTOR *v0, DVECTOR *v1, u_short *sz, u_short *flag,
 *                     long n);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        sz
 *   a3        flag
 *   0x10(sp)  n
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotTransPers3N
	.ent	RotTransPers3N
RotTransPers3N:
	lw	$t0, 0x10($sp)
	nop
.L1:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0x8($a0)
	lwc2	$3, 0xC($a0)
	lwc2	$4, 0x10($a0)
	lwc2	$5, 0x14($a0)
	nop
	RTPT
	addi	$a0, $a0, 0x18
	addi	$t0, $t0, -0x1
	swc2	$12, 0($a1)
	swc2	$13, 0x4($a1)
	swc2	$14, 0x8($a1)
	mfc2	$t2, $17
	mfc2	$t3, $18
	mfc2	$t4, $19
	cfc2	$t1, $31
	sh	$t2, 0($a2)
	sh	$t3, 0x2($a2)
	sh	$t4, 0x4($a2)
	srl	$t1, $t1, 12
	sh	$t1, 0($a3)
	addi	$a1, $a1, 0xC
	addi	$a2, $a2, 0x6
	addi	$a3, $a3, 0x2
	bgtz	$t0, .L1
	nop
	jr	$ra
	nop
	nop
	.end	RotTransPers3N
	.set	reorder
