/* LIBAPI.LIB, member A40.OBJ (hand-written assembly)
 *
 * void SwEnterCriticalSection(void);
 */
	.text
	.align	4

	.globl	SwEnterCriticalSection
	.ent	SwEnterCriticalSection
SwEnterCriticalSection:
	.set	noat
	mfc0	$a0, $12
	nop
	li	$at, -0x402
	and	$a0, $a0, $at
	mtc0	$a0, $12
	nop
	nop
	jr	$ra
	.set	at
	.end	SwEnterCriticalSection
