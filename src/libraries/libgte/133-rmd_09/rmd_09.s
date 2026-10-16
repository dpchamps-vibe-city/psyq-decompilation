/* LIBGTE.LIB, member RMD_09.OBJ (hand-written assembly)
 *
 * void RotRMD_SV_G3(long *pa, long *va, u_long *ot, int otlen, int id,
 *                   int sclip, int hclip, int vclip, int nclipmode);
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

	.globl	RotRMD_SV_G3
	.ent	RotRMD_SV_G3
RotRMD_SV_G3:
	.set	noat
	addiu	$sp, $sp, -0x20
	sw	$s0, 0x4($sp)
	sw	$s1, 0x8($sp)
	sw	$s2, 0xC($sp)
	sw	$s3, 0x10($sp)
	sw	$s4, 0x14($sp)
	sw	$s5, 0x18($sp)
	lhu	$t0, 0($a0)
	addi	$a0, $a0, 0x4
	lw	$t4, 0x30($sp)
	lw	$t7, 0x38($a0)
	lw	$t8, 0x3C($a0)
	lw	$t9, 0x40($a0)
	add	$t7, $t7, $a1
	add	$t8, $t8, $a1
	add	$t9, $t9, $a1
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
	addi	$a0, $a0, 0x44
	lw	$t7, 0x38($a0)
	lw	$t8, 0x3C($a0)
	addu	$t7, $t7, $a1
	lw	$t9, 0x40($a0)
	addu	$t8, $t8, $a1
	addu	$t9, $t9, $a1
	cfc2	$t2, $31
	mfc2	$s4, $12
	and	$t2, $t2, $v0
	bnez	$t2, .L6
	mfc2	$t5, $13
	beqz	$t4, .L2
	mfc2	$t2, $14
	addi	$t3, $t3, 0x1C
.L2:
	beqz	$s5, .L5
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
	j	.L5
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
	j	.L5
	nop
.L4:
	sll	$s2, $t2, 16
	bltz	$s2, .L6
	nop
	slt	$at, $s2, $s0
	beqz	$at, .L6
	sra	$s3, $t2, 16
	bltz	$s3, .L6
	nop
	slt	$at, $s3, $s1
	beqz	$at, .L6
	nop
.L5:
	nop
	AVSZ3
	sw	$s4, 0x8($t3)
	sw	$t5, 0x10($t3)
	sw	$t2, 0x18($t3)
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
	li	$at, 0x6000000
	or	$t1, $t1, $at
	sw	$t1, 0($t3)
	sw	$t3, 0($t5)
.L6:
	slti	$at, $t0, 0x2
	beqz	$at, .L1
	addi	$t0, $t0, -0x1
	lw	$s0, 0x4($sp)
	lw	$s1, 0x8($sp)
	lw	$s2, 0xC($sp)
	lw	$s3, 0x10($sp)
	lw	$s4, 0x14($sp)
	lw	$s5, 0x18($sp)
	nop
	jr	$ra
	addiu	$sp, $sp, 0x20
	nop
	.set	at
	.end	RotRMD_SV_G3
	.set	reorder
