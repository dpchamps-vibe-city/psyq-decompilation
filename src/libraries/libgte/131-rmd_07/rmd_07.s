/* LIBGTE.LIB, member RMD_07.OBJ (hand-written assembly)
 *
 * void RotRMD_GT4(long *pa, u_long *ot, int otlen, int id, int sclip,
 *                 int hclip, int vclip, int nclipmode);
 *
 * Register use:
 *   a0        pa
 *   a1        ot
 *   a2        otlen
 *   a3        id
 *   0x10(sp)  sclip
 *   0x14(sp)  hclip
 *   0x18(sp)  vclip
 *   0x1c(sp)  nclipmode
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotRMD_GT4
	.ent	RotRMD_GT4
RotRMD_GT4:
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
	beqz	$t0, .L10
	lui	$t8, 0xff
	ori	$t8, $t8, 0xffff
	li	$t7, 0xc000000
	lw	$s5, 0x30($sp)
	lw	$s0, 0x34($sp)
	lw	$s1, 0x38($sp)
	sll	$s0, $s0, 16
	lw	$s4, 0x3C($sp)
	li	$v0, 0x40000
	beqz	$s4, .L1
	nop
	li	$v0, 0x60000
.L1:
	li	$at, 0xE
	sub	$a2, $at, $a2
	beqz	$a3, .L2
	nop
	li	$a3, 0x34
.L2:
	lwc2	$2, 0x70($a0)
	lwc2	$3, 0x74($a0)
	lwc2	$4, 0x78($a0)
	lwc2	$5, 0x7C($a0)
.L3:
	lwc2	$0, 0x68($a0)
	lwc2	$1, 0x6C($a0)
	add	$t3, $a0, $a3
	nop
	RTPT
	nop
	nop
	lwc2	$2, 0xF8($a0)
	lwc2	$3, 0xFC($a0)
	lwc2	$4, 0x100($a0)
	lwc2	$5, 0x104($a0)
	lwc2	$0, 0x80($a0)
	lwc2	$1, 0x84($a0)
	cfc2	$t2, $31
	nop
	and	$t2, $t2, $v0
	bnez	$t2, .L9
	mfc2	$t4, $12
	mfc2	$t5, $13
	mfc2	$t2, $14
	RTPS
	beqz	$s5, .L7
	sll	$s2, $t4, 16
	bltz	$s2, .L4
	nop
	slt	$at, $s2, $s0
	beqz	$at, .L4
	sra	$s3, $t4, 16
	bltz	$s3, .L4
	nop
	slt	$at, $s3, $s1
	beqz	$at, .L4
	nop
	j	.L7
	nop
.L4:
	sll	$s2, $t5, 16
	bltz	$s2, .L5
	nop
	slt	$at, $s2, $s0
	beqz	$at, .L5
	sra	$s3, $t5, 16
	bltz	$s3, .L5
	nop
	slt	$at, $s3, $s1
	beqz	$at, .L5
	nop
	j	.L7
	nop
.L5:
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
	j	.L7
	nop
.L6:
	mfc2	$t6, $14
	nop
	sll	$s2, $t6, 16
	bltz	$s2, .L9
	nop
	slt	$at, $s2, $s0
	beqz	$at, .L9
	sra	$s3, $t6, 16
	bltz	$s3, .L9
	nop
	slt	$at, $s3, $s1
	beqz	$at, .L9
	nop
	j	.L8
	nop
.L7:
	mfc2	$t6, $14
	nop
.L8:
	nop
	AVSZ4
	sw	$t4, 0x8($t3)
	sw	$t5, 0x14($t3)
	sw	$t2, 0x20($t3)
	sw	$t6, 0x2C($t3)
	mfc2	$t1, $7
	and	$t3, $t3, $t8
	srav	$t1, $t1, $a2
	sll	$t1, $t1, 2
	add	$t2, $a1, $t1
	lw	$t4, 0($t2)
	sw	$t3, 0($t2)
	or	$t4, $t4, $t7
	sw	$t4, 0($t3)
.L9:
	addi	$t0, $t0, -0x1
	bnez	$t0, .L3
	addiu	$a0, $a0, 0x88
.L10:
	lw	$s0, 0x4($sp)
	lw	$s1, 0x8($sp)
	lw	$s2, 0xC($sp)
	lw	$s3, 0x10($sp)
	lw	$s4, 0x14($sp)
	lw	$s5, 0x18($sp)
	nop
	jr	$ra
	addiu	$sp, $sp, 0x20
	.set	at
	.end	RotRMD_GT4
	.set	reorder
