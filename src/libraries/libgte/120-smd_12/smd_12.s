/* LIBGTE.LIB, member SMD_12.OBJ (hand-written assembly)
 *
 * void RotSMD_SV_F4(long *pa, long *va, u_long *ot, int otlen, int id,
 *                   int sclip, int hclip, int vclip, int nclipmode);
 *
 * Shared-vertex form of RotSMD_F4: rotate, project and sort the POLY_F4 flat quads
 * of an SMD packet array into an ordering table.  pa starts with a halfword
 * packet count; each packet is 0x40 bytes holding two 0x18-byte GPU
 * packets (selected by id) and, at 0x30, four byte offsets into the shared
 * SVECTOR array va.  Vertices 0-2 go through RTPT and vertex 3 through RTPS;
 * the winding test uses the first three points.  A primitive is dropped
 * when it is back-facing, when the GTE flags an overflow, or, with sclip
 * set, when none of its four screen points lies inside [0,hclip) x [0,vclip).
 *
 * Register use:
 *   a0  next packet (advanced early)   s0  hclip << 16   t0  packets left
 *   a1  va, the shared vertex array    s1  vclip         t3  GPU packet
 *   a2  ot                             s5  sclip         t4  id
 *   a3  otlen                          s4  nclipmode, then SXY0
 *   v0  FLAG bits that reject a primitive
 *   t7, t8, t9, v1  vertex pointers of the packet being set up
 *   s4, t5, t2, s6  SXY0..SXY3 once the points are read back
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotSMD_SV_F4
	.ent	RotSMD_SV_F4
RotSMD_SV_F4:
	.set	noat
	addiu	$sp, $sp, -0x20
	sw	$s0, 0x4($sp)
	sw	$s1, 0x8($sp)
	sw	$s2, 0xC($sp)
	sw	$s3, 0x10($sp)
	sw	$s4, 0x14($sp)
	sw	$s5, 0x18($sp)
	sw	$s6, 0x1C($sp)
	lhu	$t0, 0($a0)	# packet count
	addi	$a0, $a0, 0x4	# pa -> first packet
	lw	$t4, 0x30($sp)	# id
	lw	$t7, 0x30($a0)	# the first packet's four vertex offsets (at 0x30) ...
	lw	$t8, 0x34($a0)
	lw	$t9, 0x38($a0)
	lw	$v1, 0x3C($a0)
	add	$t7, $t7, $a1	# ... turned into pointers into va
	add	$t8, $t8, $a1
	add	$t9, $t9, $a1
	add	$v1, $v1, $a1
	lw	$s5, 0x34($sp)	# sclip
	lw	$s0, 0x38($sp)	# hclip
	lw	$s1, 0x3C($sp)	# vclip
	sll	$s0, $s0, 16	# hclip << 16, compared against sx << 16
	lw	$s4, 0x40($sp)	# nclipmode
	li	$v0, 0x40000	# reject on FLAG bit 18
	beqz	$s4, .Lnext
	nop
	li	$v0, 0x60000	# ... and on bit 17 when nclipmode is set
.Lnext:
	lwc2	$0, 0($t7)	# V0..V2 = shared vertices 0, 1 and 2
	lwc2	$1, 0x4($t7)
	lwc2	$2, 0($t8)
	lwc2	$3, 0x4($t8)
	lwc2	$4, 0($t9)
	lwc2	$5, 0x4($t9)
	nop
	RTPT	# project the first three
	move	$t3, $a0	# t3 = this packet (its first GPU packet)
	addi	$a0, $a0, 0x40	# a0 -> next packet, 0x40 bytes on
	lw	$t7, 0x30($a0)	# prefetch the next packet's first three vertex pointers
	lw	$t8, 0x34($a0)
	addu	$t7, $t7, $a1
	lw	$t9, 0x38($a0)
	addu	$t8, $t8, $a1
	addu	$t9, $t9, $a1
	cfc2	$t2, $31	# t2 = FLAG
	NCLIP	# winding test on the first three points
	lwc2	$0, 0($v1)	# V0 = shared vertex 3
	lwc2	$1, 0x4($v1)
	mfc2	$t1, $24	# t1 = MAC0, the nclip result
	and	$t2, $t2, $v0	# keep only the rejecting FLAG bits
	blez	$t1, .Lreject	# back-facing: drop
	nop
	bnez	$t2, .Lreject	# overflow: drop
	nop
	beqz	$t4, .Lpacket	# id 0 uses the first GPU packet
	nop
	addi	$t3, $t3, 0x18	# id 1 uses the second, 0x18 bytes on
.Lpacket:
	mfc2	$s4, $12	# SXY0 (s4 is free again: nclipmode is folded into v0)
	mfc2	$t5, $13	# SXY1
	mfc2	$t2, $14	# SXY2
	RTPS	# project vertex 3 while the first three are stored
	sw	$s4, 0x8($t3)	# store the first three screen points
	sw	$t5, 0xC($t3)
	sw	$t2, 0x10($t3)
	beqz	$s5, .Laccept	# no screen clipping: accept
	sll	$s2, $s4, 16	# vertex 0: 0 <= sx < hclip and 0 <= sy < vclip ?
	bltz	$s2, .Lclip_v1
	nop
	slt	$at, $s2, $s0
	beqz	$at, .Lclip_v1
	sra	$s3, $s4, 16
	bltz	$s3, .Lclip_v1
	nop
	slt	$at, $s3, $s1
	beqz	$at, .Lclip_v1
	nop
	j	.Laccept
	nop
.Lclip_v1:
	sll	$s2, $t5, 16	# vertex 1
	bltz	$s2, .Lclip_v2
	nop
	slt	$at, $s2, $s0
	beqz	$at, .Lclip_v2
	sra	$s3, $t5, 16
	bltz	$s3, .Lclip_v2
	nop
	slt	$at, $s3, $s1
	beqz	$at, .Lclip_v2
	nop
	j	.Laccept
	nop
.Lclip_v2:
	sll	$s2, $t2, 16	# vertex 2
	bltz	$s2, .Lclip_v3
	nop
	slt	$at, $s2, $s0
	beqz	$at, .Lclip_v3
	sra	$s3, $t2, 16
	bltz	$s3, .Lclip_v3
	nop
	slt	$at, $s3, $s1
	beqz	$at, .Lclip_v3
	nop
	j	.Laccept
	nop
.Lclip_v3:
	mfc2	$s6, $14	# vertex 3: SXY2 now holds its screen point
	nop
	sll	$s2, $s6, 16	# none of the first three inside: vertex 3 decides
	bltz	$s2, .Lreject
	nop
	slt	$at, $s2, $s0
	beqz	$at, .Lreject
	sra	$s3, $s6, 16
	bltz	$s3, .Lreject
	nop
	slt	$at, $s3, $s1
	beqz	$at, .Lreject
	nop
	j	.Lemit
	nop
.Laccept:
	mfc2	$s6, $14	# SXY3, vertex 3's screen point (SXY2 after RTPS)
	nop
.Lemit:
	nop
	AVSZ4	# OTZ = average of SZ0..SZ3
	sw	$s6, 0x14($t3)	# store the fourth screen point
	li	$t2, 0xE
	sub	$t2, $t2, $a3	# t2 = 14 - otlen, the OTZ shift for the OT index
	mfc2	$t1, $7	# t1 = OTZ
	nop
	srav	$t1, $t1, $t2	# OT index = OTZ >> (14 - otlen)
	sll	$t1, $t1, 2
	add	$t5, $a2, $t1	# t5 = &ot[index]
	lw	$t1, 0($t5)	# link the packet at the head of the OT bucket
	li	$at, 0xffffff
	and	$t3, $t3, $at	# packet address without tag bits
	li	$at, 0x5000000	# 5-word tag of a flat quad
	or	$t1, $t1, $at
	sw	$t1, 0($t3)
	sw	$t3, 0($t5)
.Lreject:
	lw	$v1, 0x3C($a0)	# next packet's vertex 3 pointer
	addi	$t0, $t0, -0x1
	bgtz	$t0, .Lnext	# loop while packets remain
	addu	$v1, $v1, $a1
	lw	$s0, 0x4($sp)
	lw	$s1, 0x8($sp)
	lw	$s2, 0xC($sp)
	lw	$s3, 0x10($sp)
	lw	$s4, 0x14($sp)
	lw	$s5, 0x18($sp)
	lw	$s6, 0x1C($sp)
	nop
	jr	$ra
	addiu	$sp, $sp, 0x20
	nop
	nop
	nop
	.set	at
	.end	RotSMD_SV_F4
	.set	reorder
