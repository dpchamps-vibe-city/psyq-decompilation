/* LIBGTE.LIB, member TMD_13.OBJ (hand-written assembly)
 *
 * gte_scope_tf4_B: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	gte_scope_tf4_B
	.ent	gte_scope_tf4_B
gte_scope_tf4_B:
	.set	noat
	lhu	$t3, 0x16($a1)
	lw	$t4, 0x18($a1)
	sll	$t3, $t3, 3
	add	$t2, $a2, $t3
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	andi	$t5, $t4, 0xFFFF
	sll	$t5, $t5, 3
	add	$t2, $a2, $t5
	lwc2	$2, 0($t2)
	lwc2	$3, 0x4($t2)
	srl	$t4, $t4, 16
	sll	$t4, $t4, 3
	add	$t2, $a2, $t4
	lwc2	$4, 0($t2)
	lwc2	$5, 0x4($t2)
	RTPT
	lw	$t8, GsBACKC
	lw	$t9, GsZOVER
	lw	$t7, GsCLIP3near
	bnez	$t9, .L1
	nop
	cfc2	$t0, $31
	cfc2	$t0, $31
	li	$at, 0x7f87e000
	and	$t0, $t0, $at
	bnez	$t0, .L5
	nop
.L1:
	NCLIP
	bnez	$t8, .L2
	nop
	mfc2	$t5, $24
.L2:
	swc2	$12, 0($a3)
	lh	$t3, 0x1C($a1)
	nop
	sll	$t3, $t3, 3
	add	$t2, $a2, $t3
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	RTPS
	bnez	$t9, .L3
	nop
	cfc2	$t0, $31
	cfc2	$t0, $31
	li	$at, 0x7f87e000
	and	$t0, $t0, $at
	bnez	$t0, .L5
	nop
.L3:
	NCLIP
	bnez	$t8, .L4
	nop
	mfc2	$t1, $24
	bgtz	$t5, .L4
	nop
	bgtz	$t1, .L4
	nop
	b	.L5
	nop
.L4:
	mfc2	$t1, $17
	mfc2	$t2, $18
	mfc2	$t3, $19
	mfc2	$t4, $19
	AVSZ4
	slt	$at, $t7, $t1
	beqz	$at, .L5
	nop
	slt	$at, $t7, $t2
	beqz	$at, .L5
	nop
	slt	$at, $t7, $t3
	beqz	$at, .L5
	nop
	slt	$at, $t7, $t4
	beqz	$at, .L5
	nop
	mfc2	$t0, $7
	lw	$t4, GsCLIP3far
	sw	$t0, 0($a0)
	slt	$at, $t0, $t4
	beqz	$at, .L5
	nop
	li	$v0, 0x1
	jr	$ra
	nop
.L5:
	li	$v0, 0
	jr	$ra
	nop
	nop
	nop
	nop
	.set	at
	.end	gte_scope_tf4_B
	.set	reorder
