/* LIBGTE.LIB, member DIVF4A.OBJ (hand-written assembly)
 *
 * RCpolyF4: no prototype in the SDK headers.
 *
 * RCpolyF4A: no prototype in the SDK headers.
 *
 * func_00000490: private routine, unnamed in the original; the name is its offset.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RCpolyF4
	.ent	RCpolyF4
RCpolyF4:
	addi	$a3, $a1, 0x78
	li	$a2, 0
	.end	RCpolyF4

	.globl	RCpolyF4A
	.ent	RCpolyF4A
RCpolyF4A:
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
	lh	$t5, 0x2($t0)
	lh	$t6, 0x4($t0)
	lh	$t7, 0($t1)
	lh	$t8, 0x2($t1)
	lh	$t9, 0x4($t1)
	add	$v0, $t4, $t7
	sra	$v0, $v0, 1
	sh	$v0, 0($a3)
	add	$v0, $t5, $t8
	sra	$v0, $v0, 1
	sh	$v0, 0x2($a3)
	add	$v0, $t6, $t9
	sra	$v0, $v0, 1
	sh	$v0, 0x4($a3)
	lh	$t7, 0($t2)
	lh	$t8, 0x2($t2)
	lh	$t9, 0x4($t2)
	add	$v0, $t4, $t7
	sra	$v0, $v0, 1
	sh	$v0, 0x18($a3)
	add	$v0, $t5, $t8
	sra	$v0, $v0, 1
	sh	$v0, 0x1A($a3)
	add	$v0, $t6, $t9
	sra	$v0, $v0, 1
	sh	$v0, 0x1C($a3)
	lwc2	$0, 0($a3)
	lwc2	$1, 0x4($a3)
	lwc2	$2, 0x18($a3)
	lwc2	$3, 0x1C($a3)
	nop
	RTPT
	lh	$t4, 0($t3)
	lh	$t5, 0x2($t3)
	lh	$t6, 0x4($t3)
	add	$v0, $t4, $t7
	sra	$v0, $v0, 1
	sh	$v0, 0x48($a3)
	add	$v0, $t5, $t8
	sra	$v0, $v0, 1
	sh	$v0, 0x4A($a3)
	add	$v0, $t6, $t9
	sra	$v0, $v0, 1
	sh	$v0, 0x4C($a3)
	lh	$t7, 0($t1)
	lh	$t8, 0x2($t1)
	lh	$t9, 0x4($t1)
	add	$v0, $t4, $t7
	sra	$v0, $v0, 1
	sh	$v0, 0x30($a3)
	add	$v0, $t5, $t8
	sra	$v0, $v0, 1
	sh	$v0, 0x32($a3)
	add	$v0, $t6, $t9
	sra	$v0, $v0, 1
	sh	$v0, 0x34($a3)
	lh	$t4, 0($a3)
	lh	$t5, 0x2($a3)
	lh	$t6, 0x4($a3)
	lh	$t7, 0x48($a3)
	lh	$t8, 0x4A($a3)
	lh	$t9, 0x4C($a3)
	add	$v0, $t4, $t7
	sra	$v0, $v0, 1
	sh	$v0, 0x60($a3)
	add	$v0, $t5, $t8
	sra	$v0, $v0, 1
	sh	$v0, 0x62($a3)
	add	$v0, $t6, $t9
	sra	$v0, $v0, 1
	sh	$v0, 0x64($a3)
	swc2	$12, 0x10($a3)
	swc2	$13, 0x28($a3)
	swc2	$17, 0x14($a3)
	swc2	$18, 0x2C($a3)
	lwc2	$0, 0x30($a3)
	lwc2	$1, 0x34($a3)
	lwc2	$2, 0x48($a3)
	lwc2	$3, 0x4C($a3)
	lwc2	$4, 0x60($a3)
	lwc2	$5, 0x64($a3)
	nop
	RTPT
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
	swc2	$14, 0x70($a3)
	jal	func_00000490
	nop
	lw	$t0, 0x7C($a3)
	addiu	$t1, $a3, 0x30
	addiu	$t2, $a3, 0
	addiu	$t3, $a3, 0x60
	jal	func_00000490
	nop
	lw	$t0, 0x80($a3)
	addiu	$t1, $a3, 0x18
	addiu	$t2, $a3, 0x48
	addiu	$t3, $a3, 0x60
	jal	func_00000490
	nop
	lw	$t0, 0x84($a3)
	addiu	$t1, $a3, 0x48
	addiu	$t2, $a3, 0x30
	addiu	$t3, $a3, 0x60
	jal	func_00000490
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
	swc2	$14, -0x1C($a3)
	swc2	$17, -0x48($a3)
	swc2	$18, -0x30($a3)
	swc2	$19, -0x18($a3)
	jal	RCpolyF4A
	nop
	lw	$t4, -0x10($a3)
	addiu	$t5, $a3, -0x5C
	addiu	$t6, $a3, -0x8C
	addiu	$t7, $a3, -0x2C
	sw	$t4, 0x78($a3)
	sw	$t5, 0x7C($a3)
	sw	$t6, 0x80($a3)
	sw	$t7, 0x84($a3)
	jal	RCpolyF4A
	nop
func_00000428:
	lw	$t4, -0xC($a3)
	addiu	$t5, $a3, -0x74
	addiu	$t6, $a3, -0x44
	addiu	$t7, $a3, -0x2C
	sw	$t4, 0x78($a3)
	sw	$t5, 0x7C($a3)
	sw	$t6, 0x80($a3)
	sw	$t7, 0x84($a3)
	jal	RCpolyF4A
	nop
	lw	$t4, -0x8($a3)
	addiu	$t5, $a3, -0x44
	addiu	$t6, $a3, -0x5C
	addiu	$t7, $a3, -0x2C
	sw	$t4, 0x78($a3)
	sw	$t5, 0x7C($a3)
	sw	$t6, 0x80($a3)
	sw	$t7, 0x84($a3)
	jal	RCpolyF4A
	nop
	lw	$ra, 0x88($a3)
	addiu	$a3, $a3, -0x8C
	addiu	$a2, $a2, -0x1
.L7:
	move	$v0, $a0
	jr	$ra
	nop
	.set	at
	.end	RCpolyF4A

	.ent	func_00000490
func_00000490:
	lw	$t8, 0x10($a1)
	lw	$t4, 0x10($t0)
	lw	$t5, 0x10($t1)
	lw	$t6, 0x10($t2)
	lw	$t7, 0x10($t3)
	sw	$t8, 0x4($a0)
	sw	$t4, 0x8($a0)
	sw	$t5, 0xC($a0)
	sw	$t6, 0x10($a0)
	sw	$t7, 0x14($a0)
	lw	$t4, 0x14($a1)
	sll	$t9, $a0, 8
	srl	$t9, $t9, 8
	lw	$t8, 0($t4)
	sw	$t9, 0($t4)
	li	$t6, 0x5000000
	or	$t8, $t8, $t6
	sw	$t8, 0($a0)
	addiu	$a0, $a0, 0x18
	jr	$ra
	nop
	nop
	.end	func_00000490
	.set	reorder
