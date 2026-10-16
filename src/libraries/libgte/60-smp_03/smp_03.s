/* LIBGTE.LIB, member SMP_03.OBJ (hand-written assembly)
 *
 * long RotTransPers3(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, long *sxy0,
 *                    long *sxy1, long *sxy2, long *p, long *flag);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        sxy0
 *   0x10(sp)  sxy1
 *   0x14(sp)  sxy2
 *   0x18(sp)  p
 *   0x1c(sp)  flag
 *   v0        result (long)
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	RotTransPers3
	.ent	RotTransPers3
RotTransPers3:
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
	lw	$t3, 0x1C($sp)
	swc2	$12, 0($a3)
	swc2	$13, 0($t0)
	swc2	$14, 0($t1)
	swc2	$8, 0($t2)
	cfc2	$v1, $31
	mfc2	$v0, $19
	sw	$v1, 0($t3)
	sra	$v0, $v0, 2
	jr	$ra
	.end	RotTransPers3
