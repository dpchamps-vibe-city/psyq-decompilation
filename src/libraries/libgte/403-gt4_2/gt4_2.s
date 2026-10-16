/* LIBGTE.LIB, member GT4_2.OBJ (hand-written assembly)
 *
 * PACKET *GsTMDfastTG4NL();
 *   (declared without parameters in libgs.h)
 *
 * Register use:
 *   v0  result (PACKET *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastTG4NL
	.ent	GsTMDfastTG4NL
GsTMDfastTG4NL:
	lw	$t8, 0x10($sp)
	lw	$t9, 0x18($sp)
	lw	$t7, 0x14($sp)
	beqz	$t8, .L3
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
	lhu	$t2, 0x16($a0)
	lhu	$t3, 0x1A($a0)
	lhu	$t4, 0x1E($a0)
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
	lhu	$t5, 0x22($a0)
	move	$v1, $a0
	addiu	$a0, $a0, 0x24
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lhu	$t2, 0x16($a0)
	lhu	$t3, 0x1A($a0)
	lhu	$t4, 0x1E($a0)
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
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
	mfc2	$v0, $24
	nop
	blez	$v0, .L2
	nop
	swc2	$12, 0x8($a3)
	swc2	$13, 0x10($a3)
	swc2	$14, 0x18($a3)
	nop
	RTPS
	lb	$t5, 0x3($v1)
	lw	$t6, GsTON
	andi	$t5, $t5, 0x2
	sll	$t6, $t6, 1
	or	$t5, $t6, $t5
	sll	$t5, $t5, 24
	li	$t6, 0x2d808080
	or	$t6, $t5, $t6
	sw	$t6, 0x4($a3)
	lw	$t5, 0x4($v1)
	lw	$t6, 0x8($v1)
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	AVSZ4
	lw	$v0, 0xC($v1)
	sw	$t5, 0xC($a3)
	sw	$t6, 0x14($a3)
	sw	$v0, 0x1C($a3)
	lw	$t5, 0x10($v1)
	mfc2	$t6, $7
	sw	$t5, 0x24($a3)
	swc2	$14, 0x20($a3)
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t5, 0($t6)
	li	$v0, 0x9000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($a3)
	xor	$v0, $a3, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	addiu	$a3, $a3, 0x28
.L2:
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L3:
	move	$v0, $a3
	jr	$ra
	nop
	nop
	nop
	.end	GsTMDfastTG4NL
	.set	reorder
