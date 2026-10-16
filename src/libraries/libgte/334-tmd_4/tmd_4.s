/* LIBGTE.LIB, member TMD_4.OBJ (hand-written assembly)
 *
 * gte_scope_tg3: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	gte_scope_tg3
	.ent	gte_scope_tg3
gte_scope_tg3:
	.set	noat
	lw	$t3, 0x10($a1)
	lw	$t4, 0x14($a1)
	lw	$t5, 0x18($a1)
	srl	$t3, $t3, 16
	sll	$t3, $t3, 3
	add	$t2, $a2, $t3
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	srl	$t4, $t4, 16
	sll	$t4, $t4, 3
	add	$t2, $a2, $t4
	lwc2	$2, 0($t2)
	lwc2	$3, 0x4($t2)
	srl	$t5, $t5, 16
	sll	$t5, $t5, 3
	add	$t2, $a2, $t5
	lwc2	$4, 0($t2)
	lwc2	$5, 0x4($t2)
	nop
	nop
	RTPT
	lw	$t8, GsBACKC
	lw	$t9, GsZOVER
	lw	$t4, GsCLIP3near
	bnez	$t9, .L1
	nop
	cfc2	$t0, $31
	cfc2	$t0, $31
	nop
	li	$at, 0x7f87e000
	and	$t0, $t0, $at
	bnez	$t0, .L3
	nop
.L1:
	NCLIP
	bnez	$t8, .L2
	nop
	mfc2	$t0, $24
	mfc2	$t0, $24
	nop
	blez	$t0, .L3
	nop
.L2:
	mfc2	$t1, $17
	mfc2	$t2, $18
	mfc2	$t3, $19
	AVSZ3
	slt	$at, $t4, $t1
	beqz	$at, .L3
	nop
	slt	$at, $t4, $t2
	beqz	$at, .L3
	nop
	slt	$at, $t4, $t3
	beqz	$at, .L3
	nop
	mfc2	$t0, $7
	mfc2	$t0, $7
	lw	$t4, GsCLIP3far
	sw	$t0, 0($a0)
	slt	$at, $t0, $t4
	beqz	$at, .L3
	nop
	li	$v0, 0x1
	jr	$ra
	nop
.L3:
	li	$v0, 0
	jr	$ra
	nop
	.set	at
	.end	gte_scope_tg3
	.set	reorder
