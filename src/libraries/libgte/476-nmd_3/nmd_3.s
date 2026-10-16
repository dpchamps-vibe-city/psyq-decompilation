/* LIBGTE.LIB, member NMD_3.OBJ (hand-written assembly)
 *
 * RotNMD_FT3: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotNMD_FT3
	.ent	RotNMD_FT3
RotNMD_FT3:
	.set	noat
	lhu	$t0, 0($a0)
	addi	$a0, $a0, 0x4
	lw	$t6, 0x10($sp)
.L1:
	lwc2	$0, 0x40($a0)
	lwc2	$1, 0x44($a0)
	lwc2	$2, 0x48($a0)
	lwc2	$3, 0x4C($a0)
	lwc2	$4, 0x50($a0)
	lwc2	$5, 0x54($a0)
	nop
	RTPT
	move	$t3, $a0
	beqz	$a3, .L2
	nop
	addi	$t3, $t3, 0x20
.L2:
	cfc2	$t1, $31
	nop
	li	$at, 0x60000
	and	$t1, $t1, $at
	li	$at, 0x40000
	beq	$t1, $at, .L5
	nop
	NCLIP
	beqz	$t6, .L3
	nop
	mfc2	$t1, $24
	nop
	beqz	$t1, .L5
	nop
	b	.L4
	nop
.L3:
	mfc2	$t1, $24
	nop
	blez	$t1, .L5
	nop
.L4:
	swc2	$12, 0x8($t3)
	swc2	$13, 0x10($t3)
	swc2	$14, 0x18($t3)
	AVSZ3
	li	$t2, 0xE
	sub	$t2, $t2, $a2
	mfc2	$t1, $7
	nop
	srav	$t1, $t1, $t2
	sll	$t1, $t1, 2
	add	$t5, $a1, $t1
	lw	$t4, 0($t5)
	li	$at, 0xffffff
	and	$t3, $t3, $at
	li	$at, 0x7000000
	or	$t4, $t4, $at
	sw	$t4, 0($t3)
	sw	$t3, 0($t5)
.L5:
	addi	$a0, $a0, 0x58
	slti	$at, $t0, 0x2
	beqz	$at, .L1
	addi	$t0, $t0, -0x1
	jr	$ra
	nop
	.set	at
	.end	RotNMD_FT3
	.set	reorder
