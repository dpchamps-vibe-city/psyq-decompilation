/* LIBCARD.LIB, member PATCH.OBJ (hand-written assembly)
 *
 * _patch_card_info: no prototype in the SDK headers.
 *
 * _patch_card: no prototype in the SDK headers.
 *
 * _patch_card2: no prototype in the SDK headers.
 *
 * _copy_memcard_patch: no prototype in the SDK headers.
 */
	.text
	.align	4

	.globl	_patch_card_info
	.ent	_patch_card_info
_patch_card_info:
	sw	$ra, B_00000290
	li	$t1, 0x57
	li	$t2, 0xB0
	jalr	$t2
	li	$t2, 0x9
	lw	$v0, 0x16C($v0)
	addi	$v1, $v0, 0x1988
	sw	$zero, 0($v1)
	jal	FlushCache
	lw	$ra, B_00000290
	jr	$ra
	lhu	$t7, 0xA($v1)
	lui	$t0, 0
	or	$t8, $t7, $v0
	ori	$t9, $t8, 0x12
	sh	$t9, 0xA($v1)
	li	$t0, 0x28
.L1:
	addiu	$t0, $t0, -0x1
	bnez	$t0, .L1
	jr	$ra
	lw	$v0, 0x1074($v1)
	andi	$v0, $v0, 0x80
	beqz	$v0, .L3
.L2:
	lw	$v0, 0x1044($v1)
	andi	$v0, $v0, 0x80
	bnez	$v0, .L2
	lui	$v0, 0x1
	lw	$v0, -0x2004($v0)
	jr	$v0
.L3:
	jr	$ra
T_00000124:
	lui	$v0, 0xA001
	addiu	$v0, $v0, -0x2054
	jr	$v0
	nop
T_00000138:
	lui	$t0, 0xA001
	addiu	$t0, $t0, -0x2080
	jalr	$t0
	.end	_patch_card_info
	nop

	.globl	_patch_card
	.ent	_patch_card
_patch_card:
	.set	noat
	lui	$at, %hi(B_00000290)
	sw	$ra, %lo(B_00000290)($at)
	jal	EnterCriticalSection
	li	$t1, 0x56
	li	$t2, 0xB0
	jalr	$t2
	lw	$v0, 0x18($v0)
	lw	$v1, 0x70($v0)
	andi	$t1, $v1, 0xFFFF
	sll	$t1, $t1, 16
	lw	$v1, 0x74($v0)
	andi	$t2, $v1, 0xFFFF
	addu	$v1, $t1, $t2
	addiu	$v0, $v1, 0x28
	la	$t2, T_00000124
	la	$t1, T_00000138
.L4:
	lw	$v1, 0($t2)
	sw	$v1, 0($v0)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L4
	lui	$at, 0x1
	sw	$v0, -0x2004($at)
	jal	FlushCache
	lw	$ra, B_00000290
	jr	$ra
	.set	at
	.end	_patch_card

	.globl	_patch_card2
	.ent	_patch_card2
_patch_card2:
	sw	$ra, B_00000290
	jal	EnterCriticalSection
	li	$t1, 0x57
	li	$t2, 0xB0
	jalr	$t2
	lw	$v0, 0x16C($v0)
	lw	$v1, 0x9C8($v0)
	la	$t2, T_00000138
	la	$t1, _patch_card
.L5:
	lw	$t0, 0($t2)
	sw	$t0, 0x9C8($v0)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L5
	jal	FlushCache
	lw	$ra, B_00000290
	jr	$ra
	.end	_patch_card2

	.globl	_copy_memcard_patch
	.ent	_copy_memcard_patch
_copy_memcard_patch:
	li	$v0, 0xDF80
	la	$t2, _patch_card_info + 0x44
	la	$t1, T_00000124
.L6:
	lw	$v1, 0($t2)
	sw	$v1, 0($v0)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L6
	jr	$ra
	.end	_copy_memcard_patch

	.bss
	.align	4
B_00000290:
	.space	0x10
