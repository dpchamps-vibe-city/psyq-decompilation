/* LIBGTE.LIB, member RMPR_FCT.OBJ (hand-written assembly)
 *
 * void RotMeshPrimR_FCT3(TMESH *msh, POLY_FT3 *prim, u_long *ot,
 *                        u_long otlen, long dpq, u_long backc);
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

	.globl	RotMeshPrimR_FCT3
	.ent	RotMeshPrimR_FCT3
RotMeshPrimR_FCT3:
	.set	noat
	lui	$at, %hi(D_00000200)
	sw	$s0, %lo(D_00000200)($at)
	lui	$at, %hi(D_00000204)
	sw	$s1, %lo(D_00000204)($at)
	li	$t5, 0xE
	sub	$t5, $t5, $a3
	lw	$t0, 0($a0)
	lw	$t9, 0x14($sp)
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
	beqz	$t9, .L1
	li	$t6, 0x1
	NCLIP
	mfc2	$t6, $24
	nop
.L1:
	addi	$t6, $t6, -0x1
	srl	$t6, $t6, 31
	li	$at, 0x60000
	and	$v1, $v1, $at
	or	$v1, $v1, $t6
	bnez	$v1, .L2
	nop
	AVSZ3
	mfc2	$t4, $7
	swc2	$12, 0x8($t3)
	swc2	$13, 0x10($t3)
	swc2	$14, 0x18($t3)
	srav	$t4, $t4, $t5
	sll	$t4, $t4, 2
	add	$v0, $a2, $t4
	lw	$v1, 0($v0)
	li	$at, 0xffffff
	and	$t8, $t3, $at
	li	$at, 0x7000000
	or	$v1, $v1, $at
	sw	$v1, 0($t3)
	sw	$t8, 0($v0)
.L2:
	mfc2	$s0, $12
	mfc2	$s1, $17
	mtc2	$s0, $13
	mtc2	$s1, $18
	lw	$t7, 0x10($a0)
.L3:
	lwc2	$0, 0($t0)
	lwc2	$1, 0x4($t0)
	nop
	RTPS
	addi	$t0, $t0, 0x8
	addi	$t3, $t3, 0x20
	cfc2	$v1, $31
	li	$at, 0x60000
	and	$v1, $v1, $at
	beqz	$t9, .L4
	nop
	NCLIP
	mfc2	$t6, $24
	nop
	addi	$t6, $t6, -0x1
	srl	$t6, $t6, 31
	or	$v1, $v1, $t6
.L4:
	bnez	$v1, .L5
	nop
	AVSZ3
	mfc2	$t4, $7
	swc2	$12, 0x8($t3)
	swc2	$13, 0x10($t3)
	swc2	$14, 0x18($t3)
	srav	$t4, $t4, $t5
	sll	$t4, $t4, 2
	add	$v0, $a2, $t4
	lw	$v1, 0($v0)
	li	$at, 0xffffff
	and	$t8, $t3, $at
	li	$at, 0x7000000
	or	$v1, $v1, $at
	sw	$v1, 0($t3)
	sw	$t8, 0($v0)
.L5:
	mtc2	$s0, $13
	mtc2	$s1, $18
	addi	$t7, $t7, -0x1
	slti	$at, $t7, 0x4
	beqz	$at, .L3
	nop
	lw	$s0, D_00000200
	lw	$s1, D_00000204
	jr	$ra
	nop
	nop
	nop
	.set	at
	.end	RotMeshPrimR_FCT3
	.set	reorder

	.data
	.align	4
D_00000200:
	.word	0x00000000
D_00000204:
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
