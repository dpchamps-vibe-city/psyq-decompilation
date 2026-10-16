/* LIBHMD.LIB, member 0120000E.OBJ (hand-written assembly)
 *
 * u_long *GsU_0120000e(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x0120000e: shared semi-trans colored gouraud triangle (no define in libhmd.h; read from the flag bits).
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_0120000e
	.ent	GsU_0120000e
GsU_0120000e:
	.set	noat
	lw	$t0, 0($a0)
	lw	$t1, 0x10($a0)
	lhu	$t2, 0x2($t0)
	lw	$t3, 0x4($t0)
	lw	$t4, 0x14($a0)
	lw	$t5, 0x1C($a0)
	lw	$t6, 0x24($a0)
	sll	$t3, $t3, 2
	beqz	$t2, .L11
	addu	$t7, $t4, $t3
	li	$t9, 0x32000000
.L1:
	lw	$a1, 0xC($t7)
	lw	$a2, 0x10($t7)
	lw	$a3, 0x14($t7)
	srl	$v0, $a1, 16
	sll	$v0, $v0, 3
	addu	$t3, $v0, $t5
	lw	$v0, 0x4($t3)
	li	$t0, -0x1
	beq	$v0, $t0, .L10
	nop
	mtc2	$v0, $17
	nop
	srl	$v0, $a2, 16
	sll	$v0, $v0, 3
	addu	$t4, $v0, $t5
	lw	$v0, 0x4($t4)
	nop
	beq	$v0, $t0, .L10
	nop
	mtc2	$v0, $18
	nop
	srl	$v0, $a3, 16
	sll	$v0, $v0, 3
	addu	$v1, $v0, $t5
	lw	$v0, 0x4($v1)
	nop
	beq	$v0, $t0, .L10
	nop
	mtc2	$v0, $19
	nop
	lw	$v0, 0($t3)
	lw	$t0, 0($t4)
	lw	$t3, 0($v1)
	mtc2	$v0, $12
	mtc2	$t0, $13
	mtc2	$t3, $14
	nop
	nop
	NCLIP
	sw	$v0, 0x8($t1)
	sw	$t0, 0x10($t1)
	sw	$t3, 0x18($t1)
	mfc2	$v0, $24
	nop
	blez	$v0, .L10
	nop
	sll	$v0, $a1, 16
	lw	$a1, 0($t7)
	nop
	j	.L4
	li	$t4, 0
.L2:
	sll	$v0, $a2, 16
	lw	$a1, 0x4($t7)
	nop
	j	.L4
	li	$t4, 0x1
.L3:
	sll	$v0, $a3, 16
	lw	$a1, 0x8($t7)
	nop
	li	$t4, 0x2
.L4:
	sll	$v1, $a1, 24
	srl	$v1, $v1, 24
	sll	$t0, $a1, 16
	srl	$t0, $t0, 24
	sll	$t3, $a1, 8
	srl	$t3, $t3, 24
	ctc2	$v1, $0
	ctc2	$zero, $1
	ctc2	$t0, $2
	ctc2	$zero, $3
	ctc2	$t3, $4
	srl	$v0, $v0, 13
	addu	$t0, $v0, $t6
	lw	$v0, 0($t0)
	lw	$v1, 0x4($t0)
	sll	$t3, $v0, 16
	srl	$t3, $t3, 16
	srl	$v0, $v0, 16
	mtc2	$t3, $9
	mtc2	$v0, $10
	mtc2	$v1, $11
	nop
	nop
	MVMVA	1, 0, 3, 3, 0
	mfc2	$t3, $9
	mfc2	$v0, $10
	mfc2	$v1, $11
	nop
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
	or	$t0, $t0, $t9
	j	.L2
	sw	$t0, 0x4($t1)
.L8:
	j	.L3
	sw	$t0, 0xC($t1)
.L9:
	sw	$t0, 0x14($t1)
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
	addiu	$t1, $t1, 0x1C
.L10:
	addiu	$t2, $t2, -0x1
	bnez	$t2, .L1
	addiu	$t7, $t7, 0x18
.L11:
	lw	$v0, 0($a0)
	lui	$at, %hi(GsOUT_PACKET_P)
	sw	$t1, %lo(GsOUT_PACKET_P)($at)
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	.set	at
	.end	GsU_0120000e
	.set	reorder
