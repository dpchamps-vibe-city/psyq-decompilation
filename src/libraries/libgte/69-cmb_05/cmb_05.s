/* LIBGTE.LIB, member CMB_05.OBJ (hand-written assembly)
 *
 * long RotNclip4(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, SVECTOR *v3,
 *                long *sxy0, long *sxy1, long *sxy2, long *sxy3, long *p,
 *                long *otz, long *flag);
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
 *   0x24(sp)  otz
 *   0x28(sp)  flag
 *   v0        result (long)
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	RotNclip4
	.ent	RotNclip4
RotNclip4:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	RTPT
	lw	$t0, 0x28($sp)
	cfc2	$v1, $31
	nop
	NCLIP
	sw	$v1, 0($t0)
	nop
	lw	$t0, 0x10($sp)
	lw	$t1, 0x14($sp)
	lw	$t2, 0x18($sp)
	mfc2	$v0, $24
	bgtz	$v0, .L1
	b	.L2
.L1:
	swc2	$12, 0($t0)
	swc2	$13, 0($t1)
	swc2	$14, 0($t2)
	lwc2	$0, 0($a3)
	lwc2	$1, 0x4($a3)
	nop
	RTPS
	lw	$t0, 0x1C($sp)
	lw	$t1, 0x20($sp)
	lw	$t2, 0x24($sp)
	lw	$t3, 0x28($sp)
	swc2	$14, 0($t0)
	mfc2	$t4, $19
	swc2	$8, 0($t1)
	cfc2	$v0, $31
	sra	$t4, $t4, 2
	sw	$t4, 0($t2)
	or	$v0, $v0, $v1
	sw	$v0, 0($t3)
.L2:
	jr	$ra
	.end	RotNclip4
