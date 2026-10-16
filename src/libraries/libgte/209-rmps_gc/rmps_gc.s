/* LIBGTE.LIB, member RMPS_GC.OBJ (hand-written assembly)
 *
 * void RotMeshPrimS_GC3(TMESH *msh, POLY_G3 *prim, u_long *ot,
 *                       u_long otlen, long dpq, u_long backc);
 *   (declared only inside a comment block of libgte.h)
 *
 * Register use:
 *   a0        msh
 *   a1        prim
 *   a2        ot
 *   a3        otlen
 *   0x10(sp)  dpq
 *   0x14(sp)  backc
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotMeshPrimS_GC3
	.ent	RotMeshPrimS_GC3
RotMeshPrimS_GC3:
	.set	noat
	li	$t5, 0xE
	sub	$t5, $t5, $a3
	lw	$t0, 0($a0)
	lw	$t2, 0xC($a0)
	move	$t3, $a1
	lwc2	$0, 0($t0)
	lwc2	$1, 0x4($t0)
	lwc2	$2, 0x8($t0)
	lwc2	$3, 0xC($t0)
	lwc2	$4, 0x10($t0)
	lwc2	$5, 0x14($t0)
	addi	$t0, $t0, 0x18
	RTPT
	cfc2	$v1, $31
	lwc2	$6, 0($t2)
	lwc2	$20, 0($t2)
	lwc2	$21, 0x4($t2)
	lwc2	$22, 0x8($t2)
	lw	$t9, 0x10($sp)
	addi	$t2, $t2, 0x8
	bnez	$t9, .L1
	nop
	mtc2	$zero, $8
	nop
.L1:
	DPCT
	lw	$t6, 0x14($sp)
	nop
	beqz	$t6, .L2
	li	$t6, 0x1
	NCLIP
	mfc2	$t6, $24
	nop
.L2:
	addi	$t6, $t6, -0x1
	srl	$t6, $t6, 31
	li	$at, 0x60000
	and	$v1, $v1, $at
	or	$v1, $v1, $t6
	bnez	$v1, .L3
	nop
	AVSZ3
	mfc2	$t4, $7
	swc2	$20, 0x4($t3)
	swc2	$21, 0xC($t3)
	swc2	$22, 0x14($t3)
	swc2	$12, 0x8($t3)
	swc2	$13, 0x10($t3)
	swc2	$14, 0x18($t3)
	srav	$t4, $t4, $t5
	sll	$t4, $t4, 2
	add	$v0, $a2, $t4
	lw	$v1, 0($v0)
	li	$at, 0xffffff
	and	$t8, $t3, $at
	li	$at, 0x6000000
	or	$v1, $v1, $at
	sw	$v1, 0($t3)
	sw	$t8, 0($v0)
.L3:
	lw	$t7, 0x10($a0)
	li	$a0, 0
.L4:
	lwc2	$0, 0($t0)
	lwc2	$1, 0x4($t0)
	nop
	RTPS
	lw	$t6, 0x14($sp)
	addi	$t2, $t2, 0x4
	lwc2	$6, 0($t2)
	addi	$t0, $t0, 0x8
	addi	$t3, $t3, 0x1C
	cfc2	$v1, $31
	bnez	$t9, .L5
	nop
	mtc2	$zero, $8
	nop
.L5:
	DPCS
	li	$at, 0x60000
	and	$v1, $v1, $at
	beqz	$t6, .L7
	nop
	NCLIP
	andi	$v0, $a0, 0x1
	mfc2	$t6, $24
	bnez	$v0, .L6
	nop
	neg	$t6, $t6
.L6:
	addi	$t6, $t6, -0x1
	srl	$t6, $t6, 31
	or	$v1, $v1, $t6
.L7:
	bnez	$v1, .L8
	nop
	AVSZ3
	mfc2	$t4, $7
	swc2	$20, 0x4($t3)
	swc2	$21, 0xC($t3)
	swc2	$22, 0x14($t3)
	swc2	$12, 0x8($t3)
	swc2	$13, 0x10($t3)
	swc2	$14, 0x18($t3)
	srav	$t4, $t4, $t5
	sll	$t4, $t4, 2
	add	$v0, $a2, $t4
	lw	$v1, 0($v0)
	li	$at, 0xffffff
	and	$t8, $t3, $at
	li	$at, 0x6000000
	or	$v1, $v1, $at
	sw	$v1, 0($t3)
	sw	$t8, 0($v0)
.L8:
	addi	$t7, $t7, -0x1
	slti	$at, $t7, 0x4
	beqz	$at, .L4
	addi	$a0, $a0, 0x1
	jr	$ra
	nop
	nop
	.set	at
	.end	RotMeshPrimS_GC3
	.set	reorder
