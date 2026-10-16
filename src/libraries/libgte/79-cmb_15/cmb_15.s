/* LIBGTE.LIB, member CMB_15.OBJ (hand-written assembly)
 *
 * RotAverageNclip3_1: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotAverageNclip3_1
	.ent	RotAverageNclip3_1
RotAverageNclip3_1:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	lwc2	$2, 0($a1)
	lwc2	$3, 0x4($a1)
	lwc2	$4, 0($a2)
	lwc2	$5, 0x4($a2)
	nop
	RTPT
	lw	$t0, 0x24($sp)
	cfc2	$v0, $31
	nop
	sw	$v0, 0($t0)
	NCLIP
	mfc2	$t1, $24
	lw	$t0, 0x1C($sp)
	nop
	sw	$t1, 0($t0)
	bltz	$t1, .L1
	nop
	li	$v0, -0x1
	b	.L2
.L1:
	swc2	$12, 0($a3)
	lw	$t0, 0x10($sp)
	nop
	swc2	$13, 0($t0)
	lw	$t0, 0x14($sp)
	nop
	swc2	$14, 0($t0)
	lw	$t0, 0x18($sp)
	nop
	swc2	$8, 0($t0)
	nop
	AVSZ3
	mfc2	$t0, $7
	lw	$t1, 0x20($sp)
	nop
	sw	$t0, 0($t1)
	li	$v0, 0
.L2:
	jr	$ra
	nop
	.end	RotAverageNclip3_1
	.set	reorder
