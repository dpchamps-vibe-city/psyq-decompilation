/* LIBGTE.LIB, member DIVP.OBJ (hand-written assembly)
 *
 * DivPloyFT4: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	DivPloyFT4
	.ent	DivPloyFT4
DivPloyFT4:
	.set	noat
	cfc2	$t0, $21
	cfc2	$t1, $22
	cfc2	$t2, $23
	sw	$t0, 0x74($a1)
	sw	$t1, 0x78($a1)
	sw	$t2, 0x7C($a1)
	li	$t3, 0x1
	sllv	$t0, $t3, $a2
	sllv	$t1, $t3, $a3
	li	$t3, 0xC
	subu	$a2, $t3, $a2
	subu	$a3, $t3, $a3
	lw	$t3, 0x8($a1)
	lw	$t4, 0xC($a1)
	sw	$t3, 0x38($a1)
	sw	$t4, 0x3C($a1)
	lw	$t5, 0x18($a1)
	lw	$t6, 0x1C($a1)
	sw	$t5, 0x48($a1)
	sw	$t6, 0x4C($a1)
	lhu	$t3, 0x28($a1)
	lhu	$t4, 0x2C($a1)
	sh	$t3, 0x52($a1)
	sh	$t4, 0x56($a1)
	li	$v0, 0
.L1:
	subu	$t3, $t0, $v0
	blez	$t3, .L9
	addiu	$t3, $t3, -0x1
	sllv	$t3, $t3, $a2
	mtc2	$t3, $8
	lw	$t3, 0x38($a1)
	lw	$t4, 0x3C($a1)
	sw	$t3, 0x30($a1)
	sw	$t4, 0x34($a1)
	lw	$t5, 0x48($a1)
	lw	$t6, 0x4C($a1)
	sw	$t5, 0x40($a1)
	sw	$t6, 0x44($a1)
	lbu	$t3, 0x28($a1)
	lbu	$t4, 0x29($a1)
	ctc2	$t3, $21
	ctc2	$t4, $22
	lbu	$t5, 0x2A($a1)
	lbu	$t6, 0x2B($a1)
	mtc2	$t5, $9
	mtc2	$t6, $10
	lhu	$t3, 0x52($a1)
	lhu	$t4, 0x56($a1)
	sh	$t3, 0x50($a1)
	sh	$t4, 0x54($a1)
	INTPL
	lbu	$t3, 0x2C($a1)
	lbu	$t4, 0x2D($a1)
	lbu	$t5, 0x2E($a1)
	lbu	$t6, 0x2F($a1)
	ctc2	$t3, $21
	ctc2	$t4, $22
	mfc2	$t3, $9
	mfc2	$t4, $10
	mtc2	$t5, $9
	mtc2	$t6, $10
	sb	$t3, 0x52($a1)
	sb	$t4, 0x53($a1)
	INTPL
	lh	$t3, 0x8($a1)
	lh	$t4, 0xA($a1)
	lh	$t5, 0xC($a1)
	lh	$t6, 0x10($a1)
	lh	$t7, 0x12($a1)
	lh	$t8, 0x14($a1)
	ctc2	$t3, $21
	ctc2	$t4, $22
	ctc2	$t5, $23
	mfc2	$t3, $9
	mfc2	$t4, $10
	mtc2	$t6, $9
	mtc2	$t7, $10
	mtc2	$t8, $11
	sb	$t3, 0x56($a1)
	sb	$t4, 0x57($a1)
	INTPL
	lh	$t3, 0x18($a1)
	lh	$t4, 0x1A($a1)
	lh	$t5, 0x1C($a1)
	lh	$t6, 0x20($a1)
	lh	$t7, 0x22($a1)
	lh	$t8, 0x24($a1)
	ctc2	$t3, $21
	ctc2	$t4, $22
	ctc2	$t5, $23
	mfc2	$t3, $9
	mfc2	$t4, $10
	mfc2	$t5, $11
	andi	$t3, $t3, 0xFFFF
	sll	$t4, $t4, 16
	or	$t3, $t3, $t4
	mtc2	$t6, $9
	mtc2	$t7, $10
	mtc2	$t8, $11
	sw	$t3, 0x38($a1)
	sw	$t5, 0x3C($a1)
	INTPL
	lwc2	$0, 0x30($a1)
	lwc2	$1, 0x34($a1)
	lwc2	$2, 0x38($a1)
	lwc2	$3, 0x3C($a1)
	mfc2	$t3, $9
	mfc2	$t4, $10
	mfc2	$t5, $11
	andi	$t3, $t3, 0xFFFF
	RTPT
	sll	$t4, $t4, 16
	or	$t3, $t3, $t4
	sw	$t3, 0x48($a1)
	sw	$t5, 0x4C($a1)
	lhu	$t3, 0x50($a1)
	lhu	$t4, 0x52($a1)
	sh	$t3, 0x58($a1)
	sh	$t4, 0x5A($a1)
	swc2	$12, 0x5C($a1)
	swc2	$13, 0x60($a1)
	li	$v1, 0
.L2:
	subu	$t3, $t1, $v1
	blez	$t3, .L8
	addiu	$t3, $t3, -0x1
	sllv	$t3, $t3, $a3
	mtc2	$t3, $8
	lh	$t3, 0x30($a1)
	lh	$t4, 0x32($a1)
	lh	$t5, 0x34($a1)
	lh	$t6, 0x40($a1)
	lh	$t7, 0x42($a1)
	lh	$t8, 0x44($a1)
	ctc2	$t3, $21
	ctc2	$t4, $22
	ctc2	$t5, $23
	mtc2	$t6, $9
	mtc2	$t7, $10
	mtc2	$t8, $11
	lh	$t3, 0x38($a1)
	INTPL
	lh	$t4, 0x3A($a1)
	lh	$t5, 0x3C($a1)
	lh	$t6, 0x48($a1)
	lh	$t7, 0x4A($a1)
	lh	$t8, 0x4C($a1)
	ctc2	$t3, $21
	ctc2	$t4, $22
	ctc2	$t5, $23
	mfc2	$t3, $9
	mfc2	$t4, $10
	mfc2	$t5, $11
	mtc2	$t6, $9
	mtc2	$t7, $10
	mtc2	$t8, $11
	andi	$t3, $t3, 0xFFFF
	INTPL
	sll	$t4, $t4, 16
	or	$t3, $t3, $t4
	mtc2	$t3, $0
	mtc2	$t5, $1
	lbu	$t3, 0x50($a1)
	lbu	$t4, 0x51($a1)
	lbu	$t6, 0x54($a1)
	lbu	$t7, 0x55($a1)
	ctc2	$t3, $21
	ctc2	$t4, $22
	mfc2	$t3, $9
	mfc2	$t4, $10
	mfc2	$t5, $11
	mtc2	$t6, $9
	mtc2	$t7, $10
	andi	$t3, $t3, 0xFFFF
	sll	$t4, $t4, 16
	or	$t3, $t3, $t4
	mtc2	$t3, $2
	mtc2	$t5, $3
	lhu	$t5, 0($a1)
	INTPL
	lhu	$t3, 0x58($a1)
	lhu	$t4, 0x5A($a1)
	sll	$t5, $t5, 16
	or	$t3, $t3, $t5
	sw	$t3, 0xC($a0)
	sh	$t4, 0x1C($a0)
	lbu	$t3, 0x52($a1)
	lbu	$t4, 0x53($a1)
	lbu	$t6, 0x56($a1)
	lbu	$t7, 0x57($a1)
	lhu	$t5, 0x2($a1)
	ctc2	$t3, $21
	ctc2	$t4, $22
	sll	$t5, $t5, 16
	mfc2	$t3, $9
	mfc2	$t4, $10
	mtc2	$t6, $9
	mtc2	$t7, $10
	andi	$t3, $t3, 0xFF
	sll	$t4, $t4, 8
	INTPL
	or	$t3, $t3, $t4
	or	$t3, $t3, $t5
	sh	$t3, 0x58($a1)
	sw	$t3, 0x14($a0)
	mfc2	$t3, $9
	mfc2	$t4, $10
	andi	$t3, $t3, 0xFF
	RTPT
	sll	$t4, $t4, 8
	or	$t3, $t3, $t4
	lw	$t4, 0x70($a1)
	sh	$t3, 0x5A($a1)
	sh	$t3, 0x24($a0)
	sw	$t4, 0x4($a0)
	lh	$t4, 0x5C($a1)
	lh	$t5, 0x60($a1)
	lh	$t2, 0x5E($a1)
	lh	$t3, 0x62($a1)
	lw	$t6, 0x5C($a1)
	lw	$t7, 0x60($a1)
	sw	$t6, 0x8($a0)
	sw	$t7, 0x18($a0)
	swc2	$12, 0x64($a1)
	swc2	$13, 0x68($a1)
	li	$t8, 0x140
	lh	$t6, 0x64($a1)
	lh	$t7, 0x68($a1)
	slt	$at, $t8, $t4
	beqz	$at, .L3
	slt	$at, $t8, $t5
	beqz	$at, .L3
	slt	$at, $t8, $t6
	beqz	$at, .L3
	slt	$at, $t8, $t7
	beqz	$at, .L3
	nop
	b	.L7
	nop
.L3:
	move	$t8, $zero
	slt	$at, $t4, $t8
	beqz	$at, .L4
	slt	$at, $t5, $t8
	beqz	$at, .L4
	slt	$at, $t6, $t8
	beqz	$at, .L4
	slt	$at, $t7, $t8
	beqz	$at, .L4
	nop
	b	.L7
	nop
.L4:
	li	$t8, 0xF0
	lh	$t6, 0x66($a1)
	lh	$t7, 0x6A($a1)
	slt	$at, $t8, $t2
	beqz	$at, .L5
	slt	$at, $t8, $t3
	beqz	$at, .L5
	slt	$at, $t8, $t6
	beqz	$at, .L5
	slt	$at, $t8, $t7
	beqz	$at, .L5
	nop
	b	.L7
	nop
.L5:
	move	$t8, $zero
	slt	$at, $t2, $t8
	beqz	$at, .L6
	slt	$at, $t3, $t8
	beqz	$at, .L6
	slt	$at, $t6, $t8
	beqz	$at, .L6
	slt	$at, $t7, $t8
	beqz	$at, .L6
	nop
	b	.L7
	nop
.L6:
	lw	$t2, 0x4($a1)
	sll	$t8, $a0, 8
	lw	$t5, 0($t2)
	srl	$t8, $t8, 8
	li	$at, 0x9000000
	or	$t5, $t5, $at
	sw	$t8, 0($t2)
	sw	$t5, 0($a0)
	swc2	$12, 0x10($a0)
	swc2	$13, 0x20($a0)
	addi	$a0, $a0, 0x28
.L7:
	swc2	$12, 0x5C($a1)
	swc2	$13, 0x60($a1)
	addi	$v1, $v1, 0x1
	b	.L2
	nop
.L8:
	addi	$v0, $v0, 0x1
	b	.L1
	nop
.L9:
	move	$v0, $a0
	lw	$t0, 0x74($a1)
	lw	$t1, 0x78($a1)
	lw	$t2, 0x7C($a1)
	ctc2	$t0, $21
	ctc2	$t1, $22
	ctc2	$t2, $23
	jr	$ra
	nop
	.set	at
	.end	DivPloyFT4
	.set	reorder
