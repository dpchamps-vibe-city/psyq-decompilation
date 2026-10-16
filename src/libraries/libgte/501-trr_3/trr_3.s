/* LIBGTE.LIB, member TRR_3.OBJ (hand-written assembly)
 *
 * long TransRotPers3(SVECTOR *v0, SVECTOR *v1, SVECTOR *v2, long *sxy0,
 *                    long *sxy1, long *sxy2, long *p, long *flag);
 *
 * Register use:
 *   a0        v0
 *   a1        v1
 *   a2        v2
 *   a3        sxy0
 *   0x10(sp)  sxy1
 *   0x14(sp)  sxy2
 *   0x18(sp)  p
 *   0x1c(sp)  flag
 *   v0        result (long)
 *
 * Stack offsets are relative to sp on entry.
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	TransRotPers3
	.ent	TransRotPers3
TransRotPers3:
	cfc2	$t3, $5
	cfc2	$t4, $6
	cfc2	$t5, $7
	ctc2	$zero, $5
	ctc2	$zero, $6
	ctc2	$zero, $7
	lh	$t0, 0($a0)
	lh	$t1, 0x2($a0)
	lh	$t2, 0x4($a0)
	lh	$t6, 0($a1)
	lh	$t7, 0x2($a1)
	lh	$t8, 0x4($a1)
	lh	$t9, 0($a2)
	lh	$v0, 0x2($a2)
	lh	$v1, 0x4($a2)
	add	$t0, $t0, $t3
	add	$t1, $t1, $t4
	add	$t2, $t2, $t5
	add	$t6, $t6, $t3
	add	$t7, $t7, $t4
	add	$t8, $t8, $t5
	add	$t9, $t9, $t3
	add	$v0, $v0, $t4
	add	$v1, $v1, $t5
	andi	$t0, $t0, 0xFFFF
	sll	$t1, $t1, 16
	or	$t1, $t1, $t0
	andi	$t6, $t6, 0xFFFF
	sll	$t7, $t7, 16
	or	$t7, $t7, $t6
	andi	$t9, $t9, 0xFFFF
	sll	$v0, $v0, 16
	or	$v0, $v0, $t9
	mtc2	$t1, $0
	mtc2	$t2, $1
	mtc2	$t7, $2
	mtc2	$t8, $3
	mtc2	$v0, $4
	mtc2	$v1, $5
	nop
	RTPT
	lw	$t0, 0x10($sp)
	lw	$t1, 0x14($sp)
	lw	$t2, 0x18($sp)
	lw	$t6, 0x1C($sp)
	swc2	$12, 0($a3)
	swc2	$13, 0($t0)
	swc2	$14, 0($t1)
	swc2	$8, 0($t2)
	cfc2	$v1, $31
	mfc2	$v0, $19
	ctc2	$t3, $5
	ctc2	$t4, $6
	ctc2	$t5, $7
	sw	$v1, 0($t6)
	jr	$ra
	sra	$v0, $v0, 2
	nop
	nop
	nop
	.end	TransRotPers3
	.set	reorder
