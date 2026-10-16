/* LIBGTE.LIB, member MSC06_4.OBJ (hand-written assembly)
 *
 * void LoadAverageShort0(SVECTOR *v0, SVECTOR *v1, long p0, long p1,
 *                        SVECTOR *v2);
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

	.globl	LoadAverageShort0
	.ent	LoadAverageShort0
LoadAverageShort0:
	lw	$t0, 0($a0)
	lw	$t2, 0x4($a0)
	sra	$t1, $t0, 16
	andi	$t0, $t0, 0xFFFF
	andi	$t2, $t2, 0xFFFF
	mtc2	$a2, $8
	mtc2	$t0, $9
	mtc2	$t1, $10
	mtc2	$t2, $11
	nop
	GPF	0
	lw	$t0, 0($a1)
	lw	$t2, 0x4($a1)
	sra	$t1, $t0, 16
	andi	$t0, $t0, 0xFFFF
	andi	$t2, $t2, 0xFFFF
	mfc2	$v0, $31
	mtc2	$a3, $8
	mtc2	$t0, $9
	mtc2	$t1, $10
	mtc2	$t2, $11
	nop
	GPL	0
	mfc2	$t0, $9
	mfc2	$t1, $10
	andi	$t0, $t0, 0xFFFF
	sll	$t1, $t1, 16
	or	$t0, $t0, $t1
	lw	$t5, 0x10($sp)
	mfc2	$t2, $11
	sw	$t0, 0($t5)
	sw	$t2, 0x4($t5)
	jr	$ra
	nop
	nop
	nop
	.end	LoadAverageShort0
	.set	reorder
