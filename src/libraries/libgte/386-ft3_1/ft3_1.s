/* LIBGTE.LIB, member FT3_1.OBJ (hand-written assembly)
 *
 * PACKET *GsTMDfastTNF3();
 *   (declared without parameters in libgs.h)
 *
 * Register use:
 *   v0  result (PACKET *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastTNF3
	.ent	GsTMDfastTNF3
GsTMDfastTNF3:
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
	lw	$v0, 0x10($a0)
	lw	$t3, GsTON
	lb	$t2, 0x3($a0)
	sll	$t3, $t3, 1
	or	$t2, $t2, $t3
	sll	$v0, $v0, 8
	srl	$v0, $v0, 8
	srl	$t2, $t2, 1
	sll	$t2, $t2, 25
	or	$t2, $t2, $v0
	mtc2	$t2, $22
	lw	$t2, 0x4($a0)
	lw	$t3, 0x8($a0)
	lw	$t4, 0xC($a0)
	sw	$t2, 0xC($a2)
	sw	$t3, 0x14($a2)
	sw	$t4, 0x1C($a2)
	addiu	$a0, $a0, 0x1C
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
	li	$v0, 0x7000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($a2)
	xor	$v0, $a2, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	swc2	$22, 0x4($a2)
	swc2	$12, 0x8($a2)
	swc2	$13, 0x10($a2)
	swc2	$14, 0x18($a2)
	addiu	$a2, $a2, 0x20
.L2:
	addiu	$a3, $a3, -0x1
	bnez	$a3, .L1
	nop
.L3:
	move	$v0, $a2
	jr	$ra
	nop
	nop
	.end	GsTMDfastTNF3
	.set	reorder
