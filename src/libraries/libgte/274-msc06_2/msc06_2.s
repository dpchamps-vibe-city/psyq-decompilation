/* LIBGTE.LIB, member MSC06_2.OBJ (hand-written assembly)
 *
 * void LoadAverage0(VECTOR *v0, VECTOR *v1, long p0, long p1, VECTOR *v2);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        p0
 *   a3        p1
 *   0x10(sp)  v2
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	LoadAverage0
	.ent	LoadAverage0
LoadAverage0:
	mtc2	$a2, $8
	lwc2	$9, 0($a0)
	lwc2	$10, 0x4($a0)
	lwc2	$11, 0x8($a0)
	nop
	GPF	0
	mfc2	$v0, $31
	mtc2	$a3, $8
	lwc2	$9, 0($a1)
	lwc2	$10, 0x4($a1)
	lwc2	$11, 0x8($a1)
	nop
	GPL	0
	lw	$t0, 0x10($sp)
	nop
	swc2	$9, 0($t0)
	swc2	$10, 0x4($t0)
	swc2	$11, 0x8($t0)
	jr	$ra
	nop
	.end	LoadAverage0
	.set	reorder
