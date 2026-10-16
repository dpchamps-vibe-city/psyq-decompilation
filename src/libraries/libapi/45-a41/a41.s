/* LIBAPI.LIB, member A41.OBJ (hand-written assembly)
 *
 * void SwExitCriticalSection(void);
 */
	.text
	.align	4

	.globl	SwExitCriticalSection
	.ent	SwExitCriticalSection
SwExitCriticalSection:
	mfc0	$a0, $12
	ori	$a0, $a0, 0x401
	mtc0	$a0, $12
	nop
	nop
	jr	$ra
	.end	SwExitCriticalSection
