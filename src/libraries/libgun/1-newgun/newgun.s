/* LIBGUN.LIB, member NEWGUN.OBJ (hand-written assembly)
 *
 * _InitGun: no prototype in the SDK headers.
 *
 * _ExitGun: no prototype in the SDK headers.
 *
 * _check_gun_flag: no prototype in the SDK headers.
 *
 * _clear_gun_flag: no prototype in the SDK headers.
 *
 * read_gun_v: no prototype in the SDK headers.
 *
 * read_gun_h: no prototype in the SDK headers.
 */
	.text
	.align	4
	.set	noreorder

	.globl	_InitGun
	.ent	_InitGun
_InitGun:
	.set	noat
	lui	$at, %hi(.sbss + 0xD8)
	sw	$ra, %lo(.sbss + 0xD8)($at)
	lui	$at, %hi(.sbss + 0xD4)
	sw	$a0, %lo(.sbss + 0xD4)($at)
	lui	$at, %hi(.sbss + 0xDC)
	jal	EnterCriticalSection
	sw	$a1, %lo(.sbss + 0xDC)($at)
	li	$t2, 0xB0
	jalr	$t2
	li	$t1, 0x56
	lui	$t2, %hi(_clear_gun_flag + 0xC)
	lui	$t1, %hi(_clear_gun_flag + 0x1C)
	lw	$v0, 0x18($v0)
	addiu	$t2, $t2, %lo(_clear_gun_flag + 0xC)
	addiu	$t1, $t1, %lo(_clear_gun_flag + 0x1C)
.L1:
	lw	$v1, 0($t2)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L1
	sw	$v1, 0x7C($v0)
	jal	FlushCache
	nop
	lw	$ra, .sbss + 0xD8
	nop
	jr	$ra
	nop
	.set	at
	.end	_InitGun

	.globl	_ExitGun
	.ent	_ExitGun
_ExitGun:
	sw	$ra, .sbss + 0xD8
	jal	EnterCriticalSection
	nop
	li	$t2, 0xB0
	jalr	$t2
	li	$t1, 0x56
	lui	$t2, %hi(_clear_gun_flag + 0x20)
	lui	$t1, %hi(_clear_gun_flag + 0x2C)
	lw	$v0, 0x18($v0)
	addiu	$t2, $t2, %lo(_clear_gun_flag + 0x20)
	addiu	$t1, $t1, %lo(_clear_gun_flag + 0x2C)
.L2:
	lw	$v1, 0($t2)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L2
	sw	$v1, 0x7C($v0)
	jal	FlushCache
	nop
	jal	ExitCriticalSection
	nop
	lw	$ra, .sbss + 0xD8
	nop
	jr	$ra
	nop
	.end	_ExitGun

	.globl	_check_gun_flag
	.ent	_check_gun_flag
_check_gun_flag:
	lw	$v0, .sbss + 0xD0
	jr	$ra
	nop
	.end	_check_gun_flag

	.globl	_clear_gun_flag
	.ent	_clear_gun_flag
_clear_gun_flag:
	.set	noat
	lui	$at, %hi(.sbss + 0xD0)
	jr	$ra
	sw	$zero, %lo(.sbss + 0xD0)($at)
	la	$v0, read_gun_h + 0x14
	jalr	$v0
	nop
	nop
	nop
	nop
	nop
	nop
	.set	at
	.end	_clear_gun_flag

	.globl	read_gun_v
	.ent	read_gun_v
read_gun_v:
	lui	$v0, %hi(.sbss + 0x70)
	jr	$ra
	addiu	$v0, $v0, %lo(.sbss + 0x70)
	.end	read_gun_v

	.globl	read_gun_h
	.ent	read_gun_h
read_gun_h:
	.set	noat
	lui	$v0, %hi(.sbss + 0x10)
	jr	$ra
	addiu	$v0, $v0, %lo(.sbss + 0x10)
.L3:
	jr	$ra
	nop
	lw	$v0, .sbss + 0xD4
	li	$at, 0x1
	beq	$v0, $at, .L4
	lui	$v1, 0x1F80
	lw	$v0, 0x2030($v1)
	nop
	andi	$v0, $v0, 0x2
	beqz	$v0, .L3
	nop
	li	$v0, 0x2
	sw	$v0, 0x2030($v1)
.L4:
	lw	$v0, 0x1070($v1)
	nop
	andi	$v0, $v0, 0x400
	beqz	$v0, .L3
	nop
	li	$v0, -0x401
	sw	$v0, 0x1070($v1)
	lw	$v0, 0x1074($v1)
	nop
	andi	$v0, $v0, 0x400
	beqz	$v0, .L3
	nop
	lw	$v0, 0x10f0($v1)
	lui	$at, %hi(.sbss + 0xE0)
	sw	$v0, %lo(.sbss + 0xE0)($at)
	sw	$zero, 0x10f0($v1)
.L5:
	li	$k0, 0x200
.L6:
	lw	$v0, 0x1070($v1)
	beqz	$k0, .L8
	andi	$v0, $v0, 0x400
	beqz	$v0, .L6
	addi	$k0, $k0, -0x1
	lw	$k0, .sbss + 0xD0
	lh	$v0, 0x1100($v1)
	lui	$at, %hi(.sbss + 0x10)
	sll	$k0, $k0, 1
	addu	$at, $at, $k0
	sh	$v0, %lo(.sbss + 0x10)($at)
.L7:
	lh	$v0, 0x1110($v1)
	lh	$at, 0x1110($v1)
	nop
	bne	$v0, $at, .L7
	lui	$at, %hi(.sbss + 0x70)
	addu	$at, $at, $k0
	sh	$v0, %lo(.sbss + 0x70)($at)
	li	$v0, 0x2
	sw	$v0, 0x2030($v1)
	li	$v0, -0x401
	sw	$v0, 0x1070($v1)
	lw	$v0, .sbss + 0xD0
	lw	$k0, .sbss + 0xDC
	lui	$at, %hi(.sbss + 0xD0)
	addi	$v0, $v0, 0x1
	sw	$v0, %lo(.sbss + 0xD0)($at)
	slt	$at, $v0, $k0
	bnez	$at, .L5
	nop
.L8:
	lw	$v0, 0x1074($v1)
	li	$at, -0x401
	and	$v0, $v0, $at
	sw	$v0, 0x1074($v1)
	lw	$v0, .sbss + 0xE0
	j	.L9
	sw	$v0, 0x10f0($v1)
.L9:
	li	$k0, 0x100
	lw	$k0, 0x8($k0)
	nop
	lw	$k0, 0($k0)
	nop
	lw	$v0, 0x10($k0)
	lw	$v1, 0x14($k0)
	lw	$ra, 0x84($k0)
	addi	$k0, $k0, 0x8
	lw	$at, 0x4($k0)
	lw	$k0, 0x80($k0)
	nop
	jr	$k0
	rfe
	la	$k0, T_0000030C
	jr	$k0
	nop
T_0000030C:
	la	$k0, T_00000358
	sw	$v0, 0x4($k0)
	lui	$k0, 0x1F80
	lh	$v0, 0x1100($k0)
	addiu	$k0, $k0, 0
	la	$k0, T_00000358
	sw	$v0, 0($k0)
	lw	$v0, 0x4($k0)
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
T_00000358:
	nop
	nop
	nop
	nop
	.set	at
	.end	read_gun_h
	.set	reorder

	.data
	.align	4
D_00000368:
	.word	0x00000000
	.word	0x0000002A
	.word	0x00000000
	.word	0x00000000

	.section	.sbss
	.align	4
B_00000378:
	.space	0xF0
