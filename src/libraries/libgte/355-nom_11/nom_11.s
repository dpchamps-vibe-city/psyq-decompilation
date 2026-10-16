/* LIBGTE.LIB, member NOM_11.OBJ (hand-written assembly)
 *
 * void RotAverageNclipColorCol3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2,
 *                                   SVECTOR *v3, SVECTOR *v4, SVECTOR *v5,
 *                                   CVECTOR *v6);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        v3
 *   0x10(sp)  v4
 *   0x14(sp)  v5
 *   0x18(sp)  v6
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotAverageNclipColorCol3_nom
	.ent	RotAverageNclipColorCol3_nom
RotAverageNclipColorCol3_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	RTPT
	cfc2	$v0, $31
	AVSZ3
	NCLIP
	lwc2	$0, 0($a3)
	lwc2	$1, 0x4($a3)
	lw	$t0, 0x10($sp)
	nop
	lwc2	$2, 0($t0)
	lwc2	$3, 0x4($t0)
	lw	$t0, 0x14($sp)
	nop
	lwc2	$4, 0($t0)
	lwc2	$5, 0x4($t0)
	lw	$t0, 0x18($sp)
	nop
	lwc2	$6, 0($t0)
	nop
	NCCT
	jr	$ra
	nop
	.end	RotAverageNclipColorCol3_nom
	.set	reorder
