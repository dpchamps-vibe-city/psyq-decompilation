/* LIBGTE.LIB, member RMD_15.OBJ (hand-written assembly)
 *
 * void RotRMD_SV_GT4(long *pa, long *va, u_long *ot, int otlen, int id,
 *                    int sclip, int hclip, int vclip, int nclipmode);
 *
 * Register use:
 *   a0        pa
 *   a1        va
 *   a2        ot
 *   a3        otlen
 *   0x10(sp)  id
 *   0x14(sp)  sclip
 *   0x18(sp)  hclip
 *   0x1c(sp)  vclip
 *   0x20(sp)  nclipmode
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotRMD_SV_GT4
	.ent	RotRMD_SV_GT4
RotRMD_SV_GT4:
	.set	noat
	addiu	$sp, $sp, -0x20
	sw	$s0, 0x4($sp)
	sw	$s1, 0x8($sp)
	sw	$s2, 0xC($sp)
	sw	$s3, 0x10($sp)
	sw	$s4, 0x14($sp)
	sw	$s5, 0x18($sp)
	sw	$s6, 0x1C($sp)
	lhu	$t0, 0($a0)
	addi	$a0, $a0, 0x4
	lw	$t4, 0x30($sp)
	lw	$t7, 0x68($a0)
	lw	$t8, 0x6C($a0)
	lw	$t9, 0x70($a0)
	lw	$v1, 0x74($a0)
	add	$t7, $t7, $a1
	add	$t8, $t8, $a1
	add	$t9, $t9, $a1
	add	$v1, $v1, $a1
	lw	$s5, 0x34($sp)
	lw	$s0, 0x38($sp)
	lw	$s1, 0x3C($sp)
	sll	$s0, $s0, 16
	lw	$s4, 0x40($sp)
	li	$v0, 0x40000
	beqz	$s4, .L1
	nop
	li	$v0, 0x60000
.L1:
	lwc2	$0, 0($t7)
	lwc2	$1, 0x4($t7)
	lwc2	$2, 0($t8)
	lwc2	$3, 0x4($t8)
	lwc2	$4, 0($t9)
	lwc2	$5, 0x4($t9)
	nop
	RTPT
	move	$t3, $a0
	addi	$a0, $a0, 0x78
	lw	$t7, 0x68($a0)
	lw	$t8, 0x6C($a0)
	addu	$t7, $t7, $a1
	lw	$t9, 0x70($a0)
	addu	$t8, $t8, $a1
	addu	$t9, $t9, $a1
	cfc2	$t2, $31
	lwc2	$0, 0($v1)
	lwc2	$1, 0x4($v1)
	and	$t2, $t2, $v0
	bnez	$t2, .L8
	nop
	beqz	$t4, .L2
	nop
	addi	$t3, $t3, 0x34
.L2:
	mfc2	$s4, $12
	mfc2	$t5, $13
	mfc2	$t2, $14
	RTPS
	sw	$s4, 0x8($t3)
	sw	$t5, 0x14($t3)
	sw	$t2, 0x20($t3)
	beqz	$s5, .L6
	sll	$s2, $s4, 16
	bltz	$s2, .L3
	nop
	slt	$at, $s2, $s0
	beqz	$at, .L3
	sra	$s3, $s4, 16
	bltz	$s3, .L3
	nop
	slt	$at, $s3, $s1
	beqz	$at, .L3
	nop
	j	.L6
	nop
.L3:
	sll	$s2, $t5, 16
	bltz	$s2, .L4
	nop
	slt	$at, $s2, $s0
	beqz	$at, .L4
	sra	$s3, $t5, 16
	bltz	$s3, .L4
	nop
	slt	$at, $s3, $s1
	beqz	$at, .L4
	nop
	j	.L6
	nop
.L4:
	sll	$s2, $t2, 16
	bltz	$s2, .L5
	nop
	slt	$at, $s2, $s0
	beqz	$at, .L5
	sra	$s3, $t2, 16
	bltz	$s3, .L5
	nop
	slt	$at, $s3, $s1
	beqz	$at, .L5
	nop
	j	.L6
	nop
.L5:
	mfc2	$s6, $14
	nop
	sll	$s2, $s6, 16
	bltz	$s2, .L8
	nop
	slt	$at, $s2, $s0
	beqz	$at, .L8
	sra	$s3, $s6, 16
	bltz	$s3, .L8
	nop
	slt	$at, $s3, $s1
	beqz	$at, .L8
	nop
	j	.L7
	nop
.L6:
	mfc2	$s6, $14
	nop
.L7:
	nop
	AVSZ4
	sw	$s6, 0x2C($t3)
	li	$t2, 0xE
	sub	$t2, $t2, $a3
	mfc2	$t1, $7
	nop
	srav	$t1, $t1, $t2
	sll	$t1, $t1, 2
	add	$t5, $a2, $t1
	lw	$t1, 0($t5)
	li	$at, 0xffffff
	and	$t3, $t3, $at
	li	$at, 0xc000000
	or	$t1, $t1, $at
	sw	$t1, 0($t3)
	sw	$t3, 0($t5)
.L8:
	lw	$v1, 0x74($a0)
	addi	$t0, $t0, -0x1
	bgtz	$t0, .L1
	addu	$v1, $v1, $a1
	lw	$s0, 0x4($sp)
	lw	$s1, 0x8($sp)
	lw	$s2, 0xC($sp)
	lw	$s3, 0x10($sp)
	lw	$s4, 0x14($sp)
	lw	$s5, 0x18($sp)
	lw	$s6, 0x1C($sp)
	nop
	jr	$ra
	addiu	$sp, $sp, 0x20
	nop
	nop
	nop
	.set	at
	.end	RotRMD_SV_GT4
	.set	reorder
