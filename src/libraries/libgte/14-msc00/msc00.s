/* LIBGTE.LIB, member MSC00.OBJ (hand-written assembly)
 *
 * void InitGeom(void);
 */
	.text
	.align	4
	.set	noreorder
T_00000070:
	.word	0x00097350 /* invalid instruction */
	.word	0x00470000 /* invalid instruction */

	.globl	InitGeom
	.ent	InitGeom
InitGeom:
	sw	$ra, D_00000100
	jal	_patch_gte
	nop
	lw	$ra, D_00000100
	nop
	mfc0	$v0, $12
	li	$v1, 0x40000000
	or	$v0, $v0, $v1
	mtc0	$v0, $12
	nop
	li	$t0, 0x155
	ctc2	$t0, $29
	nop
	li	$t0, 0x100
	ctc2	$t0, $30
	nop
	li	$t0, 0x3E8
	ctc2	$t0, $26
	nop
	li	$t0, -0x1062
	ctc2	$t0, $27
	nop
	li	$t0, 0x1400000
	ctc2	$t0, $28
	nop
	ctc2	$zero, $24
	ctc2	$zero, $25
	nop
	jr	$ra
	nop
	nop
	nop
	.end	InitGeom
	.set	reorder

	.data
	.align	4
D_00000100:
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
