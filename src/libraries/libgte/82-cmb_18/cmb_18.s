/* LIBGTE.LIB, member CMB_18.OBJ (hand-written assembly)
 *
 * RotAverageNclipColorDpq3_1: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	RotAverageNclipColorDpq3_1
	.ent	RotAverageNclipColorDpq3_1
RotAverageNclipColorDpq3_1:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	RTPS
	mfc2	$t7, $8
	lwc2	$0, 0($a1)
	lwc2	$1, 0x4($a1)
	nop
	RTPS
	mfc2	$t8, $8
	lwc2	$0, 0($a2)
	lwc2	$1, 0x4($a2)
	nop
	RTPS
	lw	$v0, 0x38($sp)
	mfc2	$t9, $8
	cfc2	$v1, $31
	sw	$v1, 0($v0)
	NCLIP
	lw	$t3, 0x10($sp)
	lw	$t4, 0x14($sp)
	lw	$t5, 0x18($sp)
	mfc2	$v0, $24
	bgtz	$v0, .L1
	b	.L2
.L1:
	lwc2	$0, 0($a3)
	lwc2	$1, 0x4($a3)
	lwc2	$6, 0($t5)
	mtc2	$t7, $8
	nop
	NCDS
	lw	$t0, 0x1C($sp)
	lw	$t1, 0x28($sp)
	swc2	$12, 0($t0)
	swc2	$22, 0($t1)
	lwc2	$0, 0($t3)
	lwc2	$1, 0x4($t3)
	mtc2	$t8, $8
	nop
	NCDS
	lw	$t0, 0x20($sp)
	lw	$t1, 0x2C($sp)
	swc2	$13, 0($t0)
	swc2	$22, 0($t1)
	lwc2	$0, 0($t4)
	lwc2	$1, 0x4($t4)
	mtc2	$t9, $8
	nop
	NCDS
	lw	$t0, 0x24($sp)
	lw	$t1, 0x30($sp)
	swc2	$14, 0($t0)
	swc2	$22, 0($t1)
	AVSZ3
	lw	$t1, 0x34($sp)
	mfc2	$t0, $7
	sw	$t0, 0($t1)
.L2:
	jr	$ra
	.end	RotAverageNclipColorDpq3_1
