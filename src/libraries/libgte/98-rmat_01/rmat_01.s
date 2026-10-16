/* LIBGTE.LIB, member RMAT_01.OBJ (hand-written assembly)
 *
 * MATRIX *RotMatrix_gte(SVECTOR *r, MATRIX *m);
 *
 * Register use:
 *   a0  r
 *   a1  m
 *   v0  result (MATRIX *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotMatrix_gte
	.ent	RotMatrix_gte
RotMatrix_gte:
	.set	noat
	or	$v0, $zero, $a1
	lh	$t0, 0x4($a0)
	la	$v1, rcossin_tbl
	lw	$t4, 0($a0)
	sra	$t3, $t0, 31
	add	$t0, $t0, $t3
	xor	$t0, $t0, $t3
	sll	$t0, $t0, 2
	andi	$t0, $t0, 0x3FFC
	add	$t0, $t0, $v1
	lw	$a2, 0($t0)
	sra	$t0, $t4, 16
	sra	$t2, $t0, 31
	add	$t0, $t0, $t2
	xor	$t0, $t0, $t2
	sll	$t0, $t0, 2
	andi	$t0, $t0, 0x3FFC
	add	$t0, $t0, $v1
	lw	$a1, 0($t0)
	sll	$t0, $t4, 16
	sra	$t0, $t0, 16
	sra	$t1, $t0, 31
	add	$t0, $t0, $t1
	xor	$t0, $t0, $t1
	sll	$t0, $t0, 2
	andi	$t0, $t0, 0x3FFC
	add	$t0, $t0, $v1
	lw	$a0, 0($t0)
	sll	$at, $a2, 16
	sra	$a2, $a2, 16
	sll	$a2, $a2, 16
	add	$at, $at, $t3
	xor	$at, $at, $t3
	srl	$at, $at, 16
	or	$a2, $a2, $at
	sll	$at, $a1, 16
	sra	$a1, $a1, 16
	sll	$a1, $a1, 16
	add	$at, $at, $t2
	xor	$at, $at, $t2
	srl	$at, $at, 16
	or	$a1, $a1, $at
	sll	$at, $a0, 16
	sra	$a0, $a0, 16
	sll	$a0, $a0, 16
	add	$at, $at, $t1
	xor	$at, $at, $t1
	srl	$at, $at, 16
	or	$a0, $a0, $at
	sra	$t0, $a0, 16
	mtc2	$t0, $8
	sll	$a3, $a1, 16
	sra	$a3, $a3, 16
	mtc2	$a3, $9
	sll	$v1, $a2, 16
	sra	$v1, $v1, 16
	mtc2	$v1, $10
	sra	$at, $a2, 16
	mtc2	$at, $11
	nop
	nop
	GPF	1
	sra	$at, $a1, 16
	mult	$at, $t0
	mfc2	$t0, $9
	mfc2	$t1, $10
	sll	$t6, $a0, 16
	mfc2	$t2, $11
	sra	$t6, $t6, 16
	mtc2	$t6, $8
	mtc2	$a3, $9
	mtc2	$v1, $10
	sra	$at, $a2, 16
	mtc2	$at, $11
	nop
	nop
	GPF	1
	mflo	$at
	sra	$at, $at, 12
	sh	$at, 0x10($v0)
	mfc2	$t3, $9
	mfc2	$t4, $10
	mfc2	$t5, $11
	sra	$at, $a2, 16
	mtc2	$at, $8
	sra	$at, $a1, 16
	mtc2	$at, $9
	mult	$at, $t6
	mtc2	$t3, $10
	mtc2	$t0, $11
	nop
	nop
	GPF	1
	mfc2	$a0, $9
	mfc2	$a1, $10
	mfc2	$a2, $11
	mtc2	$v1, $8
	mtc2	$at, $9
	mtc2	$t3, $10
	mtc2	$t0, $11
	nop
	nop
	GPF	1
	add	$t1, $a1, $t1
	sll	$t1, $t1, 16
	andi	$a3, $a3, 0xFFFF
	or	$t1, $t1, $a3
	sw	$t1, 0x4($v0)
	mfc2	$at, $9
	andi	$a0, $a0, 0xFFFF
	neg	$at, $at
	sll	$at, $at, 16
	or	$at, $at, $a0
	sw	$at, 0($v0)
	mfc2	$t6, $10
	mflo	$at
	mfc2	$t7, $11
	sub	$t2, $t2, $t6
	sra	$at, $at, 12
	neg	$at, $at
	andi	$t2, $t2, 0xFFFF
	sll	$at, $at, 16
	or	$at, $at, $t2
	sw	$at, 0x8($v0)
	sub	$t4, $t4, $a2
	andi	$t4, $t4, 0xFFFF
	add	$t5, $t5, $t7
	sll	$t5, $t5, 16
	or	$t4, $t4, $t5
	jr	$ra
	sw	$t4, 0xC($v0)
	.set	at
	.end	RotMatrix_gte
	.set	reorder
