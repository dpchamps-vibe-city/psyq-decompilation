/* LIBGTE.LIB, member DIVFT4A.OBJ (hand-written assembly)
 *
 * RCpolyFT4: no prototype in the SDK headers.
 *
 * RCpolyFT4A: no prototype in the SDK headers.
 *
 * func_000004F8: private routine, unnamed in the original; the name is its offset.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RCpolyFT4
	.ent	RCpolyFT4
RCpolyFT4:
	addi	$a3, $a1, 0x78
	li	$a2, 0
	.end	RCpolyFT4

	.globl	RCpolyFT4A
	.ent	RCpolyFT4A
RCpolyFT4A:
	.set	noat
	lw	$t0, 0x78($a3)
	lw	$t1, 0x7C($a3)
	lw	$t2, 0x80($a3)
	lw	$t3, 0x84($a3)
	cfc2	$t9, $26
	lw	$t4, 0x14($t0)
	lw	$t5, 0x14($t1)
	lw	$t6, 0x14($t2)
	lw	$t7, 0x14($t3)
	sra	$t8, $t9, 1
	sltu	$at, $t4, $t8
	beqz	$at, .L1
	sltu	$at, $t5, $t8
	beqz	$at, .L1
	sltu	$at, $t6, $t8
	beqz	$at, .L1
	sltu	$at, $t7, $t8
	beqz	$at, .L1
	nop
	move	$v0, $a0
	jr	$ra
	nop
.L1:
	cfc2	$t9, $24
	lw	$v0, 0x4($a1)
	lw	$v1, 0x8($a1)
	sra	$t9, $t9, 16
	srl	$v0, $v0, 1
	srl	$v1, $v1, 1
	addu	$t8, $t9, $v0
	lh	$t4, 0x10($t0)
	lh	$t5, 0x10($t1)
	lh	$t6, 0x10($t2)
	lh	$t7, 0x10($t3)
	slt	$at, $t8, $t4
	beqz	$at, .L2
	slt	$at, $t8, $t5
	beqz	$at, .L2
	slt	$at, $t8, $t6
	beqz	$at, .L2
	slt	$at, $t8, $t7
	beqz	$at, .L2
	nop
	move	$v0, $a0
	jr	$ra
	nop
.L2:
	subu	$t8, $t9, $v0
	slt	$at, $t4, $t8
	beqz	$at, .L3
	slt	$at, $t5, $t8
	beqz	$at, .L3
	slt	$at, $t6, $t8
	beqz	$at, .L3
	slt	$at, $t7, $t8
	beqz	$at, .L3
	nop
	move	$v0, $a0
	jr	$ra
	nop
.L3:
	cfc2	$t9, $25
	lh	$t4, 0x12($t0)
	lh	$t5, 0x12($t1)
	lh	$t6, 0x12($t2)
	lh	$t7, 0x12($t3)
	sra	$t9, $t9, 16
	addu	$t8, $t9, $v1
	slt	$at, $t8, $t4
	beqz	$at, .L4
	slt	$at, $t8, $t5
	beqz	$at, .L4
	slt	$at, $t8, $t6
	beqz	$at, .L4
	slt	$at, $t8, $t7
	beqz	$at, .L4
	nop
	move	$v0, $a0
	jr	$ra
	nop
.L4:
	subu	$t8, $t9, $v1
	slt	$at, $t4, $t8
	beqz	$at, .L5
	slt	$at, $t5, $t8
	beqz	$at, .L5
	slt	$at, $t6, $t8
	beqz	$at, .L5
	slt	$at, $t7, $t8
	beqz	$at, .L5
	nop
	move	$v0, $a0
	jr	$ra
	nop
.L5:
	lh	$t4, 0($t0)
	lh	$t5, 0($t1)
	lh	$t6, 0($t2)
	lh	$t7, 0($t3)
	add	$t9, $t4, $t6
	add	$t8, $t7, $t5
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sh	$t8, 0x30($a3)
	sh	$t9, 0x18($a3)
	add	$t8, $t4, $t5
	add	$t9, $t7, $t6
	add	$v1, $t8, $t9
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sra	$v1, $v1, 2
	sh	$t8, 0($a3)
	sh	$t9, 0x48($a3)
	sh	$v1, 0x60($a3)
	lh	$t4, 0x2($t0)
	lh	$t5, 0x2($t1)
	lh	$t6, 0x2($t2)
	lh	$t7, 0x2($t3)
	add	$t9, $t4, $t6
	add	$t8, $t7, $t5
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sh	$t8, 0x32($a3)
	sh	$t9, 0x1A($a3)
	add	$t8, $t4, $t5
	add	$t9, $t7, $t6
	add	$v1, $t8, $t9
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sra	$v1, $v1, 2
	sh	$t8, 0x2($a3)
	sh	$t9, 0x4A($a3)
	sh	$v1, 0x62($a3)
	lh	$t4, 0x4($t0)
	lh	$t5, 0x4($t1)
	lh	$t6, 0x4($t2)
	lh	$t7, 0x4($t3)
	add	$t9, $t4, $t6
	add	$t8, $t7, $t5
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sh	$t8, 0x34($a3)
	sh	$t9, 0x1C($a3)
	add	$t8, $t4, $t5
	add	$t9, $t7, $t6
	add	$v1, $t8, $t9
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sra	$v1, $v1, 2
	sh	$t8, 0x4($a3)
	sh	$t9, 0x4C($a3)
	sh	$v1, 0x64($a3)
	lwc2	$0, 0($a3)
	lwc2	$1, 0x4($a3)
	lwc2	$2, 0x18($a3)
	lwc2	$3, 0x1C($a3)
	lwc2	$4, 0x60($a3)
	lwc2	$5, 0x64($a3)
	lbu	$t4, 0x8($t0)
	RTPT
	lbu	$t5, 0x8($t1)
	lbu	$t6, 0x8($t2)
	lbu	$t7, 0x8($t3)
	add	$t9, $t4, $t6
	add	$t8, $t7, $t5
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sb	$t8, 0x38($a3)
	sb	$t9, 0x20($a3)
	add	$t8, $t4, $t5
	add	$t9, $t7, $t6
	add	$v1, $t8, $t9
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sra	$v1, $v1, 2
	sb	$t8, 0x8($a3)
	sb	$t9, 0x50($a3)
	sb	$v1, 0x68($a3)
	swc2	$12, 0x10($a3)
	swc2	$13, 0x28($a3)
	swc2	$14, 0x70($a3)
	swc2	$17, 0x14($a3)
	swc2	$18, 0x2C($a3)
	swc2	$19, 0x74($a3)
	lwc2	$0, 0x30($a3)
	lwc2	$1, 0x34($a3)
	lwc2	$2, 0x48($a3)
	lwc2	$3, 0x4C($a3)
	lbu	$t4, 0x9($t0)
	RTPT
	lbu	$t5, 0x9($t1)
	lbu	$t6, 0x9($t2)
	lbu	$t7, 0x9($t3)
	add	$t9, $t4, $t6
	add	$t8, $t7, $t5
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sb	$t8, 0x39($a3)
	sb	$t9, 0x21($a3)
	add	$t8, $t4, $t5
	add	$t9, $t7, $t6
	add	$v1, $t8, $t9
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sra	$v1, $v1, 2
	sb	$t8, 0x9($a3)
	sb	$t9, 0x51($a3)
	sb	$v1, 0x69($a3)
	lw	$t4, 0($a1)
	addiu	$a2, $a2, 0x1
	bne	$t4, $a2, .L6
	nop
	move	$v1, $ra
	lw	$t0, 0x78($a3)
	addiu	$t1, $a3, 0
	addiu	$t2, $a3, 0x18
	addiu	$t3, $a3, 0x60
	swc2	$12, 0x40($a3)
	swc2	$13, 0x58($a3)
	jal	func_000004F8
	nop
	lw	$t0, 0x7C($a3)
	addiu	$t1, $a3, 0x30
	addiu	$t2, $a3, 0
	addiu	$t3, $a3, 0x60
	jal	func_000004F8
	nop
	lw	$t0, 0x80($a3)
	addiu	$t1, $a3, 0x18
	addiu	$t2, $a3, 0x48
	addiu	$t3, $a3, 0x60
	jal	func_000004F8
	nop
	lw	$t0, 0x84($a3)
	addiu	$t1, $a3, 0x48
	addiu	$t2, $a3, 0x30
	addiu	$t3, $a3, 0x60
	jal	func_000004F8
	nop
	move	$ra, $v1
	addiu	$a2, $a2, -0x1
	b	.L7
	nop
.L6:
	addiu	$a3, $a3, 0x8C
	sw	$ra, 0x88($a3)
	lw	$t4, -0x14($a3)
	addiu	$t5, $a3, -0x8C
	addiu	$t6, $a3, -0x74
	addiu	$t7, $a3, -0x2C
	sw	$t4, 0x78($a3)
	sw	$t5, 0x7C($a3)
	sw	$t6, 0x80($a3)
	sw	$t7, 0x84($a3)
	swc2	$12, -0x4C($a3)
	swc2	$13, -0x34($a3)
	swc2	$17, -0x48($a3)
	swc2	$18, -0x30($a3)
	jal	RCpolyFT4A
	nop
	lw	$t4, -0x10($a3)
	addiu	$t5, $a3, -0x5C
	addiu	$t6, $a3, -0x8C
	addiu	$t7, $a3, -0x2C
	sw	$t4, 0x78($a3)
	sw	$t5, 0x7C($a3)
	sw	$t6, 0x80($a3)
	sw	$t7, 0x84($a3)
	jal	RCpolyFT4A
	nop
func_00000490:
	lw	$t4, -0xC($a3)
	addiu	$t5, $a3, -0x74
	addiu	$t6, $a3, -0x44
	addiu	$t7, $a3, -0x2C
	sw	$t4, 0x78($a3)
	sw	$t5, 0x7C($a3)
	sw	$t6, 0x80($a3)
	sw	$t7, 0x84($a3)
	jal	RCpolyFT4A
	nop
	lw	$t4, -0x8($a3)
	addiu	$t5, $a3, -0x44
	addiu	$t6, $a3, -0x5C
	addiu	$t7, $a3, -0x2C
	sw	$t4, 0x78($a3)
	sw	$t5, 0x7C($a3)
	sw	$t6, 0x80($a3)
	sw	$t7, 0x84($a3)
	jal	RCpolyFT4A
	nop
	lw	$ra, 0x88($a3)
	addiu	$a3, $a3, -0x8C
	addiu	$a2, $a2, -0x1
.L7:
	move	$v0, $a0
	jr	$ra
	nop
	.set	at
	.end	RCpolyFT4A

	.ent	func_000004F8
func_000004F8:
	lhu	$t4, 0xC($a1)
	lhu	$t5, 0x8($t0)
	sll	$t4, $t4, 16
	addu	$t5, $t5, $t4
	lhu	$t4, 0xE($a1)
	lhu	$t6, 0x8($t1)
	sll	$t4, $t4, 16
	addu	$t6, $t6, $t4
	lhu	$t7, 0x8($t2)
	lhu	$t8, 0x8($t3)
	lw	$t4, 0x10($a1)
	sw	$t5, 0xC($a0)
	sw	$t6, 0x14($a0)
	sw	$t7, 0x1C($a0)
	sw	$t8, 0x24($a0)
	sw	$t4, 0x4($a0)
	lw	$t4, 0x10($t0)
	lw	$t5, 0x10($t1)
	lw	$t6, 0x10($t2)
	lw	$t7, 0x10($t3)
	sw	$t4, 0x8($a0)
	sw	$t5, 0x10($a0)
	sw	$t6, 0x18($a0)
	sw	$t7, 0x20($a0)
	lw	$t4, 0x14($a1)
	sll	$t9, $a0, 8
	srl	$t9, $t9, 8
	lw	$t8, 0($t4)
	sw	$t9, 0($t4)
	li	$t6, 0x9000000
	or	$t8, $t8, $t6
	sw	$t8, 0($a0)
	addiu	$a0, $a0, 0x28
	jr	$ra
	nop
	nop
	.end	func_000004F8
	.set	reorder
