/* LIBGTE.LIB, member TMD_5.OBJ (hand-written assembly)
 *
 * gte_flat3: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	gte_flat3
	.ent	gte_flat3
gte_flat3:
	.set	noat
	lw	$t8, GsLIOFF
	nop
	bnez	$t8, .L1
	nop
	lw	$t0, 0x8($a0)
	nop
	andi	$t0, $t0, 0xFFFF
	sll	$t0, $t0, 3
	add	$a1, $a1, $t0
	lwc2	$6, 0x4($a0)
	lwc2	$0, 0($a1)
	lwc2	$1, 0x4($a1)
	lw	$t7, 0($a3)
	NCCS
	li	$at, 0xffffff
	and	$a2, $a2, $at
	li	$at, 0x4000000
	or	$a2, $a2, $at
	sw	$a2, 0($t7)
	addi	$v0, $t7, 0x14
	lw	$t0, GsTON
	mfc2	$t1, $22
	mfc2	$t1, $22
	swc2	$12, 0x8($t7)
	swc2	$13, 0xC($t7)
	swc2	$14, 0x10($t7)
	sll	$t0, $t0, 25
	or	$t1, $t1, $t0
	sw	$t1, 0x4($t7)
	sw	$v0, 0($a3)
	nop
	jr	$ra
	nop
.L1:
	lw	$t7, 0($a3)
	li	$at, 0xffffff
	and	$a2, $a2, $at
	li	$at, 0x4000000
	or	$a2, $a2, $at
	sw	$a2, 0($t7)
	lw	$t0, GsTON
	swc2	$12, 0x8($t7)
	swc2	$13, 0xC($t7)
	swc2	$14, 0x10($t7)
	sll	$t0, $t0, 25
	lw	$t1, 0x4($a0)
	li	$at, 0xffffff
	and	$t1, $t1, $at
	li	$at, 0x20000000
	or	$t1, $t1, $at
	or	$t1, $t1, $t0
	sw	$t1, 0x4($t7)
	addi	$v0, $t7, 0x14
	sw	$v0, 0($a3)
	jr	$ra
	nop
	nop
	nop
	nop
	.set	at
	.end	gte_flat3
	.set	reorder
