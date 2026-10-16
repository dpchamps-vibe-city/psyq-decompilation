/* LIBHMD.LIB, member 00040151.OBJ (hand-written assembly)
 *
 * u_long *GsU_00040151(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x00040151 (GsUPNFT4): preset nonLight texture flat quad.
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_00040151
	.ent	GsU_00040151
GsU_00040151:
	lw	$a3, 0($a0)
	lw	$t9, 0x4($a0)
	lw	$t8, 0($a3)
	lw	$t7, 0x8($a0)
	lhu	$v1, PSDIDX
	addiu	$a3, $a3, 0x4
	lw	$a2, 0($a3)
	lw	$a1, 0x14($a0)
	sll	$a2, $a2, 2
	srl	$t8, $t8, 16
	beqz	$v1, .L1
	nop
	li	$v1, 0x28
.L1:
	beqz	$t8, .L4
	addu	$a3, $a1, $a2
	lw	$t0, 0x4($t9)
	lw	$t1, 0xC($a0)
	addu	$t9, $a3, $v1
	lw	$a1, 0x18($a0)
	lw	$a2, 0x1C($a0)
	lw	$t2, 0x50($a3)
	lhu	$t4, 0x54($a3)
	srl	$t3, $t2, 16
	sll	$t2, $t2, 16
	srl	$t2, $t2, 13
	sll	$t3, $t3, 3
	sll	$t4, $t4, 3
	addu	$t2, $t2, $a1
	addu	$t3, $t3, $a1
	addu	$t4, $t4, $a1
.L2:
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	lwc2	$2, 0($t3)
	lwc2	$3, 0x4($t3)
	lwc2	$4, 0($t4)
	lwc2	$5, 0x4($t4)
	nop
	nop
	RTPT
	lhu	$v1, 0x56($a3)
	nop
	sll	$v1, $v1, 3
	addu	$v1, $v1, $a1
	addiu	$a3, $a3, 0x58
	lw	$t2, 0x50($a3)
	lhu	$t4, 0x54($a3)
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
	lwc2	$0, 0($v1)
	lwc2	$1, 0x4($v1)
	mfc2	$v0, $24
	nop
	blez	$v0, .L3
	nop
	swc2	$12, 0x8($t9)
	swc2	$13, 0x10($t9)
	swc2	$14, 0x18($t9)
	nop
	nop
	RTPS
	cfc2	$v0, $31
	nop
	bltz	$v0, .L3
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
.L3:
	addiu	$t9, $t9, 0x58
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L2
	nop
.L4:
	lw	$v0, 0($a0)
	nop
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	nop
	nop
	nop
	.end	GsU_00040151
	.set	reorder
