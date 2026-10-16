/* LIBGTE.LIB, member TMD_12.OBJ (hand-written assembly)
 *
 * gte_texture_gouraud_fog3: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	gte_texture_gouraud_fog3
	.ent	gte_texture_gouraud_fog3
gte_texture_gouraud_fog3:
	.set	noat
	lw	$t8, GsLIOFF
	nop
	bnez	$t8, .L1
	nop
	li	$t0, 0x34808080
	mtc2	$t0, $6
	lw	$t0, 0x10($a0)
	nop
	andi	$t0, $t0, 0xFFFF
	sll	$t0, $t0, 3
	add	$t3, $a1, $t0
	lwc2	$0, 0($t3)
	lwc2	$1, 0x4($t3)
	lw	$t0, 0x14($a0)
	nop
	andi	$t0, $t0, 0xFFFF
	sll	$t0, $t0, 3
	add	$t3, $a1, $t0
	lwc2	$2, 0($t3)
	lwc2	$3, 0x4($t3)
	lw	$t0, 0x18($a0)
	nop
	andi	$t0, $t0, 0xFFFF
	sll	$t0, $t0, 3
	add	$t3, $a1, $t0
	lwc2	$4, 0($t3)
	lwc2	$5, 0x4($t3)
	NCDT
	lw	$t7, 0($a3)
	li	$at, 0xffffff
	and	$t0, $a2, $at
	li	$at, 0x9000000
	or	$t0, $t0, $at
	sw	$t0, 0($t7)
	lw	$t1, 0x4($a0)
	lw	$t2, 0x8($a0)
	lw	$t3, 0xC($a0)
	sw	$t1, 0xC($t7)
	sw	$t2, 0x18($t7)
	sw	$t3, 0x24($t7)
	addi	$v0, $t7, 0x28
	sw	$v0, 0($a3)
	lw	$t0, GsTON
	mfc2	$t1, $20
	mfc2	$t1, $20
	mfc2	$t2, $21
	mfc2	$t3, $22
	swc2	$12, 0x8($t7)
	swc2	$13, 0x14($t7)
	swc2	$14, 0x20($t7)
	sll	$t0, $t0, 25
	or	$t1, $t1, $t0
	sw	$t1, 0x4($t7)
	sw	$t2, 0x10($t7)
	sw	$t3, 0x1C($t7)
	jr	$ra
.L1:
	lw	$t7, 0($a3)
	li	$at, 0xffffff
	and	$a2, $a2, $at
	li	$at, 0x7000000
	or	$a2, $a2, $at
	sw	$a2, 0($t7)
	swc2	$12, 0x8($t7)
	swc2	$13, 0x10($t7)
	swc2	$14, 0x18($t7)
	lw	$t1, 0x4($a0)
	lw	$t2, 0x8($a0)
	lw	$t3, 0xC($a0)
	sw	$t1, 0xC($t7)
	sw	$t2, 0x14($t7)
	sw	$t3, 0x1C($t7)
	lw	$t0, GsTON
	li	$t1, 0x25808080
	sll	$t0, $t0, 25
	or	$t1, $t1, $t0
	sw	$t1, 0x4($t7)
	addi	$v0, $t7, 0x20
	sw	$v0, 0($a3)
	jr	$ra
	nop
	nop
	.set	at
	.end	gte_texture_gouraud_fog3
	.set	reorder
