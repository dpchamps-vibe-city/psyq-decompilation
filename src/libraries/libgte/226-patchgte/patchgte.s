/* LIBGTE.LIB, member PATCHGTE.OBJ (hand-written assembly)
 *
 * _patch_gte: no prototype in the SDK headers.
 */
	.text
	.align	4

	.globl	_patch_gte
	.ent	_patch_gte
_patch_gte:
	.set	noat
	lui	$at, %hi(B_00000150)
	sw	$ra, %lo(B_00000150)($at)
	jal	EnterCriticalSection
	li	$t1, 0x56
	li	$t2, 0xB0
	jalr	$t2
	lw	$v0, 0x18($v0)
	addiu	$v0, $v0, 0x28
	move	$t7, $v0
	la	$t2, _patch_gte + 0xAC
	la	$t1, _patch_gte + 0xC4
.L1:
	lw	$v1, 0($t2)
	lw	$t3, 0($v0)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$v1, $t3, .L3
	bne	$t2, $t1, .L1
	move	$v0, $t7
	la	$t2, _patch_gte + 0xC4
	la	$t1, _patch_gte + 0xDC
.L2:
	lw	$v1, 0($t2)
	sw	$v1, 0($v0)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L2
.L3:
	jal	FlushCache
	jal	ExitCriticalSection
	lw	$ra, B_00000150
	jr	$ra
	sw	$at, 0x4($k0)
	sw	$v0, 0x8($k0)
	sw	$v1, 0xC($k0)
	sw	$ra, 0x7C($k0)
	mfc0	$v1, $14
	nop
	sw	$at, 0x4($k0)
	sw	$v0, 0x8($k0)
	mfc0	$v0, $13
	sw	$v1, 0xC($k0)
	mfc0	$v1, $14
	sw	$ra, 0x7C($k0)
	.set	at
	.end	_patch_gte

	.bss
	.align	4
B_00000150:
	.space	0x10
