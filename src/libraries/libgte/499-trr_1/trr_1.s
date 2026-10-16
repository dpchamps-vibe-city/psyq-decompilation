/* LIBGTE.LIB, member TRR_1.OBJ (hand-written assembly)
 *
 * void TransRot_32(VECTOR *v0, VECTOR *v1, long *flag);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   a2  flag
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	TransRot_32
	.ent	TransRot_32
TransRot_32:
	cfc2	$t7, $5
	cfc2	$t8, $6
	cfc2	$t9, $7
	ctc2	$zero, $5
	ctc2	$zero, $6
	ctc2	$zero, $7
	lw	$t0, 0($a0)
	lw	$t1, 0x4($a0)
	lw	$t2, 0x8($a0)
	add	$t0, $t0, $t7
	add	$t1, $t1, $t8
	add	$t2, $t2, $t9
	bgez	$t0, .L1
	nop
	negu	$t0, $t0
	sra	$t3, $t0, 15
	negu	$t3, $t3
	andi	$t0, $t0, 0x7FFF
	negu	$t0, $t0
	b	.L2
	nop
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
	negu	$t1, $t1
	b	.L4
	nop
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
	negu	$t2, $t2
	b	.L6
	nop
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
	negu	$t3, $t3
	b	.L8
	nop
.L7:
	sll	$t3, $t3, 3
.L8:
	bgez	$t4, .L9
	nop
	negu	$t4, $t4
	sll	$t4, $t4, 3
	negu	$t4, $t4
	b	.L10
	nop
.L9:
	sll	$t4, $t4, 3
.L10:
	bgez	$t5, .L11
	nop
	negu	$t5, $t5
	sll	$t5, $t5, 3
	negu	$t5, $t5
	b	.L12
	nop
.L11:
	sll	$t5, $t5, 3
.L12:
	mfc2	$t0, $25
	mfc2	$t1, $26
	mfc2	$t2, $27
	cfc2	$v1, $31
	addu	$t0, $t0, $t3
	addu	$t1, $t1, $t4
	addu	$t2, $t2, $t5
	sw	$t0, 0($a1)
	sw	$t1, 0x4($a1)
	sw	$t2, 0x8($a1)
	ctc2	$t7, $5
	ctc2	$t8, $6
	ctc2	$t9, $7
	sw	$v1, 0($a2)
	move	$v0, $t2
	sra	$v0, $v0, 2
	jr	$ra
	nop
	.end	TransRot_32
	.set	reorder
