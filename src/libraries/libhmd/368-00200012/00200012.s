/* LIBHMD.LIB, member 00200012.OBJ (hand-written assembly)
 *
 * u_long *GsU_00200012(GsARGUNIT *);
 *
 * HMD primitive driver for unit type 0x00200012: semi-trans colored flat quad (no define in libhmd.h; read from the flag bits).
 *
 * Register use:
 *   a0  GsARGUNIT *
 *   v0  result (u_long *)
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsU_00200012
	.ent	GsU_00200012
GsU_00200012:
	.set	noat
	lw	$a3, 0($a0)
	lw	$t9, 0x4($a0)
	lw	$t8, 0($a3)
	lw	$t7, 0x8($a0)
	addiu	$a3, $a3, 0x4
	lw	$a2, 0($a3)
	lw	$a1, 0x14($a0)
	sll	$a2, $a2, 2
	srl	$t8, $t8, 16
	beqz	$t8, .L3
	addu	$a3, $a1, $a2
	lw	$t0, 0x4($t9)
	lw	$t1, 0xC($a0)
	addiu	$v0, $a0, 0x10
	lw	$t9, 0($v0)
	lw	$t2, 0x10($a3)
	lw	$t3, 0x14($a3)
	lw	$a1, 0x18($a0)
	lw	$a2, 0x1C($a0)
	srl	$t4, $t2, 16
	sll	$t4, $t4, 3
	addu	$t4, $t4, $a1
.L1:
	lwc2	$0, 0($t4)
	lwc2	$1, 0x4($t4)
	sll	$t5, $t3, 16
	srl	$t5, $t5, 13
	addu	$t5, $t5, $a1
	lwc2	$2, 0($t5)
	lwc2	$3, 0x4($t5)
	srl	$t5, $t3, 16
	sll	$t5, $t5, 3
	addu	$t5, $t5, $a1
	lwc2	$4, 0($t5)
	lwc2	$5, 0x4($t5)
	nop
	sll	$t5, $t2, 16
	RTPT
	srl	$t5, $t5, 13
	addu	$t5, $t5, $a2
	lhu	$v1, 0x18($a3)
	lw	$t2, 0($a3)
	lw	$t3, 0x4($a3)
	lw	$t4, 0x8($a3)
	li	$at, 0x2000000
	or	$t2, $t2, $at
	mtc2	$t2, $6
	sll	$v1, $v1, 3
	addu	$v1, $v1, $a1
	lw	$t2, 0xC($a3)
	addiu	$a3, $a3, 0x1C
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	NCLIP
	lwc2	$0, 0($v1)
	lwc2	$1, 0x4($v1)
	mfc2	$v0, $24
	nop
	blez	$v0, .L2
	nop
	swc2	$12, 0x8($t9)
	swc2	$13, 0x10($t9)
	swc2	$14, 0x18($t9)
	nop
	nop
	nop
	RTPS
	cfc2	$v0, $31
	nop
	bltz	$v0, .L2
	nop
	AVSZ4
	lwc2	$0, 0($t5)
	lwc2	$1, 0x4($t5)
	mfc2	$t6, $7
	nop
	nop
	NCCS
	subu	$t6, $t6, $t1
	srlv	$t6, $t6, $t7
	andi	$t6, $t6, 0xFFFF
	sll	$t6, $t6, 2
	addu	$t6, $t6, $t0
	lw	$t5, 0($t6)
	li	$v0, 0x8000000
	sll	$v1, $t5, 8
	srl	$v1, $v1, 8
	or	$v0, $v0, $v1
	sw	$v0, 0($t9)
	nop
	xor	$v0, $t9, $t5
	sll	$v1, $v0, 8
	srl	$v0, $v1, 8
	xor	$v1, $v0, $t5
	sw	$v1, 0($t6)
	swc2	$22, 0x4($t9)
	mtc2	$t3, $6
	nop
	nop
	NCCS
	swc2	$22, 0xC($t9)
	mtc2	$t4, $6
	nop
	nop
	NCCS
	swc2	$22, 0x14($t9)
	mtc2	$t2, $6
	nop
	nop
	NCCS
	swc2	$14, 0x20($t9)
	swc2	$22, 0x1C($t9)
	addiu	$t9, $t9, 0x24
.L2:
	lw	$t2, 0x10($a3)
	lw	$t3, 0x14($a3)
	srl	$t4, $t2, 16
	sll	$t4, $t4, 3
	addu	$t4, $t4, $a1
	addiu	$t8, $t8, -0x1
	bnez	$t8, .L1
	nop
.L3:
	lw	$v0, 0($a0)
	lui	$at, %hi(GsOUT_PACKET_P)
	sw	$t9, %lo(GsOUT_PACKET_P)($at)
	addiu	$v0, $v0, 0x8
	jr	$ra
	nop
	.set	at
	.end	GsU_00200012
	.set	reorder
