/* LIBAPI.LIB, member PATCH.OBJ (hand-written assembly)
 *
 * void EnablePAD(void);
 *
 * void DisablePAD(void);
 *
 * _patch_pad: no prototype in the SDK headers.
 */
	.text
	.align	4

	.globl	EnablePAD
	.ent	EnablePAD
EnablePAD:
	lw	$t1, B_00000118
	jr	$t1
	.end	EnablePAD

	.globl	DisablePAD
	.ent	DisablePAD
DisablePAD:
	lw	$t1, B_0000011C
	jr	$t1
	.end	DisablePAD

	.globl	_patch_pad
	.ent	_patch_pad
_patch_pad:
	sw	$ra, B_00000110
	jal	EnterCriticalSection
	li	$t1, 0x57
	li	$t2, 0xB0
	jalr	$t2
	lw	$v0, 0x16C($v0)
	li	$t1, 0xB
	addi	$v1, $v0, 0x884
	sw	$v1, B_00000118
	addi	$v1, $v0, 0x894
	sw	$v1, B_0000011C
.L1:
	sw	$zero, 0x594($v0)
	addiu	$v0, $v0, 0x4
	addiu	$t1, $t1, -0x1
	bnez	$t1, .L1
	jal	FlushCache
	lw	$ra, B_00000110
	jr	$ra
	.end	_patch_pad

	.bss
	.align	4
B_00000110:
	.space	0x08
B_00000118:
	.space	0x04
B_0000011C:
	.space	0x04
