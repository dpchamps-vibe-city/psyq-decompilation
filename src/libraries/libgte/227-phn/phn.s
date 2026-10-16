/* LIBGTE.LIB, member PHN.OBJ (hand-written assembly)
 *
 * void PhongLine(int istart_x, int iend_x, int p, int q, u_short **pixx,
 *                int fs, int ft, int i4, int det);
 *
 * Register use:
 *   a0        istart_x
 *   a1        iend_x
 *   a2        p
 *   a3        q
 *   0x10(sp)  pixx
 *   0x14(sp)  fs
 *   0x18(sp)  ft
 *   0x1c(sp)  i4
 *   0x20(sp)  det
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	PhongLine
	.ent	PhongLine
PhongLine:
	.set	noat
	lui	$at, %hi(D_00000360)
	sw	$s0, %lo(D_00000360)($at)
	lui	$at, %hi(D_00000364)
	sw	$s1, %lo(D_00000364)($at)
	lui	$at, %hi(D_00000368)
	sw	$s2, %lo(D_00000368)($at)
	lui	$at, %hi(D_0000036C)
	sw	$s3, %lo(D_0000036C)($at)
	lui	$at, %hi(D_00000370)
	sw	$s4, %lo(D_00000370)($at)
	lui	$at, %hi(D_00000374)
	sw	$s5, %lo(D_00000374)($at)
	lui	$at, %hi(D_00000378)
	sw	$s6, %lo(D_00000378)($at)
	lui	$at, %hi(D_0000037C)
	sw	$s7, %lo(D_0000037C)($at)
	lw	$t2, 0x10($sp)
	nop
	lw	$t2, 0($t2)
	lw	$t0, 0x14($sp)
	lw	$t1, 0x18($sp)
	lw	$s3, 0x1C($sp)
	lw	$s7, 0x20($sp)
.L1:
	li	$t3, 0x1000000
	sub	$t3, $t3, $t0
	sub	$t3, $t3, $t1
	sra	$t3, $t3, 12
	sra	$t4, $t0, 12
	sra	$t5, $t1, 12
	slti	$at, $s7, 0x65
	beqz	$at, .L7
	nop
	slti	$at, $t3, 0x1001
	bnez	$at, .L2
	nop
	li	$t3, 0x1000
.L2:
	bgez	$t3, .L3
	nop
	li	$t3, 0
.L3:
	slti	$at, $t4, 0x1001
	bnez	$at, .L4
	nop
	li	$t4, 0x1000
.L4:
	bgez	$t4, .L5
	nop
	li	$t4, 0
.L5:
	slti	$at, $t5, 0x1001
	bnez	$at, .L6
	nop
	li	$t5, 0x1000
.L6:
	bgez	$t5, .L7
	nop
	li	$t5, 0
.L7:
	andi	$t3, $t3, 0xFFFF
	sll	$t4, $t4, 16
	or	$t4, $t4, $t3
	mtc2	$t4, $0
	mtc2	$t5, $1
	nop
	MVMVA	1, 0, 0, 0, 0
	mfc2	$t3, $25
	nop
	multu	$t3, $t3
	mflo	$t6
	mfc2	$t4, $26
	nop
	multu	$t4, $t4
	mflo	$t7
	mfc2	$t5, $27
	nop
	multu	$t5, $t5
	mflo	$t8
	add	$t6, $t6, $t7
	nop
	add	$t6, $t6, $t8
	mtc2	$t6, $30
	nop
	nop
	mfc2	$v0, $31
	li	$t9, 0x1F
	li	$at, -0x2
	and	$t8, $v0, $at
	sub	$t9, $t9, $t8
	sra	$t9, $t9, 1
	addi	$s0, $t8, -0x18
	bltz	$s0, .L8
	sllv	$s1, $t6, $s0
	b	.L9
.L8:
	li	$s0, 0x18
	sub	$s0, $s0, $t8
	srav	$s1, $t6, $s0
.L9:
	addi	$s1, $s1, -0x40
	sll	$s1, $s1, 1
	lui	$s2, %hi(D_00000380)
	addu	$s2, $s2, $s1
	lh	$s2, %lo(D_00000380)($s2)
	nop
	multu	$t3, $s2
	mflo	$t3
	nop
	srav	$t3, $t3, $t9
	multu	$t4, $s2
	mflo	$t4
	andi	$t3, $t3, 0xFFFF
	srav	$t4, $t4, $t9
	multu	$t5, $s2
	mflo	$t5
	sll	$t4, $t4, 16
	srav	$t5, $t5, $t9
	or	$t4, $t4, $t3
	mtc2	$t4, $0
	mtc2	$t5, $1
	nop
	MVMVA	1, 1, 0, 3, 1
	sll	$s5, $s3, 2
	andi	$s4, $a0, 0x3
	add	$s4, $s4, $s5
	sll	$s4, $s4, 2
	lui	$s6, %hi(D_00000500)
	addu	$s6, $s6, $s4
	lw	$s6, %lo(D_00000500)($s6)
	nop
	sra	$s6, $s6, 1
	addi	$s6, $s6, -0x4
	mfc2	$t3, $9
	mfc2	$t4, $10
	mfc2	$t5, $11
	add	$t3, $t3, $s6
	sra	$t3, $t3, 3
	add	$t4, $t4, $s6
	sra	$t4, $t4, 3
	add	$t5, $t5, $s6
	sra	$t5, $t5, 3
	slti	$at, $t3, 0x20
	bnez	$at, .L10
	nop
	li	$t3, 0x1F
.L10:
	bgez	$t3, .L11
	nop
	li	$t3, 0
.L11:
	slti	$at, $t4, 0x20
	bnez	$at, .L12
	nop
	li	$t4, 0x1F
.L12:
	bgez	$t4, .L13
	nop
	li	$t4, 0
.L13:
	slti	$at, $t5, 0x20
	bnez	$at, .L14
	nop
	li	$t5, 0x1F
.L14:
	bgtz	$t5, .L15
	nop
	li	$t5, 0x1
.L15:
	sll	$t5, $t5, 10
	sll	$t4, $t4, 5
	add	$t5, $t5, $t3
	add	$t5, $t5, $t4
	sh	$t5, 0($t2)
	addi	$a0, $a0, 0x1
	add	$t0, $t0, $a2
	add	$t1, $t1, $a3
	slt	$at, $a1, $a0
	beqz	$at, .L1
	addi	$t2, $t2, 0x2
	lw	$v0, 0x10($sp)
	nop
	sw	$t2, 0($v0)
	lw	$s0, D_00000360
	lw	$s1, D_00000364
	lw	$s2, D_00000368
	lw	$s3, D_0000036C
	lw	$s4, D_00000370
	lw	$s5, D_00000374
	lw	$s6, D_00000378
	lw	$s7, D_0000037C
	jr	$ra
	nop
	nop
	nop
	.set	at
	.end	PhongLine
	.set	reorder

	.data
	.align	4
D_00000360:
	.word	0x00000000
D_00000364:
	.word	0x00000000
D_00000368:
	.word	0x00000000
D_0000036C:
	.word	0x00000000
D_00000370:
	.word	0x00000000
D_00000374:
	.word	0x00000000
D_00000378:
	.word	0x00000000
D_0000037C:
	.word	0x00000000
D_00000380:
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
D_00000500:
	.word	0x00000000
	.word	0x00000008
	.word	0x00000002
	.word	0x0000000A
	.word	0x0000000C
	.word	0x00000004
	.word	0x0000000E
	.word	0x00000006
	.word	0x00000003
	.word	0x0000000B
	.word	0x00000001
	.word	0x00000009
	.word	0x0000000F
	.word	0x00000007
	.word	0x0000000D
	.word	0x00000005
