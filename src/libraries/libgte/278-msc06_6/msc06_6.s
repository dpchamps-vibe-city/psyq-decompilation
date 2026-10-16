/* LIBGTE.LIB, member MSC06_6.OBJ (hand-written assembly)
 *
 * void LoadAverageCol(u_char *v0, u_char *v1, long p0, long p1, u_char *v2);
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

	.globl	LoadAverageCol
	.ent	LoadAverageCol
LoadAverageCol:
	lbu	$t0, 0($a0)
	lbu	$t1, 0x1($a0)
	lbu	$t2, 0x2($a0)
	mtc2	$a2, $8
	mtc2	$t0, $9
	mtc2	$t1, $10
	mtc2	$t2, $11
	nop
	GPF	0
	lbu	$t0, 0($a1)
	lbu	$t1, 0x1($a1)
	lbu	$t2, 0x2($a1)
	mfc2	$v0, $31
	mtc2	$a3, $8
	mtc2	$t0, $9
	mtc2	$t1, $10
	mtc2	$t2, $11
	li	$t3, 0xC
	GPL	0
	lw	$t5, 0x10($sp)
	mfc2	$t0, $25
	mfc2	$t1, $26
	mfc2	$t2, $27
	srav	$t0, $t0, $t3
	srav	$t1, $t1, $t3
	srav	$t2, $t2, $t3
	sb	$t0, 0($t5)
	sb	$t1, 0x1($t5)
	sb	$t2, 0x2($t5)
	jr	$ra
	nop
	nop
	.end	LoadAverageCol
	.set	reorder
