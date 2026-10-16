/* LIBHMD.LIB, member 00040051.OBJ (hand-written assembly)
 *
 * u_long *GsU_00040051(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x00040051 (GsUNFT4): nonLight texture flat quad.
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_00040051
	.ent	GsU_00040051
GsU_00040051:
	lw	$a3, 0($a0)
	lw	$t9, 0x4($a0)
	lw	$t8, 0($a3)
	lw	$t7, 0x8($a0)
	addiu	$a3, $a3, 0x4
	lw	$a2, 0($a3)
	lw	$a1, 0x14($a0)
	sll	$a2, $a2, 2
	srl	$t8, $t8, 16
	beqz	$t8, .L3
	addu	$a3, $a1, $a2
	lw	$t0, 0x4($t9)
	lw	$t1, 0xC($a0)
	lw	$a1, 0x18($a0)
	addiu	$v0, $a0, 0x10
	lw	$t9, 0($v0)
	lhu	$t2, 0xE($a3)
	lhu	$t3, 0x12($a3)
	lhu	$t4, 0x14($a3)
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
	nop
	RTPT
	lw	$v0, 0($a3)
	lhu	$v1, 0x16($a3)
	sw	$v0, 0x4($t9)
	sll	$v1, $v1, 3
	addu	$v1, $v1, $a1
	addiu	$a3, $a3, 0x18
	lhu	$t2, 0xE($a3)
	lhu	$t3, 0x12($a3)
	lhu	$t4, 0x14($a3)
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
	lwc2	$0, 0($v1)
	lwc2	$1, 0x4($v1)
	mfc2	$v0, $24
	nop
	blez	$v0, .L2
	nop
	swc2	$12, 0x8($t9)
	swc2	$13, 0x10($t9)
	swc2	$14, 0x18($t9)
	nop
	nop
	RTPS
	addiu	$v0, $a3, -0x18
	lw	$v1, 0x4($v0)
	lw	$t6, 0x8($v0)
	sw	$v1, 0xC($t9)
	sw	$t6, 0x14($t9)
	lw	$v1, 0xC($v0)
	lw	$t6, 0x10($v0)
	sw	$v1, 0x1C($t9)
	sw	$t6, 0x24($t9)
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	AVSZ4
	mfc2	$t6, $7
	nop
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
	sw	$v0, 0($t9)
	xor	$v0, $t9, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	swc2	$14, 0x20($t9)
	addiu	$t9, $t9, 0x28
.L2:
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L3:
	lw	$v0, 0($a0)
	sw	$t9, GsOUT_PACKET_P
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	nop
	nop
	nop
	.end	GsU_00040051
	.set	reorder
