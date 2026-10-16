/* LIBGTE.LIB, member SMP_4.OBJ (hand-written assembly)
 *
 * void NormalColor3(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, CVECTOR *v3,
 *                   CVECTOR *v4, CVECTOR *v5);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        v3
 *   0x10(sp)  v4
 *   0x14(sp)  v5
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	NormalColor3
	.ent	NormalColor3
NormalColor3:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	NCT
	lw	$t0, 0x10($sp)
	lw	$t1, 0x14($sp)
	swc2	$20, 0($a3)
	swc2	$21, 0($t0)
	swc2	$22, 0($t1)
	jr	$ra
	nop
	nop
	.end	NormalColor3
	.set	reorder
