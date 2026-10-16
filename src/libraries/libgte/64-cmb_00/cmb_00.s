/* LIBGTE.LIB, member CMB_00.OBJ (hand-written assembly)
 *
 * long RotTransPers4(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3,
 *                    long *sxy0, long *sxy1, long *sxy2, long *sxy3,
 *                    long *p, long *flag);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        v3
 *   0x10(sp)  sxy0
 *   0x14(sp)  sxy1
 *   0x18(sp)  sxy2
 *   0x1c(sp)  sxy3
 *   0x20(sp)  p
 *   0x24(sp)  flag
 *   v0        result (long)
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	RotTransPers4
	.ent	RotTransPers4
RotTransPers4:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	RTPT
	lw	$t0, 0x10($sp)
	lw	$t1, 0x14($sp)
	lw	$t2, 0x18($sp)
	swc2	$12, 0($t0)
	swc2	$13, 0($t1)
	swc2	$14, 0($t2)
	cfc2	$v1, $31
	lwc2	$0, 0($a3)
	lwc2	$1, 0x4($a3)
	nop
	RTPS
	lw	$t0, 0x1C($sp)
	lw	$t1, 0x20($sp)
	lw	$t2, 0x24($sp)
	swc2	$14, 0($t0)
	swc2	$8, 0($t1)
	cfc2	$t0, $31
	mfc2	$v0, $19
	or	$t0, $t0, $v1
	sw	$t0, 0($t2)
	sra	$v0, $v0, 2
	jr	$ra
	.end	RotTransPers4
