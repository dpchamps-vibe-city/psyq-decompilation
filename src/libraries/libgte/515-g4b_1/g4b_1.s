/* LIBGTE.LIB, member G4B_1.OBJ (hand-written assembly)
 *
 * GsTMDfastNG4B: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastNG4B
	.ent	GsTMDfastNG4B
GsTMDfastNG4B:
	lw	$t9, 0x14($sp)
	lw	$t7, 0x10($sp)
	beqz	$a3, .L3
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
	lw	$t2, 0x14($a0)
	lhu	$t4, 0x18($a0)
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
	lhu	$t5, 0x1A($a0)
	move	$v1, $a0
	addiu	$a0, $a0, 0x1C
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lw	$t2, 0x14($a0)
	lhu	$t4, 0x18($a0)
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
	bltz	$v0, .L2
	nop
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
	swc2	$12, 0x8($a2)
	swc2	$13, 0x10($a2)
	swc2	$14, 0x18($a2)
	nop
	RTPS
	lw	$t6, GsTON
	lw	$t5, 0x4($v1)
	sll	$t6, $t6, 25
	or	$t5, $t5, $t6
	lw	$t6, 0x8($v1)
	lw	$v0, 0xC($v1)
	sw	$t5, 0x4($a2)
	sw	$t6, 0xC($a2)
	sw	$v0, 0x14($a2)
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	AVSZ4
	lw	$t5, 0x10($v1)
	mfc2	$t6, $7
	sw	$t5, 0x1C($a2)
	swc2	$14, 0x20($a2)
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t5, 0($t6)
	li	$v0, 0x8000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($a2)
	xor	$v0, $a2, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	addiu	$a2, $a2, 0x24
.L2:
	addiu	$a3, $a3, -0x1
	bnez	$a3, .L1
	nop
.L3:
	move	$v0, $a2
	jr	$ra
	nop
	nop
	.end	GsTMDfastNG4B
	.set	reorder
