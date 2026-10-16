/* LIBGTE.LIB, member SMP_11.OBJ (hand-written assembly)
 *
 * AverageSZ3: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	AverageSZ3
	.ent	AverageSZ3
AverageSZ3:
	AVSZ3
	mfc2	$v0, $7
	jr	$ra
	.end	AverageSZ3
