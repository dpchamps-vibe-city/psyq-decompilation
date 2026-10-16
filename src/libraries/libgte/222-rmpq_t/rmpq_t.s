/* LIBGTE.LIB, member RMPQ_T.OBJ (hand-written assembly)
 *
 * void RotMeshPrimQ_T(QMESH *msh, POLY_FT4 *prim, u_long *ot, u_long otlen,
 *                     long dpq, long backc);
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

	.globl	RotMeshPrimQ_T
	.ent	RotMeshPrimQ_T
RotMeshPrimQ_T:
	.set	noat
	lui	$at, %hi(D_00000880)
	sw	$s0, %lo(D_00000880)($at)
	lui	$at, %hi(D_00000884)
	sw	$s1, %lo(D_00000884)($at)
	lui	$at, %hi(D_00000888)
	sw	$s2, %lo(D_00000888)($at)
	lui	$at, %hi(D_0000088C)
	sw	$s3, %lo(D_0000088C)($at)
	lui	$at, %hi(D_00000890)
	sw	$s4, %lo(D_00000890)($at)
	lui	$at, %hi(D_00000894)
	sw	$s5, %lo(D_00000894)($at)
	lui	$at, %hi(D_00000898)
	sw	$s6, %lo(D_00000898)($at)
	lui	$at, %hi(D_0000089C)
	sw	$s7, %lo(D_0000089C)($at)
	lw	$s0, 0x14($a0)
	lw	$s5, 0x14($sp)
	lw	$s6, 0x10($sp)
	li	$s2, 0x10
	sub	$s2, $s2, $a3
	move	$s4, $a2
	li	$t6, 0x2c808080
	mtc2	$t6, $6
	move	$t0, $a1
	lw	$t1, 0($a0)
	lw	$t2, 0x1C($sp)
	sll	$t6, $s0, 3
	add	$a3, $t2, $t6
	lw	$t6, 0x10($a0)
	nop
	sw	$t6, 0x18($a3)
	lw	$v1, 0x18($sp)
	nop
	lw	$t6, 0x14($v1)
	lw	$a1, 0($v1)
	lw	$s1, 0x4($v1)
	lw	$a2, 0x8($v1)
	lw	$s3, 0xC($v1)
	sw	$t6, 0x20($a3)
	li	$v0, 0
.L1:
	lwc2	$0, 0($t1)
	lwc2	$1, 0x4($t1)
	lwc2	$2, 0x8($t1)
	lwc2	$3, 0xC($t1)
	lwc2	$4, 0x10($t1)
	lwc2	$5, 0x14($t1)
	nop
	RTPT
	swc2	$12, 0($t2)
	swc2	$13, 0x8($t2)
	swc2	$14, 0x10($t2)
	lh	$t6, 0($t2)
	lh	$t8, 0x2($t2)
	slt	$a0, $t6, $a1
	slt	$t9, $s1, $t6
	sll	$t9, $t9, 1
	or	$a0, $a0, $t9
	slt	$t9, $t8, $a2
	sll	$t9, $t9, 2
	or	$a0, $a0, $t9
	slt	$t9, $s3, $t8
	sll	$t9, $t9, 3
	or	$a0, $a0, $t9
	sw	$a0, 0x4($t2)
	lh	$t6, 0x8($t2)
	lh	$t8, 0xA($t2)
	slt	$a0, $t6, $a1
	slt	$t9, $s1, $t6
	sll	$t9, $t9, 1
	or	$a0, $a0, $t9
	slt	$t9, $t8, $a2
	sll	$t9, $t9, 2
	or	$a0, $a0, $t9
	slt	$t9, $s3, $t8
	sll	$t9, $t9, 3
	or	$a0, $a0, $t9
	sw	$a0, 0xC($t2)
	lh	$t6, 0x10($t2)
	lh	$t8, 0x12($t2)
	slt	$a0, $t6, $a1
	slt	$t9, $s1, $t6
	sll	$t9, $t9, 1
	or	$a0, $a0, $t9
	slt	$t9, $t8, $a2
	sll	$t9, $t9, 2
	or	$a0, $a0, $t9
	slt	$t9, $s3, $t8
	sll	$t9, $t9, 3
	or	$a0, $a0, $t9
	sw	$a0, 0x14($t2)
	addi	$v0, $v0, 0x3
	addi	$t1, $t1, 0x18
	addi	$t2, $t2, 0x18
	slt	$at, $v0, $s0
	bnez	$at, .L1
	nop
	li	$v1, 0x1
.L2:
	lwc2	$0, 0($t1)
	lwc2	$1, 0x4($t1)
	lwc2	$2, 0x8($t1)
	lwc2	$3, 0xC($t1)
	lwc2	$4, 0x10($t1)
	lwc2	$5, 0x14($t1)
	nop
	RTPT
	lw	$t2, 0x1C($sp)
	nop
	lw	$t3, 0($t2)
	lw	$t4, 0x8($t2)
	lw	$t5, 0x10($t2)
	sw	$t3, 0x8($t0)
	sw	$t4, 0x10($t0)
	swc2	$12, 0($a3)
	swc2	$13, 0x8($a3)
	swc2	$14, 0x10($a3)
	lh	$t6, 0($a3)
	lh	$t8, 0x2($a3)
	slt	$a0, $t6, $a1
	slt	$t9, $s1, $t6
	sll	$t9, $t9, 1
	or	$a0, $a0, $t9
	slt	$t9, $t8, $a2
	sll	$t9, $t9, 2
	or	$a0, $a0, $t9
	slt	$t9, $s3, $t8
	sll	$t9, $t9, 3
	or	$a0, $a0, $t9
	sw	$a0, 0x4($a3)
	lh	$t6, 0x8($a3)
	lh	$t8, 0xA($a3)
	slt	$a0, $t6, $a1
	slt	$t9, $s1, $t6
	sll	$t9, $t9, 1
	or	$a0, $a0, $t9
	slt	$t9, $t8, $a2
	sll	$t9, $t9, 2
	or	$a0, $a0, $t9
	slt	$t9, $s3, $t8
	sll	$t9, $t9, 3
	or	$a0, $a0, $t9
	sw	$a0, 0xC($a3)
	lh	$t6, 0x10($a3)
	lh	$t8, 0x12($a3)
	slt	$a0, $t6, $a1
	slt	$t9, $s1, $t6
	sll	$t9, $t9, 1
	or	$a0, $a0, $t9
	slt	$t9, $t8, $a2
	sll	$t9, $t9, 2
	or	$a0, $a0, $t9
	slt	$t9, $s3, $t8
	sll	$t9, $t9, 3
	or	$a0, $a0, $t9
	sw	$a0, 0x14($a3)
	cfc2	$t6, $31
	nop
	li	$at, 0x60000
	and	$t6, $t6, $at
	beqz	$t6, .L3
	nop
	addi	$t0, $t0, 0x28
	b	.L9
	nop
.L3:
	mfc2	$t6, $19
	lw	$t8, 0x20($a3)
	nop
	slt	$at, $t6, $t8
	bnez	$at, .L4
	nop
	addi	$t0, $t0, 0x28
	b	.L9
	nop
.L4:
	bnez	$s6, .L5
	nop
	mtc2	$zero, $8
	nop
.L5:
	DPCS
	beqz	$s5, .L6
	nop
	mtc2	$t4, $14
	nop
	nop
	NCLIP
	mfc2	$t6, $24
	nop
	bgez	$t6, .L7
	nop
.L6:
	lw	$a0, 0x4($t2)
	lw	$t6, 0xC($t2)
	lw	$t8, 0x4($a3)
	lw	$t9, 0xC($a3)
	and	$a0, $a0, $t6
	and	$a0, $a0, $t8
	and	$a0, $a0, $t9
	bnez	$a0, .L7
	nop
	swc2	$22, 0x4($t0)
	swc2	$12, 0x18($t0)
	swc2	$13, 0x20($t0)
	mfc2	$t6, $18
	nop
	srav	$t6, $t6, $s2
	sll	$t6, $t6, 2
	add	$t6, $t6, $s4
	lw	$t8, 0($t6)
	li	$at, 0xffffff
	and	$t9, $t0, $at
	li	$at, 0x9000000
	or	$t8, $t8, $at
	sw	$t8, 0($t9)
	sw	$t9, 0($t6)
.L7:
	addi	$t0, $t0, 0x28
	beqz	$s5, .L8
	nop
	lw	$t6, 0x10($a3)
	nop
	mtc2	$t6, $12
	nop
	nop
	NCLIP
	mfc2	$t6, $24
	nop
	blez	$t6, .L9
	nop
.L8:
	lw	$a0, 0xC($t2)
	lw	$t6, 0x14($t2)
	lw	$t8, 0xC($a3)
	lw	$t9, 0x14($a3)
	and	$a0, $a0, $t6
	and	$a0, $a0, $t8
	and	$a0, $a0, $t9
	bnez	$a0, .L9
	nop
	swc2	$22, 0x4($t0)
	lw	$t6, 0x8($a3)
	lw	$t8, 0x10($a3)
	sw	$t4, 0x8($t0)
	sw	$t5, 0x10($t0)
	sw	$t6, 0x18($t0)
	sw	$t8, 0x20($t0)
	mfc2	$t6, $19
	nop
	srav	$t6, $t6, $s2
	sll	$t6, $t6, 2
	add	$t6, $t6, $s4
	lw	$t8, 0($t6)
	li	$at, 0xffffff
	and	$t9, $t0, $at
	li	$at, 0x9000000
	or	$t8, $t8, $at
	sw	$t8, 0($t9)
	sw	$t9, 0($t6)
.L9:
	addi	$t0, $t0, 0x28
	lw	$t7, 0x10($t2)
	lw	$s7, 0x14($t2)
	lw	$t6, 0($a3)
	lw	$t8, 0x4($a3)
	lw	$t9, 0x8($a3)
	sw	$t6, 0($t2)
	sw	$t8, 0x4($t2)
	sw	$t9, 0x8($t2)
	lw	$t6, 0xC($a3)
	lw	$t8, 0x10($a3)
	lw	$t9, 0x14($a3)
	sw	$t6, 0xC($t2)
	sw	$t8, 0x10($t2)
	sw	$t9, 0x14($t2)
	addi	$t1, $t1, 0x18
	addi	$t2, $t2, 0x18
	li	$v0, 0x3
.L10:
	lwc2	$0, 0($t1)
	lwc2	$1, 0x4($t1)
	lwc2	$2, 0x8($t1)
	lwc2	$3, 0xC($t1)
	lwc2	$4, 0x10($t1)
	lwc2	$5, 0x14($t1)
	nop
	RTPT
	lw	$t3, 0($t2)
	lw	$t4, 0x8($t2)
	lw	$t5, 0x10($t2)
	lw	$t6, -0x8($t2)
	sw	$t7, 0x8($t0)
	sw	$t3, 0x10($t0)
	sw	$t6, 0x18($t0)
	swc2	$12, 0($a3)
	swc2	$13, 0x8($a3)
	swc2	$14, 0x10($a3)
	lh	$t6, 0($a3)
	lh	$t8, 0x2($a3)
	slt	$a0, $t6, $a1
	slt	$t9, $s1, $t6
	sll	$t9, $t9, 1
	or	$a0, $a0, $t9
	slt	$t9, $t8, $a2
	sll	$t9, $t9, 2
	or	$a0, $a0, $t9
	slt	$t9, $s3, $t8
	sll	$t9, $t9, 3
	or	$a0, $a0, $t9
	sw	$a0, 0x4($a3)
	lh	$t6, 0x8($a3)
	lh	$t8, 0xA($a3)
	slt	$a0, $t6, $a1
	slt	$t9, $s1, $t6
	sll	$t9, $t9, 1
	or	$a0, $a0, $t9
	slt	$t9, $t8, $a2
	sll	$t9, $t9, 2
	or	$a0, $a0, $t9
	slt	$t9, $s3, $t8
	sll	$t9, $t9, 3
	or	$a0, $a0, $t9
	sw	$a0, 0xC($a3)
	lh	$t6, 0x10($a3)
	lh	$t8, 0x12($a3)
	slt	$a0, $t6, $a1
	slt	$t9, $s1, $t6
	sll	$t9, $t9, 1
	or	$a0, $a0, $t9
	slt	$t9, $t8, $a2
	sll	$t9, $t9, 2
	or	$a0, $a0, $t9
	slt	$t9, $s3, $t8
	sll	$t9, $t9, 3
	or	$a0, $a0, $t9
	sw	$a0, 0x14($a3)
	cfc2	$t6, $31
	nop
	li	$at, 0x60000
	and	$t6, $t6, $at
	beqz	$t6, .L11
	nop
	addi	$t0, $t0, 0x50
	b	.L19
	nop
.L11:
	mfc2	$t6, $19
	lw	$t8, 0x20($a3)
	nop
	slt	$at, $t6, $t8
	bnez	$at, .L12
	nop
	addi	$t0, $t0, 0x50
	b	.L19
	nop
.L12:
	bnez	$s6, .L13
	nop
	mtc2	$zero, $8
	nop
.L13:
	DPCS
	beqz	$s5, .L14
	nop
	mtc2	$t3, $13
	mtc2	$t7, $14
	nop
	nop
	NCLIP
	mfc2	$t6, $24
	nop
	bgez	$t6, .L15
	nop
.L14:
	move	$a0, $s7
	lw	$t6, 0x4($t2)
	lw	$t8, -0x4($t2)
	lw	$t9, 0x4($a3)
	and	$a0, $a0, $t6
	and	$a0, $a0, $t8
	and	$a0, $a0, $t9
	bnez	$a0, .L15
	nop
	swc2	$22, 0x4($t0)
	swc2	$12, 0x20($t0)
	mfc2	$t6, $18
	nop
	srav	$t6, $t6, $s2
	sll	$t6, $t6, 2
	add	$t6, $t6, $s4
	lw	$t8, 0($t6)
	li	$at, 0xffffff
	and	$t9, $t0, $at
	li	$at, 0x9000000
	or	$t8, $t8, $at
	sw	$t8, 0($t9)
	sw	$t9, 0($t6)
.L15:
	addi	$t0, $t0, 0x28
	beqz	$s5, .L16
	nop
	mtc2	$t4, $14
	nop
	nop
	NCLIP
	mfc2	$t6, $24
	nop
	blez	$t6, .L17
	nop
.L16:
	lw	$a0, 0x4($t2)
	lw	$t6, 0xC($t2)
	lw	$t8, 0x4($a3)
	lw	$t9, 0xC($a3)
	and	$a0, $a0, $t6
	and	$a0, $a0, $t8
	and	$a0, $a0, $t9
	bnez	$a0, .L17
	nop
	swc2	$22, 0x4($t0)
	lw	$t6, 0($a3)
	lw	$t8, 0x8($a3)
	sw	$t3, 0x8($t0)
	sw	$t4, 0x10($t0)
	sw	$t6, 0x18($t0)
	sw	$t8, 0x20($t0)
	mfc2	$t6, $18
	nop
	srav	$t6, $t6, $s2
	sll	$t6, $t6, 2
	add	$t6, $t6, $s4
	lw	$t8, 0($t6)
	li	$at, 0xffffff
	and	$t9, $t0, $at
	li	$at, 0x9000000
	or	$t8, $t8, $at
	sw	$t8, 0($t9)
	sw	$t9, 0($t6)
.L17:
	addi	$t0, $t0, 0x28
	beqz	$s5, .L18
	nop
	lwc2	$12, 0x10($a3)
	lwc2	$13, 0x8($a3)
	nop
	nop
	NCLIP
	mfc2	$t6, $24
	nop
	blez	$t6, .L19
	nop
.L18:
	lw	$a0, 0xC($t2)
	lw	$t6, 0x14($t2)
	lw	$t8, 0xC($a3)
	lw	$t9, 0x14($a3)
	and	$a0, $a0, $t6
	and	$a0, $a0, $t8
	and	$a0, $a0, $t9
	bnez	$a0, .L19
	nop
	swc2	$22, 0x4($t0)
	lw	$t6, 0x8($a3)
	lw	$t8, 0x10($a3)
	sw	$t4, 0x8($t0)
	sw	$t5, 0x10($t0)
	sw	$t6, 0x18($t0)
	sw	$t8, 0x20($t0)
	mfc2	$t6, $19
	nop
	srav	$t6, $t6, $s2
	sll	$t6, $t6, 2
	add	$t6, $t6, $s4
	lw	$t8, 0($t6)
	li	$at, 0xffffff
	and	$t9, $t0, $at
	li	$at, 0x9000000
	or	$t8, $t8, $at
	sw	$t8, 0($t9)
	sw	$t9, 0($t6)
.L19:
	addi	$t0, $t0, 0x28
	lw	$t7, 0x10($t2)
	lw	$s7, 0x14($t2)
	lw	$t6, 0($a3)
	lw	$t8, 0x4($a3)
	lw	$t9, 0x8($a3)
	sw	$t6, 0($t2)
	sw	$t8, 0x4($t2)
	sw	$t9, 0x8($t2)
	lw	$t6, 0xC($a3)
	lw	$t8, 0x10($a3)
	lw	$t9, 0x14($a3)
	sw	$t6, 0xC($t2)
	sw	$t8, 0x10($t2)
	sw	$t9, 0x14($t2)
	addi	$t1, $t1, 0x18
	addi	$t2, $t2, 0x18
	addi	$v0, $v0, 0x3
	slt	$at, $v0, $s0
	bnez	$at, .L10
	nop
	lw	$t6, 0x18($a3)
	addi	$v1, $v1, 0x1
	slt	$at, $v1, $t6
	bnez	$at, .L2
	nop
	lw	$s0, D_00000880
	lw	$s1, D_00000884
	lw	$s2, D_00000888
	lw	$s3, D_0000088C
	lw	$s4, D_00000890
	lw	$s5, D_00000894
	lw	$s6, D_00000898
	lw	$s7, D_0000089C
	jr	$ra
	nop
	nop
	nop
	.set	at
	.end	RotMeshPrimQ_T
	.set	reorder

	.data
	.align	4
D_00000880:
	.word	0x00000000
D_00000884:
	.word	0x00000000
D_00000888:
	.word	0x00000000
D_0000088C:
	.word	0x00000000
D_00000890:
	.word	0x00000000
D_00000894:
	.word	0x00000000
D_00000898:
	.word	0x00000000
D_0000089C:
	.word	0x00000000
