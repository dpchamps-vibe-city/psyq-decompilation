/* LIBHMD.LIB, member MIME_S.OBJ (hand-written assembly)
 *
 * GsVNMIMeFunc: no prototype in the SDK headers.
 *
 * GsRestoreOrgsVNMIMe: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	GsVNMIMeFunc
	.ent	GsVNMIMeFunc
GsVNMIMeFunc:
	mtc2	$a3, $8
.L1:
	lw	$t3, 0($a1)
	lh	$t5, 0x4($a1)
	sra	$t4, $t3, 16
	mtc2	$t3, $9
	mtc2	$t4, $10
	mtc2	$t5, $11
	addi	$a1, $a1, 0x8
	addi	$a2, $a2, -0x1
	GPF	1
	lw	$t0, 0($a0)
	lh	$t2, 0x4($a0)
	sra	$t1, $t0, 16
	mfc2	$t3, $25
	mfc2	$t4, $26
	mfc2	$t5, $27
	add	$t3, $t0, $t3
	add	$t4, $t1, $t4
	add	$t5, $t2, $t5
	sh	$t3, 0($a0)
	sh	$t4, 0x2($a0)
	sh	$t5, 0x4($a0)
	bgtz	$a2, .L1
	addi	$a0, $a0, 0x8
	jr	$ra
	nop
	.end	GsVNMIMeFunc

	.globl	GsRestoreOrgsVNMIMe
	.ent	GsRestoreOrgsVNMIMe
GsRestoreOrgsVNMIMe:
	lw	$t0, 0($a0)
	addi	$t1, $a0, 0x4
	sra	$t0, $t0, 16
.L2:
	beqz	$t0, .L5
	nop
	lw	$v0, 0($t1)
	addi	$t1, $t1, 0x4
	addi	$t0, $t0, -0x1
	sll	$v0, $v0, 2
	add	$t2, $a1, $v0
	addi	$t4, $t2, -0x8
	lw	$t3, 0($t2)
	nop
	sra	$t3, $t3, 16
.L3:
	beqz	$t3, .L2
	nop
	addi	$t4, $t4, 0xC
	addi	$t3, $t3, -0x1
	lw	$v0, 0x8($t4)
	nop
	andi	$v1, $v0, 0xFFFF
	beqz	$v1, .L3
	nop
	swl	$zero, 0x8($t4)
	sra	$t5, $v0, 16
	lw	$v0, 0($t4)
	lw	$v1, 0x4($t4)
	sll	$v0, $v0, 3
	sll	$v1, $v1, 3
	add	$t6, $a3, $v0
	add	$t7, $a2, $v1
.L4:
	beqz	$t5, .L2
	nop
	addi	$t5, $t5, -0x1
	lw	$v0, 0($t7)
	lw	$v1, 0x4($t7)
	addi	$t7, $t7, 0x8
	sw	$v0, 0($t6)
	sw	$v1, 0x4($t6)
	j	.L4
	addi	$t6, $t6, 0x8
.L5:
	jr	$ra
	nop
	nop
	nop
	nop
	.end	GsRestoreOrgsVNMIMe
	.set	reorder
