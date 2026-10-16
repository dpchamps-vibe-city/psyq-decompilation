/* LIBGTE.LIB, member G4S_2.OBJ (hand-written assembly)
 *
 * GsTMDfastG4NLD: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastG4NLD
	.ent	GsTMDfastG4NLD
GsTMDfastG4NLD:
	lw	$t8, 0x10($sp)
	lw	$t9, 0x18($sp)
	lw	$t7, 0x14($sp)
	sw	$s0, 0x10($sp)
	beqz	$t8, .L4
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
	lhu	$t2, 0xA($a0)
	lhu	$t3, 0xE($a0)
	lhu	$t4, 0x12($a0)
	sll	$t2, $t2, 3
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
	lw	$t3, GsTON
	lw	$t2, 0x4($a0)
	sll	$t3, $t3, 25
	or	$t2, $t2, $t3
	mtc2	$t2, $20
	lhu	$t5, 0x16($a0)
	addiu	$a0, $a0, 0x18
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lhu	$t2, 0xA($a0)
	lhu	$t3, 0xE($a0)
	lhu	$t4, 0x12($a0)
	sll	$t2, $t2, 3
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
	swc2	$12, 0x8($a3)
	swc2	$13, 0x10($a3)
	swc2	$14, 0x18($a3)
	nop
	RTPS
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
	mfc2	$t6, $7
	nop
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
	sw	$v0, 0($a3)
	xor	$v0, $a3, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	swc2	$20, 0x4($a3)
	swc2	$20, 0xC($a3)
	swc2	$20, 0x14($a3)
	swc2	$20, 0x1C($a3)
	swc2	$14, 0x20($a3)
	addiu	$a3, $a3, 0x24
.L3:
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L4:
	lw	$s0, 0x10($sp)
	move	$v0, $a3
	jr	$ra
	nop
	nop
	nop
	.end	GsTMDfastG4NLD
	.set	reorder
