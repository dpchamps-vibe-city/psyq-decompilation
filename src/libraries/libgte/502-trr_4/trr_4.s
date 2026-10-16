/* LIBGTE.LIB, member TRR_4.OBJ (hand-written assembly)
 *
 * VECTOR *ApplyTransposeMatrixLV(MATRIX *m, VECTOR *v0, VECTOR *v1);
 *
 * Register use:
 *   a0  m
 *   a1  v0
 *   a2  v1
 *   v0  result (VECTOR *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	ApplyTransposeMatrixLV
	.ent	ApplyTransposeMatrixLV
ApplyTransposeMatrixLV:
	lh	$v0, 0x6($a0)
	lh	$t0, 0($a0)
	sll	$v0, $v0, 16
	andi	$t0, $t0, 0xFFFF
	or	$t0, $t0, $v0
	lh	$v0, 0x2($a0)
	lh	$t1, 0xC($a0)
	sll	$v0, $v0, 16
	andi	$t1, $t1, 0xFFFF
	or	$t1, $t1, $v0
	lh	$v0, 0xE($a0)
	lh	$t2, 0x8($a0)
	sll	$v0, $v0, 16
	andi	$t2, $t2, 0xFFFF
	or	$t2, $t2, $v0
	lh	$v0, 0xA($a0)
	lh	$t3, 0x4($a0)
	sll	$v0, $v0, 16
	andi	$t3, $t3, 0xFFFF
	or	$t3, $t3, $v0
	lw	$t4, 0x10($a0)
	ctc2	$t0, $0
	ctc2	$t1, $1
	ctc2	$t2, $2
	ctc2	$t3, $3
	ctc2	$t4, $4
	lw	$t0, 0($a1)
	lw	$t1, 0x4($a1)
	lw	$t2, 0x8($a1)
	bgez	$t0, .L1
	nop
	negu	$t0, $t0
	sra	$t3, $t0, 15
	negu	$t3, $t3
	andi	$t0, $t0, 0x7FFF
	b	.L2
	negu	$t0, $t0
.L1:
	sra	$t3, $t0, 15
	andi	$t0, $t0, 0x7FFF
.L2:
	bgez	$t1, .L3
	nop
	negu	$t1, $t1
	sra	$t4, $t1, 15
	negu	$t4, $t4
	andi	$t1, $t1, 0x7FFF
	b	.L4
	negu	$t1, $t1
.L3:
	sra	$t4, $t1, 15
	andi	$t1, $t1, 0x7FFF
.L4:
	bgez	$t2, .L5
	nop
	negu	$t2, $t2
	sra	$t5, $t2, 15
	negu	$t5, $t5
	andi	$t2, $t2, 0x7FFF
	b	.L6
	negu	$t2, $t2
.L5:
	sra	$t5, $t2, 15
	andi	$t2, $t2, 0x7FFF
.L6:
	andi	$t3, $t3, 0xFFFF
	sll	$t4, $t4, 16
	or	$t3, $t3, $t4
	mtc2	$t3, $0
	mtc2	$t5, $1
	nop
	MVMVA	0, 0, 0, 3, 0
	mfc2	$t3, $25
	mfc2	$t4, $26
	mfc2	$t5, $27
	andi	$t0, $t0, 0xFFFF
	sll	$t1, $t1, 16
	or	$t0, $t0, $t1
	mtc2	$t0, $0
	mtc2	$t2, $1
	nop
	MVMVA	1, 0, 0, 3, 0
	bgez	$t3, .L7
	nop
	negu	$t3, $t3
	sll	$t3, $t3, 3
	b	.L8
	negu	$t3, $t3
.L7:
	sll	$t3, $t3, 3
.L8:
	bgez	$t4, .L9
	nop
	negu	$t4, $t4
	sll	$t4, $t4, 3
	b	.L10
	negu	$t4, $t4
.L9:
	sll	$t4, $t4, 3
.L10:
	bgez	$t5, .L11
	nop
	negu	$t5, $t5
	sll	$t5, $t5, 3
	b	.L12
	negu	$t5, $t5
.L11:
	sll	$t5, $t5, 3
.L12:
	mfc2	$t0, $25
	mfc2	$t1, $26
	mfc2	$t2, $27
	addu	$t0, $t0, $t3
	addu	$t1, $t1, $t4
	addu	$t2, $t2, $t5
	sw	$t0, 0($a2)
	sw	$t1, 0x4($a2)
	sw	$t2, 0x8($a2)
	jr	$ra
	move	$v0, $a2
	.end	ApplyTransposeMatrixLV
	.set	reorder
