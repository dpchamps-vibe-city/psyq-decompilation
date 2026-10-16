/* LIBGTE.LIB, member MSC05.OBJ (hand-written assembly)
 *
 * void gteMIMefunc(SVECTOR *otp, SVECTOR *dfp, long n, long p);
 *
 * Register use:
 *   a0  otp
 *   a1  dfp
 *   a2  n
 *   a3  p
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	gteMIMefunc
	.ent	gteMIMefunc
gteMIMefunc:
	sll	$a2, $a2, 3
	add	$a2, $a2, $a1
	mtc2	$a3, $8
.L1:
	lw	$t0, 0($a1)
	lh	$t2, 0x4($a1)
	sra	$t1, $t0, 16
	andi	$t0, $t0, 0xFFFF
	mtc2	$t0, $9
	mtc2	$t1, $10
	mtc2	$t2, $11
	nop
	nop
	GPF	1
	lw	$v0, 0($a0)
	lh	$a3, 0x4($a0)
	sra	$v1, $v0, 16
	andi	$v0, $v0, 0xFFFF
	addi	$a1, $a1, 0x8
	mfc2	$t0, $9
	mfc2	$t1, $10
	mfc2	$t2, $11
	add	$v0, $v0, $t0
	add	$v1, $v1, $t1
	add	$a3, $a3, $t2
	sh	$v0, 0($a0)
	sh	$v1, 0x2($a0)
	sh	$a3, 0x4($a0)
	addi	$a0, $a0, 0x8
	bne	$a1, $a2, .L1
	nop
	jr	$ra
	nop
	.end	gteMIMefunc
	.set	reorder
