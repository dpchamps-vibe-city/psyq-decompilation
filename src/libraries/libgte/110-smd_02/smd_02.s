/* LIBGTE.LIB, member SMD_02.OBJ (hand-written assembly)
 *
 * void RotSMD_FT3(long *pa, u_long *ot, int otlen, int id, int sclip,
 *                 int hclip, int vclip, int nclipmode);
 *
 * Rotate, project and sort the POLY_FT3 flat textured triangles of an SMD packet array into an
 * ordering table.  pa starts with a halfword packet count; each packet is
 * 0x58 bytes holding two 0x20-byte GPU packets (selected by id) and the
 * three SVECTOR vertices at 0x40.  A primitive is dropped when it is
 * back-facing, when the GTE flags an overflow, or, with sclip set, when
 * none of its three screen points lies inside [0,hclip) x [0,vclip).
 *
 * Register use:
 *   a0  current packet              s0  hclip << 16     t0  packets left
 *   a1  ot                          s1  vclip           t3  GPU packet
 *   a2  14 - otlen (OTZ shift)      s4  nclipmode       t7  0x07000000 tag
 *   a3  GPU packet offset           s5  sclip           t8  0x00ffffff mask
 *   v0  FLAG bits that reject a primitive
 *   t4, t5, t2  SXY0, SXY1, SXY2 once the points are read back
 */
	.include	"inline_a.inc"
	.text
	.align	4
	.set	noreorder

	.globl	RotSMD_FT3
	.ent	RotSMD_FT3
RotSMD_FT3:
	.set	noat
	addiu	$sp, $sp, -0x20
	sw	$s0, 0x4($sp)
	sw	$s1, 0x8($sp)
	sw	$s2, 0xC($sp)
	sw	$s3, 0x10($sp)
	sw	$s4, 0x14($sp)
	sw	$s5, 0x18($sp)
	lhu	$t0, 0($a0)	# packet count
	addi	$a0, $a0, 0x4	# pa -> first packet
	beqz	$t0, .Ldone	# nothing to do
	lui	$t8, 0xff
	ori	$t8, $t8, 0xffff	# t8 = 0x00ffffff, OT link mask
	li	$t7, 0x7000000	# t7 = 7-word tag of a flat textured triangle
	lw	$s5, 0x30($sp)	# sclip
	lw	$s0, 0x34($sp)	# hclip
	lw	$s1, 0x38($sp)	# vclip
	sll	$s0, $s0, 16	# hclip << 16, compared against sx << 16
	lw	$s4, 0x3C($sp)	# nclipmode
	li	$v0, 0x40000	# reject on FLAG bit 18
	beqz	$s4, .Lflags
	nop
	li	$v0, 0x60000	# ... and on bit 17 when nclipmode is set
.Lflags:
	li	$at, 0xE
	sub	$a2, $at, $a2	# a2 = 14 - otlen, the OTZ shift for the OT index
	beqz	$a3, .Lpacket
	nop
	li	$a3, 0x20	# a3 = GPU packet offset: 0 for id 0, 0x20 otherwise
.Lpacket:
	lwc2	$0, 0x40($a0)	# V0..V2 = the packet's three vertices (at 0x40)
	lwc2	$1, 0x44($a0)
	lwc2	$2, 0x48($a0)
	lwc2	$3, 0x4C($a0)
	lwc2	$4, 0x50($a0)
	lwc2	$5, 0x54($a0)
	nop
.Lnext:
	RTPT	# project all three
	add	$t3, $a0, $a3	# t3 = GPU packet of this SMD packet
	nop
	lwc2	$0, 0x98($a0)	# preload the next packet's vertices while the GTE works
	lwc2	$1, 0x9C($a0)
	lwc2	$2, 0xA0($a0)
	lwc2	$3, 0xA4($a0)
	cfc2	$t2, $31	# t2 = FLAG
	NCLIP	# winding test
	lwc2	$4, 0xA8($a0)
	lwc2	$5, 0xAC($a0)
	mfc2	$t1, $24	# t1 = MAC0, the nclip result
	and	$t2, $t2, $v0	# keep only the rejecting FLAG bits
	blez	$t1, .Lreject	# back-facing: drop
	nop
	bnez	$t2, .Lreject	# overflow: drop
	mfc2	$t4, $12	# SXY0, SXY1, SXY2 (SXY0 loads in the delay slot)
	mfc2	$t5, $13
	mfc2	$t2, $14
	beqz	$s5, .Laccept	# no screen clipping: accept
	sll	$s2, $t4, 16	# vertex 0: 0 <= sx < hclip and 0 <= sy < vclip ?
	bltz	$s2, .Lclip_v1
	nop
	slt	$at, $s2, $s0
	beqz	$at, .Lclip_v1
	sra	$s3, $t4, 16
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
	sll	$s2, $t2, 16	# vertex 2; none inside drops the primitive
	bltz	$s2, .Lreject
	nop
	slt	$at, $s2, $s0
	beqz	$at, .Lreject
	sra	$s3, $t2, 16
	bltz	$s3, .Lreject
	nop
	slt	$at, $s3, $s1
	beqz	$at, .Lreject
	nop
	j	.Laccept	# jump to the next instruction, as the original has it
	nop
.Laccept:
	nop
	AVSZ3	# OTZ = average of SZ1..SZ3
	sw	$t4, 0x8($t3)	# store the three screen points
	sw	$t5, 0x10($t3)
	sw	$t2, 0x18($t3)
	mfc2	$t1, $7	# t1 = OTZ
	and	$t3, $t3, $t8	# packet address without tag bits
	srav	$t1, $t1, $a2	# OT index = OTZ >> (14 - otlen)
	sll	$t1, $t1, 2
	add	$t2, $a1, $t1	# t2 = &ot[index]
	lw	$t4, 0($t2)	# link the packet at the head of the OT bucket
	sw	$t3, 0($t2)
	or	$t4, $t4, $t7
	sw	$t4, 0($t3)
.Lreject:
	addi	$t0, $t0, -0x1
	bnez	$t0, .Lnext
	addiu	$a0, $a0, 0x58	# next packet, 0x58 bytes on
.Ldone:
	lw	$s0, 0x4($sp)
	lw	$s1, 0x8($sp)
	lw	$s2, 0xC($sp)
	lw	$s3, 0x10($sp)
	lw	$s4, 0x14($sp)
	lw	$s5, 0x18($sp)
	nop
	jr	$ra
	addiu	$sp, $sp, 0x20
	nop
	.set	at
	.end	RotSMD_FT3
	.set	reorder
