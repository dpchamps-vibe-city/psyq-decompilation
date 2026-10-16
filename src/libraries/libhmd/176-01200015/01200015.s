/* LIBHMD.LIB, member 01200015.OBJ (hand-written assembly)
 *
 * u_long *GsU_01200015(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x01200015 (GsUSTPSGT4): semi-trans shared texture gouraud quad.
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_01200015
	.ent	GsU_01200015
GsU_01200015:
	.set	noat
	sw	$s0, 0x18($a0)
	sw	$s1, 0x20($a0)
	lw	$t0, 0($a0)
	lw	$t1, 0x10($a0)
	lhu	$t2, 0x2($t0)
	lw	$t3, 0x4($t0)
	lw	$t4, 0x14($a0)
	lw	$t5, 0x1C($a0)
	lw	$t6, 0x24($a0)
	sll	$t3, $t3, 2
	beqz	$t2, .L22
	addu	$t7, $t4, $t3
	sw	$s2, 0x10($a0)
.L1:
	lw	$a1, 0xC($t7)
	lw	$a2, 0x10($t7)
	lw	$a3, 0x14($t7)
	lw	$t9, 0x18($t7)
	srl	$v0, $a1, 16
	sll	$v0, $v0, 3
	addu	$t3, $v0, $t5
	lw	$v0, 0x4($t3)
	li	$t0, -0x1
	beq	$v0, $t0, .L21
	nop
	mtc2	$v0, $16
	nop
	srl	$v0, $a2, 16
	sll	$v0, $v0, 3
	addu	$t4, $v0, $t5
	lw	$v0, 0x4($t4)
	nop
	beq	$v0, $t0, .L21
	nop
	mtc2	$v0, $17
	nop
	srl	$v0, $a3, 16
	sll	$v0, $v0, 3
	addu	$v1, $v0, $t5
	lw	$v0, 0x4($v1)
	nop
	beq	$v0, $t0, .L21
	nop
	mtc2	$v0, $18
	nop
	srl	$v0, $t9, 16
	sll	$v0, $v0, 3
	addu	$s0, $v0, $t5
	lw	$v0, 0x4($s0)
	nop
	beq	$v0, $t0, .L21
	nop
	mtc2	$v0, $19
	nop
	lw	$v0, 0($t3)
	lw	$t0, 0($t4)
	lw	$t3, 0($v1)
	mtc2	$v0, $12
	mtc2	$t0, $13
	mtc2	$t3, $14
	lw	$t4, 0($s0)
	lw	$s2, 0x8($t7)
	NCLIP
	sw	$v0, 0x8($t1)
	sw	$t0, 0x14($t1)
	sw	$t3, 0x20($t1)
	sw	$t4, 0x2C($t1)
	mfc2	$v0, $24
	li	$s1, 0x3e000000
	bgtz	$v0, .L10
	nop
	mtc2	$t4, $12
	nop
	nop
	NCLIP
	sw	$t4, 0x8($t1)
	mfc2	$v0, $24
	li	$s1, 0x36000000
	bgtz	$v0, .L21
	nop
	sll	$v0, $t9, 16
	j	.L4
	li	$t4, 0
.L2:
	sll	$v0, $a2, 16
	j	.L4
	li	$t4, 0x1
.L3:
	sll	$v0, $a3, 16
	li	$t4, 0x2
.L4:
	srl	$v0, $v0, 13
	addu	$t0, $v0, $t6
	lw	$v0, 0($t0)
	lw	$v1, 0x4($t0)
	sll	$t3, $v0, 16
	srl	$t3, $t3, 21
	srl	$v0, $v0, 21
	srl	$v1, $v1, 5
	slti	$at, $t3, 0xFF
	bnez	$at, .L5
	nop
	li	$t3, 0xFF
.L5:
	slti	$at, $v0, 0xFF
	bnez	$at, .L6
	nop
	li	$v0, 0xFF
.L6:
	slti	$at, $v1, 0xFF
	bnez	$at, .L7
	nop
	li	$v1, 0xFF
.L7:
	sll	$v0, $v0, 8
	sll	$v1, $v1, 16
	or	$t0, $t3, $v0
	or	$t0, $t0, $v1
	li	$at, 0x2
	beq	$t4, $at, .L9
	nop
	li	$at, 0x1
	beq	$t4, $at, .L8
	nop
	or	$t0, $t0, $s1
	j	.L2
	sw	$t0, 0x4($t1)
.L8:
	j	.L3
	sw	$t0, 0x10($t1)
.L9:
	sw	$t0, 0x1C($t1)
	AVSZ3
	lw	$t0, 0($t7)
	lw	$a2, 0x4($t7)
	li	$at, 0xffff0000
	and	$t0, $t0, $at
	andi	$a1, $a1, 0xFFFF
	or	$a1, $a1, $t0
	sw	$a1, 0xC($t1)
	sw	$a2, 0x18($t1)
	sw	$s2, 0x24($t1)
	lw	$t0, 0x4($a0)
	lw	$a1, 0xC($a0)
	lw	$a2, 0x8($a0)
	lw	$a3, 0x4($t0)
	mfc2	$t4, $7
	nop
	subu	$t4, $t4, $a1
	srlv	$t4, $t4, $a2
	andi	$t4, $t4, 0xFFFF
	sll	$t4, $t4, 2
	addu	$t4, $t4, $a3
	lw	$v0, 0($t4)
	li	$v1, 0x9000000
	sll	$t3, $v0, 8
	srl	$t3, $t3, 8
	or	$v1, $v1, $t3
	sw	$v1, 0($t1)
	xor	$v1, $t1, $v0
	sll	$t3, $v1, 8
	srl	$v1, $t3, 8
	xor	$t3, $v1, $v0
	sw	$t3, 0($t4)
	j	.L21
	addiu	$t1, $t1, 0x28
.L10:
	srl	$v0, $s2, 16
	sll	$v0, $v0, 16
	j	.L14
	li	$t4, 0
.L11:
	sll	$v0, $a2, 16
	j	.L14
	li	$t4, 0x1
.L12:
	sll	$v0, $a3, 16
	j	.L14
	li	$t4, 0x2
.L13:
	sll	$v0, $t9, 16
	li	$t4, 0x3
.L14:
	srl	$v0, $v0, 13
	addu	$t0, $v0, $t6
	lw	$v0, 0($t0)
	lw	$v1, 0x4($t0)
	sll	$t3, $v0, 16
	srl	$t3, $t3, 21
	srl	$v0, $v0, 21
	srl	$v1, $v1, 5
	slti	$at, $t3, 0xFF
	bnez	$at, .L15
	nop
	li	$t3, 0xFF
.L15:
	slti	$at, $v0, 0xFF
	bnez	$at, .L16
	nop
	li	$v0, 0xFF
.L16:
	slti	$at, $v1, 0xFF
	bnez	$at, .L17
	nop
	li	$v1, 0xFF
.L17:
	sll	$v0, $v0, 8
	sll	$v1, $v1, 16
	or	$t0, $t3, $v0
	or	$t0, $t0, $v1
	li	$at, 0x3
	beq	$t4, $at, .L20
	nop
	li	$at, 0x2
	beq	$t4, $at, .L19
	nop
	li	$at, 0x1
	beq	$t4, $at, .L18
	nop
	or	$t0, $t0, $s1
	j	.L11
	sw	$t0, 0x4($t1)
.L18:
	j	.L12
	sw	$t0, 0x10($t1)
.L19:
	j	.L13
	sw	$t0, 0x1C($t1)
.L20:
	sw	$t0, 0x28($t1)
	AVSZ4
	lw	$a2, 0($t7)
	lw	$a3, 0x4($t7)
	sw	$a2, 0xC($t1)
	sw	$a3, 0x18($t1)
	sw	$s2, 0x24($t1)
	sw	$a1, 0x30($t1)
	lw	$t0, 0x4($a0)
	lw	$a1, 0xC($a0)
	lw	$a2, 0x8($a0)
	lw	$a3, 0x4($t0)
	mfc2	$t4, $7
	nop
	subu	$t4, $t4, $a1
	srlv	$t4, $t4, $a2
	andi	$t4, $t4, 0xFFFF
	sll	$t4, $t4, 2
	addu	$t4, $t4, $a3
	lw	$v0, 0($t4)
	li	$v1, 0xc000000
	sll	$t3, $v0, 8
	srl	$t3, $t3, 8
	or	$v1, $v1, $t3
	sw	$v1, 0($t1)
	xor	$v1, $t1, $v0
	sll	$t3, $v1, 8
	srl	$v1, $t3, 8
	xor	$t3, $v1, $v0
	sw	$t3, 0($t4)
	addiu	$t1, $t1, 0x34
.L21:
	addiu	$t2, $t2, -0x1
	bnez	$t2, .L1
	addiu	$t7, $t7, 0x1C
.L22:
	lw	$v0, 0($a0)
	lui	$at, %hi(GsOUT_PACKET_P)
	sw	$t1, %lo(GsOUT_PACKET_P)($at)
	addiu	$v0, $v0, 0x8
	lw	$s0, 0x18($a0)
	lw	$s1, 0x20($a0)
	lw	$s2, 0x10($a0)
	jr	$ra
	nop
	.set	at
	.end	GsU_01200015
	.set	reorder
