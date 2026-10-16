/* LIBAPI.LIB, member A96.OBJ (hand-written assembly)
 *
 * GetCr: no prototype in the SDK headers.
 */
	.text
	.align	4

	.globl	GetCr
	.ent	GetCr
GetCr:
	mfc0	$v0, $13
	jr	$ra
	.end	GetCr
