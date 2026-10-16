/* LIBGTE.LIB, member SMP_12.OBJ (hand-written assembly)
 *
 * AverageSZ4: no prototype in the SDK headers.
 */
	.include	"inline_a.inc"
	.text
	.align	4

	.globl	AverageSZ4
	.ent	AverageSZ4
AverageSZ4:
	AVSZ4
	mfc2	$v0, $7
	jr	$ra
	.end	AverageSZ4
