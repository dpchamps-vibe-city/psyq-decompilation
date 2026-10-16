/* LIBGTE.LIB, member GT3F_2.OBJ (hand-written assembly)
 *
 * GsTMDfastTG3NL_FLIP: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastTG3NL_FLIP
	.ent	GsTMDfastTG3NL_FLIP
GsTMDfastTG3NL_FLIP:
	lw	$t8, 0x10($sp)
	lw	$t9, 0x18($sp)
	lw	$t7, 0x14($sp)
	beqz	$t8, .L3
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
	lhu	$t2, 0x12($a0)
	lhu	$t3, 0x16($a0)
	lhu	$t4, 0x1A($a0)
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
	lwc2	$20, 0x4($a0)
	lwc2	$21, 0x8($a0)
	lwc2	$22, 0xC($a0)
	lb	$t2, 0x3($a0)
	lw	$t3, GsTON
	andi	$t2, $t2, 0x2
	sll	$t3, $t3, 1
	or	$t2, $t3, $t2
	sll	$t2, $t2, 24
	li	$v1, 0x25808080
	or	$v1, $v1, $t2
	sw	$v1, 0x4($a3)
	addiu	$a0, $a0, 0x1C
	lhu	$t2, 0x12($a0)
	lhu	$t3, 0x16($a0)
	lhu	$t4, 0x1A($a0)
	sll	$t2, $t2, 3
	sll	$t3, $t3, 3
	sll	$t4, $t4, 3
	addu	$t2, $t2, $a1
	addu	$t3, $t3, $a1
	addu	$t4, $t4, $a1
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	NCLIP
	mfc2	$v0, $24
	nop
	bgez	$v0, .L2
	nop
	AVSZ3
	mfc2	$t6, $7
	swc2	$20, 0xC($a3)
	swc2	$21, 0x14($a3)
	swc2	$22, 0x1C($a3)
	swc2	$12, 0x8($a3)
	swc2	$13, 0x10($a3)
	swc2	$14, 0x18($a3)
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t5, 0($t6)
	li	$v0, 0x7000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($a3)
	xor	$v0, $a3, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	addiu	$a3, $a3, 0x20
.L2:
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L3:
	move	$v0, $a3
	jr	$ra
	nop
	nop
	.end	GsTMDfastTG3NL_FLIP
	.set	reorder
