/* LIBGTE.LIB, member RMPS_G.OBJ (hand-written assembly)
 *
 * void RotMeshPrimS_G3(TMESH *msh, POLY_G3 *prim, u_long *ot, u_long otlen,
 *                      long dpq, u_long backc);
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

	.globl	RotMeshPrimS_G3
	.ent	RotMeshPrimS_G3
RotMeshPrimS_G3:
	.set	noat
	li	$t5, 0xE
	sub	$t5, $t5, $a3
	lw	$t0, 0($a0)
	lw	$t1, 0x4($a0)
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
	lwc2	$0, 0($t1)
	lwc2	$1, 0x4($t1)
	lwc2	$2, 0x8($t1)
	lwc2	$3, 0xC($t1)
	lwc2	$4, 0x10($t1)
	lwc2	$5, 0x14($t1)
	lwc2	$6, 0($t2)
	lw	$t9, 0x10($sp)
	addi	$t1, $t1, 0x10
	beqz	$t9, .L1
	addi	$t2, $t2, 0x8
	NCDT
	b	.L2
	nop
.L1:
	NCCT
.L2:
	lw	$t6, 0x14($sp)
	nop
	beqz	$t6, .L3
	li	$t6, 0x1
	NCLIP
	mfc2	$t6, $24
	nop
.L3:
	addi	$t6, $t6, -0x1
	srl	$t6, $t6, 31
	li	$at, 0x60000
	and	$v1, $v1, $at
	or	$v1, $v1, $t6
	bnez	$v1, .L4
	nop
	AVSZ3
	mfc2	$t4, $7
	swc2	$20, 0x4($t3)
	swc2	$12, 0x8($t3)
	swc2	$20, 0xC($t3)
	swc2	$13, 0x10($t3)
	swc2	$20, 0x14($t3)
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
.L4:
	lw	$t7, 0x10($a0)
	li	$a0, 0
.L5:
	lwc2	$0, 0($t0)
	lwc2	$1, 0x4($t0)
	nop
	RTPS
	lw	$t6, 0x14($sp)
	addi	$t2, $t2, 0x4
	lwc2	$6, 0($t2)
	addi	$t0, $t0, 0x8
	addi	$t1, $t1, 0x8
	addi	$t3, $t3, 0x1C
	cfc2	$v1, $31
	lwc2	$0, 0($t1)
	lwc2	$1, 0x4($t1)
	beqz	$t9, .L6
	nop
	NCDS
	b	.L7
	nop
.L6:
	NCCS
.L7:
	li	$at, 0x60000
	and	$v1, $v1, $at
	beqz	$t6, .L9
	nop
	NCLIP
	andi	$v0, $a0, 0x1
	mfc2	$t6, $24
	bnez	$v0, .L8
	nop
	neg	$t6, $t6
.L8:
	addi	$t6, $t6, -0x1
	srl	$t6, $t6, 31
	or	$v1, $v1, $t6
.L9:
	bnez	$v1, .L10
	nop
	AVSZ3
	mfc2	$t4, $7
	swc2	$20, 0x4($t3)
	swc2	$12, 0x8($t3)
	swc2	$21, 0xC($t3)
	swc2	$13, 0x10($t3)
	swc2	$22, 0x14($t3)
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
.L10:
	addi	$t7, $t7, -0x1
	slti	$at, $t7, 0x4
	beqz	$at, .L5
	addi	$a0, $a0, 0x1
	jr	$ra
	nop
	.set	at
	.end	RotMeshPrimS_G3
	.set	reorder
