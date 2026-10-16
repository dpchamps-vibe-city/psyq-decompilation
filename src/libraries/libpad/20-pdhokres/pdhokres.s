/* LIBPAD.LIB, member PDHOKRES.OBJ (hand-written assembly)
 *
 * _padGunInitHook: no prototype in the SDK headers.
 *
 * _padGunExitHook: no prototype in the SDK headers.
 *
 * _padGetHitCount: no prototype in the SDK headers.
 *
 * _padClrHitCount: no prototype in the SDK headers.
 */
	.text
	.align	4

	.globl	_padGunInitHook
	.ent	_padGunInitHook
_padGunInitHook:
	.set	noat
	lui	$at, %hi(B_0000031C)
	sw	$ra, %lo(B_0000031C)($at)
	lui	$at, %hi(B_00000314)
	sw	$a0, %lo(B_00000314)($at)
	lui	$at, %hi(B_00000318)
	sw	$a1, %lo(B_00000318)($at)
	jal	EnterCriticalSection
	li	$t1, 0x56
	li	$t2, 0xB0
	jalr	$t2
	lw	$v0, 0x18($v0)
	la	$t2, _padClrHitCount + 0xC
	la	$t1, _padClrHitCount + 0x18
.L1:
	lw	$v1, 0($t2)
	sw	$v1, 0x80($v0)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L1
	jal	FlushCache
	lw	$ra, B_0000031C
	jr	$ra
	.set	at
	.end	_padGunInitHook

	.globl	_padGunExitHook
	.ent	_padGunExitHook
_padGunExitHook:
	sw	$ra, B_0000031C
	jal	EnterCriticalSection
	li	$t1, 0x56
	li	$t2, 0xB0
	jalr	$t2
	lw	$v0, 0x18($v0)
	la	$t2, _padClrHitCount + 0x1C
	la	$t1, _padClrHitCount + 0x28
.L2:
	lw	$v1, 0($t2)
	sw	$v1, 0x80($v0)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L2
	jal	FlushCache
	jal	ExitCriticalSection
	lw	$ra, B_0000031C
	jr	$ra
	.end	_padGunExitHook

	.globl	_padGetHitCount
	.ent	_padGetHitCount
_padGetHitCount:
	lw	$v0, B_00000310
	jr	$ra
	.end	_padGetHitCount

	.globl	_padClrHitCount
	.ent	_padClrHitCount
_padClrHitCount:
	.set	noat
	lui	$at, %hi(B_00000310)
	sw	$zero, %lo(B_00000310)($at)
	jr	$ra
	la	$v0, _padClrHitCount + 0x2C
	jalr	$v0
	nop
	nop
	nop
	nop
	lui	$v1, 0x1F80
	lw	$v0, B_00000314
	li	$at, 0x1
	beq	$v0, $at, .L3
	lw	$v0, 0x2030($v1)
	andi	$v0, $v0, 0x2
	beqz	$v0, .L8
	li	$v0, 0x2
	sw	$v0, 0x2030($v1)
.L3:
	lw	$v0, 0x1070($v1)
	andi	$v0, $v0, 0x400
	beqz	$v0, .L8
	li	$v0, -0x401
	sw	$v0, 0x1070($v1)
	lw	$v0, 0x1074($v1)
	andi	$v0, $v0, 0x400
	beqz	$v0, .L8
	lw	$v0, 0x10f0($v1)
	lui	$at, %hi(B_00000320)
	sw	$v0, %lo(B_00000320)($at)
	sw	$zero, 0x10f0($v1)
.L4:
	li	$k0, 0x200
.L5:
	lw	$v0, 0x1070($v1)
	andi	$v0, $v0, 0x400
	beqz	$k0, .L7
	addi	$k0, $k0, -0x1
	beqz	$v0, .L5
	lh	$v0, 0x1100($v1)
	lw	$k0, B_00000310
	li	$at, 0x2
	mult	$k0, $at
	mflo	$k0
	lui	$at, %hi(_padGunPosHbuf)
	addu	$at, $at, $k0
	sh	$v0, %lo(_padGunPosHbuf)($at)
.L6:
	lh	$v0, 0x1110($v1)
	lh	$at, 0x1110($v1)
	bne	$v0, $at, .L6
	lui	$at, %hi(_padGunPosVbuf)
	addu	$at, $at, $k0
	sh	$v0, %lo(_padGunPosVbuf)($at)
	li	$v0, 0x2
	sw	$v0, 0x2030($v1)
	li	$v0, -0x401
	sw	$v0, 0x1070($v1)
	lw	$v0, B_00000310
	addi	$v0, $v0, 0x1
	lui	$at, %hi(B_00000310)
	sw	$v0, %lo(B_00000310)($at)
	lw	$k0, B_00000318
	slt	$at, $v0, $k0
	bnez	$at, .L4
.L7:
	lw	$v0, 0x1074($v1)
	li	$at, -0x401
	and	$v0, $v0, $at
	sw	$v0, 0x1074($v1)
	lw	$v0, B_00000320
	sw	$v0, 0x10f0($v1)
	j	.L9
.L8:
	jr	$ra
.L9:
	li	$k0, 0x100
	lw	$k0, 0x8($k0)
	lw	$k0, 0($k0)
	addi	$k0, $k0, 0x8
	lw	$v0, 0x8($k0)
	lw	$v1, 0xC($k0)
	lw	$ra, 0x7C($k0)
	lw	$at, 0x4($k0)
	lw	$k0, 0x80($k0)
	nop
	rfe
	jr	$k0
	.set	at
	.end	_padClrHitCount

	.bss
	.align	4
B_00000310:
	.space	0x04
B_00000314:
	.space	0x04
B_00000318:
	.space	0x04
B_0000031C:
	.space	0x04
B_00000320:
	.space	0x10
	.comm	_padGunPosHbuf, 96, 8
	.comm	_padGunPosVbuf, 96, 8
