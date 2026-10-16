/* LIBHMD.LIB, member 01020014.OBJ (hand-written assembly)
 *
 * u_long *GsU_01020014(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x01020014 (GsUSFG4): shared fog gouraud quad.
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_01020014
	.ent	GsU_01020014
GsU_01020014:
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
	beqz	$t2, .L17
	addu	$t7, $t4, $t3
.L1:
	lw	$a1, 0x4($t7)
	lw	$a2, 0x8($t7)
	lw	$a3, 0xC($t7)
	lw	$t9, 0x10($t7)
	srl	$v0, $a1, 16
	sll	$v0, $v0, 3
	addu	$t3, $v0, $t5
	lw	$v0, 0x4($t3)
	li	$t0, -0x1
	beq	$v0, $t0, .L16
	nop
	mtc2	$v0, $16
	nop
	srl	$v0, $a2, 16
	sll	$v0, $v0, 3
	addu	$t4, $v0, $t5
	lw	$v0, 0x4($t4)
	nop
	beq	$v0, $t0, .L16
	nop
	mtc2	$v0, $17
	nop
	srl	$v0, $a3, 16
	sll	$v0, $v0, 3
	addu	$v1, $v0, $t5
	lw	$v0, 0x4($v1)
	nop
	beq	$v0, $t0, .L16
	nop
	mtc2	$v0, $18
	nop
	srl	$v0, $t9, 16
	sll	$v0, $v0, 3
	addu	$s0, $v0, $t5
	lw	$v0, 0x4($s0)
	nop
	beq	$v0, $t0, .L16
	nop
	mtc2	$v0, $19
	nop
	lw	$v0, 0($t3)
	lw	$t0, 0($t4)
	lw	$s1, 0($v1)
	mtc2	$v0, $12
	mtc2	$t0, $13
	mtc2	$s1, $14
	lw	$t8, 0($s0)
	nop
	NCLIP
	sw	$v0, 0x8($t1)
	sw	$t0, 0x10($t1)
	sw	$s1, 0x18($t1)
	sw	$t8, 0x20($t1)
	mfc2	$v0, $24
	nop
	bgtz	$v0, .L8
	nop
	mtc2	$t8, $12
	nop
	nop
	NCLIP
	sw	$t8, 0x8($t1)
	mfc2	$v0, $24
	nop
	bgtz	$v0, .L16
	nop
	lw	$v0, 0($t7)
	nop
	sll	$t8, $v0, 24
	srl	$t8, $t8, 24
	sll	$t0, $v0, 16
	srl	$t0, $t0, 24
	sll	$s1, $v0, 8
	srl	$s1, $s1, 24
	ctc2	$t8, $0
	ctc2	$zero, $1
	ctc2	$t0, $2
	ctc2	$zero, $3
	ctc2	$s1, $4
	li	$t8, 0
	sll	$v0, $t9, 16
	move	$s1, $s0
.L2:
	srl	$v0, $v0, 13
	addu	$t0, $v0, $t6
	lw	$v0, 0($t0)
	lw	$a1, 0x4($t0)
	sll	$s0, $v0, 16
	srl	$s0, $s0, 16
	srl	$v0, $v0, 16
	mtc2	$s0, $9
	mtc2	$v0, $10
	mtc2	$a1, $11
	nop
	nop
	MVMVA	1, 0, 3, 3, 0
	lhu	$t9, 0x6($s1)
	nop
	li	$s1, 0x30000000
	mtc2	$t9, $8
	nop
	mfc2	$s0, $9
	mfc2	$v0, $10
	mfc2	$a1, $11
	nop
	slti	$at, $s0, 0xFF
	bnez	$at, .L3
	nop
	li	$s0, 0xFF
.L3:
	slti	$at, $v0, 0xFF
	bnez	$at, .L4
	nop
	li	$v0, 0xFF
.L4:
	slti	$at, $a1, 0xFF
	bnez	$at, .L5
	nop
	li	$a1, 0xFF
.L5:
	sll	$v0, $v0, 8
	sll	$a1, $a1, 16
	or	$t0, $s0, $v0
	or	$t0, $t0, $a1
	or	$t0, $t0, $s1
	mtc2	$t0, $6
	nop
	nop
	DPCS
	li	$at, 0x2
	beq	$t8, $at, .L7
	nop
	li	$at, 0x1
	beq	$t8, $at, .L6
	nop
	move	$s1, $t4
	swc2	$22, 0x4($t1)
	sll	$v0, $a2, 16
	j	.L2
	addiu	$t8, $t8, 0x1
.L6:
	move	$s1, $v1
	swc2	$22, 0xC($t1)
	sll	$v0, $a3, 16
	j	.L2
	addiu	$t8, $t8, 0x1
.L7:
	swc2	$22, 0x14($t1)
	nop
	nop
	AVSZ3
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
	li	$v1, 0x6000000
	sll	$t3, $v0, 8
	srl	$t3, $t3, 8
	or	$v1, $v1, $t3
	sw	$v1, 0($t1)
	xor	$v1, $t1, $v0
	sll	$t3, $v1, 8
	srl	$v1, $t3, 8
	xor	$t3, $v1, $v0
	sw	$t3, 0($t4)
	j	.L16
	addiu	$t1, $t1, 0x1C
.L8:
	lw	$v0, 0($t7)
	nop
	sll	$t8, $v0, 24
	srl	$t8, $t8, 24
	sll	$t0, $v0, 16
	srl	$t0, $t0, 24
	sll	$s1, $v0, 8
	srl	$s1, $s1, 24
	ctc2	$t8, $0
	ctc2	$zero, $1
	ctc2	$t0, $2
	ctc2	$zero, $3
	ctc2	$s1, $4
	li	$t8, 0
	sll	$v0, $a1, 16
	move	$s1, $t3
.L9:
	srl	$v0, $v0, 13
	addu	$t0, $v0, $t6
	lw	$v0, 0($t0)
	lw	$a1, 0x4($t0)
	sll	$t3, $v0, 16
	srl	$t3, $t3, 16
	srl	$v0, $v0, 16
	mtc2	$t3, $9
	mtc2	$v0, $10
	mtc2	$a1, $11
	nop
	nop
	MVMVA	1, 0, 3, 3, 0
	lhu	$a1, 0x6($s1)
	nop
	li	$s1, 0x38000000
	mtc2	$a1, $8
	nop
	mfc2	$t3, $9
	mfc2	$v0, $10
	mfc2	$a1, $11
	nop
	slti	$at, $t3, 0xFF
	bnez	$at, .L10
	nop
	li	$t3, 0xFF
.L10:
	slti	$at, $v0, 0xFF
	bnez	$at, .L11
	nop
	li	$v0, 0xFF
.L11:
	slti	$at, $a1, 0xFF
	bnez	$at, .L12
	nop
	li	$a1, 0xFF
.L12:
	sll	$v0, $v0, 8
	sll	$a1, $a1, 16
	or	$t0, $t3, $v0
	or	$t0, $t0, $a1
	or	$t0, $t0, $s1
	mtc2	$t0, $6
	nop
	nop
	DPCS
	li	$at, 0x3
	beq	$t8, $at, .L15
	nop
	li	$at, 0x2
	beq	$t8, $at, .L14
	nop
	li	$at, 0x1
	beq	$t8, $at, .L13
	nop
	move	$s1, $t4
	swc2	$22, 0x4($t1)
	sll	$v0, $a2, 16
	j	.L9
	addiu	$t8, $t8, 0x1
.L13:
	move	$s1, $v1
	swc2	$22, 0xC($t1)
	sll	$v0, $a3, 16
	j	.L9
	addiu	$t8, $t8, 0x1
.L14:
	move	$s1, $s0
	swc2	$22, 0x14($t1)
	sll	$v0, $t9, 16
	j	.L9
	addiu	$t8, $t8, 0x1
.L15:
	swc2	$22, 0x1C($t1)
	nop
	nop
	AVSZ4
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
	li	$v1, 0x8000000
	sll	$t3, $v0, 8
	srl	$t3, $t3, 8
	or	$v1, $v1, $t3
	sw	$v1, 0($t1)
	xor	$v1, $t1, $v0
	sll	$t3, $v1, 8
	srl	$v1, $t3, 8
	xor	$t3, $v1, $v0
	sw	$t3, 0($t4)
	addiu	$t1, $t1, 0x24
.L16:
	addiu	$t2, $t2, -0x1
	bnez	$t2, .L1
	addiu	$t7, $t7, 0x14
.L17:
	lw	$v0, 0($a0)
	lui	$at, %hi(GsOUT_PACKET_P)
	sw	$t1, %lo(GsOUT_PACKET_P)($at)
	addiu	$v0, $v0, 0x8
	lw	$s0, 0x18($a0)
	lw	$s1, 0x20($a0)
	jr	$ra
	nop
	nop
	nop
	.set	at
	.end	GsU_01020014
	.set	reorder
