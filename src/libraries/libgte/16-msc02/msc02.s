/* LIBGTE.LIB, member MSC02.OBJ (hand-written assembly)
 *
 * void InvSquareRoot(long a, long *b, long *c);
 *
 * Register use:
 *   a0  a
 *   a1  b
 *   a2  c
 *
 * long VectorNormalS(VECTOR *v0, SVECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   v0  result (long)
 *
 * long VectorNormal(VECTOR *v0, VECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   v0  result (long)
 *
 * long VectorNormalSS(SVECTOR *v0, SVECTOR *v1);
 *
 * Register use:
 *   a0  v0
 *   a1  v1
 *   v0  result (long)
 *
 * func_00000170: private routine, unnamed in the original; the name is its offset.
 *
 * void MatrixNormal(MATRIX *m, MATRIX *n);
 *
 * Register use:
 *   a0  m
 *   a1  n
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	InvSquareRoot
	.ent	InvSquareRoot
InvSquareRoot:
	.set	noat
	mtc2	$a0, $30
	nop
	nop
	mfc2	$v0, $31
	li	$at, 0x20
	beq	$v0, $at, .L3
	nop
	beqz	$v0, .L3
	nop
	andi	$t0, $v0, 0x1
	li	$at, -0x2
	and	$t2, $v0, $at
	li	$t1, 0x1F
	sub	$t1, $t1, $t2
	sra	$t1, $t1, 1
	addi	$t3, $t2, -0x18
	bltz	$t3, .L1
	nop
	sllv	$t4, $a0, $t3
	b	.L2
.L1:
	li	$t3, 0x18
	sub	$t3, $t3, $t2
	srav	$t4, $a0, $t3
.L2:
	addi	$t4, $t4, -0x40
	sll	$t4, $t4, 1
	lui	$t5, %hi(D_00000334)
	addu	$t5, $t5, $t4
	lh	$t5, %lo(D_00000334)($t5)
	sw	$t1, 0($a2)
	sw	$t5, 0($a1)
	li	$v0, 0x1
	jr	$ra
	nop
.L3:
	jr	$ra
	li	$v0, -0x1
	.set	at
	.end	InvSquareRoot

	.globl	VectorNormalS
	.ent	VectorNormalS
VectorNormalS:
	lw	$t0, 0($a0)
func_00000100:
	lw	$t1, 0x4($a0)
	lw	$t2, 0x8($a0)
	b	.L4
	nop
	.end	VectorNormalS

	.globl	VectorNormal
	.ent	VectorNormal
VectorNormal:
	lw	$t0, 0($a0)
	lw	$t1, 0x4($a0)
	lw	$t2, 0x8($a0)
	move	$a3, $ra
	jal	func_00000170
	nop
	sw	$t0, 0($a1)
	sw	$t1, 0x4($a1)
	sw	$t2, 0x8($a1)
	move	$ra, $a3
	jr	$ra
	nop
	.end	VectorNormal

	.globl	VectorNormalSS
	.ent	VectorNormalSS
VectorNormalSS:
	lh	$t0, 0($a0)
	lh	$t1, 0x2($a0)
	lh	$t2, 0x4($a0)
.L4:
	move	$a3, $ra
	jal	func_00000170
	nop
	sh	$t0, 0($a1)
	sh	$t1, 0x2($a1)
	sh	$t2, 0x4($a1)
	move	$ra, $a3
	jr	$ra
	nop
	.end	VectorNormalSS

	.ent	func_00000170
func_00000170:
	.set	noat
	mtc2	$t0, $9
	mtc2	$t1, $10
	mtc2	$t2, $11
	nop
	SQR	0
	mfc2	$t3, $25
	mfc2	$t4, $26
	mfc2	$t5, $27
	add	$t3, $t3, $t4
	add	$v0, $t3, $t5
	mtc2	$v0, $30
	nop
	nop
	mfc2	$v1, $31
	li	$at, -0x2
	and	$v1, $v1, $at
	li	$t6, 0x1F
	sub	$t6, $t6, $v1
	sra	$t6, $t6, 1
	addi	$t3, $v1, -0x18
	bltz	$t3, .L5
	nop
	b	.L6
	sllv	$t4, $v0, $t3
.L5:
	li	$t3, 0x18
	sub	$t3, $t3, $v1
	srav	$t4, $v0, $t3
.L6:
	addi	$t4, $t4, -0x40
	sll	$t4, $t4, 1
	lui	$t5, %hi(D_00000334)
	addu	$t5, $t5, $t4
	lh	$t5, %lo(D_00000334)($t5)
	nop
	mtc2	$t5, $8
	mtc2	$t0, $9
	mtc2	$t1, $10
	mtc2	$t2, $11
	nop
	nop
	GPF	0
	mfc2	$t0, $25
	mfc2	$t1, $26
	mfc2	$t2, $27
	srav	$t0, $t0, $t6
	srav	$t1, $t1, $t6
	srav	$t2, $t2, $t6
	jr	$ra
	nop
	.set	at
	.end	func_00000170

	.globl	MatrixNormal
	.ent	MatrixNormal
MatrixNormal:
	lh	$t0, 0($a0)
	lh	$t1, 0x2($a0)
	lh	$t2, 0x4($a0)
	lh	$t3, 0x6($a0)
	lh	$t4, 0x8($a0)
	lh	$t5, 0xA($a0)
	cfc2	$v0, $0
	cfc2	$v1, $2
	cfc2	$a2, $4
	ctc2	$t0, $0
	ctc2	$t1, $2
	ctc2	$t2, $4
	mtc2	$t5, $11
	mtc2	$t3, $9
	mtc2	$t4, $10
	nop
	OP	1
	mfc2	$t7, $25
	mfc2	$t8, $26
	mfc2	$t9, $27
	ctc2	$t3, $0
	ctc2	$t4, $2
	ctc2	$t5, $4
	nop
	OP	1
	mtc2	$t3, $0
	mtc2	$t4, $1
	mtc2	$t5, $2
	mfc2	$t0, $25
	mfc2	$t1, $26
	mfc2	$t2, $27
	ctc2	$v0, $0
	ctc2	$v1, $2
	ctc2	$a2, $4
	move	$a3, $ra
	jal	func_00000170
	nop
	sh	$t0, 0($a1)
	sh	$t1, 0x2($a1)
	sh	$t2, 0x4($a1)
	mfc2	$t0, $0
	mfc2	$t1, $1
	mfc2	$t2, $2
	jal	func_00000170
	nop
	sh	$t0, 0x6($a1)
	sh	$t1, 0x8($a1)
	sh	$t2, 0xA($a1)
	move	$t0, $t7
	move	$t1, $t8
	jal	func_00000170
	move	$t2, $t9
	sh	$t0, 0xC($a1)
	sh	$t1, 0xE($a1)
	sh	$t2, 0x10($a1)
	move	$ra, $a3
	jr	$ra
	nop
	nop
	nop
	.end	MatrixNormal
	.set	reorder

	.data
	.align	4
D_00000320:
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
D_00000334:
	.word	0x0FE01000
	.word	0x0FA30FC1
	.word	0x0F680F85
	.word	0x0F300F4C
	.word	0x0EFB0F15
	.word	0x0EC70EE1
	.word	0x0E960EAE
	.word	0x0E660E7E
	.word	0x0E380E4F
	.word	0x0E0C0E22
	.word	0x0DE20DF7
	.word	0x0DB90DCD
	.word	0x0D910DA5
	.word	0x0D6B0D7E
	.word	0x0D450D58
	.word	0x0D210D33
	.word	0x0CFF0D10
	.word	0x0CDD0CEE
	.word	0x0CBC0CCC
	.word	0x0C9C0CAC
	.word	0x0C7D0C8D
	.word	0x0C5F0C6E
	.word	0x0C420C51
	.word	0x0C260C34
	.word	0x0C0A0C18
	.word	0x0BEF0BFD
	.word	0x0BD50BE2
	.word	0x0BBB0BC8
	.word	0x0BA20BAF
	.word	0x0B8A0B96
	.word	0x0B720B7E
	.word	0x0B5B0B67
	.word	0x0B450B50
	.word	0x0B2E0B39
	.word	0x0B190B24
	.word	0x0B040B0E
	.word	0x0AEF0AF9
	.word	0x0ADB0AE5
	.word	0x0AC70AD1
	.word	0x0AB40ABD
	.word	0x0AA10AAA
	.word	0x0A8E0A97
	.word	0x0A7C0A85
	.word	0x0A6A0A73
	.word	0x0A590A61
	.word	0x0A470A50
	.word	0x0A370A3F
	.word	0x0A260A2E
	.word	0x0A160A1E
	.word	0x0A060A0E
	.word	0x09F609FE
	.word	0x09E709EF
	.word	0x09D809E0
	.word	0x09C909D1
	.word	0x09BB09C2
	.word	0x09AD09B4
	.word	0x099E09A5
	.word	0x09910998
	.word	0x0983098A
	.word	0x0976097C
	.word	0x0969096F
	.word	0x095C0962
	.word	0x094F0955
	.word	0x09430949
	.word	0x0936093C
	.word	0x092A0930
	.word	0x091E0924
	.word	0x09120918
	.word	0x0907090D
	.word	0x08FB0901
	.word	0x08F008F6
	.word	0x08E508EB
	.word	0x08DA08E0
	.word	0x08CF08D5
	.word	0x08C508CA
	.word	0x08BA08BF
	.word	0x08B008B5
	.word	0x08A608AB
	.word	0x089C08A1
	.word	0x08920897
	.word	0x0888088D
	.word	0x087E0883
	.word	0x0875087A
	.word	0x086B0870
	.word	0x08620867
	.word	0x0859085E
	.word	0x08500855
	.word	0x0847084C
	.word	0x083E0843
	.word	0x0836083A
	.word	0x082D0831
	.word	0x08240829
	.word	0x081C0820
	.word	0x08140818
	.word	0x080C0810
	.word	0x08040808
	.word	0x00000000
	.word	0x00000000
	.word	0x00000000
