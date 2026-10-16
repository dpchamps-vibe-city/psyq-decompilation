/* LIBHMD.LIB, member 01140255.OBJ (hand-written assembly)
 *
 * u_long *GsU_01140255(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x01140255: unit type not described in libhmd.h (no define in libhmd.h; read from the flag bits).
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_01140255
	.ent	GsU_01140255
GsU_01140255:
	.set	noat
	lw	$t0, 0($a0)
	lw	$t1, 0x10($a0)
	lhu	$t2, 0x2($t0)
	lw	$t3, 0x4($t0)
	lw	$t4, 0x14($a0)
	sll	$t3, $t3, 2
	beqz	$t2, .L3
	addu	$t7, $t4, $t3
	lw	$t6, 0x4($a0)
	lw	$t8, 0xC($a0)
	lw	$t9, 0x4($t6)
	lw	$t5, 0x1C($a0)
.L1:
	lw	$a1, 0x1C($t7)
	lw	$a2, 0x20($t7)
	lw	$t6, 0x24($t7)
	srl	$v0, $a1, 16
	sll	$v0, $v0, 3
	addu	$t3, $v0, $t5
	lw	$v0, 0x4($t3)
	li	$t0, -0x1
	beq	$v0, $t0, .L2
	nop
	mtc2	$v0, $16
	nop
	srl	$v0, $a2, 16
	sll	$v0, $v0, 3
	addu	$t4, $v0, $t5
	lw	$v0, 0x4($t4)
	nop
	beq	$v0, $t0, .L2
	nop
	mtc2	$v0, $17
	nop
	sll	$v0, $t6, 16
	srl	$v0, $v0, 13
	addu	$v1, $v0, $t5
	lw	$v0, 0x4($v1)
	nop
	beq	$v0, $t0, .L2
	nop
	mtc2	$v0, $18
	nop
	srl	$v0, $t6, 16
	sll	$v0, $v0, 3
	addu	$a3, $v0, $t5
	lw	$v0, 0x4($a3)
	nop
	beq	$v0, $t0, .L2
	nop
	mtc2	$v0, $19
	nop
	lw	$v0, 0($t3)
	lw	$t0, 0($t4)
	lw	$t3, 0($v1)
	mtc2	$v0, $12
	mtc2	$t0, $13
	mtc2	$t3, $14
	lw	$t4, 0($a3)
	nop
	sw	$v0, 0xC($t1)
	sw	$t0, 0x18($t1)
	sw	$t3, 0x24($t1)
	sw	$t4, 0x30($t1)
	AVSZ4
	lw	$v0, 0x4($t7)
	lw	$v1, 0x8($t7)
	lw	$t4, 0xC($t7)
	lw	$t6, 0x10($t7)
	lw	$t0, 0x14($t7)
	lw	$t3, 0x18($t7)
	sw	$v0, 0x8($t1)
	sw	$v1, 0x14($t1)
	sw	$t4, 0x20($t1)
	sw	$t6, 0x2C($t1)
	sw	$t0, 0x10($t1)
	sw	$t3, 0x1C($t1)
	sw	$a1, 0x28($t1)
	sw	$a2, 0x34($t1)
	lw	$v0, 0($t7)
	mfc2	$t4, $7
	lw	$t6, 0x8($a0)
	sw	$v0, 0x4($t1)
	subu	$t4, $t4, $t8
	srlv	$t4, $t4, $t6
	andi	$t4, $t4, 0xFFFF
	sll	$t4, $t4, 2
	addu	$t4, $t4, $t9
	lw	$v0, 0($t4)
	li	$v1, 0xe000000
	sll	$t3, $v0, 8
	srl	$t3, $t3, 8
	or	$v1, $v1, $t3
	sw	$v1, 0($t1)
	li	$at, 0xe2000000
	xor	$v1, $t1, $v0
	sw	$at, 0x38($t1)
	sll	$t3, $v1, 8
	srl	$v1, $t3, 8
	xor	$t3, $v1, $v0
	sw	$t3, 0($t4)
	addiu	$t1, $t1, 0x3C
.L2:
	addiu	$t2, $t2, -0x1
	bnez	$t2, .L1
	addiu	$t7, $t7, 0x28
.L3:
	lw	$v0, 0($a0)
	lui	$at, %hi(GsOUT_PACKET_P)
	sw	$t1, %lo(GsOUT_PACKET_P)($at)
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	nop
	nop
	.set	at
	.end	GsU_01140255
	.set	reorder
