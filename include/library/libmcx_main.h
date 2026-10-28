#ifndef LIBRARY_LIBMCX_MAIN_H
#define LIBRARY_LIBMCX_MAIN_H

#include "libmcx_init.h"

/* Command sequence is shared with the interrupt-driven MCXRESI state
 * machine; MCXMAIN clears it after completing volatile hardware writes. */
extern volatile int _mcxCmdSeq;
extern volatile int _mcxStat;
/* MCXMAIN McxSync reads the pending command number once (listing
 * .text+0x584 lui/lw) and clears it in every completion tail (.text+0x6DC). */
extern int _mcxFuncNo;
extern int _mcxPass;
int _mcxChkRsrv(int port);

/* MCXMAIN _mcxDsrEntry reads these words and installs the MCXRESI
 * interrupt record in SysDeqIntRP's second argument. */
extern int _mcxIntRestSize;
extern int _mcxCallFromC;
extern int _mcxPort;
extern McxInterruptRecord _mcxTblDsrEnt;

/* MCXMAIN data+0/+4 hold SIO0 0x1F801040 and I_STAT 0x1F801070.
 * The handler stores a halfword at SIO+0xA and accesses I_STAT/I_MASK
 * as words at offsets0/4. */
extern volatile unsigned short *D_000006F0;
extern volatile unsigned int *D_000006F4;

/* MCXRESI _mcxStepSio and MCXDSR _mcxFastDsrEnt read globals, not
 * incoming argument registers. _mcxDsrEntry tests StepSio's result. */
int _mcxStepSio(void);
void _mcxFastDsrEnt(void);

/* MCXMAIN timer state: SetRC2wait stores the captured counter, requested
 * delay and wrap accumulator at original BSS+4/+8/+12; ChkRC2wait
 * reads these words in its signed elapsed-time comparison. */
/* SioRW captures the receive-byte register in original BSS+0. */
extern int B_00000700;
int _mcxChkRC2wait(void);
extern int B_00000704;
extern int B_00000708;
extern int B_0000070C;

#endif
