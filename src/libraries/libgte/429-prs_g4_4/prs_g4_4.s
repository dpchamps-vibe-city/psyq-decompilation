/* LIBGTE.LIB, member PRS_G4_4.OBJ (hand-written assembly)
 *
 * PACKET *GsPrstG4LFG();
 *   (declared without parameters in libgs.h)
 *
 * Register use:
 *   v0  result (PACKET *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsPrstG4LFG
	.ent	GsPrstG4LFG
GsPrstG4LFG:
	lw	$t8, 0x10($sp)
	lw	$t9, 0x18($sp)
	lw	$t7, 0x14($sp)
	beqz	$t8, .L4
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
.L1:
	lw	$t2, 0x8($a0)
	lw	$t3, 0xC($a0)
	lw	$t4, 0x10($a0)
.L2:
	srl	$t5, $t2, 16
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
	srl	$t5, $t3, 16
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lwc2	$2, 0($t5)
	lwc2	$3, 0x4($t5)
	srl	$t5, $t4, 16
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lwc2	$4, 0($t5)
	lwc2	$5, 0x4($t5)
	nop
	RTPT
	lw	$t5, 0x14($a0)
	sll	$t2, $t2, 16
	srl	$t2, $t2, 13
	addu	$t2, $t2, $a2
	sll	$t3, $t3, 16
	srl	$t3, $t3, 13
	addu	$t3, $t3, $a2
	sll	$t4, $t4, 16
	srl	$t4, $t4, 13
	addu	$t4, $t4, $a2
	srl	$v1, $t5, 16
	sll	$v1, $v1, 3
	addu	$v1, $v1, $a1
	sll	$t5, $t5, 16
	srl	$t5, $t5, 13
	addu	$t5, $t5, $a2
	cfc2	$v0, $31
	nop
	bltz	$v0, .L3
	nop
	NCLIP
	lwc2	$0, 0($v1)
	lwc2	$1, 0x4($v1)
	mfc2	$v1, $24
	nop
	blez	$v1, .L3
	nop
	swc2	$12, 0x8($a3)
	swc2	$13, 0x10($a3)
	swc2	$14, 0x18($a3)
	nop
	RTPS
	lwc2	$2, 0($t3)
	lwc2	$3, 0x4($t3)
	lwc2	$4, 0($t4)
	lwc2	$5, 0x4($t4)
	cfc2	$v0, $31
	bltz	$v0, .L3
	nop
	AVSZ4
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
	lwc2	$6, 0x4($a0)
	mfc2	$t6, $7
	nop
	NCDS
	swc2	$22, 0x1C($a3)
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	NCDT
	addiu	$a0, $a0, 0x18
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
	lw	$t2, 0x8($a0)
	lw	$t3, 0xC($a0)
	lw	$t4, 0x10($a0)
	nop
	swc2	$14, 0x20($a3)
	swc2	$20, 0x4($a3)
	swc2	$21, 0xC($a3)
	swc2	$22, 0x14($a3)
	addiu	$a3, $a3, 0x48
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L2
	nop
	b	.L4
	nop
.L3:
	addiu	$a0, $a0, 0x18
	addiu	$a3, $a3, 0x48
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L4:
	move	$v0, $a0
	jr	$ra
	nop
	nop
	.end	GsPrstG4LFG
	.set	reorder
