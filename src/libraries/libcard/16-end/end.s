/* LIBCARD.LIB, member END.OBJ (hand-written assembly)
 *
 * _ExitCard: no prototype in the SDK headers.
 */
	.text
	.align	4

	.globl	_ExitCard
	.ent	_ExitCard
_ExitCard:
	sw	$ra, B_000000F0
	jal	EnterCriticalSection
	li	$t1, 0x56
	li	$t2, 0xB0
	jalr	$t2
	lw	$v0, 0x18($v0)
	la	$t2, _ExitCard + 0x70
	la	$t1, _ExitCard + 0x7C
.L1:
	lw	$v1, 0($t2)
	sw	$v1, 0x70($v0)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L1
	jal	FlushCache
	jal	ExitCriticalSection
	lw	$ra, B_000000F0
	jr	$ra
	.end	_ExitCard
	nop
	nop
	nop
	nop

	.bss
	.align	4
B_000000F0:
	.space	0x10
