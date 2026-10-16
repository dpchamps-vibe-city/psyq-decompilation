/* LIBGTE.LIB, member PMD_12.OBJ (hand-written assembly)
 *
 * void RotPMD_SV_GT3(long *pa, long *va, u_long *ot, int otlen, int id,
 *                    int backc);
 *
 * Register use:
 *   a0        pa
 *   a1        va
 *   a2        ot
 *   a3        otlen
 *   0x10(sp)  id
 *   0x14(sp)  backc
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotPMD_SV_GT3
	.ent	RotPMD_SV_GT3
RotPMD_SV_GT3:
	.set	noat
	lhu	$t0, 0($a0)
	addi	$a0, $a0, 0x4
	lw	$t6, 0x14($sp)
	lw	$t4, 0x10($sp)
	lw	$t7, 0x50($a0)
	lw	$t8, 0x54($a0)
	lw	$t9, 0x58($a0)
	add	$t7, $t7, $a1
	add	$t8, $t8, $a1
	add	$t9, $t9, $a1
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
	addi	$a0, $a0, 0x5C
	lw	$t7, 0x50($a0)
	lw	$t8, 0x54($a0)
	addu	$t7, $t7, $a1
	lw	$t9, 0x58($a0)
	addu	$t8, $t8, $a1
	addu	$t9, $t9, $a1
	cfc2	$t1, $31
	nop
	li	$at, 0x60000
	and	$t1, $t1, $at
	bnez	$t1, .L5
	nop
	NCLIP
	beqz	$t4, .L2
	nop
	addi	$t3, $t3, 0x28
.L2:
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
	swc2	$13, 0x14($t3)
	swc2	$14, 0x20($t3)
	nop
	AVSZ3
	li	$t2, 0xE
	sub	$t2, $t2, $a3
	mfc2	$t1, $7
	nop
	srav	$t1, $t1, $t2
	sll	$t1, $t1, 2
	add	$t5, $a2, $t1
	lw	$t1, 0($t5)
	li	$at, 0xffffff
	and	$t3, $t3, $at
	li	$at, 0x9000000
	or	$t1, $t1, $at
	sw	$t1, 0($t3)
	sw	$t3, 0($t5)
.L5:
	slti	$at, $t0, 0x2
	beqz	$at, .L1
	addi	$t0, $t0, -0x1
	jr	$ra
	nop
	nop
	nop
	nop
	.set	at
	.end	RotPMD_SV_GT3
	.set	reorder
