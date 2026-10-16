/* LIBGTE.LIB, member SMP_6.OBJ (hand-written assembly)
 *
 * void NormalColorDpq3(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, CVECTOR *v3,
 *                      long p, CVECTOR *v4, CVECTOR *v5, CVECTOR *v6);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        v3
 *   0x10(sp)  p
 *   0x14(sp)  v4
 *   0x18(sp)  v5
 *   0x1c(sp)  v6
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	NormalColorDpq3
	.ent	NormalColorDpq3
NormalColorDpq3:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	lwc2	$6, 0($a3)
	lwc2	$8, 0x10($sp)
	nop
	NCDT
	lw	$t0, 0x14($sp)
	lw	$t1, 0x18($sp)
	lw	$t2, 0x1C($sp)
	swc2	$20, 0($t0)
	swc2	$21, 0($t1)
	swc2	$22, 0($t2)
	jr	$ra
	nop
	nop
	nop
	.end	NormalColorDpq3
	.set	reorder
