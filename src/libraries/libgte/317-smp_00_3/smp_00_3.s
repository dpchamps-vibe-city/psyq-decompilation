/* LIBGTE.LIB, member SMP_00_3.OBJ (hand-written assembly)
 *
 * void DpqColor3(CVECTOR *v0, CVECTOR *v1, CVECTOR *v2, long p,
 *                CVECTOR *v3, CVECTOR *v4, CVECTOR *v5);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        p
 *   0x10(sp)  v3
 *   0x14(sp)  v4
 *   0x18(sp)  v5
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	DpqColor3
	.ent	DpqColor3
DpqColor3:
	lwc2	$20, 0($a0)
	lwc2	$21, 0($a1)
	lwc2	$22, 0($a2)
	lwc2	$6, 0($a2)
	mtc2	$a3, $8
	nop
	DPCT
	lw	$t0, 0x10($sp)
	lw	$t1, 0x14($sp)
	lw	$t2, 0x18($sp)
	swc2	$20, 0($t0)
	swc2	$21, 0($t1)
	swc2	$22, 0($t2)
	jr	$ra
	nop
	nop
	.end	DpqColor3
	.set	reorder
