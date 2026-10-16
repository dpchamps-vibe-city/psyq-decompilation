/* LIBGTE.LIB, member PMD_1.OBJ (hand-written assembly)
 *
 * void RotPMD_F3(long *pa, u_long *ot, int otlen, int id, int backc);
 *
 * Register use:
 *   a0        pa
 *   a1        ot
 *   a2        otlen
 *   a3        id
 *   0x10(sp)  backc
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	RotPMD_F3
	.ent	RotPMD_F3
RotPMD_F3:
	.set	noat
	lhu	$t0, 0($a0)
	addi	$a0, $a0, 0x4
	lw	$t6, 0x10($sp)
	lwc2	$0, 0x28($a0)
	lwc2	$1, 0x2C($a0)
	lwc2	$2, 0x30($a0)
	lwc2	$3, 0x34($a0)
	lwc2	$4, 0x38($a0)
	lwc2	$5, 0x3C($a0)
	li	$t2, 0xE
	sub	$t2, $t2, $a2
	move	$t3, $a0
	addi	$t3, $t3, -0x40
	beqz	$a3, .L1
	addi	$t3, $t3, 0x14
.L1:
	RTPT
	addi	$a0, $a0, 0x40
	addi	$t3, $t3, 0x40
	lwc2	$0, 0x28($a0)
	lwc2	$1, 0x2C($a0)
	lwc2	$2, 0x30($a0)
	lwc2	$3, 0x34($a0)
	lwc2	$4, 0x38($a0)
	lwc2	$5, 0x3C($a0)
	cfc2	$t1, $31
	nop
	li	$at, 0x60000
	and	$t1, $t1, $at
	bnez	$t1, .L3
	bnez	$t6, .L2
	NCLIP
	mfc2	$t1, $24
	blez	$t1, .L3
.L2:
	swc2	$12, 0x8($t3)
	swc2	$13, 0xC($t3)
	swc2	$14, 0x10($t3)
	nop
	AVSZ3
	mfc2	$t1, $7
	srav	$t1, $t1, $t2
	sll	$t1, $t1, 2
	add	$t5, $a1, $t1
	lw	$t4, 0($t5)
	li	$at, 0xffffff
	and	$t1, $t3, $at
	li	$at, 0x4000000
	or	$t4, $t4, $at
	sw	$t4, 0($t3)
	sw	$t1, 0($t5)
.L3:
	slti	$at, $t0, 0x2
	addi	$t0, $t0, -0x1
	beqz	$at, .L1
	jr	$ra
	.set	at
	.end	RotPMD_F3
