/* LIBGTE.LIB, member PRS_F3_2.OBJ (hand-written assembly)
 *
 * PACKET *GsPrstF3NL();
 *   (declared without parameters in libgs.h)
 *
 * Register use:
 *   v0  result (PACKET *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsPrstF3NL
	.ent	GsPrstF3NL
GsPrstF3NL:
	lw	$t8, 0x10($sp)
	lw	$t9, 0x18($sp)
	lw	$t7, 0x14($sp)
	beqz	$t8, .L3
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
	lw	$t3, 0xC($a0)
	lhu	$t2, 0xA($a0)
	srl	$t4, $t3, 16
	sll	$t3, $t3, 16
	srl	$t3, $t3, 13
	sll	$t2, $t2, 3
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
	addiu	$a0, $a0, 0x10
	lw	$t3, 0xC($a0)
	lhu	$t2, 0xA($a0)
	srl	$t4, $t3, 16
	sll	$t3, $t3, 16
	srl	$t3, $t3, 13
	sll	$t2, $t2, 3
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
	blez	$v0, .L2
	nop
	AVSZ3
	mfc2	$t6, $7
	nop
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t5, 0($t6)
	li	$v0, 0x4000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($a3)
	xor	$v0, $a3, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	swc2	$12, 0x8($a3)
	swc2	$13, 0xC($a3)
	swc2	$14, 0x10($a3)
.L2:
	addiu	$a3, $a3, 0x28
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L3:
	move	$v0, $a0
	jr	$ra
	nop
	nop
	nop
	nop
	.end	GsPrstF3NL
	.set	reorder
