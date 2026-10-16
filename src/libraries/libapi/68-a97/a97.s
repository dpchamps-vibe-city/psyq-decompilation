/* LIBAPI.LIB, member A97.OBJ (hand-written assembly)
 *
 * GetSr: no prototype in the SDK headers.
 */
	.text
	.align	4

	.globl	GetSr
	.ent	GetSr
GetSr:
	mfc0	$v0, $12
	jr	$ra
	.end	GetSr
