/* LIBGTE.LIB, member GT4S_1.OBJ (hand-written assembly)
 *
 * GsTMDfastTNG4D: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastTNG4D
	.ent	GsTMDfastTNG4D
GsTMDfastTNG4D:
	lw	$t7, 0x10($sp)
	lw	$t9, 0x14($sp)
	sw	$s0, 0x10($sp)
	beqz	$a3, .L4
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
	lw	$t2, 0x24($a0)
	lhu	$t4, 0x28($a0)
	srl	$t3, $t2, 16
	sll	$t2, $t2, 16
	srl	$t2, $t2, 13
	sll	$t3, $t3, 3
	sll	$t4, $t4, 3
	addu	$t2, $t2, $a1
	addu	$t3, $t3, $a1
	addu	$t4, $t4, $a1
.L1:
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	lwc2	$2, 0($t3)
	lwc2	$3, 0x4($t3)
	lwc2	$4, 0($t4)
	lwc2	$5, 0x4($t4)
	nop
	RTPT
	lw	$v1, GsTON
	lb	$v0, 0x3($a0)
	sll	$v1, $v1, 1
	or	$v0, $v0, $v1
	lw	$v1, 0x14($a0)
	srl	$v0, $v0, 1
	sll	$v0, $v0, 25
	sll	$v1, $v1, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	mtc2	$v0, $20
	lwc2	$21, 0x18($a0)
	lwc2	$22, 0x1C($a0)
	lwc2	$6, 0x20($a0)
	lhu	$t5, 0x2A($a0)
	move	$v1, $a0
	addiu	$a0, $a0, 0x2C
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lw	$t2, 0x24($a0)
	lhu	$t4, 0x28($a0)
	srl	$t3, $t2, 16
	sll	$t2, $t2, 16
	srl	$t2, $t2, 13
	sll	$t3, $t3, 3
	sll	$t4, $t4, 3
	addu	$t2, $t2, $a1
	addu	$t3, $t3, $a1
	addu	$t4, $t4, $a1
	cfc2	$v0, $31
	nop
	bltz	$v0, .L3
	nop
	NCLIP
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
	mfc2	$s0, $24
	swc2	$12, 0x8($a2)
	swc2	$13, 0x14($a2)
	swc2	$14, 0x20($a2)
	nop
	RTPS
	lw	$t5, 0x4($v1)
	lw	$t6, 0x8($v1)
	cfc2	$v0, $31
	NCLIP
	bltz	$v0, .L3
	nop
	bgtz	$s0, .L2
	nop
	mfc2	$v0, $24
	nop
	bgez	$v0, .L3
	nop
.L2:
	AVSZ4
	lw	$v0, 0xC($v1)
	sw	$t5, 0xC($a2)
	sw	$t6, 0x18($a2)
	sw	$v0, 0x24($a2)
	lw	$t5, 0x10($v1)
	mfc2	$t6, $7
	sw	$t5, 0x30($a2)
	swc2	$14, 0x2C($a2)
	swc2	$20, 0x4($a2)
	swc2	$21, 0x10($a2)
	swc2	$22, 0x1C($a2)
	swc2	$6, 0x28($a2)
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t5, 0($t6)
	li	$v0, 0xc000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($a2)
	xor	$v0, $a2, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	addiu	$a2, $a2, 0x34
.L3:
	addiu	$a3, $a3, -0x1
	bnez	$a3, .L1
	nop
.L4:
	lw	$s0, 0x10($sp)
	move	$v0, $a2
	jr	$ra
	nop
	.end	GsTMDfastTNG4D
	.set	reorder
