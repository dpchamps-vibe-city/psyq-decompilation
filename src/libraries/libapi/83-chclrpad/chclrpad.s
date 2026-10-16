/* LIBAPI.LIB, member CHCLRPAD.OBJ (hand-written assembly)
 *
 * _remove_ChgclrPAD: no prototype in the SDK headers.
 */
	.text
	.align	4

	.globl	_remove_ChgclrPAD
	.ent	_remove_ChgclrPAD
_remove_ChgclrPAD:
	sw	$ra, B_000000E0
	jal	EnterCriticalSection
	li	$t1, 0x57
	li	$t2, 0xB0
	jalr	$t2
	li	$t2, 0x9
	lw	$v0, 0x16C($v0)
	addi	$v1, $v0, 0x62C
.L1:
	sw	$zero, 0($v1)
	addiu	$v1, $v1, 0x4
	addiu	$t2, $t2, -0x1
	bnez	$t2, .L1
	jal	FlushCache
	jal	ExitCriticalSection
	lw	$ra, B_000000E0
	jr	$ra
	.end	_remove_ChgclrPAD

	.bss
	.align	4
B_000000E0:
	.space	0x10
