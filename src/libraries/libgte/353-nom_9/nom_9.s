/* LIBGTE.LIB, member NOM_9.OBJ (hand-written assembly)
 *
 * long RotColorDpq3_nom(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3,
 *                       SVECTOR *v4, SVECTOR *v5, CVECTOR *v6);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        v3
 *   0x10(sp)  v4
 *   0x14(sp)  v5
 *   0x18(sp)  v6
 *   v0        result (long)
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotColorDpq3_nom
	.ent	RotColorDpq3_nom
RotColorDpq3_nom:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	RTPT
	cfc2	$v0, $31
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
	NCDT
	jr	$ra
	nop
	nop
	nop
	.end	RotColorDpq3_nom
	.set	reorder
