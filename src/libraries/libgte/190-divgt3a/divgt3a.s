/* LIBGTE.LIB, member DIVGT3A.OBJ (hand-written assembly)
 *
 * RCpolyGT3: no prototype in the SDK headers.
 *
 * RCpolyGT3A: no prototype in the SDK headers.
 *
 * func_00000474: private routine, unnamed in the original; the name is its offset.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RCpolyGT3
	.ent	RCpolyGT3
RCpolyGT3:
	addi	$a3, $a1, 0x60
	li	$a2, 0
	.end	RCpolyGT3

	.globl	RCpolyGT3A
	.ent	RCpolyGT3A
RCpolyGT3A:
	.set	noat
	lw	$t0, 0x48($a3)
	lw	$t1, 0x4C($a3)
	lw	$t2, 0x50($a3)
	cfc2	$t9, $26
	lw	$t4, 0x14($t0)
	lw	$t5, 0x14($t1)
	lw	$t6, 0x14($t2)
	sra	$t8, $t9, 1
	sltu	$at, $t4, $t8
	beqz	$at, .L1
	sltu	$at, $t5, $t8
	beqz	$at, .L1
	sltu	$at, $t6, $t8
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
	slt	$at, $t8, $t4
	beqz	$at, .L2
	slt	$at, $t8, $t5
	beqz	$at, .L2
	slt	$at, $t8, $t6
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
	nop
	move	$v0, $a0
	jr	$ra
	nop
.L3:
	cfc2	$t9, $25
	lh	$t4, 0x12($t0)
	lh	$t5, 0x12($t1)
	lh	$t6, 0x12($t2)
	sra	$t9, $t9, 16
	addu	$t8, $t9, $v1
	slt	$at, $t8, $t4
	beqz	$at, .L4
	slt	$at, $t8, $t5
	beqz	$at, .L4
	slt	$at, $t8, $t6
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
	nop
	move	$v0, $a0
	jr	$ra
	nop
.L5:
	lh	$t4, 0($t0)
	lh	$t5, 0($t1)
	lh	$t6, 0($t2)
	add	$t7, $t4, $t5
	add	$t8, $t5, $t6
	add	$t9, $t6, $t4
	sra	$t7, $t7, 1
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sh	$t7, 0($a3)
	sh	$t8, 0x18($a3)
	sh	$t9, 0x30($a3)
	lh	$t4, 0x2($t0)
	lh	$t5, 0x2($t1)
	lh	$t6, 0x2($t2)
	add	$t7, $t4, $t5
	add	$t8, $t5, $t6
	add	$t9, $t6, $t4
	sra	$t7, $t7, 1
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sh	$t7, 0x2($a3)
	sh	$t8, 0x1A($a3)
	sh	$t9, 0x32($a3)
	lh	$t4, 0x4($t0)
	lh	$t5, 0x4($t1)
	lh	$t6, 0x4($t2)
	add	$t7, $t4, $t5
	add	$t8, $t5, $t6
	add	$t9, $t6, $t4
	sra	$t7, $t7, 1
	sra	$t8, $t8, 1
	sra	$t9, $t9, 1
	sh	$t7, 0x4($a3)
	sh	$t8, 0x1C($a3)
	sh	$t9, 0x34($a3)
	lwc2	$0, 0($a3)
	lwc2	$1, 0x4($a3)
	lwc2	$2, 0x18($a3)
	lwc2	$3, 0x1C($a3)
	lwc2	$4, 0x30($a3)
	lwc2	$5, 0x34($a3)
	lbu	$t4, 0x8($t0)
	lbu	$t5, 0x8($t1)
	lbu	$t6, 0x8($t2)
	addu	$t7, $t4, $t5
	addu	$t8, $t5, $t6
	addu	$t9, $t6, $t4
	srl	$t7, $t7, 1
	srl	$t8, $t8, 1
	srl	$t9, $t9, 1
	sb	$t7, 0x8($a3)
	sb	$t8, 0x20($a3)
	sb	$t9, 0x38($a3)
	RTPT
	lbu	$t4, 0x9($t0)
	lbu	$t5, 0x9($t1)
	lbu	$t6, 0x9($t2)
	addu	$t7, $t4, $t5
	addu	$t8, $t5, $t6
	addu	$t9, $t6, $t4
	srl	$t7, $t7, 1
	srl	$t8, $t8, 1
	srl	$t9, $t9, 1
	sb	$t7, 0x9($a3)
	sb	$t8, 0x21($a3)
	sb	$t9, 0x39($a3)
	lbu	$t4, 0xC($t0)
	lbu	$t5, 0xC($t1)
	lbu	$t6, 0xC($t2)
	addu	$t7, $t4, $t5
	addu	$t8, $t5, $t6
	addu	$t9, $t6, $t4
	srl	$t7, $t7, 1
	srl	$t8, $t8, 1
	srl	$t9, $t9, 1
	sb	$t7, 0xC($a3)
	sb	$t8, 0x24($a3)
	sb	$t9, 0x3C($a3)
	lbu	$t4, 0xD($t0)
	lbu	$t5, 0xD($t1)
	lbu	$t6, 0xD($t2)
	addu	$t7, $t4, $t5
	addu	$t8, $t5, $t6
	addu	$t9, $t6, $t4
	srl	$t7, $t7, 1
	srl	$t8, $t8, 1
	srl	$t9, $t9, 1
	sb	$t7, 0xD($a3)
	sb	$t8, 0x25($a3)
	sb	$t9, 0x3D($a3)
	lbu	$t4, 0xE($t0)
	lbu	$t5, 0xE($t1)
	lbu	$t6, 0xE($t2)
	addu	$t7, $t4, $t5
	addu	$t8, $t5, $t6
	addu	$t9, $t6, $t4
	srl	$t7, $t7, 1
	srl	$t8, $t8, 1
	srl	$t9, $t9, 1
	sb	$t7, 0xE($a3)
	sb	$t8, 0x26($a3)
	sb	$t9, 0x3E($a3)
	lw	$t4, 0($a1)
	addiu	$a2, $a2, 0x1
	bne	$t4, $a2, .L6
	nop
	swc2	$12, 0x10($a3)
	swc2	$13, 0x28($a3)
	swc2	$14, 0x40($a3)
	move	$v1, $ra
	lw	$t0, 0x4C($a3)
	addiu	$t1, $a3, 0x18
	addiu	$t2, $a3, 0
	jal	func_00000474
	nop
	addiu	$t0, $a3, 0
	addiu	$t1, $a3, 0x18
	addiu	$t2, $a3, 0x30
	jal	func_00000474
	nop
	lw	$t0, 0x48($a3)
	addiu	$t1, $a3, 0
	addiu	$t2, $a3, 0x30
	jal	func_00000474
	nop
	lw	$t0, 0x50($a3)
	addiu	$t1, $a3, 0x30
	addiu	$t2, $a3, 0x18
	jal	func_00000474
	nop
	move	$ra, $v1
	addiu	$a2, $a2, -0x1
	b	.L7
	nop
.L6:
	swc2	$17, 0x14($a3)
	swc2	$18, 0x2C($a3)
	swc2	$19, 0x44($a3)
	swc2	$12, 0x10($a3)
	swc2	$13, 0x28($a3)
	swc2	$14, 0x40($a3)
	addiu	$a3, $a3, 0x58
	sw	$ra, 0x54($a3)
	lw	$t4, -0x10($a3)
	addiu	$t5, $a3, -0x58
	addiu	$t6, $a3, -0x28
	sw	$t4, 0x48($a3)
	sw	$t5, 0x4C($a3)
	sw	$t6, 0x50($a3)
	jal	RCpolyGT3A
	nop
	lw	$t4, -0xC($a3)
	addiu	$t5, $a3, -0x40
	addiu	$t6, $a3, -0x58
	sw	$t4, 0x48($a3)
func_0000040C:
	sw	$t5, 0x4C($a3)
	sw	$t6, 0x50($a3)
	jal	RCpolyGT3A
	nop
	lw	$t4, -0x8($a3)
	addiu	$t5, $a3, -0x28
	addiu	$t6, $a3, -0x40
	sw	$t4, 0x48($a3)
	sw	$t5, 0x4C($a3)
	sw	$t6, 0x50($a3)
	jal	RCpolyGT3A
	nop
	addiu	$t4, $a3, -0x58
	addiu	$t5, $a3, -0x40
	addiu	$t6, $a3, -0x28
	sw	$t4, 0x48($a3)
	sw	$t5, 0x4C($a3)
	sw	$t6, 0x50($a3)
	jal	RCpolyGT3A
	nop
	lw	$ra, 0x54($a3)
	addiu	$a3, $a3, -0x58
	addiu	$a2, $a2, -0x1
.L7:
	move	$v0, $a0
	jr	$ra
	nop
	.set	at
	.end	RCpolyGT3A

	.ent	func_00000474
func_00000474:
	lhu	$t4, 0xC($a1)
	lhu	$t5, 0x8($t0)
	sll	$t4, $t4, 16
	addu	$t5, $t5, $t4
	lhu	$t4, 0xE($a1)
	lhu	$t6, 0x8($t1)
	sll	$t4, $t4, 16
	addu	$t6, $t6, $t4
	lhu	$t7, 0x8($t2)
	lb	$t4, 0x13($a1)
	sw	$t5, 0xC($a0)
	sw	$t6, 0x18($a0)
	sw	$t7, 0x24($a0)
	sb	$t4, 0xF($t0)
	lw	$t4, 0x10($t0)
	lw	$t5, 0x10($t1)
	lw	$t6, 0x10($t2)
	sw	$t4, 0x8($a0)
	sw	$t5, 0x14($a0)
	sw	$t6, 0x20($a0)
	lw	$t4, 0x14($a1)
	sll	$t9, $a0, 8
	srl	$t9, $t9, 8
	lw	$t8, 0($t4)
	sw	$t9, 0($t4)
	li	$t6, 0x9000000
	or	$t8, $t8, $t6
	lw	$t4, 0xC($t0)
	lw	$t5, 0xC($t1)
	lw	$t6, 0xC($t2)
	sw	$t4, 0x4($a0)
	sw	$t5, 0x10($a0)
	sw	$t6, 0x1C($a0)
	sw	$t8, 0($a0)
	addiu	$a0, $a0, 0x28
	jr	$ra
	nop
	.end	func_00000474
	.set	reorder
