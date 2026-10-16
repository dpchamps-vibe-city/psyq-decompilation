/* LIBGTE.LIB, member CMB_03.OBJ (hand-written assembly)
 *
 * RotNclip: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	RotNclip
	.ent	RotNclip
RotNclip:
	lwc2	$0, 0($a0)
	lwc2	$1, 0x4($a0)
	nop
	RTPS
	cfc2	$v0, $31
	swc2	$8, 0($a1)
	sw	$v0, 0($a2)
	NCLIP
	mfc2	$v0, $24
	jr	$ra
	.end	RotNclip
