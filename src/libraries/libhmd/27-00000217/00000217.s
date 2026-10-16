/* LIBHMD.LIB, member 00000217.OBJ (hand-written assembly)
 *
 * u_long *GsU_00000217(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x00000217: unit type not described in libhmd.h (no define in libhmd.h; read from the flag bits).
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_00000217
	.ent	GsU_00000217
GsU_00000217:
	.set	noat
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
	addiu	$v0, $a0, 0x10
	lw	$t9, 0($v0)
	lw	$a1, 0x18($a0)
	lw	$a2, 0x1C($a0)
.L1:
	lw	$t2, 0x20($a3)
	lw	$t3, 0x24($a3)
	lw	$t4, 0x28($a3)
	lw	$v1, 0x2C($a3)
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
	lw	$t2, 0x1C($a3)
	nop
	srl	$t2, $t2, 16
	RTPT
	sll	$t2, $t2, 3
	addu	$t2, $t2, $a2
	sll	$t3, $t3, 16
	srl	$t3, $t3, 13
	addu	$t3, $t3, $a2
	sll	$t4, $t4, 16
	srl	$t4, $t4, 13
	addu	$t4, $t4, $a2
	srl	$t5, $v1, 16
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
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
	swc2	$12, 0xC($t9)
	swc2	$13, 0x18($t9)
	swc2	$14, 0x24($t9)
	nop
	nop
	RTPS
	lw	$t5, 0x4($a3)
	nop
	mtc2	$t5, $6
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	AVSZ4
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	sll	$t2, $v1, 16
	srl	$t2, $t2, 13
	addu	$t2, $t2, $a2
	mfc2	$t6, $7
	nop
	nop
	NCCS
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t5, 0($t6)
	li	$v0, 0xe000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($t9)
	li	$at, 0xe2000000
	xor	$v0, $t9, $t5
	sw	$at, 0x38($t9)
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	lwc2	$0, 0($t3)
	lwc2	$1, 0x4($t3)
	lw	$t5, 0x8($a3)
	swc2	$22, 0x8($t9)
	mtc2	$t5, $6
	nop
	nop
	NCCS
	lw	$t5, 0xC($a3)
	lwc2	$0, 0($t4)
	lwc2	$1, 0x4($t4)
	swc2	$22, 0x14($t9)
	mtc2	$t5, $6
	nop
	nop
	NCCS
	lw	$t5, 0x10($a3)
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	swc2	$22, 0x20($t9)
	mtc2	$t5, $6
	nop
	nop
	NCCS
	lw	$t2, 0x14($a3)
	lw	$t3, 0x18($a3)
	lw	$t4, 0x1C($a3)
	lw	$v1, 0x20($a3)
	sw	$t2, 0x10($t9)
	sw	$t3, 0x1C($t9)
	sw	$t4, 0x28($t9)
	sw	$v1, 0x34($t9)
	lw	$t2, 0($a3)
	swc2	$14, 0x30($t9)
	swc2	$22, 0x2C($t9)
	sw	$t2, 0x4($t9)
	addiu	$t9, $t9, 0x3C
.L2:
	addiu	$a3, $a3, 0x30
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L3:
	lw	$v0, 0($a0)
	lui	$at, %hi(GsOUT_PACKET_P)
	sw	$t9, %lo(GsOUT_PACKET_P)($at)
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	nop
	nop
	.set	at
	.end	GsU_00000217
	.set	reorder
