/* LIBGTE.LIB, member SMP_06.OBJ (hand-written assembly)
 *
 * NormalClipS: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	NormalClipS
	.ent	NormalClipS
NormalClipS:
	NCLIP
	mfc2	$v0, $24
	jr	$ra
	.end	NormalClipS
