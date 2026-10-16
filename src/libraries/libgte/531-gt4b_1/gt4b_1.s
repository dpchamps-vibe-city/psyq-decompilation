/* LIBGTE.LIB, member GT4B_1.OBJ (hand-written assembly)
 *
 * u_long *GsTMDfastTNG4B(TMD_P_TNG4 *primtop, SVECTOR *vertop, POLY_GT4 *s,
 *                        u_long n, u_long shift, GsOT *otp);
 *   (declared only inside a comment block of libgte.h)
 *
 * Register use:
 *   a0        primtop
 *   a1        vertop
 *   a2        s
 *   a3        n
 *   0x10(sp)  shift
 *   0x14(sp)  otp
 *   v0        result (u_long *)
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsTMDfastTNG4B
	.ent	GsTMDfastTNG4B
GsTMDfastTNG4B:
	lw	$t9, 0x14($sp)
	lw	$t7, 0x10($sp)
	beqz	$a3, .L3
	lw	$t0, 0x4($t9)
	lw	$t1, 0x8($t9)
	lw	$t2, 0x24($a0)
	lhu	$t4, 0x28($a0)
	srl	$t3, $t2, 16
	sll	$t2, $t2, 16
	srl	$t2, $t2, 13
	sll	$t3, $t3, 3
	sll	$t4, $t4, 3
	addu	$t2, $t2, $a1
	addu	$t3, $t3, $a1
	addu	$t4, $t4, $a1
.L1:
	lwc2	$0, 0($t2)
	lwc2	$1, 0x4($t2)
	lwc2	$2, 0($t3)
	lwc2	$3, 0x4($t3)
	lwc2	$4, 0($t4)
	lwc2	$5, 0x4($t4)
	nop
	RTPT
	lw	$v1, GsTON
	lb	$v0, 0x3($a0)
	sll	$v1, $v1, 1
	or	$v0, $v0, $v1
	lw	$v1, 0x14($a0)
	srl	$v0, $v0, 1
	sll	$v0, $v0, 25
	sll	$v1, $v1, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	mtc2	$v0, $20
	lwc2	$21, 0x18($a0)
	lwc2	$22, 0x1C($a0)
	lwc2	$6, 0x20($a0)
	lhu	$t5, 0x2A($a0)
	move	$v1, $a0
	addiu	$a0, $a0, 0x2C
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lw	$t2, 0x24($a0)
	lhu	$t4, 0x28($a0)
	srl	$t3, $t2, 16
	sll	$t2, $t2, 16
	srl	$t2, $t2, 13
	sll	$t3, $t3, 3
	sll	$t4, $t4, 3
	addu	$t2, $t2, $a1
	addu	$t3, $t3, $a1
	addu	$t4, $t4, $a1
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
	swc2	$12, 0x8($a2)
	swc2	$13, 0x14($a2)
	swc2	$14, 0x20($a2)
	nop
	RTPS
	lw	$t5, 0x4($v1)
	lw	$t6, 0x8($v1)
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	AVSZ4
	lw	$v0, 0xC($v1)
	sw	$t5, 0xC($a2)
	sw	$t6, 0x18($a2)
	sw	$v0, 0x24($a2)
	lw	$t5, 0x10($v1)
	mfc2	$t6, $7
	sw	$t5, 0x30($a2)
	swc2	$14, 0x2C($a2)
	swc2	$20, 0x4($a2)
	swc2	$21, 0x10($a2)
	swc2	$22, 0x1C($a2)
	swc2	$6, 0x28($a2)
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t5, 0($t6)
	li	$v0, 0xc000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($a2)
	xor	$v0, $a2, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	addiu	$a2, $a2, 0x34
.L2:
	addiu	$a3, $a3, -0x1
	bnez	$a3, .L1
	nop
.L3:
	move	$v0, $a2
	jr	$ra
	nop
	nop
	nop
	.end	GsTMDfastTNG4B
	.set	reorder
