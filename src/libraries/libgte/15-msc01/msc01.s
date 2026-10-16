/* LIBGTE.LIB, member MSC01.OBJ (hand-written assembly)
 *
 * long SquareRoot0(long a);
 *
 * Register use:
 *   a0  a
 *   v0  result (long)
 */
	.text
	.align	4
	.set	noreorder

	.globl	SquareRoot0
	.ent	SquareRoot0
SquareRoot0:
	.set	noat
	mtc2	$a0, $30
	nop
	nop
	mfc2	$v0, $31
	li	$at, 0x20
	beq	$v0, $at, .L3
	nop
	andi	$t0, $v0, 0x1
	li	$at, -0x2
	and	$t2, $v0, $at
	li	$t1, 0x1F
	sub	$t1, $t1, $t2
	sra	$t1, $t1, 1
	addi	$t3, $t2, -0x18
	bltz	$t3, .L1
	nop
	sllv	$t4, $a0, $t3
	b	.L2
.L1:
	li	$t3, 0x18
	sub	$t3, $t3, $t2
	srav	$t4, $a0, $t3
.L2:
	addi	$t4, $t4, -0x40
	sll	$t4, $t4, 1
	lui	$t5, %hi(SQRT)
	addu	$t5, $t5, $t4
	lh	$t5, %lo(SQRT)($t5)
	nop
	sllv	$t5, $t5, $t1
	srl	$v0, $t5, 12
	jr	$ra
	nop
.L3:
	jr	$ra
	li	$v0, 0
	nop
	nop
	nop
	.set	at
	.end	SquareRoot0
	.set	reorder
