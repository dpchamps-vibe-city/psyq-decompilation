/* LIBGTE.LIB, member NMD_13.OBJ (hand-written assembly)
 *
 * RotNMD_SV_F4: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	RotNMD_SV_F4
	.ent	RotNMD_SV_F4
RotNMD_SV_F4:
	.set	noat
	lhu	$t0, 0($a0)
	addi	$a0, $a0, 0x4
	lw	$t6, 0x14($sp)
	lw	$t4, 0x10($sp)
	lw	$t7, 0x30($a0)
	lw	$t8, 0x34($a0)
	lw	$t9, 0x38($a0)
	lw	$v1, 0x3C($a0)
	add	$t7, $t7, $a1
	add	$t8, $t8, $a1
	add	$t9, $t9, $a1
	add	$v1, $v1, $a1
.L1:
	lwc2	$0, 0($t7)
	lwc2	$1, 0x4($t7)
	lwc2	$2, 0($t8)
	lwc2	$3, 0x4($t8)
	lwc2	$4, 0($t9)
	lwc2	$5, 0x4($t9)
	nop
	RTPT
	move	$t3, $a0
	addi	$a0, $a0, 0x40
	lw	$t7, 0x30($a0)
	lw	$t8, 0x34($a0)
	addu	$t7, $t7, $a1
	lw	$t9, 0x38($a0)
	addu	$t8, $t8, $a1
	addu	$t9, $t9, $a1
	cfc2	$t1, $31
	nop
	li	$at, 0x60000
	and	$t1, $t1, $at
	li	$at, 0x40000
	beq	$t1, $at, .L4
	bnez	$t6, .L2
	NCLIP
	mfc2	$t1, $24
	blez	$t1, .L4
.L2:
	beqz	$t4, .L3
	addi	$t3, $t3, 0x18
.L3:
	swc2	$12, 0x8($t3)
	swc2	$13, 0xC($t3)
	swc2	$14, 0x10($t3)
	lwc2	$0, 0($v1)
	lwc2	$1, 0x4($v1)
	nop
	RTPS
	swc2	$14, 0x14($t3)
	AVSZ4
	li	$t2, 0xE
	sub	$t2, $t2, $a3
	mfc2	$t1, $7
	srav	$t1, $t1, $t2
	sll	$t1, $t1, 2
	add	$t5, $a2, $t1
	lw	$t1, 0($t5)
	li	$at, 0xffffff
	and	$t3, $t3, $at
	li	$at, 0x5000000
	or	$t1, $t1, $at
	sw	$t1, 0($t3)
	sw	$t3, 0($t5)
.L4:
	lw	$v1, 0x3C($a0)
	addi	$t0, $t0, -0x1
	addu	$v1, $v1, $a1
	bgtz	$t0, .L1
	jr	$ra
	.set	at
	.end	RotNMD_SV_F4
