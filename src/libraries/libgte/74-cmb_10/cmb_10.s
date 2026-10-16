/* LIBGTE.LIB, member CMB_10.OBJ (hand-written assembly)
 *
 * void ColorMatDpq(SVECTOR *v0, CVECTOR *v1, long p, CVECTOR *v2,
 *                  long matc);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        p
 *   a3        v2
 *   0x10(sp)  matc
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	ColorMatDpq
	.ent	ColorMatDpq
ColorMatDpq:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	MVMVA	1, 1, 0, 3, 1
	lw	$t0, 0x10($sp)
.L1:
	SQR	1
	addi	$t0, $t0, -0x1
	bgtz	$t0, .L1
	nop
	lwc2	$6, 0($a1)
	mtc2	$a2, $8
	nop
	CDP
	swc2	$22, 0($a3)
	jr	$ra
	nop
	.end	ColorMatDpq
	.set	reorder
