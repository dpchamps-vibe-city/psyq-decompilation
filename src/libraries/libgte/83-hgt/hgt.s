/* LIBGTE.LIB, member HGT.OBJ (hand-written assembly)
 *
 * void RotMeshH(short *Yheight, DVECTOR *Vo, u_short *sz, u_short *flag,
 *               short Xoffset, short Zoffset, short m, short n,
 *               DVECTOR *base);
 *
 * Register use:
 *   a0        Yheight
 *   a1        Vo
 *   a2        sz
 *   a3        flag
 *   0x10(sp)  Xoffset
 *   0x14(sp)  Zoffset
 *   0x18(sp)  m
 *   0x1c(sp)  n
 *   0x20(sp)  base
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotMeshH
	.ent	RotMeshH
RotMeshH:
	lw	$t6, 0x10($sp)
	lw	$t7, 0x14($sp)
	lw	$t5, 0x18($sp)
	lw	$t8, 0x20($sp)
	lw	$t1, 0x1C($sp)
	lh	$t9, 0($t8)
	lh	$t3, 0x2($t8)
.L1:
	move	$t0, $t5
	move	$t2, $t9
.L2:
	lh	$t4, 0($a0)
	mtc2	$t3, $1
	sll	$t4, $t4, 16
	andi	$v1, $t2, 0xFFFF
	or	$t4, $t4, $v1
	mtc2	$t4, $0
	nop
	nop
	RTPS
	addi	$a0, $a0, 0x2
	add	$t2, $t2, $t6
	addi	$t0, $t0, -0x1
	swc2	$14, 0($a1)
	mfc2	$v1, $19
	cfc2	$v0, $31
	sh	$v1, 0($a2)
	srl	$v0, $v0, 12
	sh	$v0, 0($a3)
	addi	$a1, $a1, 0x4
	addi	$a2, $a2, 0x2
	addi	$a3, $a3, 0x2
	bgtz	$t0, .L2
	nop
	add	$t3, $t3, $t7
	addi	$t1, $t1, -0x1
	bgtz	$t1, .L1
	nop
	jr	$ra
	nop
	nop
	nop
	.end	RotMeshH
	.set	reorder
