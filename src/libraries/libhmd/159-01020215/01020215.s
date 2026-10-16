/* LIBHMD.LIB, member 01020215.OBJ (hand-written assembly)
 *
 * u_long *GsU_01020215(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x01020215: fog shared tile texture gouraud quad (no define in libhmd.h; read from the flag bits).
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_01020215
	.ent	GsU_01020215
GsU_01020215:
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
	lw	$a1, 0x10($t7)
	lw	$a2, 0x14($t7)
	lw	$a3, 0x18($t7)
	lw	$t9, 0x1C($t7)
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
	lw	$t8, 0($v1)
	mtc2	$v0, $12
	mtc2	$t0, $13
	mtc2	$t8, $14
	lw	$s1, 0($s0)
	lw	$s2, 0xC($t7)
	NCLIP
	sw	$v0, 0xC($t1)
	sw	$t0, 0x18($t1)
	sw	$t8, 0x24($t1)
	sw	$s1, 0x30($t1)
	mfc2	$v0, $24
	nop
	bgtz	$v0, .L10
	nop
	mtc2	$s1, $12
	nop
	nop
	NCLIP
	sw	$s1, 0xC($t1)
	mfc2	$v0, $24
	nop
	bgtz	$v0, .L21
	nop
	sll	$v0, $t9, 16
	move	$t0, $s0
	j	.L4
	li	$t8, 0
.L2:
	sll	$v0, $a2, 16
	move	$t0, $t4
	j	.L4
	li	$t8, 0x1
.L3:
	sll	$v0, $a3, 16
	move	$t0, $v1
	li	$t8, 0x2
.L4:
	lhu	$s0, 0x6($t0)
	li	$s1, 0x34000000
	mtc2	$s0, $8
	srl	$v0, $v0, 13
	addu	$t0, $v0, $t6
	lw	$v0, 0($t0)
	lw	$s0, 0x4($t0)
	sll	$t3, $v0, 16
	srl	$t3, $t3, 21
	srl	$v0, $v0, 21
	srl	$s0, $s0, 5
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
	slti	$at, $s0, 0xFF
	bnez	$at, .L7
	nop
	li	$s0, 0xFF
.L7:
	sll	$v0, $v0, 8
	sll	$s0, $s0, 16
	or	$t0, $t3, $v0
	or	$t0, $t0, $s0
	or	$t0, $t0, $s1
	mtc2	$t0, $6
	nop
	nop
	DPCS
	li	$at, 0x2
	beq	$t8, $at, .L9
	nop
	li	$at, 0x1
	beq	$t8, $at, .L8
	nop
	swc2	$22, 0x8($t1)
	j	.L2
	nop
.L8:
	swc2	$22, 0x14($t1)
	j	.L3
	nop
.L9:
	swc2	$22, 0x20($t1)
	nop
	nop
	AVSZ3
	lw	$v0, 0($t7)
	lw	$t0, 0x4($t7)
	lw	$a2, 0x8($t7)
	li	$at, 0xffff0000
	and	$t0, $t0, $at
	andi	$a1, $a1, 0xFFFF
	or	$a1, $a1, $t0
	sw	$v0, 0x4($t1)
	sw	$a1, 0x10($t1)
	sw	$a2, 0x1C($t1)
	sw	$s2, 0x28($t1)
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
	li	$v1, 0xb000000
	sll	$t3, $v0, 8
	srl	$t3, $t3, 8
	or	$v1, $v1, $t3
	sw	$v1, 0($t1)
	li	$at, 0xe2000000
	xor	$v1, $t1, $v0
	sw	$at, 0x2C($t1)
	sll	$t3, $v1, 8
	srl	$v1, $t3, 8
	xor	$t3, $v1, $v0
	sw	$t3, 0($t4)
	j	.L21
	addiu	$t1, $t1, 0x30
.L10:
	srl	$v0, $s2, 16
	sll	$v0, $v0, 16
	move	$t0, $t3
	j	.L14
	li	$t8, 0
.L11:
	sll	$v0, $a2, 16
	move	$t0, $t4
	j	.L14
	li	$t8, 0x1
.L12:
	sll	$v0, $a3, 16
	move	$t0, $v1
	j	.L14
	li	$t8, 0x2
.L13:
	sll	$v0, $t9, 16
	move	$t0, $s0
	li	$t8, 0x3
.L14:
	lhu	$t3, 0x6($t0)
	srl	$v0, $v0, 13
	addu	$t0, $v0, $t6
	mtc2	$t3, $8
	lw	$s1, 0($t0)
	lw	$v0, 0x4($t0)
	sll	$t3, $s1, 16
	srl	$t3, $t3, 21
	srl	$t0, $s1, 21
	srl	$v0, $v0, 5
	slti	$at, $t3, 0xFF
	bnez	$at, .L15
	li	$s1, 0x3c000000
	li	$t3, 0xFF
.L15:
	slti	$at, $t0, 0xFF
	bnez	$at, .L16
	nop
	li	$t0, 0xFF
.L16:
	slti	$at, $v0, 0xFF
	bnez	$at, .L17
	nop
	li	$v0, 0xFF
.L17:
	sll	$t0, $t0, 8
	sll	$v0, $v0, 16
	or	$t3, $t3, $t0
	or	$t3, $t3, $v0
	or	$t0, $t3, $s1
	mtc2	$t0, $6
	nop
	nop
	DPCS
	li	$at, 0x3
	beq	$t8, $at, .L20
	nop
	li	$at, 0x2
	beq	$t8, $at, .L19
	nop
	li	$at, 0x1
	beq	$t8, $at, .L18
	nop
	swc2	$22, 0x8($t1)
	j	.L11
	nop
.L18:
	swc2	$22, 0x14($t1)
	j	.L12
	nop
.L19:
	swc2	$22, 0x20($t1)
	j	.L13
	nop
.L20:
	swc2	$22, 0x2C($t1)
	nop
	nop
	AVSZ4
	lw	$a2, 0x4($t7)
	lw	$a3, 0x8($t7)
	sw	$a2, 0x10($t1)
	sw	$a3, 0x1C($t1)
	sw	$s2, 0x28($t1)
	sw	$a1, 0x34($t1)
	lw	$v0, 0($t7)
	lw	$t0, 0x4($a0)
	lw	$a1, 0xC($a0)
	lw	$a2, 0x8($a0)
	lw	$a3, 0x4($t0)
	sw	$v0, 0x4($t1)
	mfc2	$t4, $7
	nop
	subu	$t4, $t4, $a1
	srlv	$t4, $t4, $a2
	andi	$t4, $t4, 0xFFFF
	sll	$t4, $t4, 2
	addu	$t4, $t4, $a3
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
.L21:
	addiu	$t2, $t2, -0x1
	bnez	$t2, .L1
	addiu	$t7, $t7, 0x20
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
	nop
	nop
	nop
	.set	at
	.end	GsU_01020215
	.set	reorder
