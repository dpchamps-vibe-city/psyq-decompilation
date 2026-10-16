/* LIBGTE.LIB, member CMB_14.OBJ (hand-written assembly)
 *
 * long RotColorMatDpq(SVECTOR *v0, SVECTOR *v1, CVECTOR *v2, long *sxy,
 *                     CVECTOR *v3, long matc, long flag);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        sxy
 *   0x10(sp)  v3
 *   0x14(sp)  matc
 *   0x18(sp)  flag
 *   v0        result (long)
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	RotColorMatDpq
	.ent	RotColorMatDpq
RotColorMatDpq:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	RTPS
	lw	$t0, 0x18($sp)
	cfc2	$v0, $31
	sw	$v0, 0($t0)
	lwc2	$0, 0($a1)
	lwc2	$1, 0x4($a1)
	nop
	MVMVA	1, 1, 0, 3, 1
	lw	$t0, 0x14($sp)
.L1:
	SQR	1
	addi	$t0, $t0, -0x1
	bgtz	$t0, .L1
	lwc2	$6, 0($a2)
	nop
	CDP
	lw	$t0, 0x10($sp)
	swc2	$14, 0($a3)
	mfc2	$v0, $19
	swc2	$22, 0($t0)
	sra	$v0, $v0, 2
	jr	$ra
	.end	RotColorMatDpq
