/* LIBGTE.LIB, member PMD_6.OBJ (hand-written assembly)
 *
 * void RotPMD_G4(long *pa, u_long *ot, int otlen, int id, int backc);
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
	.set	noreorder

	.globl	RotPMD_G4
	.ent	RotPMD_G4
RotPMD_G4:
	.set	noat
	lhu	$t0, 0($a0)
	addi	$a0, $a0, 0x4
	lw	$t6, 0x10($sp)
.L1:
	lwc2	$0, 0x48($a0)
	lwc2	$1, 0x4C($a0)
	lwc2	$2, 0x50($a0)
	lwc2	$3, 0x54($a0)
	lwc2	$4, 0x58($a0)
	lwc2	$5, 0x5C($a0)
	nop
	RTPT
	move	$t3, $a0
	beqz	$a3, .L2
	nop
	addi	$t3, $t3, 0x24
.L2:
	cfc2	$t1, $31
	nop
	li	$at, 0x60000
	and	$t1, $t1, $at
	bnez	$t1, .L4
	nop
	bnez	$t6, .L3
	nop
	NCLIP
	mfc2	$t1, $24
	nop
	blez	$t1, .L4
	nop
.L3:
	swc2	$12, 0x8($t3)
	swc2	$13, 0x10($t3)
	swc2	$14, 0x18($t3)
	lwc2	$0, 0x60($a0)
	lwc2	$1, 0x64($a0)
	nop
	RTPS
	swc2	$14, 0x20($t3)
	nop
	AVSZ4
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
	li	$at, 0x8000000
	or	$t4, $t4, $at
	sw	$t4, 0($t3)
	sw	$t3, 0($t5)
.L4:
	addi	$a0, $a0, 0x68
	slti	$at, $t0, 0x2
	beqz	$at, .L1
	addi	$t0, $t0, -0x1
	jr	$ra
	nop
	nop
	.set	at
	.end	RotPMD_G4
	.set	reorder
