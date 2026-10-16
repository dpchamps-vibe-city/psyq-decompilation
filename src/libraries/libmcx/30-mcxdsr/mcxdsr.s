/* LIBMCX.LIB, member MCXDSR.OBJ (hand-written assembly)
 *
 * _mcxStartFastDsr: no prototype in the SDK headers.
 *
 * _mcxStopFastDsr: no prototype in the SDK headers.
 *
 * _mcxVecDsr: no prototype in the SDK headers.
 *
 * _mcxFastDsrEnt: no prototype in the SDK headers.
 *
 * _mcxVecSave: no prototype in the SDK headers.
 */
	.text
	.align	4

	.globl	_mcxStartFastDsr
	.ent	_mcxStartFastDsr
_mcxStartFastDsr:
	sw	$ra, D_000003A4
	sw	$zero, index
	sw	$a0, D_000003A8
	sw	$a1, D_000003AC
	sw	$a2, _mcxIntRestSize
	sw	$a3, D_000003B0
	lw	$v0, D_000003A0
	bnez	$v0, .L1
	li	$t1, 0x56
	li	$t2, 0xB0
	jalr	$t2
	lw	$v0, 0x18($v0)
	addiu	$v0, $v0, 0x70
	sw	$v0, D_000003A0
.L1:
	jal	func_000001F0
	bnez	$v0, .L4
	lw	$v0, D_000003A0
	la	$t2, _mcxVecSave
	la	$t1, _mcxVecSave + 0xC
.L2:
	lw	$v1, 0($v0)
	sw	$v1, 0($t2)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L2
	lw	$v0, D_000003A0
	la	$t2, _mcxVecDsr
	la	$t1, _mcxVecDsr + 0x10
.L3:
	lw	$v1, 0($t2)
	sw	$v1, 0($v0)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L3
	jal	FlushCache
.L4:
	lw	$ra, D_000003A4
	jr	$ra
	.end	_mcxStartFastDsr

	.globl	_mcxStopFastDsr
	.ent	_mcxStopFastDsr
_mcxStopFastDsr:
	sw	$ra, D_000003A4
	lw	$v0, D_000003A0
	beqz	$v0, .L6
func_00000180:
	jal	func_000001F0
	beqz	$v0, .L6
	lw	$v0, D_000003A0
	la	$t2, _mcxVecSave
	la	$t1, _mcxVecSave + 0xC
.L5:
	lw	$v1, 0($t2)
	sw	$v1, 0($v0)
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L5
	jal	FlushCache
.L6:
	lw	$ra, D_000003A4
	jr	$ra
	.end	_mcxStopFastDsr

	.globl	_mcxVecDsr
	.ent	_mcxVecDsr
_mcxVecDsr:
	la	$v0, _mcxFastDsrEnt
	jalr	$v0
	nop
func_000001F0:
	la	$t2, _mcxVecDsr
	la	$t1, _mcxVecDsr + 0x10
.L7:
	lw	$v1, 0($t2)
	lw	$t0, 0($v0)
	bne	$v1, $t0, .L8
	addiu	$t2, $t2, 0x4
	addiu	$v0, $v0, 0x4
	bne	$t2, $t1, .L7
	li	$v0, 0x1
	jr	$ra
.L8:
	li	$v0, 0
	jr	$ra
	.end	_mcxVecDsr

	.globl	_mcxFastDsrEnt
	.ent	_mcxFastDsrEnt
_mcxFastDsrEnt:
	.set	noat
	lw	$v0, _mcxIntRestSize
	beqz	$v0, .L11
	lui	$v1, 0x1F80
	lw	$v0, 0x1070($v1)
	andi	$v0, $v0, 0x80
	beqz	$v0, .L11
	lw	$v0, D_000003A8
	beqz	$v0, .L9
	lbu	$zero, 0x1040($v1)
	lw	$k0, D_000003AC
	lbu	$v0, 0($k0)
	sb	$v0, 0x1040($v1)
	addiu	$k0, $k0, 0x1
	lui	$at, %hi(D_000003AC)
	sw	$k0, %lo(D_000003AC)($at)
	j	.L10
.L9:
	lw	$k0, D_000003AC
	lbu	$v0, 0x1040($v1)
	sb	$zero, 0x1040($v1)
	sb	$v0, 0($k0)
	addiu	$k0, $k0, 0x1
	lui	$at, %hi(D_000003AC)
	sw	$k0, %lo(D_000003AC)($at)
.L10:
	li	$k0, -0x81
	sw	$k0, 0x1070($v1)
	lhu	$k0, 0x104a($v1)
	ori	$k0, $k0, 0x10
	sh	$k0, 0x104a($v1)
	lw	$v1, D_000003B0
	lb	$k0, 0($v1)
	xor	$k0, $k0, $v0
	sb	$k0, 0($v1)
	lw	$k0, _mcxIntRestSize
	addiu	$k0, $k0, -0x1
	lui	$at, %hi(_mcxIntRestSize)
	sw	$k0, %lo(_mcxIntRestSize)($at)
	lw	$k0, _mcxCmdSeq
	addiu	$k0, $k0, 0x1
	lui	$at, %hi(_mcxCmdSeq)
	sw	$k0, %lo(_mcxCmdSeq)($at)
	lw	$k0, _mcxCallFromC
	bnez	$k0, .L12
	j	.L13
.L11:
	lui	$at, %hi(D_000003A4)
	sw	$ra, %lo(D_000003A4)($at)
	.set	at
	.end	_mcxFastDsrEnt

	.globl	_mcxVecSave
	.ent	_mcxVecSave
_mcxVecSave:
	.set	noat
	nop
	nop
	nop
	nop
	lw	$ra, D_000003A4
.L12:
	jr	$ra
.L13:
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
	.end	_mcxVecSave

	.data
	.align	4
D_000003A0:
	.word	0x00000000
D_000003A4:
	.word	0x00000000
D_000003A8:
	.word	0x00000000
D_000003AC:
	.word	0x00000000
D_000003B0:
	.word	0x00000000
	.globl	_mcxIntRestSize
_mcxIntRestSize:
	.word	0x00000000
	.globl	_mcxCallFromC
_mcxCallFromC:
	.word	0x00000000
	.word	0x00000000
