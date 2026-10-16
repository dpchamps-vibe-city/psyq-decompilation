/* LIBGTE.LIB, member PPM.OBJ (hand-written assembly)
 *
 * ScanXY0: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	ScanXY0
	.ent	ScanXY0
ScanXY0:
	.set	noat
	lui	$at, %hi(D_00000360)
	sw	$s0, %lo(D_00000360)($at)
	lui	$at, %hi(D_00000364)
	sw	$s1, %lo(D_00000364)($at)
	lui	$at, %hi(D_00000368)
	sw	$s2, %lo(D_00000368)($at)
	lui	$at, %hi(D_0000036C)
	sw	$s3, %lo(D_0000036C)($at)
	lui	$at, %hi(D_00000370)
	sw	$s4, %lo(D_00000370)($at)
	lui	$at, %hi(D_00000374)
	sw	$s5, %lo(D_00000374)($at)
	lui	$at, %hi(D_00000378)
	sw	$s6, %lo(D_00000378)($at)
	lui	$at, %hi(D_0000037C)
	sw	$s7, %lo(D_0000037C)($at)
	move	$t1, $a2
	nop
	addi	$t1, $t1, -0x78
	sll	$t1, $t1, 4
	lw	$t2, 0x30($sp)
	nop
	sll	$t2, $t2, 4
	lw	$s0, 0x14($sp)
	lw	$s1, 0x18($sp)
	move	$t0, $a0
	lw	$s4, 0x20($sp)
	lw	$s5, 0x24($sp)
	lw	$s6, 0x28($sp)
	lw	$s7, 0x2C($sp)
	lw	$a0, 0x34($sp)
	lw	$v0, 0x1C($sp)
	nop
	lw	$t7, 0($v0)
.L1:
	slt	$at, $t0, $a2
	bnez	$at, .L15
	nop
	sra	$s2, $s0, 12
	sra	$s3, $s1, 12
	slt	$at, $s2, $a1
	beqz	$at, .L2
	nop
	move	$s2, $a1
.L2:
	slt	$at, $a3, $s2
	beqz	$at, .L3
	nop
	move	$s2, $a3
.L3:
	slt	$at, $s3, $a1
	beqz	$at, .L4
	nop
	move	$s3, $a1
.L4:
	slt	$at, $a3, $s3
	beqz	$at, .L5
	nop
	move	$s3, $a3
.L5:
	sub	$v0, $s2, $a1
	sll	$v0, $v0, 1
	add	$t7, $t7, $v0
	addi	$v0, $s2, -0xA0
	sll	$v0, $v0, 4
	andi	$v0, $v0, 0xFFFF
	sll	$t9, $t1, 16
	or	$t9, $t9, $v0
	mtc2	$t9, $0
	mtc2	$t2, $1
	nop
	RTPS
	addi	$t9, $t9, 0x10
	mfc2	$t3, $14
	nop
	andi	$t4, $t3, 0xFFFF
	sra	$t5, $t3, 16
	bgez	$t4, .L6
	nop
	li	$t4, 0
.L6:
	slti	$at, $t4, 0x100
	bnez	$at, .L7
	nop
	li	$t4, 0xFF
.L7:
	bgez	$t5, .L8
	nop
	li	$t5, 0
.L8:
	slti	$at, $t5, 0x100
	bnez	$at, .L9
	nop
	li	$t5, 0xFF
.L9:
	mtc2	$t9, $0
	nop
.L10:
	RTPS
	sll	$t5, $t5, 8
	add	$t5, $t5, $t4
	sll	$t5, $t5, 1
	add	$t5, $t5, $a0
	lh	$t6, 0($t5)
	addi	$t9, $t9, 0x10
	mtc2	$t9, $0
	sh	$t6, 0($t7)
	mfc2	$t3, $14
	addi	$s2, $s2, 0x1
	andi	$t4, $t3, 0xFFFF
	sra	$t5, $t3, 16
	li	$at, 0xff00ff00
	and	$t8, $t3, $at
	beqz	$t8, .L14
	nop
	bgez	$t4, .L11
	nop
	li	$t4, 0
.L11:
	slti	$at, $t4, 0x100
	bnez	$at, .L12
	nop
	li	$t4, 0xFF
.L12:
	bgez	$t5, .L13
	nop
	li	$t5, 0
.L13:
	slti	$at, $t5, 0x100
	bnez	$at, .L14
	nop
	li	$t5, 0xFF
.L14:
	slt	$at, $s3, $s2
	beqz	$at, .L10
	addi	$t7, $t7, 0x2
	sub	$v0, $a3, $s3
	sll	$v0, $v0, 1
	add	$t7, $t7, $v0
	addi	$t1, $t1, 0x10
.L15:
	lw	$v0, 0x4($s4)
	lw	$v1, 0($s5)
	slt	$at, $t0, $v0
	beqz	$at, .L16
	nop
	b	.L18
	addu	$s0, $s0, $v1
.L16:
	lw	$v0, 0x8($s4)
	lw	$v1, 0x4($s5)
	slt	$at, $t0, $v0
	beqz	$at, .L17
	nop
	b	.L18
	addu	$s0, $s0, $v1
.L17:
	lw	$v1, 0x8($s5)
	nop
	addu	$s0, $s0, $v1
.L18:
	lw	$v0, 0x4($s6)
	lw	$v1, 0($s7)
	slt	$at, $t0, $v0
	beqz	$at, .L19
	nop
	b	.L21
	addu	$s1, $s1, $v1
.L19:
	lw	$v0, 0x8($s6)
	lw	$v1, 0x4($s7)
	slt	$at, $t0, $v0
	beqz	$at, .L20
	nop
	b	.L21
	addu	$s1, $s1, $v1
.L20:
	lw	$v1, 0x8($s7)
	nop
	addu	$s1, $s1, $v1
.L21:
	slt	$at, $s1, $s0
	beqz	$at, .L22
	nop
	move	$s0, $s1
.L22:
	lw	$v0, 0x10($sp)
	addi	$t0, $t0, 0x1
	slt	$at, $v0, $t0
	beqz	$at, .L1
	nop
	lw	$s0, D_00000360
	lw	$s1, D_00000364
	lw	$s2, D_00000368
	lw	$s3, D_0000036C
	lw	$s4, D_00000370
	lw	$s5, D_00000374
	lw	$s6, D_00000378
	lw	$s7, D_0000037C
	jr	$ra
	nop
	.set	at
	.end	ScanXY0
	.set	reorder

	.data
	.align	4
D_00000360:
	.word	0x00000000
D_00000364:
	.word	0x00000000
D_00000368:
	.word	0x00000000
D_0000036C:
	.word	0x00000000
D_00000370:
	.word	0x00000000
D_00000374:
	.word	0x00000000
D_00000378:
	.word	0x00000000
D_0000037C:
	.word	0x00000000
