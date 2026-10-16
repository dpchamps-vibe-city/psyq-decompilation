/* LIBGTE.LIB, member MTX_006.OBJ (hand-written assembly)
 *
 * void PushMatrix(void);
 *
 * void PopMatrix(void);
 */
	.text
	.align	4
	.set	noreorder

	.globl	PushMatrix
	.ent	PushMatrix
PushMatrix:
	.set	noat
	lw	$t6, D_000001CC
	nop
	slti	$at, $t6, 0x280
	bnez	$at, .L1
	nop
	lui	$at, %hi(D_000001C0)
	sw	$ra, %lo(D_000001C0)($at)
	lui	$a0, %hi(D_00000450)
	jal	printf
	addiu	$a0, $a0, %lo(D_00000450)
	lw	$ra, D_000001C0
	nop
	jr	$ra
	nop
.L1:
	la	$t7, D_000001D0
	addu	$t7, $t7, $t6
	cfc2	$t0, $0
	cfc2	$t1, $1
	sw	$t0, 0($t7)
	sw	$t1, 0x4($t7)
	cfc2	$t0, $2
	cfc2	$t1, $3
	sw	$t0, 0x8($t7)
	sw	$t1, 0xC($t7)
	cfc2	$t0, $4
	nop
	sw	$t0, 0x10($t7)
	cfc2	$t0, $5
	cfc2	$t1, $6
	cfc2	$t2, $7
	sw	$t0, 0x14($t7)
	sw	$t1, 0x18($t7)
	sw	$t2, 0x1C($t7)
	addi	$t6, $t6, 0x20
	lui	$at, %hi(D_000001CC)
	sw	$t6, %lo(D_000001CC)($at)
	jr	$ra
	nop
	.set	at
	.end	PushMatrix

	.globl	PopMatrix
	.ent	PopMatrix
PopMatrix:
	lw	$t6, D_000001CC
	nop
	bgtz	$t6, .L2
	nop
	sw	$ra, D_000001C0
	lui	$a0, %hi(D_00000481)
	jal	printf
	addiu	$a0, $a0, %lo(D_00000481)
	lw	$ra, D_000001C0
	nop
	jr	$ra
	nop
.L2:
	addi	$t6, $t6, -0x20
	sw	$t6, D_000001CC
	la	$t7, D_000001D0
	addu	$t7, $t7, $t6
	lw	$t0, 0($t7)
	lw	$t1, 0x4($t7)
	ctc2	$t0, $0
	ctc2	$t1, $1
	lw	$t0, 0x8($t7)
	lw	$t1, 0xC($t7)
	ctc2	$t0, $2
	ctc2	$t1, $3
	lw	$t0, 0x10($t7)
	nop
	ctc2	$t0, $4
	nop
	lw	$t0, 0x14($t7)
	lw	$t1, 0x18($t7)
	lw	$t2, 0x1C($t7)
	ctc2	$t0, $5
	ctc2	$t1, $6
	ctc2	$t2, $7
	jr	$ra
	nop
	nop
	nop
	.end	PopMatrix
	.set	reorder

	.data
	.align	4
D_000001C0:
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
D_000001CC:
	.word	0x00000000
D_000001D0:
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
D_00000450:
	.word	0x6F727245
	.word	0x43203A72
	.word	0x74276E61
	.word	0x73757020
	.word	0x616D2068
	.word	0x78697274
	.word	0x6174732C
	.word	0x6D286B63
	.word	0x32207861
	.word	0x69202930
	.word	0x75662073
	.word	0x0A216C6C
	.byte	0x00
D_00000481:
	.byte	0x45
	.short	0x7272
	.word	0x203A726F
	.word	0x276E6143
	.word	0x6F702074
	.word	0x616D2070
	.word	0x78697274
	.word	0x6174732C
	.word	0x69206B63
	.word	0x6D652073
	.word	0x21797470
	.word	0x6854000A
	.word	0x66207369
	.word	0x74636E75
	.word	0x206E6F69
	.word	0x6E207369
	.word	0x6920746F
	.word	0x656C706D
	.word	0x746E656D
	.word	0x0A2E6465
	.word	0x00000000
