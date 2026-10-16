/* LIBGTE.LIB, member CMB_09.OBJ (hand-written assembly)
 *
 * long RotAverageNclipColorCol3(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2,
 *                               SVECTOR *v3, SVECTOR *v4, SVECTOR *v5,
 *                               CVECTOR *v6, long *sxy0, long *sxy1,
 *                               long *sxy2, CVECTOR *v7, CVECTOR *v8,
 *                               CVECTOR *v9, long *otz, long *flag);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        v3
 *   0x10(sp)  v4
 *   0x14(sp)  v5
 *   0x18(sp)  v6
 *   0x1c(sp)  sxy0
 *   0x20(sp)  sxy1
 *   0x24(sp)  sxy2
 *   0x28(sp)  v7
 *   0x2c(sp)  v8
 *   0x30(sp)  v9
 *   0x34(sp)  otz
 *   0x38(sp)  flag
 *   v0        result (long)
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotAverageNclipColorCol3
	.ent	RotAverageNclipColorCol3
RotAverageNclipColorCol3:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	RTPT
	lw	$t0, 0x38($sp)
	cfc2	$t1, $31
	nop
	sw	$t1, 0($t0)
	NCLIP
	lw	$t0, 0x10($sp)
	lw	$t1, 0x14($sp)
	lw	$t2, 0x18($sp)
	mfc2	$v0, $24
	nop
	bgtz	$v0, .L1
	nop
	b	.L2
.L1:
	lwc2	$0, 0($a3)
	lwc2	$1, 0x4($a3)
	lwc2	$2, 0($t0)
	lwc2	$3, 0x4($t0)
	lwc2	$4, 0($t1)
	lwc2	$5, 0x4($t1)
	lwc2	$6, 0($t2)
	nop
	NCCT
	lw	$t0, 0x1C($sp)
	lw	$t1, 0x20($sp)
	lw	$t2, 0x24($sp)
	lw	$t3, 0x28($sp)
	lw	$t4, 0x2C($sp)
	lw	$t5, 0x30($sp)
	swc2	$12, 0($t0)
	swc2	$13, 0($t1)
	swc2	$14, 0($t2)
	swc2	$20, 0($t3)
	swc2	$21, 0($t4)
	swc2	$22, 0($t5)
	nop
	AVSZ3
	lw	$t1, 0x34($sp)
	mfc2	$t0, $7
	nop
	sw	$t0, 0($t1)
.L2:
	jr	$ra
	nop
	nop
	nop
	.end	RotAverageNclipColorCol3
	.set	reorder
